
#include "../../include/miniRT.h"
#include <fcntl.h>
#include <unistd.h>

#include <ctype.h>

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[10];
	char		line[70000];
	static int	buffer_readed;
	static int 	buffer_pos;
	int			i;

	i = 0;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_readed)
		{
			buffer_readed = read(fd, buffer, 10);
			buffer_pos = 0;
			if (buffer_readed <= 0)
				break ;
		}
		line[i++] = buffer[buffer_pos++];
		if (line[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
		free(str);
	str = NULL;
}



double ft_atof(const char *str)
{
    double result = 0.0;
    double factor = 1.0;
    int sign = 1;
    int seen_dot = 0;

    // Skip whitespace
    while (isspace(*str)) // TODO: forbiden Function 
        str++;

    // Handle sign
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    // Process digits
    while (*str)
    {
        if (*str == '.')
        {
            if (seen_dot)
                break;  // Second dot, stop parsing
            seen_dot = 1;
        }
        else if (ft_isdigit(*str))
        {
            if (seen_dot)
            {
                factor /= 10.0;
                result = result + (*str - '0') * factor;
            }
            else
            {
                result = result * 10.0 + (*str - '0');
            }
        }
        else
        {
            break;  // Non-digit character, stop parsing
        }
        str++;
    }

    return sign * result;
}

static int parse_color(char *str, t_color *color)
{
    char **parts = ft_split(str, ',');
    if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
    {
        ft_free_split(parts);
        return (0);
    }
    color->r = ft_atoi(parts[0]);
    color->g = ft_atoi(parts[1]);
    color->b = ft_atoi(parts[2]);
    ft_free_split(parts);
    if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 || color->b < 0 || color->b > 255)
        return (0);
    return (1);
}

static int parse_vector(char *str, t_vector *vec)
{
    char **parts = ft_split(str, ',');
    if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
    {
        ft_free_split(parts);
        return (0);
    }
    vec->x = ft_atof(parts[0]);
    vec->y = ft_atof(parts[1]);
    vec->z = ft_atof(parts[2]);
    ft_free_split(parts);
    return (1);
}

static int parse_ambient(char *line, t_scene *scene)
{
    char **parts = ft_split(line, ' ');
    if (!parts || !parts[1] || !parts[2] || parts[3])
    {
        ft_free_split(parts);
        return (0);
    }
    scene->ambient.ratio = ft_atof(parts[1]);
    if (scene->ambient.ratio < 0 || scene->ambient.ratio > 1 || !parse_color(parts[2], &scene->ambient.color))
    {
        ft_free_split(parts);
        return (0);
    }
    ft_free_split(parts);
    return (1);
}

static int parse_camera(char *line, t_scene *scene)
{
    char **parts = ft_split(line, ' ');
    if (!parts || !parts[1] || !parts[2] || !parts[3] || parts[4])
    {
        ft_free_split(parts);
        return (0);
    }
    if (!parse_vector(parts[1], &scene->camera.position) ||
        !parse_vector(parts[2], &scene->camera.orientation))
    {
        ft_free_split(parts);
        return (0);
    }
    scene->camera.fov = ft_atoi(parts[3]);
    if (scene->camera.fov < 0 || scene->camera.fov > 180)
    {
        ft_free_split(parts);
        return (0);
    }
    ft_free_split(parts);
    return (1);
}

static int parse_light(char *line, t_scene *scene)
{
    char **parts = ft_split(line, ' ');
    if (!parts || !parts[1] || !parts[2] || !parts[3] || parts[4])
    {
        ft_free_split(parts);
        return (0);
    }
    if (!parse_vector(parts[1], &scene->light.position))
    {
        ft_free_split(parts);
        return (0);
    }
    scene->light.brightness = ft_atof(parts[2]);
    if (scene->light.brightness < 0 || scene->light.brightness > 1 || !parse_color(parts[3], &scene->light.color))
    {
        ft_free_split(parts);
        return (0);
    }
    ft_free_split(parts);
    return (1);
}

