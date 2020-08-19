/**
 * @file
 * @brief Simple program in C++ to test the different aspects of `libquat`
 * library.
 * @author Krishna Vedala
 */

#include "../include/libquat.h"
#include <cmath>
#include <iostream>
#include <cassert>

/**
 * @brief Test program in C++
 *
 * @return int
 */
auto main() -> int {
    vec_3d a = {1.f, 2.f, 3.f};
    vec_3d b = {1.f, 1.f, 1.f};
    vec_3d c = {0.f};
    float d = 0.f;

    std::cout << print_vector(&a, "a");
    std::cout << print_vector(&b, "b");

    d = ~a;
    std::cout << "|a| =" << d << "\n";
    d = ~b;
    std::cout << "|b| =" << d << "\n";

    d = a * b;
    std::cout << "Dot product: " << d << "\n";

    c = a ^ b;
    std::cout << "Vector product ";
    std::cout << print_vector(&c, "c");

    quaternion quat = {0.7071f, 0.7071f, 0.f, 0.f};
    euler eul = {0.f};
    eul = euler_from_quat(&quat);
    std::cout << "Euler: " << eul.pitch << ", " << eul.roll << ", " << eul.yaw
              << "\n";

    quaternion test_quat;
    test_quat = quat_from_euler(&eul);
    std::cout << "Quaternion: " << test_quat.w << ", " << test_quat.dual.x
              << ", " << test_quat.dual.y << ", " << test_quat.dual.z << "\n";

    assert(fabsf(test_quat.q0 - quat.q0) < 0.1f);
    assert(fabsf(test_quat.q1 - quat.q1) < 0.1f);
    assert(fabsf(test_quat.q2 - quat.q2) < 0.1f);
    assert(fabsf(test_quat.q3 - quat.q3) < 0.1f);

    quaternion q1 = {1.f, -1.f, -1.f, 1.f};
    quaternion q2 = {-1.f, -1.f, -1.f, -1.f};
    quaternion q3 = quaternion_multiply(&q1, &q2);
    std::cout << "Quaternion: " << q3.q0 << ", " << q3.q1 << ", " << q3.q2
              << ", " << q3.q3 << "\n";

    quaternion q4;
    q4.w = q1.q0 * q2.q0 - (q1.dual * q2.dual);

    std::cout << "Quaternion: " << q4.q0 << ", " << q4.q1 << ", " << q4.q2
              << ", " << q4.q3 << "\n";

    return 0;
}
