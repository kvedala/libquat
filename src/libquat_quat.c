/**
 * @file
 * @brief API Functions related to 3D Quaternion operations.
 * @author Krishna Vedala
 */

#include <stdio.h>
#ifdef __arm__
#define LIBQUAT_ARM
#include <arm_math.h>
#else
#include <math.h>
#endif
#include <string.h>  // for memmove

#include "libquat.h"
#include "libquat_internal.h"

quaternion quat_from_euler(const euler *in_euler, quaternion *out_quat)
{
    if (!in_euler)  // if null
    {
        fprintf(stderr, "%s: Invalid input.", __func__);
        return *out_quat;
    }

    quaternion temp;

    float cy = cosf(in_euler->yaw * 0.5f);
    float sy = sinf(in_euler->yaw * 0.5f);
    float cp = cosf(in_euler->pitch * 0.5f);
    float sp = sinf(in_euler->pitch * 0.5f);
    float cr = cosf(in_euler->roll * 0.5f);
    float sr = sinf(in_euler->roll * 0.5f);

    temp.w = cr * cp * cy + sr * sp * sy;
    temp.q1 = sr * cp * cy - cr * sp * sy;
    temp.q2 = cr * sp * cy + sr * cp * sy;
    temp.q3 = cr * cp * sy - sr * sp * cy;

    if (out_quat)  // if not null
        memcpy(out_quat, &temp, sizeof(temp));

    return temp;
}

euler euler_from_quat(const quaternion *in_quat, euler *out_euler)
{
    if (!in_quat)  // if null
    {
        fprintf(stderr, "%s: Invalid input.", __func__);
        return *out_euler;
    }

    euler temp;

    temp.roll = atan2f(
        2.f * (in_quat->w * in_quat->q1 + in_quat->q2 * in_quat->q3),
        1.f - 2.f * (in_quat->q1 * in_quat->q1 + in_quat->q2 * in_quat->q2));
    temp.pitch =
        asinf(2.f * (in_quat->w * in_quat->q2 + in_quat->q1 * in_quat->q3));
    temp.yaw = atan2f(
        2.f * (in_quat->w * in_quat->q3 + in_quat->q1 * in_quat->q2),
        1.f - 2.f * (in_quat->q2 * in_quat->q2 + in_quat->q3 * in_quat->q3));

    if (out_euler)  // if not null
        memcpy(out_euler, &temp, sizeof(temp));

    return temp;
}

quaternion quaternion_multiply(const quaternion *in_quat1,
                               const quaternion *in_quat2, quaternion *out_quat)
{
    if (!in_quat1 || !in_quat2)  // if null
    {
        fprintf(stderr, "%s: Invalid input.", __func__);
        return *out_quat;
    }

    quaternion temp;

    temp.w = in_quat1->w * in_quat2->w - in_quat1->q1 * in_quat2->q1 -
             in_quat1->q2 * in_quat2->q2 - in_quat1->q3 * in_quat2->q3;
    temp.q1 = in_quat1->w * in_quat2->q1 + in_quat1->q1 * in_quat2->w +
              in_quat1->q2 * in_quat2->q3 - in_quat1->q3 * in_quat2->q2;
    temp.q2 = in_quat1->w * in_quat2->q2 - in_quat1->q1 * in_quat2->q3 +
              in_quat1->q2 * in_quat2->w + in_quat1->q3 * in_quat2->q1;
    temp.q3 = in_quat1->w * in_quat2->q3 + in_quat1->q1 * in_quat2->q2 -
              in_quat1->q2 * in_quat2->q1 + in_quat1->q3 * in_quat2->w;

    if (out_quat)  // if not null
        memcpy(out_quat, &temp, sizeof(temp));

    return temp;
}
