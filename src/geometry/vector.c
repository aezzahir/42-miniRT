/**
 * @file vector.c
 * @brief Defines vector operations
 */

#include "../../include/miniRT.h"

t_vector vector_create(float x, float y, float z) {
    return (t_vector){x, y, z};
}

t_vector vector_add(t_vector v1, t_vector v2) {
    return vector_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

t_vector vector_subtract(t_vector v1, t_vector v2) {
    return vector_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

float vector_dot_product(t_vector v1, t_vector v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

t_vector vector_cross_product(t_vector v1, t_vector v2) {
    return vector_create(
        (v1.y * v2.z) - (v1.z * v2.y),
        (v1.z * v2.x) - (v1.x * v2.z),
        (v1.x * v2.y) - (v1.y * v2.x)
    );
}

float vector_magnitude(t_vector v) {
    return sqrt(vector_dot_product(v, v));
}

t_vector vector_normalize(t_vector v) {
    float mag = vector_magnitude(v);
    if (mag == 0.0) return v;  // Avoid division by zero
    return vector_create(v.x / mag, v.y / mag, v.z / mag);
}

t_vector vector_multiply(t_vector v, float scalar) {
    return vector_create(v.x * scalar, v.y * scalar, v.z * scalar);
}

float vector_distance(t_vector v1, t_vector v2) {
    return vector_magnitude(vector_subtract(v2, v1));
}


t_vector vector_negate(t_vector v) {
    return vector_create(-v.x, -v.y, -v.z);
}

t_vector vector_reflect(t_vector incident, t_vector normal) {
    float dot = vector_dot_product(incident, normal);
    t_vector scaled_normal = vector_multiply(normal, 2 * dot);
    return vector_subtract(incident, scaled_normal);
}

float vector_length(t_vector v) {
    return vector_magnitude(v);
}

// Optional: You might find this useful for debugging
void vector_print(t_vector v) {
    printf("Vector: (%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}



t_vector vector_translate(t_vector v, t_vector translation) {
    return vector_add(v, translation);
}

t_vector vector_rotate_x(t_vector v, float angle) {
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    return vector_create(
        v.x,
        v.y * cos_a - v.z * sin_a,
        v.y * sin_a + v.z * cos_a
    );
}

t_vector vector_rotate_y(t_vector v, float angle) {
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    return vector_create(
        v.x * cos_a + v.z * sin_a,
        v.y,
        -v.x * sin_a + v.z * cos_a
    );
}

t_vector vector_rotate_z(t_vector v, float angle) {
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    return vector_create(
        v.x * cos_a - v.y * sin_a,
        v.x * sin_a + v.y * cos_a,
        v.z
    );
}

t_vector vector_rotate(t_vector v, t_vector rotation) {
    v = vector_rotate_x(v, rotation.x);
    v = vector_rotate_y(v, rotation.y);
    v = vector_rotate_z(v, rotation.z);
    return v;
}

// Quaternion structure for more efficient rotations
typedef struct {
    float w, x, y, z;
} t_quaternion;

t_quaternion quaternion_create(float angle, t_vector axis) {
    float half_angle = angle * 0.5f;
    float sin_half = sin(half_angle);
    axis = vector_normalize(axis);
    return (t_quaternion){
        .w = cos(half_angle),
        .x = axis.x * sin_half,
        .y = axis.y * sin_half,
        .z = axis.z * sin_half
    };
}

t_vector vector_rotate_quaternion(t_vector v, t_quaternion q) {
    t_quaternion q_conj = {q.w, -q.x, -q.y, -q.z};
    t_quaternion v_quat = {0, v.x, v.y, v.z};
    t_quaternion result;

    // q * v
    result.w = -q.x*v_quat.x - q.y*v_quat.y - q.z*v_quat.z;
    result.x =  q.w*v_quat.x + q.y*v_quat.z - q.z*v_quat.y;
    result.y =  q.w*v_quat.y + q.z*v_quat.x - q.x*v_quat.z;
    result.z =  q.w*v_quat.z + q.x*v_quat.y - q.y*v_quat.x;

    // (q * v) * q_conj
    v.x = result.w*q_conj.x + result.x*q_conj.w + result.y*q_conj.z - result.z*q_conj.y;
    v.y = result.w*q_conj.y + result.y*q_conj.w + result.z*q_conj.x - result.x*q_conj.z;
    v.z = result.w*q_conj.z + result.z*q_conj.w + result.x*q_conj.y - result.y*q_conj.x;

    return v;
}