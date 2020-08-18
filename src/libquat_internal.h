/**
 * @addtogroup quaternions Library for 3D Vectors & Quaternions
 * @{
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

#ifdef __cplusplus
/**< internal variable to keep a track of version validity */
extern "C"
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
/** @} */
