/**
 * @addtogroup quaternions Library for 3D Vectors & Quaternions
 * @{
 * @file
 * @brief Library that provides data types for 3D vectors and quaternions,
 * inter-conversions and related operations.
 * @version @LIBQUAT_VERSION_MAJOR@.@LIBQUAT_VERSION_MINOR@
 * @author Krishna Vedala
 */

#ifndef __LIBQUAT_H_
#define __LIBQUAT_H_

#if BUILDING_LIBQUAT && HAVE_VISIBILITY
#define LIBQUAT_DLL_EXPORTED __attribute__((__visibility__("default")))
#elif BUILDING_LIBQUAT && defined _MSC_VER
#define LIBQUAT_DLL_EXPORTED __declspec(dllexport)
#elif defined _MSC_VER
#define LIBQUAT_DLL_EXPORTED __declspec(dllimport)
#else
#define LIBQUAT_DLL_EXPORTED
#endif

#define LIBQUAT_EPSILON                                               \
    1e-9 /**< Minimum recognizable value. Any value less than this is \
            considered to be @f$=0@f$ */

#ifdef __cplusplus
#include <iostream>
extern "C" {
#endif

/**
 * @addtogroup errors Error module
 * @{
 */
/** Library return types indicating different error types. */
typedef enum {
    LIBQUAT_OK = 0,      /**< No error */
    LIBQUAT_BAD_VERSION, /**< header and library version do not match */
    LIBQUAT_DIV_BY_ZERO, /**< Division by zero */
} libquat_err;

/**
 * Obtain descriptive string message for a #libquat_err type error code.
 * @param[in] err_code error code from the library api calls
 * @return error description string
 */
LIBQUAT_DLL_EXPORTED const char *err_to_str(libquat_err err_code);

/**
 * Function to check the version number of the library with the header.
 * @param[in] major_ver provide major version as input
 * @return error of type #libquat_err
 */
LIBQUAT_DLL_EXPORTED libquat_err libquat_version_check(const char major_ver);
/** @} */

/**
 * @addtogroup vec_3d 3D Vector operations
 * @{
 */
/** 3D vector type */
typedef struct vec_3d_ {
    float x; /**< X co-ordinate */
    float y; /**< Y co-ordinate */
    float z; /**< Z co-ordinate */
} vec_3d;
/** @} */

/**
 * @addtogroup matrix Matrix operations
 * @{
 */
/** A 3x3 Matrix type definition */
typedef struct mat_3x3_ {
    union { /**< 3 element row 1 */
        float row1[3];
        vec_3d vec1;
    };
    union { /**< 3 element row 2 */
        float row2[3];
        vec_3d vec2;
    };
    union { /**< 3 element row 3 */
        float row3[3];
        vec_3d vec3;
    };
} mat_3x3;
/** @} */

/**
 * @addtogroup vec_3d 3D Vector operations
 * @{
 */
/**
 * Obtain the dot product of two 3D vectors.
 * @f[
 * \vec{a}\cdot\vec{b}=a_xb_x + a_yb_y + a_zb_z
 * @f]
 * @param[in] a first vector
 * @param[in] b second vector
 * @returns resulting dot product
 */
LIBQUAT_DLL_EXPORTED float dot_prod(const vec_3d *a, const vec_3d *b);

/**
 * Subtract one vector from another. @f[
 * \vec{c}=\vec{a}-\vec{b}=\left(a_x-b_x\right)\hat{i}+
 * \left(a_y-b_y\right)\hat{j}+\left(a_z-b_z\right)\hat{k}@f]
 * @param[in] a vector to subtract from
 * @param[in] b vector to subtract
 * @returns resultant vector
 */
LIBQUAT_DLL_EXPORTED vec_3d vector_sub(const vec_3d *a, const vec_3d *b);

/**
 * Add one vector to another. @f[
 * \vec{c}=\vec{a}+\vec{b}=\left(a_x+b_x\right)\hat{i}+
 * \left(a_y+b_y\right)\hat{j}+\left(a_z+b_z\right)\hat{k}@f]
 * @param[in] a vector to add to
 * @param[in] b vector to add
 * @returns resultant vector
 */
LIBQUAT_DLL_EXPORTED vec_3d vector_add(const vec_3d *a, const vec_3d *b);

/**
 * Compute the vector product of two 3d vectors.
 * @f[\begin{align*}
 * \vec{a}\times\vec{b} &= \begin{vmatrix}
 *  \hat{i} & \hat{j} & \hat{k}\\
 *  a_x & a_y & a_z\\
 *  b_x & b_y & b_z
 *  \end{vmatrix}\\
 *  &= \left(a_yb_z-b_ya_z\right)\hat{i} - \left(a_xb_z-b_xa_z\right)\hat{j}
 * + \left(a_xb_y-b_xa_y\right)\hat{k} \end{align*}
 * @f]
 * @param[in] a first vector @f$\vec{a}@f$
 * @param[in] b second vector @f$\vec{b}@f$
 * @returns resultant vector @f$\vec{o}=\vec{a}\times\vec{b}@f$
 */
LIBQUAT_DLL_EXPORTED vec_3d vector_prod(const vec_3d *a, const vec_3d *b);

/**
 * Print formatted vector on stdout.
 * @param[in] a vector to print
 * @param[in] name  name of the vector
 * @returns formatted vector for printing
 */
LIBQUAT_DLL_EXPORTED LIBQUAT_DLL_EXPORTED const char *print_vector(
    const vec_3d *a, const char *name);

/**
 * Compute the norm a vector.
 * @f[\lVert\vec{a}\rVert = \sqrt{\vec{a}\cdot\vec{a}} @f]
 * @param[in] a input vector
 * @returns norm of the given vector
 */
LIBQUAT_DLL_EXPORTED float vector_norm(const vec_3d *a);

/**
 * Obtain unit vector in the same direction as given vector.
 * @f[\hat{a}=\frac{\vec{a}}{\lVert\vec{a}\rVert}@f]
 * @param[in] a input vector
 * @returns unit vector in the direction of @f$\vec{a}@f$
 */
LIBQUAT_DLL_EXPORTED vec_3d unit_vec(const vec_3d *a);

/**
 * The cross product of vectors can be represented as a matrix
 * multiplication operation. This function obtains the `3x3` matrix
 * of the cross-product operator from the first vector.
 * @f[\begin{align*}
 * \left(\vec{a}\times\right)\vec{b} &= \tilde{A}_a\vec{b}\\
 * \tilde{A}_a &=
 * \begin{bmatrix}0&-a_z&a_y\\a_z&0&-a_x\\-a_y&a_x&0\end{bmatrix}
 * \end{align*}@f]
 * @param[in] a input vector
 * @returns the `3x3` matrix for the cross product operator
 * @f$\left(\vec{a}\times\right)@f$
 */
LIBQUAT_DLL_EXPORTED mat_3x3 get_cross_matrix(const vec_3d *a);

/** @} */

/** @addtogroup quats 3D Quaternion operations
 * @{
 */
/** a Quaternion type represented using a scalar \f$w\f$ or \f$q_0\f$ and a
 * 3D vector \f$\left(q_1,q_2,q_3\right)\f$
 */
typedef struct quaternion_ {
    union {
        float w;  /**< real part of quaternion */
        float q0; /**< real part of quaternion */
    };
    /**< dual part of quaternion */
    union {
        vec_3d dual; /**< can be a 3D vector */
        /** or individual values */
        struct {
            float q1, q2, q3;
        };
    };
} quaternion;

/** 3D Euler or Tait-Bryan angles (in radian) */
typedef struct euler_ {
    union {
        float roll; /**< or bank \f$\phi\f$ = rotation about X axis */
        float bank; /**< or roll \f$\phi\f$ = rotation about X axis */
    };
    union {
        float pitch; /**< or elevation \f$\theta\f$ = rotation about Y axis */
        float elevation; /**< or pitch \f$\theta\f$ = rotation about Y axis */
    };
    union {
        float yaw;     /**< or heading \f$\psi\f$ = rotation about Z axis */
        float heading; /**< or yaw \f$\psi\f$ = rotation about Z axis */
    };
} euler;

/**
 * Function to convert given Euler angles to a quaternion.
 * \f{eqnarray*}{
 * q_{0} & =
 * &\cos\left(\frac{\phi}{2}\right)\cos\left(\frac{\theta}{2}\right)\cos\left(\frac{\psi}{2}\right)
 * +
 * \sin\left(\frac{\phi}{2}\right)\sin\left(\frac{\theta}{2}\right)\sin\left(\frac{\psi}{2}\right)\\
 * q_{1} & =
 * &\sin\left(\frac{\phi}{2}\right)\cos\left(\frac{\theta}{2}\right)\cos\left(\frac{\psi}{2}\right)
 * -
 * \cos\left(\frac{\phi}{2}\right)\sin\left(\frac{\theta}{2}\right)\sin\left(\frac{\psi}{2}\right)\\
 * q_{2} & =
 * &\cos\left(\frac{\phi}{2}\right)\sin\left(\frac{\theta}{2}\right)\cos\left(\frac{\psi}{2}\right)
 * +
 * \sin\left(\frac{\phi}{2}\right)\cos\left(\frac{\theta}{2}\right)\sin\left(\frac{\psi}{2}\right)\\
 * q_{3} & =
 * &\cos\left(\frac{\phi}{2}\right)\cos\left(\frac{\theta}{2}\right)\sin\left(\frac{\psi}{2}\right)
 * -
 * \sin\left(\frac{\phi}{2}\right)\sin\left(\frac{\theta}{2}\right)\cos\left(\frac{\psi}{2}\right)\\
 * \f}
 *
 * @param [in] in_euler input Euler angles instance
 * @returns converted quaternion
 */
LIBQUAT_DLL_EXPORTED quaternion quat_from_euler(const euler *in_euler);

/**
 * Function to convert given quaternion to Euler angles.
 * \f{eqnarray*}{
 * \phi & = &
 * \tan^{-1}\left[\frac{2\left(q_0q_1+q_2q_3\right)}{1-2\left(q_1^2+q_2^2\right)}\right]\\
 * \theta & =
 * &-\sin^{-1}\left[2\left(q_0q_2-q_3q_1\right)\right]\\
 * \psi & = &
 * \tan^{-1}\left[\frac{2\left(q_0q_3+q_1q_2\right)}{1-2\left(q_2^2+q_3^2\right)}\right]\\
 * \f}
 *
 * @param [in] in_quat input quaternion instance
 * @returns converted euler angles
 */
LIBQUAT_DLL_EXPORTED euler euler_from_quat(const quaternion *in_quat);

/**
 * Function to multiply two quaternions.
 * \f{eqnarray*}{
 * \mathbf{c} & = & \mathbf{a}\otimes\mathbf{b}\\
 * & = & \begin{bmatrix}a_{0} & a_{1} & a_{2} &
 *  a_{3}\end{bmatrix}\otimes\begin{bmatrix}b_{0} & b_{1} & b_{2} &
 *  b_{3}\end{bmatrix}\\
 * & = &
 * \begin{bmatrix}
 *  a_{0}b_{0}-a_{1}b_{1}-a_{2}b_{2}-a_{3}b_{3}\\
 *  a_{0}b_{1}+a_{1}b_{0}+a_{2}b_{3}-a_{3}b_{2}\\
 *  a_{0}b_{2}-a_{1}b_{3}+a_{2}b_{0}+a_{3}b_{1}\\
 *  a_{0}b_{3}+a_{1}b_{2}-a_{2}b_{1}+a_{3}b_{0}
 * \end{bmatrix}^{T}
 * \f}
 *
 * @param [in] in_quat1 first input quaternion instance
 * @param [in] in_quat2 second input quaternion instance
 * @returns resultant quaternion
 */
LIBQUAT_DLL_EXPORTED quaternion quaternion_multiply(const quaternion *in_quat1,
                                                    const quaternion *in_quat2);

/**
 * Function to add two quaternions.
 *
 * @param [in] in_quat1 first input quaternion instance
 * @param [in] in_quat2 second input quaternion instance
 * @returns resultant quaternion
 */
LIBQUAT_DLL_EXPORTED quaternion quaternion_add(const quaternion *in_quat1,
                                               const quaternion *in_quat2);

/**
 * Function to subtract two quaternions.
 *
 * @param [in] in_quat1 first input quaternion instance
 * @param [in] in_quat2 second input quaternion instance
 * @returns resultant quaternion
 */
LIBQUAT_DLL_EXPORTED quaternion quaternion_sub(const quaternion *in_quat1,
                                               const quaternion *in_quat2);

/**
 * @brief Get conjugate of a quaternion. The conjugate is defined as:
 * \f[
 * \mathbf{A}^* = q_0- i \vec{q}
 * \f]
 *
 * @param in_quat1 input quaternion
 * @return conjugate of the input quaternion
 */
LIBQUAT_DLL_EXPORTED quaternion get_conjugate(const quaternion *in_quat1);

/**
 * @brief Get inverse of a quaternion. The inverse is defined as:
 * \f[
 * \mathbf{A}^{-1} = \frac{\mathbf{A}^*}{\left\lVert\mathbf{A}\right\rVert}
 * \f]
 *
 * @param in_quat1 input quaternion
 * @return inverse of the input quaternion if exists
 * @returns NULL quaternion if inverse does not exist
 */
LIBQUAT_DLL_EXPORTED quaternion get_inverse(const quaternion &in_quat1);

/** @} */

/** @addtogroup dual_quats 3D Dual-Quaternion operations
 * @{
 */
/** a dual quaternion type */
typedef struct dual_quat_ {
    quaternion real; /**< real part of dual quaternion */
    quaternion dual; /**< dual part of dual quaternion */
} dual_quat;

/** @} */

#ifdef __cplusplus
}

