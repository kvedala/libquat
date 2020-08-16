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

#define LIBQUAT_EPSILON                                               \
    1e-9 /**< Minimum recognizable value. Any value less than this is \
            considered to be @f$=0@f$ */

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @addtogroup errors Error module
     * @{
     */
    /** Library return types indicating different error types. */
    typedef enum
    {
        LIBQUAT_OK = 0,      /**< No error */
        LIBQUAT_BAD_VERSION, /**< header and library version do not match */
        LIBQUAT_DIV_BY_ZERO, /**< Division by zero */
    } libquat_err;

    /**
     * Obtain descriptive string message for a #libquat_err type error code.
     * @param[in] err_code error code from the library api calls
     * @return error description string
     */
    const char *err_to_str(libquat_err err_code);

    /**
     * Function to check the version number of the library with the header.
     * @param[in] major_ver provide major version as input
     * @return error of type #libquat_err
     */
    libquat_err libquat_version_check(const char major_ver);
    /** @} */

    /**
     * @addtogroup matrix Matrix operations
     * @{
     */
    /** A 3x3 Matrix type definition */
    typedef struct mat_3x3_
    {
        float row1[3]; /**< 3 element row 1 */
        float row2[3]; /**< 3 element row 2 */
        float row3[3]; /**< 3 element row 3 */
    } mat_3x3;
    /** @} */

    /**
     * @addtogroup vec_3d 3D Vector operations
     * @{
     */
    /** 3D vector type */
    typedef struct vec_3d_
    {
        float x; /**< X co-ordinate */
        float y; /**< Y co-ordinate */
        float z; /**< Z co-ordinate */
    } vec_3d;

    /**
     * Obtain the dot product of two 3D vectors.
     * @f[
     * \vec{a}\cdot\vec{b}=a_xb_x + a_yb_y + a_zb_z
     * @f]
     * @param[in] a first vector
     * @param[in] b second vector
     * @param[out] o resulting dot product
     */
    void dot_prod(const vec_3d *a, const vec_3d *b, float *o);

    /**
     * Subtract one vector from another. @f[
     * \vec{c}=\vec{a}-\vec{b}=\left(a_x-b_x\right)\hat{i}+
     * \left(a_y-b_y\right)\hat{j}+\left(a_z-b_z\right)\hat{k}@f]
     * @param[in] a vector to subtract from
     * @param[in] b vector to subtract
     * @param[out] out resultant vector
     */
    void vector_sub(const vec_3d *a, const vec_3d *b, vec_3d *out);

    /**
     * Add one vector to another. @f[
     * \vec{c}=\vec{a}+\vec{b}=\left(a_x+b_x\right)\hat{i}+
     * \left(a_y+b_y\right)\hat{j}+\left(a_z+b_z\right)\hat{k}@f]
     * @param[in] a vector to add to
     * @param[in] b vector to add
     * @param[out] out resultant vector
     */
    void vector_add(const vec_3d *a, const vec_3d *b, vec_3d *out);

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
     * @param[out] o resultant vector @f$\vec{o}=\vec{a}\times\vec{b}@f$
     */
    void vector_prod(const vec_3d *a, const vec_3d *b, vec_3d *o);

    /**
     * Print formatted vector on stdout.
     * @param[in] a vector to print
     * @param[in] name  name of the vector
     */
    const char *print_vector(const vec_3d *a, const char *name);

    /**
     * Compute the norm a vector.
     * @f[\lVert\vec{a}\rVert = \sqrt{\vec{a}\cdot\vec{a}} @f]
     * @param[in] a input vector
     * @param[out] n norm of the given vector
     */
    void vector_norm(const vec_3d *a, float *n);

    /**
     * Obtain unit vector in the same direction as given vector.
     * @f[\hat{a}=\frac{\vec{a}}{\lVert\vec{a}\rVert}@f]
     * @param[in] a input vector
     * @param[out] a_hat unit vector in the direction of @f$\vec{a}@f$
     */
    libquat_err unit_vec(const vec_3d *a, vec_3d *a_hat);

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
     * @param[out] A the `3x3` matrix for the cross product operator
     * @f$\left(\vec{a}\times\right)@f$
     */
    void get_cross_matrix(const vec_3d *a, mat_3x3 *A);

    /** @} */

    /** @addtogroup quats 3D Quaternion operations
     * @{
     */
    /** a Quaternion type represented using a scalar \f$w\f$ or \f$q_0\f$ and a
     * 3D vector \f$\left(q_1,q_2,q_3\right)\f$
     */
    typedef struct quaternion_
    {
        float w; /**< real part of quaternion */
        union {  /**< dual part of quaternion also a 3D vector */
            vec_3d dual;
            struct
            {
                float q1, q2, q3;
            };
        };
    } quaternion;

    /** 3D Euler or Tait-Bryan angles (in radian) */
    typedef struct euler_
    {
        float roll;    /**< or bank \f$\phi\f$ = rotation about X axis */
        float pitch;   /**< or elevation \f$\theta\f$ = rotation about Y axis */
        float yaw;     /**< or elevation \f$\psi\f$ = rotation about Z axis */
        float heading; /**< \f$\alpha\f$ Angle between X & magnetic north */
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
     * @param [out] out_quat output quaternion instance
     */
    void quat_from_euler(const euler *in_euler, quaternion *out_quat);

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
     * @param [out] out_euler output Euler angles instance
     */
    void euler_from_quat(const quaternion *in_quat, euler *out_euler);

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
     * @param [out] out_quat output quaternion instance
     */
    void quaternion_multiply(const quaternion *in_quat1,
                             const quaternion *in_quat2, quaternion *out_quat);

    /** @} */

    /** @addtogroup dual_quats 3D Dual-Quaternion operations
     * @{
     */
    /** a dual quaternion type */
    typedef struct dual_quat_
    {
        quaternion real; /**< real part of dual quaternion */
        quaternion dual; /**< dual part of dual quaternion */
    } dual_quat;

    /** @} */

#ifdef __cplusplus
}
#endif

#endif  // __LIBQUAT_H_

/** @} */
