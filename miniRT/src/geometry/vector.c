/*
 * vector.c
 * Defines vector operations (addition, subtraction, dot product, cross product, etc.)
 */
#include <math.h>

typedef struct cartesian_coordinates {
    double x;
    double y;
    double z;
} t_vector;

typedef struct spherical_coordinates {
    double r;
    double theta;
    double phi;
} t_svector;

/*
 * Add two vectors
 */
t_vector vector_add(t_vector v1, t_vector v2) {
    t_vector result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;
}

/*
 * Subtract one vector from another
 */


t_vector vector_subtract(t_vector v1, t_vector v2)
{
    t_vector result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

/*
 * Calculate the dot product of two vectors
 */


double vector_dot_product(t_vector v1, t_vector v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

/*
 * Calculate the cross product of two vectors
 */

t_vector vector_cross_product(t_vector v1, t_vector v2)
{
    t_vector result;
    result.x = (v1.y * v2.z) - (v1.z * v2.y);
    result.y = (v1.z * v2.x) - (v1.x * v2.z);
    result.z = (v1.x * v2.y) - (v1.y * v2.x);
    return result;
}

/*
 * Calculate the magnitude of a vector
 */

double vector_magnitude(t_vector v)
{
    return sqrt(vector_dot_product(v, v));
}

/*
 * Calculate the unit vector of a given vector
 */

t_vector vector_normalize(t_vector v)
{
    double mag = vector_magnitude(v);
    if (mag == 0.0) {
        return v;  // Avoid division by zero
    }
    t_vector result;
    result.x = v.x / mag;
    result.y = v.y / mag;
    result.z = v.z / mag;
    return result;
}

/*
 * Convert Cartesian coordinates to spherical coordinates
 */

t_svector cartesian_to_spherical(t_vector v)
{
    t_svector result;
    result.r = vector_magnitude(v);
    result.theta = atan2(sqrt(v.x * v.x + v.y * v.y), v.z);
    result.phi = atan2(v.y, v.x);
    return result;
}

/*
 * Convert spherical coordinates to Cartesian coordinates
 */

t_vector spherical_to_cartesian(t_svector s)
{
    t_vector result;
    result.x = s.r * sin(s.theta) * cos(s.phi);
    result.y = s.r * sin(s.theta) * sin(s.phi);
    result.z = s.r * cos(s.theta);
    return result;
}

/*
 * Calculate the angle between the two vectors and return the angle between them in radians
 */

double vector_angle(t_vector v1, t_vector v2)
{
    double dot_product = vector_dot_product(v1, v2);
    double magnitude_product = vector_magnitude(v1) * vector_magnitude(v2);
    return acos(dot_product / magnitude_product);
}

/**
 * Computes the distance between two vectors and returns the distance between them
 */

double vector_distance(t_vector v1, t_vector v2)
{
    t_vector diff = vector_subtract(v2, v1);
    return vector_magnitude(diff);
}