static int parse_sphere(char *line, t_scene *scene)
{
    t_sphere *sphere = malloc(sizeof(t_sphere));
    char **parts = ft_split(line, ' ');
    if (!parts || !parts[1] || !parts[2] || !parts[3] || parts[4])
    {
        free(sphere);
        ft_free_split(parts);
        return (0);
    }
    if (!parse_vector(parts[1], &sphere->center))
    {
        free(sphere);
        ft_free_split(parts);
        return (0);
    }
    sphere->diameter = ft_atof(parts[2]);
    if (sphere->diameter <= 0 || !parse_color(parts[3], &sphere->color))
    {
        free(sphere);
        ft_free_split(parts);
        return (0);
    }
    ft_lstadd_back(scene->spheres, ft_lstnew(sphere));
    ft_free_split(parts);
    sphere->enable_intersection = 1;
    return (1);
}

static int parse_plane(char *line, t_scene *scene)
{
    t_plane *plane = malloc(sizeof(t_plane));
    char **parts = ft_split(line, ' ');
    if (!parts || !parts[1] || !parts[2] || !parts[3] || parts[4])
    {
        free(plane);
        ft_free_split(parts);
        return (0);
    }
    if (!parse_vector(parts[1], &plane->point) || !parse_vector(parts[2], &plane->normal))
    {
        free(plane);
        ft_free_split(parts);
        return (0);
    }
    if (!parse_color(parts[3], &plane->color))
    {
        free(plane);
        ft_free_split(parts);
        return (0);
    }
    ft_lstadd_back(scene->planes, ft_lstnew(plane));
    ft_free_split(parts);
    plane->enable_intersection = 1;
    return (1);
}

static int parse_cylinder(char *line, t_scene *scene)
{
    t_cylinder *cylinder = malloc(sizeof(t_cylinder));
    char **parts = ft_split(line, ' ');
    if (!parts || !parts[1] || !parts[2] || !parts[3] || !parts[4] || !parts[5] || parts[6])
    {
        free(cylinder);
        ft_free_split(parts);
        return (0);
    }
    if (!parse_vector(parts[1], &cylinder->center) || !parse_vector(parts[2], &cylinder->axis))
    {
        free(cylinder);
        ft_free_split(parts);
        return (0);
    }
    cylinder->diameter = ft_atof(parts[3]);
    cylinder->height = ft_atof(parts[4]);
    if (cylinder->diameter <= 0 || cylinder->height <= 0 || !parse_color(parts[5], &cylinder->color))
    {
        free(cylinder);
        ft_free_split(parts);
        return (0);
    }
    ft_lstadd_back(scene->cylinders, ft_lstnew(cylinder));
    ft_free_split(parts);
    cylinder->enable_intersection = 1;
    return (1);
}
static int parse_cone(char *line, t_scene *scene)
{
    t_cone *cone = malloc(sizeof(t_cone));
    char **parts = ft_split(line, ' ');
    if (!parts || !parts[1] || !parts[2] || !parts[3] || !parts[4] || !parts[5] || parts[6])
    {
        free(cone);
        ft_free_split(parts);
        return (0);
    }
    if (!parse_vector(parts[1], &cone->center) || !parse_vector(parts[2], &cone->axis))
    {
        free(cone);
        ft_free_split(parts);
        return (0);
    }
    cone->diameter = ft_atof(parts[3]);
    cone->height = ft_atof(parts[4]);
    if (cone->diameter <= 0 || cone->height <= 0 || !parse_color(parts[5], &cone->color))
    {
        free(cone);
        ft_free_split(parts);
        return (0);
    }
    ft_lstadd_back(scene->cones, ft_lstnew(cone));
    ft_free_split(parts);
    cone->enable_intersection = 1;
    return (1);
}
int parse_scene(char *filename, t_scene *scene)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);

    char *line;
    while ((line = get_next_line(fd)))
    {
        if (ft_strncmp(line, "A ", 2) == 0 && !parse_ambient(line, scene))
            return (0);
        else if (ft_strncmp(line, "C ", 2) == 0 && !parse_camera(line, scene))
            return (0);
        else if (ft_strncmp(line, "L ", 2) == 0 && !parse_light(line, scene))
            return (0);
        else if (ft_strncmp(line, "sp ", 3) == 0 && !parse_sphere(line, scene))
            return (0);
        else if (ft_strncmp(line, "pl ", 3) == 0 && !parse_plane(line, scene))
            return (0);
        else if (ft_strncmp(line, "cy ", 3) == 0 && !parse_cylinder(line, scene))
            return (0);
         else if (ft_strncmp(line, "co ", 3) == 0 && !parse_cone(line, scene))
            return (0);
        free(line);
    }
    close(fd);
    return (1);
}