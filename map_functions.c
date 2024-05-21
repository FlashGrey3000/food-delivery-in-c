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

void parse_json_response_cordinates(const char *filename, double *latitude, double *longitude) {
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

    *latitude = cJSON_GetArrayItem(coordinates, 0)->valuedouble;
    *longitude = cJSON_GetArrayItem(coordinates, 1)->valuedouble;

    cJSON_Delete(json);
    free(data);
}

void parse_json_response_distance(const char *filename, float *trav_D, float *trav_T) {
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

    cJSON *resourceSets = cJSON_GetObjectItem(json, "resourceSets");
    if (!resourceSets) {
        fprintf(stderr, "JSON object 'resourceSets' not found\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    cJSON *resourceSet = cJSON_GetArrayItem(resourceSets, 0);
    if (!cJSON_IsObject(resourceSet)) {
        fprintf(stderr, "First resourceSet is not an object\n");
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

    cJSON *results = cJSON_GetObjectItem(resource, "results");
    if (!cJSON_IsArray(results)) {
        fprintf(stderr, "results is not an array\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    cJSON *result = cJSON_GetArrayItem(results, 0);
    if (!cJSON_IsObject(result)) {
        fprintf(stderr, "First object is not an array\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    cJSON *travelDistance = cJSON_GetObjectItem(result, "travelDistance");
    cJSON *travelDuration = cJSON_GetObjectItem(result, "travelDuration");

    if (!cJSON_IsNumber(travelDistance) || !cJSON_IsNumber(travelDuration)) {
        printf("travelDistance or travelDuration is not a number\n");
        cJSON_Delete(json);
        free(data);
        return;
    }

    *trav_D = travelDistance->valuedouble;
    *trav_T = travelDuration->valuedouble;

    cJSON_Delete(json);
    free(data);
}

void update_user_coordinates(const char *addr1, const char *addr2, const char *city, const char *state, const int pincode, double *latitude, double *longitude) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing cURL.\n");
        return;
    }

    // URL-encode the address components
    char *encoded_addr1 = curl_easy_escape(curl, addr1, 0);
    char *encoded_addr2 = curl_easy_escape(curl, addr2, 0);
    char *encoded_city = curl_easy_escape(curl, city, 0);
    char *encoded_state = curl_easy_escape(curl, state, 0);

    if (!encoded_addr1 || !encoded_addr2 || !encoded_city || !encoded_state) {
        fprintf(stderr, "Error encoding address components.\n");
        curl_easy_cleanup(curl);
        if (encoded_addr1) curl_free(encoded_addr1);
        if (encoded_addr2) curl_free(encoded_addr2);
        if (encoded_city) curl_free(encoded_city);
        if (encoded_state) curl_free(encoded_state);
        return;
    }

    char url[1024];
    snprintf(url, sizeof(url), "https://dev.virtualearth.net/REST/v1/Locations/IN/%s/%s/%d/%s/%s?key=%s&maxResults=1", encoded_state, encoded_city, pincode, encoded_addr2, encoded_addr1, API_KEY);
    printf("Request URL: %s\n", url);

    FILE *response_file = fopen("response.json", "w");
    if (!response_file) {
        fprintf(stderr, "Error: Unable to open response file.\n");
        curl_free(encoded_addr1);
        curl_free(encoded_addr2);
        curl_free(encoded_city);
        curl_free(encoded_state);
        curl_easy_cleanup(curl);
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_file);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        fclose(response_file);
        curl_free(encoded_addr1);
        curl_free(encoded_addr2);
        curl_free(encoded_city);
        curl_free(encoded_state);
        curl_easy_cleanup(curl);
        return;
    }

    fclose(response_file);

    // Clean up URL-encoded strings
    curl_free(encoded_addr1);
    curl_free(encoded_addr2);
    curl_free(encoded_city);
    curl_free(encoded_state);

    curl_easy_cleanup(curl);

    parse_json_response_cordinates("response.json", latitude, longitude);
}

void get_distance(double org_lat, double org_long, double des_lat, double des_long, float *trav_D, float *trav_T) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing cURL.\n");
        return;
    }

    char url[1024];
    snprintf(url, sizeof(url), "https://dev.virtualearth.net/REST/v1/Routes/DistanceMatrix?origins=%f,%f&destinations=%f,%f&travelMode=driving&key=%s", org_lat, org_long, des_lat, des_long, API_KEY);
    printf("Request URL: %s\n", url);

    FILE *response_file = fopen("response.json", "w");
    if (!response_file) {
        fprintf(stderr, "Error: Unable to open response file.\n");
        curl_easy_cleanup(curl);
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_file);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        fclose(response_file);
        curl_easy_cleanup(curl);
        return;
    }

    fclose(response_file);
    curl_easy_cleanup(curl);

    parse_json_response_distance("response.json", trav_D, trav_T);
}