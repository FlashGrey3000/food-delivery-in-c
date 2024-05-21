#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

#define API_KEY "Asy8n0risQlPzXgXmk-fiCHB6GTBFa2DqDVgAuemQp4_l3u8nG0_LLNQbdApIxhM"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    FILE *stream = (FILE *)userdata;
    if (!stream) return 0;
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void parse_json_response(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s for reading\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(length + 1);
    if (!data) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return;
    }

    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);

    cJSON *json = cJSON_Parse(data);
    if (!json) {
        fprintf(stderr, "JSON parse error: %s\n", cJSON_GetErrorPtr());
        free(data);
        return;
    }

    // Example: Extracting the coordinates (latitude and longitude)
    cJSON *resourceSets = cJSON_GetObjectItem(json, "resourceSets");
    if (!resourceSets) {
        fprintf(stderr, "JSON object 'resourceSets' not found\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    cJSON *resourceSet = cJSON_GetArrayItem(resourceSets, 0);
    if (!resourceSet) {
        fprintf(stderr, "JSON array item 'resourceSet' not found\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    cJSON *resources = cJSON_GetObjectItem(resourceSet, "resources");
    if (!resources) {
        fprintf(stderr, "JSON object 'resources' not found\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    cJSON *resource = cJSON_GetArrayItem(resources, 0);
    if (!resource) {
        fprintf(stderr, "JSON array item 'resource' not found\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    cJSON *point = cJSON_GetObjectItem(resource, "point");
    if (!point) {
        fprintf(stderr, "JSON object 'point' not found\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    cJSON *coordinates = cJSON_GetObjectItem(point, "coordinates");
    if (!coordinates || cJSON_GetArraySize(coordinates) != 2) {
        fprintf(stderr, "Invalid or missing coordinates\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    double latitude = cJSON_GetArrayItem(coordinates, 0)->valuedouble;
    double longitude = cJSON_GetArrayItem(coordinates, 1)->valuedouble;
    printf("Latitude: %f, Longitude: %f\n", latitude, longitude);

    cJSON_Delete(json);
    free(data);
}

char* sanitize_url(const char* input) {
    size_t input_len = strlen(input);
    char* result = malloc(input_len + 1);
    if (!result) {
        return NULL; // Memory allocation failed
    }

    const char *src = input;
    char *dst = result;

    while (*src) {
        if (strncmp(src, "%2F", 3) == 0) {
            *dst++ = '/';
            src += 3;
        } else if (strncmp(src, "%0D", 3) == 0 || strncmp(src, "%0A", 3) == 0) {
            // Skip %0D (carriage return) and %0A (newline)
            src += 3;
        } else if (strncmp(src, "%20/", 4) == 0) {
            // Skip %20 before /
            *dst++ = '/';
            src += 4;
        } else if (strncmp(src, "%20", 3) == 0) {
            // Skip isolated %20 (space)
            src += 3;
        } else if (strncmp(src, ", ", 1) == 0) {
            *dst++ = '/';
            src += 1;
        } else if (strncmp(src, " ", 1) == 0) {
            strncpy(dst, "%20", 3);
            dst+=3;
            src+=1;
        } else {
            *dst++ = *src++;
        }
    }

    // Remove trailing %20
    if (dst - result >= 3 && strncmp(dst - 3, "%20", 3) == 0) {
        dst -= 3;
    }

    *dst = '\0'; // Null-terminate the result
    return result;
}

void create_url(const char* location, const char* name, char* encoded_url) {
    char temp_url[1024];
    snprintf(temp_url, sizeof(temp_url), "http://dev.virtualearth.net/REST/v1/Locations/%s/%s?key=%s&maxResults=1", location, name, API_KEY);

    char* sanitized_url = sanitize_url(temp_url);
    if (!sanitized_url) {
        fprintf(stderr, "Failed to sanitize URL\n");
        return;
    }

    strncpy(encoded_url, sanitized_url, 1024);
    free(sanitized_url);
}

int main() {
    char details[300];
    FILE *fp;
    char c;
    fp = fopen("city_wise_rests/zomato_chennai.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: File not found or unable to open.\n");
        return -1;
    }

    CURL *curl;
    FILE *response_file;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error: Unable to initialize cURL.\n");
        fclose(fp);
        return -1;
    }

    while (fgets(details, sizeof(details), fp) != NULL) {
        char rest_name[100];
        char rest_loc[200];

        // Extract restaurant name and location from file
        char *first_colon_pos = strchr(details, ':') - 1;
        int len_before_colon = first_colon_pos - details;
        strncpy(rest_name, details, len_before_colon);
        rest_name[len_before_colon] = '\0';  // Null-terminate the string

        char *last_colon_pos = strrchr(details, ':');
        strcpy(rest_loc, last_colon_pos + 1);

        // Trim leading spaces from restaurant location
        char *trimmed_rest_loc = rest_loc;
        while (*trimmed_rest_loc == ' ') {
            trimmed_rest_loc++;
        }

        printf("Restaurant Name: %s\n", rest_name);
        printf("Restaurant Location: %s\n", trimmed_rest_loc);

        // Create URL for the restaurant location
        char encoded_url[1024];
        create_url(trimmed_rest_loc, rest_name, encoded_url);

        printf("Encoded URL: %s\n", encoded_url);

        // Open response file
        response_file = fopen("response.json", "w");
        if (!response_file) {
            fprintf(stderr, "Error: Unable to open response file.\n");
            fclose(fp);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return -1;
        }

        // Set cURL options and perform request
        curl_easy_setopt(curl, CURLOPT_URL, encoded_url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_file);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            fclose(response_file);
            fclose(fp);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return -1;
        }

        // Close response file and parse JSON response
        fclose(response_file);
        parse_json_response("response.json");
    }

    // Clean up resources and close file
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    fclose(fp);

    return 0;
}
