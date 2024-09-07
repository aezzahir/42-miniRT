/**
 * @file vector.h
 * @brief Header file for vector operations
 */

#ifndef VECTOR_H
#define VECTOR_H

typedef struct s_vector {
    float x;
    float y;
    float z;
} t_vector;
typedef t_vector t_point; // the point and vector have the same representation but different meaning a point is as specific location in the 3D space P(x, y, z)
                            // but a vector is not he indicate a direction and a magnitude V(x, y, z)
// Vector operations
t_vector vector_create(float x, float y, float z);
t_vector vector_add(t_vector v1, t_vector v2);
t_vector vector_subtract(t_vector v1, t_vector v2);
float vector_dot_product(t_vector v1, t_vector v2);
t_vector vector_cross_product(t_vector v1, t_vector v2);
float vector_magnitude(t_vector v);
t_vector vector_normalize(t_vector v);
t_vector vector_multiply(t_vector v, float scalar);
float vector_distance(t_vector v1, t_vector v2);

#endif /* VECTOR_H */


