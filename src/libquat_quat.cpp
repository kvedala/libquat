/**
 * @file
 * @brief API Functions related to 3D Quaternion operations.
 * @author Krishna Vedala
 */
#include "libquat.h"
#include "libquat_internal.h"

#ifdef __arm__
#define LIBQUAT_ARM
#include <arm_math.h>
#else
#include <cmath>
#endif

quaternion quat_from_euler(const euler *in_euler) {
    quaternion temp = {0.f};

    if (!in_euler)  // if null
    {
        fprintf(stderr, "%s: Invalid input.", __func__);
        return temp;
    }

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

    return temp;
}

euler euler_from_quat(const quaternion *in_quat) {
    euler temp = {0.f};

    if (!in_quat)  // if null
    {
        fprintf(stderr, "%s: Invalid input.", __func__);
        return temp;
    }

    temp.roll = atan2f(
        2.f * (in_quat->w * in_quat->q1 + in_quat->q2 * in_quat->q3),
        1.f - 2.f * (in_quat->q1 * in_quat->q1 + in_quat->q2 * in_quat->q2));
    temp.pitch =
        asinf(2.f * (in_quat->w * in_quat->q2 + in_quat->q1 * in_quat->q3));
    temp.yaw = atan2f(
        2.f * (in_quat->w * in_quat->q3 + in_quat->q1 * in_quat->q2),
        1.f - 2.f * (in_quat->q2 * in_quat->q2 + in_quat->q3 * in_quat->q3));

    return temp;
}

quaternion operator*(const quaternion &in_quat1, const quaternion &in_quat2) {
    quaternion temp = {0.f};

    temp.w = in_quat1.w * in_quat2.w - in_quat1.q1 * in_quat2.q1 -
             in_quat1.q2 * in_quat2.q2 - in_quat1.q3 * in_quat2.q3;
    temp.q1 = in_quat1.w * in_quat2.q1 + in_quat1.q1 * in_quat2.w +
              in_quat1.q2 * in_quat2.q3 - in_quat1.q3 * in_quat2.q2;
    temp.q2 = in_quat1.w * in_quat2.q2 - in_quat1.q1 * in_quat2.q3 +
              in_quat1.q2 * in_quat2.w + in_quat1.q3 * in_quat2.q1;
    temp.q3 = in_quat1.w * in_quat2.q3 + in_quat1.q1 * in_quat2.q2 -
              in_quat1.q2 * in_quat2.q1 + in_quat1.q3 * in_quat2.w;

    return temp;
}

quaternion operator*(const float scalar, const quaternion &in_quat) {
    quaternion temp = {0.f};

    temp.w = in_quat.q0 * scalar;
    temp.q1 = in_quat.q1 * scalar;
    temp.q2 = in_quat.q2 * scalar;
    temp.q3 = in_quat.q3 * scalar;

    return temp;
}

quaternion operator*(const quaternion &in_quat, const float scalar) {
    quaternion temp = {0.f};

    temp.w = in_quat.q0 * scalar;
    temp.q1 = in_quat.q1 * scalar;
    temp.q2 = in_quat.q2 * scalar;
    temp.q3 = in_quat.q3 * scalar;

    return temp;
}

quaternion operator/(const quaternion &in_quat, const float scalar) {
    quaternion temp = {0.f};

    temp.w = in_quat.q0 / scalar;
    temp.q1 = in_quat.q1 / scalar;
    temp.q2 = in_quat.q2 / scalar;
    temp.q3 = in_quat.q3 / scalar;

    return temp;
}

quaternion quaternion_multiply(const quaternion *in_quat1,
                               const quaternion *in_quat2) {
    if (!in_quat1 || !in_quat2)  // if null
    {
        fprintf(stderr, "%s: Invalid input.", __func__);
        return {0.f};
    }

    return *in_quat1 + *in_quat2;
}

quaternion operator!(const quaternion &in_quat1) {
    quaternion temp = {0.f};

    temp.w = in_quat1.w;
    temp.q1 = -in_quat1.q1;
    temp.q2 = -in_quat1.q2;
    temp.q3 = -in_quat1.q3;

    return temp;
}

quaternion get_conjugate(const quaternion *in_quat1) {
    if (!in_quat1) {
        std::cerr << __func__ << ": Invalid input.\n";
        return {0.f};
    }

    return !(*in_quat1);
}

quaternion operator+(const quaternion &in_quat1, const quaternion &in_quat2) {
    quaternion temp = {0.f};

    temp.w = in_quat1.w + in_quat2.w;
    temp.dual = in_quat1.dual + in_quat2.dual;

    return temp;
}

quaternion quaternion_add(const quaternion *in_quat1,
                          const quaternion *in_quat2) {
    if (!in_quat1 || !in_quat2)  // if null
    {
        std::cerr << __func__ << ": Invalid input.";
        return {0.f};
    }

    return *in_quat1 + *in_quat2;
}

quaternion operator-(const quaternion &in_quat1, const quaternion &in_quat2) {
    quaternion temp = {0.f};

    temp.w = in_quat1.w - in_quat2.w;
    temp.dual = in_quat1.dual - in_quat2.dual;

    return temp;
}

quaternion quaternion_sub(const quaternion *in_quat1,
                          const quaternion *in_quat2) {
    if (!in_quat1 || !in_quat2)  // if null
    {
        std::cerr << __func__ << ": Invalid input.";
        return {0.f};
    }

    return *in_quat1 - *in_quat2;
}

float operator~(const quaternion &in_quat1) {
    float temp = 0.f;

    temp += in_quat1.q0 * in_quat1.q0;
    temp += in_quat1.dual * in_quat1.dual;

    return sqrtf(temp);
}

quaternion operator+(const quaternion &quat) {
    float mag = ~quat;  // get norm
    if (mag == 0) {
        std::cerr << __func__ << ": Inverse does not exist\n";
    }
    quaternion temp = !quat;  // get conjugate
    return temp / (mag * mag);
}

quaternion get_inverse(const quaternion *quat) { return +(*quat); }