/**
 * @addtogroup vec_3d 3D Vector operations
 * @{
 */

/**
 * Subtract one vector from another.
 * @f[
 * \vec{c}=\vec{a}-\vec{b}=\left(a_x-b_x\right)\hat{i}+
 * \left(a_y-b_y\right)\hat{j}+\left(a_z-b_z\right)\hat{k}
 * @f]
 * @param[in] a vector to subtract from
 * @param[in] b vector to subtract
 * @returns resultant vector
 */
LIBQUAT_DLL_EXPORTED vec_3d operator-(const vec_3d &a, const vec_3d &b);

/**
 * Unary negation operator.
 * @f[
 * -\vec{a}=(-a_x)\hat{i}+ (-a_y)\hat{j} + (-a_z)\hat{k}
 * @f]
 * @param[in] a vector to negate
 * @returns resultant vector
 */
LIBQUAT_DLL_EXPORTED vec_3d operator-(const vec_3d &a);

/**
 * Add one vector to another.
 * @f[
 * \vec{c}=\vec{a}-\vec{b}=\left(a_x-b_x\right)\hat{i}+
 * \left(a_y-b_y\right)\hat{j}+\left(a_z-b_z\right)\hat{k}
 * @f]
 * @param[in] a first vector to add
 * @param[in] b second vector to add
 * @returns resultant vector
 */
