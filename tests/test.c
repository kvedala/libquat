/**
 * @file
 * @brief Simple program in C to test the different aspects of `libquat`
 * library.
 * @author Krishna Vedala
 */

#include <stdio.h>
#include <math.h>
#include "../include/libquat.h"

/**
 * @brief Test program in C
 *
 * @return int
 */
int main(void)
{
    vec_3d a = {1., 2., 3.};
    vec_3d b = {1., 1., 1.};
    vec_3d c;
    float d;

    printf("%s", print_vector(&a, "a"));
    printf("%s", print_vector(&b, "b"));

    vector_norm(&a, &d);
    printf("|a| = %.4g\n", d);
    vector_norm(&b, &d);
    printf("|b| = %.4g\n", d);

    dot_prod(&a, &b, &d);
    printf("Dot product: %f\n", d);

    vector_prod(&a, &b, &c);
    printf("Vector product ");
    printf("%s", print_vector(&c, "c"));

    return 0;
}
