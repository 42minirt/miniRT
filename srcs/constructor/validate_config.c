#include "minirt.h"

static bool	is_vec_in_normal_range(t_vec vec)
{
	const double x = vec.x;
	const double y = vec.y;
	const double z = vec.z;

	return ((-1.0 <= x && x <= 1.0) \
	&& (-1.0 <= y && y <= 1.0) \
	&& (-1.0 <= z && z <= 1.0));
}

static bool is_color_in_range(t_color color)
{
	const double	r = color.r;
	const double	g = color.g;
	const double	b = color.b;

	return ((0.0 <= r && r <= 255.0) \
	&& (0.0 <= g && g <= 255.0) \
	&& (0.0 <= b && b <= 255.0));
}

static bool is_ratio_in_range(double ratio)
{
	return (0.0 <= ratio && ratio <= 1.0);
}

static bool is_angle_in_range(double ratio)
{
	return (0.0 <= ratio && ratio <= 180.0);
}

t_parse_res	validate_ambient_info(t_scene_info *scene)
{
	if (!is_ratio_in_range(scene->brightness))
	{
		printf("   [DEBUG] ambient NG :: brightness out of range\n");
		return (ERROR_OUT_OF_RANGE);
	}
	if (!is_color_in_range(scene->ambient_color))
	{
		printf("   [DEBUG] ambient NG :: color out of range\n");
		return (ERROR_OUT_OF_RANGE);
	}
	return (PASS);
}

t_parse_res	validate_lights_info(t_scene_info *scene)
{
	t_list	*node;
	t_light	*light;

	node = scene->lights;
	while (node)
	{
		light = node->content;
		if (!is_ratio_in_range(light->brightness))
			return (ERROR_OUT_OF_RANGE);
		if (!is_color_in_range(light->light_color))
			return (ERROR_OUT_OF_RANGE);
		if (light->type == LT_POINT)
		{
			if (!is_angle_in_range(light->sl_angle))
				return (ERROR_OUT_OF_RANGE);
		}
		node = node->next;
	}
	return (PASS);
}

t_parse_res	validate_sphere(t_sphere *sphere)
{
	if (sphere->diameter <= 0.0)
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

t_parse_res	validate_plane(t_plane *plane)
{
	if (!is_vec_in_normal_range(plane->normal))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

t_parse_res	validate_cylinder(t_cylinder *cylinder)
{
	if (!is_vec_in_normal_range(cylinder->axis))
		return (ERROR_OUT_OF_RANGE);
	if (cylinder->diameter <= 0.0)
		return (ERROR_OUT_OF_RANGE);
	if (cylinder->height <= 0.0)
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

t_parse_res	validate_corn(t_corn *corn)
{
	if (!is_vec_in_normal_range(corn->axis))
		return (ERROR_OUT_OF_RANGE);
	if (corn->diameter <= 0.0)
		return (ERROR_OUT_OF_RANGE);
	if (corn->height <= 0.0)
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

t_parse_res	validate_obj_shape(t_obj *obj)
{
	if (obj->type == BALL)
		return (validate_sphere(obj->shape_data->sphere));
	if (obj->type == PLANE)
		return (validate_plane(obj->shape_data->plane));
	if (obj->type == CYLINDER)
		return (validate_cylinder(obj->shape_data->cylinder));
	if (obj->type == CORN)
		return (validate_corn(obj->shape_data->corn));
	return (ERROR_INVALID_TYPE);
}

t_parse_res	validate_obj_color(t_obj *obj)
{
	if (!is_color_in_range(obj->obj_color->kd))
		return (ERROR_OUT_OF_RANGE);
	if (obj->obj_color->is_checker \
	&& !is_color_in_range(obj->obj_color->checker_color))
		return (ERROR_OUT_OF_RANGE);
	return (PASS);
}

t_parse_res	validate_objects_info(t_scene_info *scene)
{
	t_list		*node;
	t_obj 		*obj;
	t_parse_res	res;

	node = scene->objs;
	while (node)
	{
		obj = node->content;
		res = validate_obj_shape(obj);
		if (res != PASS)
			return (res);
		res = validate_obj_color(obj);
		if (res != PASS)
			return (res);
		node = node->next;
	}
	return (PASS);
}

t_parse_res	validate_scene(t_scene_info *scene)
{
	t_parse_res	res;

	res = validate_ambient_info(scene);
	if (res != PASS)
		return (res);
	res = validate_lights_info(scene);
	if (res != PASS)
		return (res);
	res = validate_objects_info(scene);
	return (res);
}

t_parse_res	validate_camera(t_camera_info *camera)
{

}

