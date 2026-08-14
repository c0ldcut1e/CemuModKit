#ifndef FMT_FORMAT_WIIU_H_
#define FMT_FORMAT_WIIU_H_

#include "format.h"
#include "printf.h"

#include <coreinit/debug.h>

FMT_BEGIN_NAMESPACE

namespace wiiu_detail
{
    inline auto osreport_write(string_view text) -> size_t
    {
        const char *data = text.data();
        size_t remaining = text.size();
        size_t written   = 0;
        while (remaining != 0)
        {
            int chunk = remaining > 512 ? 512 : (int) remaining;
            OSReport("%.*s", chunk, data);
            data += chunk;
            remaining -= (size_t) chunk;
            written += (size_t) chunk;
        }

        return written;
    }
} // namespace wiiu_detail

inline void wiiu_vprint(string_view formatString, format_args args) { wiiu_detail::osreport_write(vformat(formatString, args)); }

inline void wiiu_vprintln(string_view formatString, format_args args)
{
    wiiu_vprint(formatString, args);
    wiiu_detail::osreport_write("\n");
}

template<typename... T>
inline void wiiu_print(format_string<T...> formatString, T &&...args)
{
    wiiu_detail::osreport_write(format(formatString, static_cast<T &&>(args)...));
}

template<typename... T>
inline void wiiu_println(format_string<T...> formatString, T &&...args)
{
    wiiu_print(formatString, static_cast<T &&>(args)...);
    wiiu_detail::osreport_write("\n");
}

inline auto wiiu_vprintf(string_view formatString, printf_args args) -> int
{
    return (int) wiiu_detail::osreport_write(vsprintf(formatString, args));
}

template<typename... T>
inline auto wiiu_printf(string_view formatString, const T &...args) -> int
{
    return wiiu_vprintf(formatString, make_printf_args(args...));
}

template<typename... T>
inline auto wiiu_printfln(string_view formatString, const T &...args) -> int
{
    int written = wiiu_printf(formatString, args...);
    wiiu_detail::osreport_write("\n");
    return written + 1;
}

inline void wiiu_debug_vprint(string_view formatString, format_args args)
{
#ifdef DEBUG
    wiiu_vprint(formatString, args);
#endif
}

inline void wiiu_debug_vprintln(string_view formatString, format_args args)
{
#ifdef DEBUG
    wiiu_vprintln(formatString, args);
#endif
}

template<typename... T>
inline void wiiu_debug_print(format_string<T...> formatString, T &&...args)
{
#ifdef DEBUG
    wiiu_print(formatString, static_cast<T &&>(args)...);
#endif
}

template<typename... T>
inline void wiiu_debug_println(format_string<T...> formatString, T &&...args)
{
#ifdef DEBUG
    wiiu_println(formatString, static_cast<T &&>(args)...);
#endif
}

inline auto wiiu_debug_vprintf(string_view formatString, printf_args args) -> int
{
#ifdef DEBUG
    return wiiu_vprintf(formatString, args);
#else
    return 0;
#endif
}

template<typename... T>
inline auto wiiu_debug_printf(string_view formatString, const T &...args) -> int
{
#ifdef DEBUG
    return wiiu_printf(formatString, args...);
#else
    return 0;
#endif
}

template<typename... T>
inline auto wiiu_debug_printfln(string_view formatString, const T &...args) -> int
{
#ifdef DEBUG
    return wiiu_printfln(formatString, args...);
#else
    return 0;
#endif
}

inline void wiiu_verbose_debug_vprint(string_view formatString, format_args args)
{
#ifdef VERBOSE_DEBUG
    wiiu_vprint(formatString, args);
#endif
}

inline void wiiu_verbose_debug_vprintln(string_view formatString, format_args args)
{
#ifdef VERBOSE_DEBUG
    wiiu_vprintln(formatString, args);
#endif
}

template<typename... T>
inline void wiiu_verbose_debug_print(format_string<T...> formatString, T &&...args)
{
#ifdef VERBOSE_DEBUG
    wiiu_print(formatString, static_cast<T &&>(args)...);
#endif
}

template<typename... T>
inline void wiiu_verbose_debug_println(format_string<T...> formatString, T &&...args)
{
#ifdef VERBOSE_DEBUG
    wiiu_println(formatString, static_cast<T &&>(args)...);
#endif
}

inline auto wiiu_verbose_debug_vprintf(string_view formatString, printf_args args) -> int
{
#ifdef VERBOSE_DEBUG
    return wiiu_vprintf(formatString, args);
#else
    return 0;
#endif
}

template<typename... T>
inline auto wiiu_verbose_debug_printf(string_view formatString, const T &...args) -> int
{
#ifdef VERBOSE_DEBUG
    return wiiu_printf(formatString, args...);
#else
    return 0;
#endif
}

template<typename... T>
inline auto wiiu_verbose_debug_printfln(string_view formatString, const T &...args) -> int
{
#ifdef VERBOSE_DEBUG
    return wiiu_printfln(formatString, args...);
#else
    return 0;
#endif
}

FMT_END_NAMESPACE

#endif // FMT_FORMAT_WIIU_H_
