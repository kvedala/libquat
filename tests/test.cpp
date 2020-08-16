/**
  @file
  @brief Simple program to test the different aspects of `libquat` library.
  @author Krishna Vedala
*/

#include "libquat.h"
#include <cmath>
#include <iostream>

int main(void)
{
    vec_3d a = {1., 2., 3.};
    vec_3d b = {1., 1., 1.};
    vec_3d c;
    float d;

    std::cout << print_vector(&a, "a");
    std::cout << print_vector(&b, "b");

    vector_norm(&a, &d);
    std::cout << "|a| =" << d << "\n";
    vector_norm(&b, &d);
    std::cout << "|b| =" << d << "\n";

    dot_prod(&a, &b, &d);
    std::cout << "Dot product: " << d << "\n";

    vector_prod(&a, &b, &c);
    std::cout << "Vector product ";
    std::cout << print_vector(&c, "c");

    quaternion quat = {0.7071, 0.7071, 0, 0};
    euler eul = {0};
    euler_from_quat(&quat, &eul);
    std::cout << "Euler: " << eul.pitch << ", " << eul.roll << ", " << eul.yaw
              << "\n";

    quaternion test_quat;
    quat_from_euler(&eul, &test_quat);
    std::cout << "Quaternion: " << test_quat.w << ", " << test_quat.dual.x
              << ", " << test_quat.dual.y << ", " << test_quat.dual.z << "\n";

    return 0;
}
