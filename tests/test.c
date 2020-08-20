/**
 * @file
 * @brief Simple program in C to test the different aspects of `libquat`
 * library.
 * @author Krishna Vedala
 */

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "../include/libquat.h"

/**
 * @brief Test program in C
 *
 * @return int
 */
int main(void) {
    vec_3d a = {1.f, 2.f, 3.f};
    vec_3d b = {1.f, 1.f, 1.f};
    vec_3d c = {0.f};
    float d = 0.f;

    printf("%s", print_vector(&a, "a"));
    printf("%s", print_vector(&b, "b"));

    d = vector_norm(&a);
    printf("|a| = %.4g\n", d);
    d = vector_norm(&b);
    printf("|b| = %.4g\n", d);

    d = dot_prod(&a, &b);
    printf("Dot product: %f\n", d);

    c = vector_prod(&a, &b);
    printf("Vector product ");
    printf("%s", print_vector(&c, "c"));

    quaternion quat = {0.7071f, 0.7071f, 0.f, 0.f};
    euler eul = {0.f};
    eul = euler_from_quat(&quat);
    printf("Euler: % .3g, % .3g, % .3g\n", eul.pitch, eul.roll, eul.yaw);

    quaternion test_quat;
    test_quat = quat_from_euler(&eul);
    printf("Quaternion: %+.3g %+.3g %+.3g %+.3g\n", test_quat.w,
           test_quat.dual.x, test_quat.dual.y, test_quat.dual.z);

    assert(fabsf(test_quat.q0 - quat.q0) < 0.1f);
    assert(fabsf(test_quat.q1 - quat.q1) < 0.1f);
    assert(fabsf(test_quat.q2 - quat.q2) < 0.1f);
    assert(fabsf(test_quat.q3 - quat.q3) < 0.1f);

    quaternion q1 = {1.f, -1.f, -1.f, 1.f};
    quaternion q2 = {-1.f, -1.f, -1.f, -1.f};
    quaternion q3 = quaternion_multiply(&q1, &q2);
    printf("Quaternion: %+.3g %+.3g %+.3g %+.3g\n", q3.q0, q3.q1, q3.q2, q3.q3);

    return 0;
}
