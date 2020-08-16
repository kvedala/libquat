/**
 * @file libquat_internal.h
 * API functions to handle library errors.
 * @author Krishna Vedala
 */
#ifndef _LIBQUAT_INTERNAL_
#define _LIBQUAT_INTERNAL_

static const char libquat_author[] =
    "Krishna Vedala"; /**< Store this internally */
static const char libquat_major_ver =
    LIBQUAT_MAJOR_VER; /**< Store this internally */
static const char libquat_minor_ver =
    LIBQUAT_MINOR_VER; /**< Store this internally */

#ifdef __cplusplus
/**< internal variable to keep a track of version validity */
extern "C" char is_libquat_valid;
#else
/**< internal variable to keep a track of version validity */
extern char is_libquat_valid;
#endif

#endif