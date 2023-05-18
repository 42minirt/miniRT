#include "minirt.h"

bool	is_bump_data_exists(t_obj_color obj_color)
{
	return (obj_color.bump_data.data != NULL);
}

bool	is_image_data_exists(t_obj_color obj_color)
{
	return (obj_color.texture_data.data != NULL);
}

t_vec	get_bump_normal(t_intersection_point *its_p)
{

}

t_vec	get_normal(t_intersection_point *its_p)
{
	if (is_bump_data_exists(its_p->obj->obj_color))
		return (get_bump_normal(its_p));
	return (its_p->normal);
}

bool	is_obj_exists_extension_of_ray(t_scene_info *scene, t_diffuse_param p)
{

}

bool	is_in_range_spotlight(t_diffuse_param p)
{
	double	angle_pos2light;

	angle_pos2light = acos(dot(p.vec_light2pos, p.light->sl_dir)) * 180.0 / (2.0 * M_PI);
	if (angle_pos2light < 0)
		angle_pos2light *= -1.0; //todo: check
	return (angle_pos2light <= p.light->sl_angle);
}

t_color	get_diffuse_color(t_diffuse_param p)
{
	t_color	ret_color;

	ret_color = init_color(0.0, 0.0, 0.0);
	if (is_image_data_exists(p.its_p->obj->obj_color))
		return (ret_color);
	if (p.dot_n_pos2light <= 0.0)
		return (ret_color);

	if (p.light->type == LT_POINT && !is_in_range_spotlight(p))
		return (ret_color);
	ret_color = color_k1c1_k2c2(1.0, p.its_p->obj->obj_color.kd, \
							p.dot_n_pos2light, p.light->light_color);
	return (ret_color);
}

t_color get_checker_color(t_diffuse_param p)
{

}

t_color	get_image_color(t_diffuse_param p)
{

}

void	calc_diffuse_param(t_diffuse_param *p, t_intersection_point *its_p, t_ray ray, t_light *light)
{
	p->ray = ray;
	p->vec_normal = get_normal(its_p);
	p->vec_pos2light = sub(light->point, its_p->position);
	p->vec_pos2light = norm_vec(p->vec_pos2light);
	p->vec_light2pos = inverse(p->vec_pos2light);
	p->vec_specular = norm_vec(p->vec_light2pos);

	p->dot_n_pos2light = dot(its_p->normal, p->vec_pos2light);
}

t_color	calc_diffuse_ref_by_light(t_scene_info *scene, \
								t_intersection_point *its_p, \
								t_ray eye2screen, t_light *light)
{
	t_color			ret_color;
	t_diffuse_param	p;

	calc_diffuse_param(&p);
	ret_color = init_color(0.0, 0.0, 0.0);
	if (is_obj_exists_extension_of_ray(scene, p))
		return (ret_color);
	ret_color = color_add(ret_color, get_diffuse_color(p));
	ret_color = color_add(ret_color, get_checker_color(p));
	ret_color = color_add(ret_color, get_image_color(p));
	return (ret_color);
}

t_color	calc_diffuse_reflection(t_scene_info *scene, \
							t_intersection_point *its_p, t_ray eye2screen)
{
	t_color	ret_color;
	t_list	*node;
	t_light	*light;

	ret_color = init_color(0.0, 0.0, 0.0);
	if (its_p->obj->obj_color.is_perfect_ref)
		return (ret_color);
	node = scene->lights;
	while (node)
	{
		light = node->content;
		ret_color = color_add(ret_color, \
		calc_diffuse_ref_by_light(scene, its_p, eye2screen, light));
		node = node->next;
	}
	return (ret_color);
}