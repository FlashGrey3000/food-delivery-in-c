#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

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

char* replace_percent2F_with_slash(const char* input) {
    size_t input_len = strlen(input);
    size_t search_len = 3; // Length of "%2F"
    char* result = malloc(input_len + 1);
    if (!result) {
        return NULL;
    }

    const char *src = input;
    char *dst = result;

    while (*src) {
        if (strncmp(src, "%2F", search_len) == 0) {
            *dst++ = '/';
            src += search_len;
        } else {
            *dst++ = *src++;
        }
    }

    *dst = '\0';
    return result;
}

void get_rest_coords(char *rest_name, char *rest_loc) {
    CURL *curl = curl_easy_init();
    if (curl) {

        //url encoding blah blah
        replace_commas_with_slashes(rest_loc);
        char *name = curl_easy_escape(curl, rest_name, 0);
        char *loc = curl_easy_escape(curl, rest_loc, 0);
        char *floc = replace_percent2F_with_slash(loc);
        floc[strlen(floc)-3]='\0';

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
    char details[] = "The Beach Terrace : New : Pizza, Italian, Beverages, Cafe : ₹2,000 for two : VGP Golden Beach Resort, SH 49, Injambakkam, Chennai (Madras)";
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

    // Debugging info
    printf("Restaurant Name: %s\n", rest_name);
    printf("Restaurant Location: %s\n", trimmed_rest_loc);

    get_rest_coords(rest_name, trimmed_rest_loc);
    return 0;
}