LIBQUAT_DLL_EXPORTED vec_3d operator+(const vec_3d &a, const vec_3d &b);

/**
 * Obtain the dot product of two 3D vectors.
 * @f[
 * \vec{a}\cdot\vec{b}=a_xb_x + a_yb_y + a_zb_z
 * @f]
 * @param[in] a first vector
 * @param[in] b second vector
 * @returns resulting dot product
 */
LIBQUAT_DLL_EXPORTED float operator*(const vec_3d &a, const vec_3d &b);

/**
 * Scalar multiplication of a 3D vector.
 * @f[
 * a\cdot\vec{b}=a\cdot b_x\hat{i} + a\cdot b_y \hat{j} + a\cdot b_z\hat{k}
 * @f]
 * @param[in] a pre-multiplying scalar
 * @param[in] b second vector
 * @returns resulting dot product
 */
LIBQUAT_DLL_EXPORTED vec_3d operator*(const float a, const vec_3d &b);

/**
 * Scalar multiplication of a 3D vector.
 * @f[
 * \vec{a}\cdot b=a_x\cdot b\hat{i} + a_y\cdot b\hat{j} + a_z\cdot b\hat{k}
 * @f]
 * @param[in] a first vector
 * @param[in] b post-multiplying scalar
 * @returns resulting dot product
 */
