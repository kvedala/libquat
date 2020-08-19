/**
 * @file
 * @brief API functions to handle library errors.
 * @author Krishna Vedala
 */

#include <stdio.h>
#include <string.h>

#include "libquat.h"
#include "libquat_internal.h"

char is_libquat_valid = 0;

const char *err_to_str(libquat_err err_code) {
    switch (err_code) {
        case LIBQUAT_OK:
            return "OK.";
        case LIBQUAT_DIV_BY_ZERO:
            return "Division by zero.";
        case LIBQUAT_BAD_VERSION:
            return "Header and library version do not match";
        default:
            return "Unknown error type.";
    }
}

libquat_err libquat_version_check(const char major_ver) {
    if (is_libquat_valid) {
        return LIBQUAT_OK;
    }

    if (libquat_major_ver != major_ver) {
        return LIBQUAT_BAD_VERSION;
    }

    is_libquat_valid = 1;
    return LIBQUAT_OK;
}
