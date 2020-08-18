/**
 * @file
 * @brief API functions to handle library errors.
 * @author Krishna Vedala
 */
#ifndef _LIBQUAT_INTERNAL_
#define _LIBQUAT_INTERNAL_

static const char libquat_major_ver =
    LIBQUAT_MAJOR_VER; /**< Store this internally */
static const char libquat_minor_ver =
    LIBQUAT_MINOR_VER; /**< Store this internally */

#ifndef LIBQUAT_DLL_EXPORTED
#if BUILDING_LIBQUAT && HAVE_VISIBILITY
#define LIBQUAT_DLL_EXPORTED __attribute__((__visibility__("default")))
#elif BUILDING_LIBQUAT && defined _MSC_VER
#define LIBQUAT_DLL_EXPORTED __declspec(dllexport)
#elif defined _MSC_VER
#define LIBQUAT_DLL_EXPORTED __declspec(dllimport)
#else
#define LIBQUAT_DLL_EXPORTED
#endif
#endif

#ifdef __cplusplus
/**< internal variable to keep a track of version validity */
extern "C" LIBQUAT_DLL_EXPORTED
{
#endif
    /**< internal variable to keep a track of version validity */
    extern char is_libquat_valid;

    // #define err_msg(...) print_err()

    // void print_err(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
