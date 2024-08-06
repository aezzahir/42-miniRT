/**
 * @file vector.c
 * @brief Defines vector operations
 */

#include "../include/vector.h"
#include <math.h>
#include <stdlib.h>

t_vector vector_create(double x, double y, double z) {
    return (t_vector){x, y, z};
}

t_vector vector_add(t_vector v1, t_vector v2) {
    return vector_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

t_vector vector_subtract(t_vector v1, t_vector v2) {
    return vector_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

double vector_dot_product(t_vector v1, t_vector v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

t_vector vector_cross_product(t_vector v1, t_vector v2) {
    return vector_create(
        (v1.y * v2.z) - (v1.z * v2.y),
        (v1.z * v2.x) - (v1.x * v2.z),
        (v1.x * v2.y) - (v1.y * v2.x)
    );
}

double vector_magnitude(t_vector v) {
    return sqrt(vector_dot_product(v, v));
}

t_vector vector_normalize(t_vector v) {
    double mag = vector_magnitude(v);
    if (mag == 0.0) return v;  // Avoid division by zero
    return vector_create(v.x / mag, v.y / mag, v.z / mag);
}

t_vector vector_multiply(t_vector v, double scalar) {
    return vector_create(v.x * scalar, v.y * scalar, v.z * scalar);
}

double vector_distance(t_vector v1, t_vector v2) {
    return vector_magnitude(vector_subtract(v2, v1));
}