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