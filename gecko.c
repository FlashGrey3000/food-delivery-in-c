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

void replace_commas_with_slashes(char *str) {
    while (*str != '\0') {
        if (*str == '/') {
            *str = ' ';
        }
        if (*str == ',') {
            *str = '/';
        }
        str++;
    }
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
    if (cJSON_IsArray(resourceSets)) {
        cJSON *resourceSet = cJSON_GetArrayItem(resourceSets, 0);
        if (resourceSet) {
            cJSON *resources = cJSON_GetObjectItem(resourceSet, "resources");
            if (cJSON_IsArray(resources)) {
                cJSON *resource = cJSON_GetArrayItem(resources, 0);
                if (resource) {
                    cJSON *point = cJSON_GetObjectItem(resource, "point");
                    if (point) {
                        cJSON *coordinates = cJSON_GetObjectItem(point, "coordinates");
                        if (cJSON_IsArray(coordinates) && cJSON_GetArraySize(coordinates) == 2) {
                            double latitude = cJSON_GetArrayItem(coordinates, 0)->valuedouble;
                            double longitude = cJSON_GetArrayItem(coordinates, 1)->valuedouble;
                            printf("Latitude: %f, Longitude: %f\n", latitude, longitude);
                        }
                    }
                }
            }
        }
    }

    cJSON_Delete(json);
    free(data);
}

void get_rest_coords(char *rest_name, char *rest_loc) {
    CURL *curl = curl_easy_init();
    if (curl) {
        replace_commas_with_slashes(rest_loc);
        char *name = curl_easy_escape(curl, rest_name, 0);
        char *loc = curl_easy_escape(curl, rest_loc, 0);
        char *floc = sanitize_url(loc);
        floc = sanitize_url(floc);

        if (name && loc && floc) {
            char url[1024];
            snprintf(url, sizeof(url), "http://dev.virtualearth.net/REST/v1/Locations/%s/%s?key=%s&maxResults=1", floc, name, API_KEY);

            // Debugging info
            printf("Encoded URL: %s\n", url);

            FILE *response_file = fopen("response.json", "w");
            if (response_file) {
                curl_easy_setopt(curl, CURLOPT_URL, url);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_file);
                CURLcode res = curl_easy_perform(curl);
                if (res != CURLE_OK) {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                }
                fclose(response_file);
            } else {
                fprintf(stderr, "Failed to open response file for writing\n");
            }

            curl_free(name);
            curl_free(loc);
            free(floc);
        } else {
            fprintf(stderr, "Failed to encode parameters\n");
        }
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Failed to initialize libcurl\n");
    }
}

int main() {
    char details[300];
    FILE *fp;
    char c;
    fp = fopen("city_wise_rests/zomato_chennai.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "file not found");
        return -1;
    }

    while (fgets(details, sizeof(details), fp) != NULL)
    {
        printf("%s", details);
    
        char rest_name[100];
        char rest_loc[200];

        char *first_colon_pos = strchr(details, ':')-1;
        int len_before_colon = first_colon_pos - details;
        strncpy(rest_name, details, len_before_colon);
        rest_name[len_before_colon] = '\0';  // Null-terminate the string

        char *last_colon_pos = strrchr(details, ':');
        strcpy(rest_loc, last_colon_pos + 1);

        char *trimmed_rest_loc = rest_loc;
        while (*trimmed_rest_loc == ' ') {
            trimmed_rest_loc++;
        }

        printf("Restaurant Name: %s\n", rest_name);
        printf("Restaurant Location: %s\n", trimmed_rest_loc);

        get_rest_coords(rest_name, trimmed_rest_loc);

        parse_json_response("response.json");
    
    }

    fclose(fp);
    return 0;
}
