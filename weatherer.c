#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#define APIKEY "183b1bd833f24eb4983142217243105"

char * get_condition(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s for reading\n", filename);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(length + 1);
    if (!data) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
    }

    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);

    cJSON *json = cJSON_Parse(data);
    if (!json) {
        fprintf(stderr, "JSON parse error: %s\n", cJSON_GetErrorPtr());
        free(data);
    }

    cJSON *current = cJSON_GetObjectItem(json, "current");
    if (!current) {
        fprintf(stderr, "JSON object 'current' not found\n");
        cJSON_Delete(json);
        free(data);
    }

    cJSON *condition = cJSON_GetObjectItem(current, "condition");
    if (!condition) {
        fprintf(stderr, "JSON object 'condition' not found\n");
        cJSON_Delete(json);
        free(data);
    }

    cJSON *text = cJSON_GetObjectItem(condition, "text");
        if (!text) {
        fprintf(stderr, "JSON object 'text' not found\n");
        cJSON_Delete(json);
        free(data);
    }

    char *result = strdup(text->valuestring);
    cJSON_Delete(json);

    return result;
}

double get_temp_from_json(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s for reading\n", filename);
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(length + 1);
    if (!data) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return -1;
    }

    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);

    cJSON *json = cJSON_Parse(data);
    if (!json) {
        fprintf(stderr, "JSON parse error: %s\n", cJSON_GetErrorPtr());
        free(data);
        return -1;
    }

    cJSON *current = cJSON_GetObjectItem(json, "current");
    if (!current) {
        fprintf(stderr, "JSON object 'current' not found\n");
        cJSON_Delete(json);
        free(data);
        return -1;
    }

    cJSON *temp_c = cJSON_GetObjectItem(current, "temp_c");
    if (!temp_c) {
        fprintf(stderr, "JSON object 'temp_c' not found\n");
        cJSON_Delete(json);
        free(data);
        return -1;
    }

    cJSON_Delete(json);
    free(data);

    return temp_c->valuedouble;
}

double get_temp(char *city) {

    char url[200];
    snprintf(url, sizeof(url), "http://api.weatherapi.com/v1/current.json?key=%s&q=%s&aqi=no", APIKEY, city);


    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing cURL.\n");
        return -1;
    }

    FILE *response_file = fopen("response.json", "w");
    if (!response_file) {
        fprintf(stderr, "Error: Unable to open response file.\n");
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_file);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return -1;
    }

    fclose(response_file);
    curl_easy_cleanup(curl);

    int temp = get_temp_from_json("response.json");

    return temp;
}