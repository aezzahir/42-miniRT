/*
 * geometry.h
 * Declarations for geometric operations and object-specific functions
 */
#include <math.h>




typedef struct s_cartesian_vector {
    double x;
    double y;
    double z;
} t_cartesian_vector;
// special case for point    coordinates
typedef struct s_spherical_vector {
    double radius;
    double theta;
    double phi;
} t_spherical_vector;


// Function to calculate the length of a vector
double vector_length(const t_cartesian_vector* vector)
{
    return sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
}


// Function to normalize a vector
void vector_normalize(t_cartesian_vector* vector)
{
    double length = vector_length(vector);
    if (length != 0) {
        vector->x /= length;
        vector->y /= length;
        vector->z /= length;
    }
}


// Function to calculate the dot product of two vectors


double vector_dot_product(const t_cartesian_vector* vector1, const t_cartesian_vector* vector2)
{
    return vector1->x * vector2->x + vector1->y * vector2->y + vector1->z * vector2->z;
}

// add a vector to the cartesian
void vector_add(t_cartesian_vector* result, const t_cartesian_vector* vector1, const t_cartesian_vector* vector2)
{
    result->x = vector1->x + vector2->x;
    result->y = vector1->y + vector2->y;
    result->z = vector1->z + vector2->z;
}

// transform vector from cartesian to spherical


void vector_cartesian_to_spherical(const t_cartesian_vector* vector, t_spherical_vector* spherical)
{
    spherical->radius = sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
    spherical->theta = atan2(sqrt(vector->x * vector->x + vector->y * vector->y), vector->z);
    spherical->phi = atan2(vector->y, vector->x);
}



// transform vector from spherical to cartesian

void vector_spherical_to_cartesian(const t_spherical_vector* spherical, t_cartesian_vector* cartesian)
{
    cartesian->x = spherical->radius * sin(spherical->theta) * cos(spherical->phi);
    cartesian->y = spherical->radius * sin(spherical->theta) * sin(spherical->phi);
    cartesian->z = spherical->radius * cos(spherical->theta);
}


// Function to calculate the cross product of two vectors

void vector_cross_product(t_cartesian_vector* result, const t_cartesian_vector* vector1, const t_cartesian_vector* vector2)
{
    result->x = vector1->y * vector2->z - vector1->z * vector2->y;
    result->y = vector1->z * vector2->x - vector1->x * vector2->z;
    result->z = vector1->x * vector2->y - vector1->y * vector2->x;
}


// Function to calculate the angle between two vectors in degrees

double vector_angle_between(const t_cartesian_vector* vector1, const t_cartesian_vector* vector2)
{
    double dot_product = vector_dot_product(vector1, vector2);
    double magnitude_product = vector_length(vector1) * vector_length(vector2);

    if (magnitude_product != 0) {
        return acos(dot_product / magnitude_product) * 180 / M_PI;
    } else {
        return 0;
    }
}

