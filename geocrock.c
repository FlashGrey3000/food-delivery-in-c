#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Function to encode the URL except slashes
char* encode_except_slash(const char* input) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        return NULL; // curl initialization failed
    }

    char *encoded_url = NULL;
    size_t input_len = strlen(input);
    char *temp = malloc(input_len * 3 + 1); // Allocate enough space for worst case

    if (temp) {
        char *p = temp;
        for (const char *src = input; *src; ++src) {
            if (*src == '/') {
                *p++ = *src; // Keep slashes as is
            } else {
                char *escaped_char = curl_easy_escape(curl, src, 1);
                if (escaped_char) {
                    strcpy(p, escaped_char);
                    p += strlen(escaped_char);
                    curl_free(escaped_char);
                }
            }
        }
        *p = '\0';
        encoded_url = strdup(temp);
        free(temp);
    }

    curl_easy_cleanup(curl);
    return encoded_url;
}

int main() {
    const char *base_url = "http://dev.virtualearth.net/REST/v1/Locations/";
    char *details = "No 50 New No 150, Kodambakkam High Road, Nungambakkam, Chennai, Tamil Nadu 600034, The Thief";
    const char *api_key = "?key=Asy8n0risQlPzXgXmk-fiCHB6GTBFa2DqDVgAuemQp4_l3u8nG0_LLNQbdApIxhM&maxResults=1";

    char rest_name[50];
    char rest_loc[200];

    char *first_colon_pos = strchr(details, ':');
    int len_before_colon = first_colon_pos - details;
    strncpy(rest_name, details, len_before_colon);
    rest_name[len_before_colon] = '\0'; 

    char *last_colon_pos = strrchr(details, ':');
    strcpy(rest_loc, last_colon_pos + 1);

    char *trimmed_rest_loc = rest_loc;
    while (*trimmed_rest_loc == ' ') {
        trimmed_rest_loc++;
    }
    
    // Encode the address while keeping slashes intact
    char *encoded_address = encode_except_slash(address);

    printf("%s", encoded_address);
    if (!encoded_address) {
        fprintf(stderr, "Error encoding URL.\n");
        return 1;
    }

    // Construct the full URL
    char full_url[1024];
    snprintf(full_url, sizeof(full_url), "%s%s%s", base_url, encoded_address, api_key);

    // Print the full URL
    printf("Full URL: %s\n", full_url);

    // Make the request (optional, using libcurl)
    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, full_url);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }

    // Clean up
    free(encoded_address);
    return 0;
}
