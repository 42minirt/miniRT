#include "minirt.h"

static t_light_type	get_light_type(t_identifier id)
{
	if (id == id_point_light)
		return (LT_POINT);
	return (LT_SPOT);
}

// L   XYZ   brightness_ratio[0,1]   RGB[0,255]
// sl  XYZ   brightness_ratio[0,1]   RGB[0,255]   angle[0,180]
t_parse_res	get_light_detail(const char *line, int id_no, t_light *light)
{
	size_t	idx;

	light->type = get_light_type(id_no);
	idx = 0;
	if (parsing_vec(line, &light->point, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_double_num(line, &light->brightness, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (parsing_color(line, &light->light_color, &idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	if (light->type == LT_SPOT)
		if (parsing_double_num(line, &light->sl_angle, &idx) == FAILURE)
			return (ERROR_INVALID_ARG);
	if (line[idx])
		return (ERROR_TOO_MANY_INFO);
	return (PASS);
}

t_parse_res	get_lights_setting(const char *line, t_scene_info *scene, int id_no)
{
	t_list			*new_list;
	t_light			*light;
	t_parse_res		parse_result;

	light = (t_light *)ft_calloc(sizeof(t_light), 1);
	if (!light)
		return (ERROR_FATAL);
	parse_result = get_light_detail(line, id_no, light);
	if (parse_result != PASS)
	{
		free(light);
		return (parse_result);
	}
	new_list = ft_lstnew(light);
	if (!new_list)
	{
		free(light);
		return (ERROR_FATAL);
	}
	ft_lstadd_back(&scene->lights, new_list);
	return (PASS);

}
