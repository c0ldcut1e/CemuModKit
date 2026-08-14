#pragma once

#include "../cut.h"
#include "../nsysnet/_socket.h"

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CURL CURL;
typedef struct CURLM CURLM;
typedef struct CURLSH CURLSH;

typedef int64_t curl_off_t;
typedef int curl_socket_t;

typedef void *(*curl_malloc_callback)(size_t size);
typedef void (*curl_free_callback)(void *ptr);
typedef void *(*curl_realloc_callback)(void *ptr, size_t size);
typedef char *(*curl_strdup_callback)(const char *str);
typedef void *(*curl_calloc_callback)(size_t nmemb, size_t size);

typedef size_t (*curl_write_callback)(char *ptr, size_t size, size_t nmemb, void *userdata);
typedef size_t (*curl_read_callback)(char *buffer, size_t size, size_t nitems, void *userdata);
typedef int (*curl_progress_callback)(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
typedef int (*curl_sockopt_callback)(void *clientp, curl_socket_t curlfd, int purpose);

typedef struct curl_slist
{
    char *data;
    struct curl_slist *next;
} curl_slist;
CUT_CHECK_OFFSET(curl_slist, 0x00, data);
CUT_CHECK_OFFSET(curl_slist, 0x04, next);
CUT_CHECK_SIZE(curl_slist, 0x08);

typedef enum CURLcode
{
    CURLE_OK                       = 0,
    CURLE_UNSUPPORTED_PROTOCOL     = 1,
    CURLE_FAILED_INIT              = 2,
    CURLE_URL_MALFORMAT            = 3,
    CURLE_COULDNT_RESOLVE_PROXY    = 5,
    CURLE_COULDNT_RESOLVE_HOST     = 6,
    CURLE_COULDNT_CONNECT          = 7,
    CURLE_WEIRD_SERVER_REPLY       = 8,
    CURLE_REMOTE_ACCESS_DENIED     = 9,
    CURLE_HTTP_RETURNED_ERROR      = 22,
    CURLE_WRITE_ERROR              = 23,
    CURLE_UPLOAD_FAILED            = 25,
    CURLE_READ_ERROR               = 26,
    CURLE_OUT_OF_MEMORY            = 27,
    CURLE_OPERATION_TIMEDOUT       = 28,
    CURLE_SSL_CONNECT_ERROR        = 35,
    CURLE_BAD_DOWNLOAD_RESUME      = 36,
    CURLE_FUNCTION_NOT_FOUND       = 41,
    CURLE_ABORTED_BY_CALLBACK      = 42,
    CURLE_BAD_FUNCTION_ARGUMENT    = 43,
    CURLE_INTERFACE_FAILED         = 45,
    CURLE_TOO_MANY_REDIRECTS       = 47,
    CURLE_UNKNOWN_OPTION           = 48,
    CURLE_SSL_ENGINE_NOTFOUND      = 53,
    CURLE_SSL_ENGINE_SETFAILED     = 54,
    CURLE_SEND_ERROR               = 55,
    CURLE_RECV_ERROR               = 56,
    CURLE_SSL_CERTPROBLEM          = 58,
    CURLE_SSL_CIPHER               = 59,
    CURLE_PEER_FAILED_VERIFICATION = 60,
    CURLE_SEND_FAIL_REWIND         = 65,
    CURLE_SSL_CACERT               = 60,
    CURLE_SSL_ENGINE_INITFAILED    = 66,
    CURLE_LOGIN_DENIED             = 67,
    CURLE_SSL_CACERT_BADFILE       = 77,
    CURLE_REMOTE_FILE_NOT_FOUND    = 78,
    CURLE_SSL_SHUTDOWN_FAILED      = 80,
    CURLE_AGAIN                    = 81,
} CURLcode;

typedef enum CURLMcode
{
    CURLM_OK              = 0,
    CURLM_BAD_HANDLE      = 1,
    CURLM_BAD_EASY_HANDLE = 2,
    CURLM_OUT_OF_MEMORY   = 3,
    CURLM_INTERNAL_ERROR  = 4,
    CURLM_BAD_SOCKET      = 5,
    CURLM_UNKNOWN_OPTION  = 6,
    CURLM_ADDED_ALREADY   = 7,
} CURLMcode;

typedef enum CURLSHcode
{
    CURLSHE_OK           = 0,
    CURLSHE_BAD_OPTION   = 1,
    CURLSHE_IN_USE       = 2,
    CURLSHE_INVALID      = 3,
    CURLSHE_NOMEM        = 4,
    CURLSHE_NOT_BUILT_IN = 5,
} CURLSHcode;

typedef enum CURLMSG
{
    CURLMSG_NONE = 0,
    CURLMSG_DONE = 1,
    CURLMSG_LAST = 2,
} CURLMSG;

typedef struct CURLMsg
{
    CURLMSG msg;
    CURL *easy_handle;
    union
    {
        void *whatever;
        CURLcode result;
    } data;
} CURLMsg;
CUT_CHECK_OFFSET(CURLMsg, 0x00, msg);
CUT_CHECK_OFFSET(CURLMsg, 0x04, easy_handle);
CUT_CHECK_OFFSET(CURLMsg, 0x08, data);
CUT_CHECK_SIZE(CURLMsg, 0x0C);

#define CURL_GLOBAL_SSL      (1 << 0)
#define CURL_GLOBAL_WIN32    (1 << 1)
#define CURL_GLOBAL_ALL      (CURL_GLOBAL_SSL | CURL_GLOBAL_WIN32)
#define CURL_GLOBAL_NOTHING  0
#define CURL_GLOBAL_DEFAULT  CURL_GLOBAL_ALL

#define CURLPAUSE_RECV       (1 << 0)
#define CURLPAUSE_RECV_CONT  (0)
#define CURLPAUSE_SEND       (1 << 2)
#define CURLPAUSE_SEND_CONT  (0)
#define CURLPAUSE_ALL        (CURLPAUSE_RECV | CURLPAUSE_SEND)
#define CURLPAUSE_CONT       (CURLPAUSE_RECV_CONT | CURLPAUSE_SEND_CONT)

#define NSSL_VERIFY_NONE     0x0
#define NSSL_VERIFY_PEER     (1 << 0)
#define NSSL_VERIFY_HOSTNAME (1 << 1)
#define NSSL_VERIFY_DATE     (1 << 2)

typedef enum CURLoption
{
    CURLOPT_WRITEDATA            = 10001,
    CURLOPT_FILE                 = CURLOPT_WRITEDATA,
    CURLOPT_URL                  = 10002,
    CURLOPT_PROXY                = 10004,
    CURLOPT_READDATA             = 10009,
    CURLOPT_INFILE               = CURLOPT_READDATA,
    CURLOPT_WRITEFUNCTION        = 20011,
    CURLOPT_READFUNCTION         = 20012,
    CURLOPT_TIMEOUT              = 13,
    CURLOPT_INFILESIZE           = 14,
    CURLOPT_POSTFIELDS           = 10015,
    CURLOPT_LOW_SPEED_LIMIT      = 19,
    CURLOPT_LOW_SPEED_TIME       = 20,
    CURLOPT_HTTPHEADER           = 10023,
    CURLOPT_HEADERDATA           = 10029,
    CURLOPT_WRITEHEADER          = CURLOPT_HEADERDATA,
    CURLOPT_NOPROGRESS           = 43,
    CURLOPT_POST                 = 47,
    CURLOPT_FOLLOWLOCATION       = 52,
    CURLOPT_PROGRESSFUNCTION     = 20056,
    CURLOPT_PROGRESSDATA         = 10057,
    CURLOPT_CONNECTTIMEOUT       = 78,
    CURLOPT_HEADERFUNCTION       = 20079,
    CURLOPT_HTTPGET              = 80,
    CURLOPT_BUFFERSIZE           = 98,
    CURLOPT_NOSIGNAL             = 99,
    CURLOPT_SHARE                = 10100,
    CURLOPT_INFILESIZE_LARGE     = 30115,
    CURLOPT_POSTFIELDSIZE_LARGE  = 30120,
    CURLOPT_SOCKOPTFUNCTION      = 20148,
    CURLOPT_SOCKOPTDATA          = 10149,
    CURLOPT_CONNECTTIMEOUT_MS    = 156,
    CURLOPT_MAX_SEND_SPEED_LARGE = 30145,
    CURLOPT_MAX_RECV_SPEED_LARGE = 30146,

    CURLOPT_NSSL_CONTEXT    = 210,
    CURLOPT_UNKNOWN_211     = 211,
    CURLOPT_NSSL_VERIFY_OPT = CURLOPT_UNKNOWN_211,
    CURLOPT_UNKNOWN_215     = 215,
} CURLoption;

typedef enum CURLINFO
{
    CURLINFO_STRING = 0x100000,
    CURLINFO_LONG   = 0x200000,
    CURLINFO_DOUBLE = 0x300000,
    CURLINFO_SLIST  = 0x400000,

    CURLINFO_RESPONSE_CODE           = CURLINFO_LONG + 2,
    CURLINFO_SIZE_UPLOAD             = CURLINFO_DOUBLE + 7,
    CURLINFO_SIZE_DOWNLOAD           = CURLINFO_DOUBLE + 8,
    CURLINFO_SPEED_DOWNLOAD          = CURLINFO_DOUBLE + 9,
    CURLINFO_SPEED_UPLOAD            = CURLINFO_DOUBLE + 10,
    CURLINFO_SSL_VERIFYRESULT        = CURLINFO_LONG + 13,
    CURLINFO_CONTENT_LENGTH_DOWNLOAD = CURLINFO_DOUBLE + 15,
    CURLINFO_CONTENT_TYPE            = CURLINFO_STRING + 18,
    CURLINFO_REDIRECT_URL            = CURLINFO_STRING + 31,
} CURLINFO;

typedef enum CURLSHoption
{
    CURLSHOPT_NONE       = 0,
    CURLSHOPT_SHARE      = 1,
    CURLSHOPT_UNSHARE    = 2,
    CURLSHOPT_LOCKFUNC   = 3,
    CURLSHOPT_UNLOCKFUNC = 4,
    CURLSHOPT_USERDATA   = 5,
} CURLSHoption;

typedef enum curl_lock_data
{
    CURL_LOCK_DATA_NONE        = 0,
    CURL_LOCK_DATA_SHARE       = 1,
    CURL_LOCK_DATA_COOKIE      = 2,
    CURL_LOCK_DATA_DNS         = 3,
    CURL_LOCK_DATA_SSL_SESSION = 4,
    CURL_LOCK_DATA_CONNECT     = 5,
} curl_lock_data;

typedef enum curl_lock_access
{
    CURL_LOCK_ACCESS_NONE   = 0,
    CURL_LOCK_ACCESS_SHARED = 1,
    CURL_LOCK_ACCESS_SINGLE = 2,
} curl_lock_access;

typedef enum CURLMoption
{
    CURLMOPT_SOCKETFUNCTION = 20001,
    CURLMOPT_SOCKETDATA     = 10002,
    CURLMOPT_PIPELINING     = 3,
    CURLMOPT_TIMERFUNCTION  = 20004,
    CURLMOPT_TIMERDATA      = 10005,
    CURLMOPT_MAXCONNECTS    = 6,
} CURLMoption;

CUT_IMPORT CURLcode (*curl_global_init_mem)(uint32_t flags, curl_malloc_callback malloc_callback, curl_free_callback free_callback,
                                            curl_realloc_callback realloc_callback, curl_strdup_callback strdup_callback,
                                            curl_calloc_callback calloc_callback);
CUT_IMPORT CURLcode (*curl_global_init)(uint32_t flags);

CUT_IMPORT curl_slist *(*curl_slist_append)(curl_slist *list, const char *data);
CUT_IMPORT void (*curl_slist_free_all)(curl_slist *list);

CUT_IMPORT const char *(*curl_easy_strerror)(CURLcode code);

CUT_IMPORT CURLSH *(*curl_share_init)(void);
CUT_IMPORT CURLSHcode (*curl_share_setopt)(CURLSH *share, CURLSHoption option, ...);
CUT_IMPORT CURLSHcode (*curl_share_cleanup)(CURLSH *share);

CUT_IMPORT CURL *(*mw_curl_easy_init)(void);
CUT_IMPORT CURL *(*curl_easy_init)(void);
CUT_IMPORT void (*curl_easy_reset)(CURL *curl);
CUT_IMPORT CURLcode (*curl_easy_setopt)(CURL *curl, CURLoption option, ...);
CUT_IMPORT CURLcode (*curl_easy_getinfo)(CURL *curl, CURLINFO info, ...);
CUT_IMPORT CURLcode (*curl_easy_perform)(CURL *curl);
CUT_IMPORT void (*curl_easy_cleanup)(CURL *curl);
CUT_IMPORT CURLcode (*curl_easy_pause)(CURL *curl, int bitmask);

CUT_IMPORT CURLM *(*curl_multi_init)(void);
CUT_IMPORT CURLMcode (*curl_multi_add_handle)(CURLM *multi_handle, CURL *curl_handle);
CUT_IMPORT CURLMcode (*curl_multi_perform)(CURLM *multi_handle, int *running_handles);
CUT_IMPORT CURLMsg *(*curl_multi_info_read)(CURLM *multi_handle, int *msgs_in_queue);
CUT_IMPORT CURLMcode (*curl_multi_remove_handle)(CURLM *multi_handle, CURL *curl_handle);
CUT_IMPORT CURLMcode (*curl_multi_setopt)(CURLM *multi_handle, CURLMoption option, ...);
CUT_IMPORT CURLMcode (*curl_multi_fdset)(CURLM *multi_handle, fd_set *read_fd_set, fd_set *write_fd_set, fd_set *exc_fd_set, int *max_fd);
CUT_IMPORT CURLMcode (*curl_multi_cleanup)(CURLM *multi_handle);
CUT_IMPORT CURLMcode (*curl_multi_timeout)(CURLM *multi_handle, long *timeout_ms);

#ifdef __cplusplus
}
#endif
