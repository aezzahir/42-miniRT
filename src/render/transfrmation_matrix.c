// Matrix structure to hold 4x4 transformation matrix
typedef struct s_matrix4 {
    float m[4][4];
} t_matrix4;

// Function to create camera-to-world transformation matrix
t_matrix4 get_camera_to_world_matrix(t_camera *camera) {
    t_matrix4 matrix;
    t_vector right = camera->right;
    t_vector up = camera->up;
    t_vector forward = camera->forward;
    t_vector position = camera->position;

    // Right vector forms the first row (camera's x-axis)
    matrix.m[0][0] = right.x;
    matrix.m[0][1] = right.y;
    matrix.m[0][2] = right.z;
    matrix.m[0][3] = position.x;

    // Up vector forms the second row (camera's y-axis)
    matrix.m[1][0] = up.x;
    matrix.m[1][1] = up.y;
    matrix.m[1][2] = up.z;
    matrix.m[1][3] = position.y;

    // Forward vector forms the third row (camera's z-axis)
    matrix.m[2][0] = forward.x;
    matrix.m[2][1] = forward.y;
    matrix.m[2][2] = forward.z;
    matrix.m[2][3] = position.z;

    // Homogeneous coordinate row
    matrix.m[3][0] = 0.0f;
    matrix.m[3][1] = 0.0f;
    matrix.m[3][2] = 0.0f;
    matrix.m[3][3] = 1.0f;

    return matrix;
}

// Function to create world-to-camera transformation matrix (inverse of camera-to-world)
t_matrix4 get_world_to_camera_matrix(t_camera *camera) {
    t_matrix4 matrix;
    t_vector right = camera->right;
    t_vector up = camera->up;
    t_vector forward = camera->forward;
    t_vector position = camera->position;

    // Transpose of rotation matrix (inverse of orthogonal matrix)
    matrix.m[0][0] = right.x;   matrix.m[0][1] = up.x;   matrix.m[0][2] = forward.x;
    matrix.m[1][0] = right.y;   matrix.m[1][1] = up.y;   matrix.m[1][2] = forward.y;
    matrix.m[2][0] = right.z;   matrix.m[2][1] = up.z;   matrix.m[2][2] = forward.z;

    // Translation part (negative position multiplied by rotation matrix)
    matrix.m[0][3] = -(right.x * position.x + right.y * position.y + right.z * position.z);
    matrix.m[1][3] = -(up.x * position.x + up.y * position.y + up.z * position.z);
    matrix.m[2][3] = -(forward.x * position.x + forward.y * position.y + forward.z * position.z);

    // Homogeneous coordinate row
    matrix.m[3][0] = 0.0f;
    matrix.m[3][1] = 0.0f;
    matrix.m[3][2] = 0.0f;
    matrix.m[3][3] = 1.0f;

    return matrix;
}

// Utility function to transform a point using a matrix
t_vector transform_point(t_matrix4 matrix, t_vector point) {
    t_vector result;
    float w;

    result.x = matrix.m[0][0] * point.x + matrix.m[0][1] * point.y + 
               matrix.m[0][2] * point.z + matrix.m[0][3];
    result.y = matrix.m[1][0] * point.x + matrix.m[1][1] * point.y + 
               matrix.m[1][2] * point.z + matrix.m[1][3];
    result.z = matrix.m[2][0] * point.x + matrix.m[2][1] * point.y + 
               matrix.m[2][2] * point.z + matrix.m[2][3];
    w = matrix.m[3][0] * point.x + matrix.m[3][1] * point.y + 
        matrix.m[3][2] * point.z + matrix.m[3][3];

    // Perform perspective division if w != 1
    if (w != 1.0f && w != 0.0f) {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }

    return result;
}

// Utility function to transform a vector (direction) using a matrix
t_vector transform_vector(t_matrix4 matrix, t_vector vector) {
    t_vector result;

    // Only apply rotation, ignore translation
    result.x = matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y + 
               matrix.m[0][2] * vector.z;
    result.y = matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y + 
               matrix.m[1][2] * vector.z;
    result.z = matrix.m[2][0] * vector.x + matrix.m[2][1] * vector.y + 
               matrix.m[2][2] * vector.z;

    return result;
}