LIBQUAT_DLL_EXPORTED vec_3d operator*(const vec_3d &a, const float b);

/**
 * Scalar division of a 3D vector.
 * @param[in] a vector to divide
 * @param[in] b scalar divisor
 * @returns resulting quotient
 */
LIBQUAT_DLL_EXPORTED vec_3d operator/(const vec_3d &a, const float b);

/**
 * Compute the vector product of two 3d vectors.
 * @f[\begin{align*}
 * \vec{a}\times\vec{b} &= \begin{vmatrix}
 *  \hat{i} & \hat{j} & \hat{k}\\
 *  a_x & a_y & a_z\\
 *  b_x & b_y & b_z
 *  \end{vmatrix}\\
 *  &= \left(a_yb_z-b_ya_z\right)\hat{i} - \left(a_xb_z-b_xa_z\right)\hat{j}
 * + \left(a_xb_y-b_xa_y\right)\hat{k} \end{align*}
 * @f]
 * @param[in] a first vector @f$\vec{a}@f$
 * @param[in] b second vector @f$\vec{b}@f$
 * @returns resultant vector @f$\vec{o}=\vec{a}\times\vec{b}@f$
 */
LIBQUAT_DLL_EXPORTED vec_3d operator^(const vec_3d &a, const vec_3d &b);

