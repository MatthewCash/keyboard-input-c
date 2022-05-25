#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

int send_message(char *json_buf)
{
    CURL *easy_handle = curl_easy_init();

    curl_easy_setopt(easy_handle, CURLOPT_URL, getenv("DEVICES_HTTP_URL"));
    
    char auth_token_header_buf[120] = "authorization: ";
    strncat(auth_token_header_buf, getenv("AUTH_TOKEN"), 120 - sizeof("authorization: "));

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: applications/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, auth_token_header_buf);
    headers = curl_slist_append(headers, "charset: utf-8");
    curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, json_buf);

    curl_easy_perform(easy_handle);

    return 0;
}
