#include "../../include/miniRT.h"

static float    compute_cone_body_intersection(t_ray *r, t_cone *n)
{
	t_vector    co;

    float (t2), (a), (b), (c), (d), (x), (e), (t1);
    co = vector_subtract(r->origin, n->center);
    t2 = (n->diameter / n->height) * (n->diameter / n->height) / 4.0f;
    x = vector_dot_product(r->direction, n->axis);
    e = vector_dot_product(co, n->axis);
    
    a = vector_dot_product(r->direction, r->direction) - (1.0f + t2) * x * x;
    b = 2.0f * (vector_dot_product(r->direction, co) - (1.0f + t2) * x * e);
    c = vector_dot_product(co, co) - (1.0f + t2) * e * e;
    d = b * b - 4.0f * a * c;
    if (d < 0 || fabs(a) < 1e-6)
        return (INFINITY);
    d = sqrt(d);
    t1 = (-b - d) / (2.0f * a);
    if (t1 < 1e-6)
        t1 = (-b + d) / (2.0f * a);
    if (t1 < 1e-6)
        return (INFINITY);
    return (t1);
}

static float    compute_base_cap_intersection(t_ray *r, t_cone *c)
{
	float   t1;
	float   t2;
	t_plane c_base;
	t_point hit;

	c_base.color = c->color;
	c_base.normal = c->axis;
	c_base.point = vector_add(c->center, vector_multiply(c->axis, c->height));
	t1 = get_plane_distance(r, &c_base);
	hit = vector_add(r->origin, vector_multiply(r->direction, t1));
	t2 = vector_magnitude(vector_subtract(c_base.point, hit));
	if (t2 <= c->diameter / 2)
		return (t1);
    return (INFINITY);
}

float   get_cone_distance(t_ray *ray, t_cone *cone)
{
    float   t_body;
    float   t_cap;

    if (!cone->enable_intersection)
        return (INFINITY);
    t_body = compute_cone_body_intersection(ray, cone);
    t_cap = compute_base_cap_intersection(ray, cone);
    return (fmin(t_body, t_cap));
}

t_vector    calculate_cone_normal(t_cone *c, t_point hit)
{
    float (h), (c_angle);
    t_vector (hp), (axis_point), (r), (n);
    hp = vector_subtract(hit, c->center);
    h = vector_dot_product(vector_negate(c->axis), vector_subtract(
            hp, vector_multiply(c->axis, c->height)));
    if (fabs(h) < 1e-5)
        return (c->axis);
    axis_point = vector_multiply(c->axis, h);
    r = vector_subtract(hp, axis_point);
    if (vector_length(r) < 1e-6)
    {
        c_angle = atan2(c->diameter / 2.0f, c->height);
        return (vector_normalize((t_vector){
            c->axis.x * tan(c_angle),
            c->axis.y * tan(c_angle),
            1.0f
        }));
    }
    n = vector_normalize(vector_subtract(r,
        vector_multiply(c->axis, vector_dot_product(r, c->axis))));
    return (n);
}