/**
 * Compute the norm a vector.
 * @f[\lVert\vec{a}\rVert = \sqrt{\vec{a}\cdot\vec{a}} @f]
 * @param[in] a input vector
 * @returns n norm of the given vector
 */
LIBQUAT_DLL_EXPORTED float operator~(const vec_3d &a);

/**
 * operator to print a vec_3d instance.
 * @param out std::ostream stream to print output to
 * @param v vector to print
 * @returns formatted stream
 */
LIBQUAT_DLL_EXPORTED std::ostream &operator<<(std::ostream &out,
                                              vec_3d const &v);
/**
 * operator to print a vec_3d instance.
 * @param out std::ostream stream to print output to
 * @param v vector to print
 * @returns formatted stream
 */
LIBQUAT_DLL_EXPORTED std::ostream &operator<<(std::ostream &out,
                                              quaternion const &v);

/** @} */

/** @addtogroup quats 3D Quaternion operations
 * @{
 */

/**
 * Function to add two quaternions.
 *
 * @param [in] in_quat1 first input quaternion instance
 * @param [in] in_quat2 second input quaternion instance
 * @returns resultant quaternion
 */
LIBQUAT_DLL_EXPORTED quaternion operator+(const quaternion &in_quat1,
                                          const quaternion &in_quat2);

/**
 * Function to subtract two quaternions.
 *
 * @param [in] in_quat1 quaternion to subtract from
 * @param [in] in_quat2 quaternion to subtract
 * @returns resultant quaternion
 */
LIBQUAT_DLL_EXPORTED quaternion operator-(const quaternion &in_quat1,
                                          const quaternion &in_quat2);

/**
 * Function to multiply two quaternions.
 * \f{eqnarray*}{
 * \mathbf{c} & = & \mathbf{a}\otimes\mathbf{b}\\
 * & = & \begin{bmatrix}a_{0} & a_{1} & a_{2} &
 *  a_{3}\end{bmatrix}\otimes\begin{bmatrix}b_{0} & b_{1} & b_{2} &
 *  b_{3}\end{bmatrix}\\
 * & = &
 * \begin{bmatrix}
 *  a_{0}b_{0}-a_{1}b_{1}-a_{2}b_{2}-a_{3}b_{3}\\
 *  a_{0}b_{1}+a_{1}b_{0}+a_{2}b_{3}-a_{3}b_{2}\\
 *  a_{0}b_{2}-a_{1}b_{3}+a_{2}b_{0}+a_{3}b_{1}\\
 *  a_{0}b_{3}+a_{1}b_{2}-a_{2}b_{1}+a_{3}b_{0}
 * \end{bmatrix}^{T}
 * \f}
 *
 * @param [in] in_quat1 first input quaternion instance
 * @param [in] in_quat2 second input quaternion instance
 * @returns resultant quaternion
 */
LIBQUAT_DLL_EXPORTED quaternion operator*(const quaternion &in_quat1,
                                          const quaternion &in_quat2);

/**
 * Scalar multiplication of a 3D quaternion.
 * @param[in] a pre-multiplying scalar
 * @param[in] b second quaternion
 * @returns resulting dot product
 */
LIBQUAT_DLL_EXPORTED quaternion operator*(const float a, const quaternion &b);

/**
 * Scalar multiplication of a 3D quaternion.
 * @param[in] a pre-multiplying quaternion
 * @param[in] b post-multiplying scalar
 * @returns resulting product
 */
LIBQUAT_DLL_EXPORTED quaternion operator*(const quaternion &a, const float b);

/**
 * Scalar division of a 3D quaternion.
 * @param[in] a quaternion to divide
 * @param[in] b scalar divisor
 * @returns resulting quotient
 */
LIBQUAT_DLL_EXPORTED quaternion operator/(const quaternion &a, const float b);

/**
 * @brief Get conjugate of a quaternion. The conjugate is defined as:
 * \f[
 * \mathbf{A}^* = q_0- i \vec{q}
 * \f]
 *
 * @param in_quat1 input quaternion
 * @return conjugate of the input quaternion
 */
LIBQUAT_DLL_EXPORTED quaternion operator!(const quaternion &in_quat1);

/**
 * Compute the norm a quaternion.
 * @f[
 * \lVert A\rVert = \sqrt{q_0^2 + \vec{a}\cdot\vec{a}}
 * @f]
 * @param[in] a input vector
 * @returns n norm of the given vector
 */
LIBQUAT_DLL_EXPORTED float operator~(const quaternion &a);

/** @} */

#endif

#endif  // __LIBQUAT_H_

/** @} */
