#pragma once

#include "../curl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsNLibCurl
{
    CURLcode (*curl_global_init_mem)(uint32_t flags, curl_malloc_callback malloc_callback, curl_free_callback free_callback,
                                     curl_realloc_callback realloc_callback, curl_strdup_callback strdup_callback,
                                     curl_calloc_callback calloc_callback);
    CURLcode (*curl_global_init)(uint32_t flags);

    curl_slist *(*curl_slist_append)(curl_slist *list, const char *data);
    void (*curl_slist_free_all)(curl_slist *list);

    const char *(*curl_easy_strerror)(CURLcode code);

    CURLSH *(*curl_share_init)(void);
    CURLSHcode (*curl_share_setopt)(CURLSH *share, CURLSHoption option, ...);
    CURLSHcode (*curl_share_cleanup)(CURLSH *share);

    CURL *(*mw_curl_easy_init)(void);
    CURL *(*curl_easy_init)(void);
    void (*curl_easy_reset)(CURL *curl);
    CURLcode (*curl_easy_setopt)(CURL *curl, CURLoption option, ...);
    CURLcode (*curl_easy_getinfo)(CURL *curl, CURLINFO info, ...);
    CURLcode (*curl_easy_perform)(CURL *curl);
    void (*curl_easy_cleanup)(CURL *curl);
    CURLcode (*curl_easy_pause)(CURL *curl, int bitmask);

    CURLM *(*curl_multi_init)(void);
    CURLMcode (*curl_multi_add_handle)(CURLM *multi_handle, CURL *curl_handle);
    CURLMcode (*curl_multi_perform)(CURLM *multi_handle, int *running_handles);
    CURLMsg *(*curl_multi_info_read)(CURLM *multi_handle, int *msgs_in_queue);
    CURLMcode (*curl_multi_remove_handle)(CURLM *multi_handle, CURL *curl_handle);
    CURLMcode (*curl_multi_setopt)(CURLM *multi_handle, CURLMoption option, ...);
    CURLMcode (*curl_multi_fdset)(CURLM *multi_handle, fd_set *read_fd_set, fd_set *write_fd_set, fd_set *exc_fd_set, int *max_fd);
    CURLMcode (*curl_multi_cleanup)(CURLM *multi_handle);
    CURLMcode (*curl_multi_timeout)(CURLM *multi_handle, long *timeout_ms);
} ImportsNLibCurl;

#ifdef __cplusplus
}
#endif
