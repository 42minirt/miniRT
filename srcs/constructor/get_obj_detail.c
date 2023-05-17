#include "minirt.h"

// sp   XYZ                    diameter            RGB[0,255]   <OPTION>
static t_parse_res	get_sphere_detail(const char *line, t_obj *obj)
{
	size_t		idx;

	obj->type = BALL;
	idx = 0;
	if (parsing_vec(line, &obj->shape_data.sphere.center, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parse_double(line, &obj->shape_data.sphere.diameter, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_color(line, &obj->obj_color.kd, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (!line[idx])
		return (PASS);
	if (get_bonus_detail(line, obj, &idx) != PASS)
		return (ERROR_INVALID_ARG);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}

// pl   XYZ   norm_vec[-1,1]                       RGB[0,255]   <OPTION>
static t_parse_res	get_plane_detail(const char *line, t_obj *obj)
{
	size_t		idx;

	obj->type = PLANE;
	idx = 0;
	if (parsing_vec(line, &obj->shape_data.plane.center, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_vec(line, &obj->shape_data.plane.normal, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_color(line, &obj->obj_color.kd, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (!line[idx])
		return (PASS);
	if (get_bonus_detail(line, obj, &idx) != PASS)
		return (ERROR_INVALID_ARG);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}

// cy   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION>
static t_parse_res	get_cylinder_detail(const char *line, t_obj *obj)
{
	size_t		idx;

	obj->type = CYLINDER;
	idx = 0;
	if (parsing_vec(line, &obj->shape_data.cylinder.bottom_center, &idx) \
		== FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_vec(line, &obj->shape_data.cylinder.axis, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parse_double(line, &obj->shape_data.cylinder.diameter, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parse_double(line, &obj->shape_data.cylinder.height, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_color(line, &obj->obj_color.kd, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (!line[idx])
		return (PASS);
	if (get_bonus_detail(line, obj, &idx) != PASS)
		return (ERROR_INVALID_ARG);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}

// co   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION>
static t_parse_res	get_corn_detail(const char *line, t_obj *obj)
{
	size_t		idx;

	obj->type = CORN;
	idx = 0;
	if (parsing_vec(line, &obj->shape_data.corn.bottom_center, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_vec(line, &obj->shape_data.corn.axis, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parse_double(line, &obj->shape_data.corn.diameter, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parse_double(line, &obj->shape_data.corn.height, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_color(line, &obj->obj_color.kd, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (!line[idx])
		return (PASS);
	if (get_bonus_detail(line, obj, &idx) != PASS)
		return (ERROR_INVALID_ARG);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}

t_parse_res	get_obj_detail(const char *line, int id_no, t_obj *obj)
{
	t_parse_res	res;

	res = ERROR_FATAL;
	if (id_no == id_sphere)
		res = get_sphere_detail(line, obj);
	else if (id_no == id_plane)
		res = get_plane_detail(line, obj);
	else if (id_no == id_cylinder)
		res = get_cylinder_detail(line, obj);
	else if (id_no == id_corn)
		res = get_corn_detail(line, obj);
	return (res);
}
