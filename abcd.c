#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define API_KEY "Asy8n0risQlPzXgXmk-fiCHB6GTBFa2DqDVgAuemQp4_l3u8nG0_LLNQbdApIxhM"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    FILE *stream = (FILE *)userdata;
    if (!stream) return 0;
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void get_distance(const char *origin, const char *destination) {
    CURL *curl = curl_easy_init();
    if (curl) {
        // URL encode the origin and destination
        char *encoded_origin = curl_easy_escape(curl, origin, 0);
        char *encoded_destination = curl_easy_escape(curl, destination, 0);

        if (encoded_origin && encoded_destination) {
            char url[1024];
            snprintf(url, sizeof(url), "https://dev.virtualearth.net/REST/v1/Routes/DistanceMatrix?origins=%s&destinations=%s&key=%s",
                     encoded_origin, encoded_destination, API_KEY);
            
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
            curl_free(encoded_origin);
            curl_free(encoded_destination);
        } else {
            fprintf(stderr, "Failed to encode parameters\n");
        }
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Failed to initialize libcurl\n");
    }
}

int main() {
    const char *origin = "Seattle, WA";
    const char *destination = "San Francisco, CA";
    get_distance(origin, destination);
    return 0;
}
