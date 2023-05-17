#include "minirt.h"

t_vec	get_bump_normal(t_intersection_point *its_p)
{

}

t_color	calc_diffuse_each_light(t_scene_info *scene, \
								t_intersection_point *its_p, \
								t_ray eye2screen, t_light *light)
{
	t_color	color;
	t_vec	normal;
	t_vec	pos2light;
	double	dot_n_pos2light;

	normal = its_p->normal;
	if (its_p->obj->obj_color.bump_data.data)
		normal = get_bump_normal(its_p);
	pos2light = sub(light->point, its_p->position);
	pos2light = norm_vec(pos2light);
	dot_n_pos2light = dot(its_p->normal, pos2light); // dot_n_pos2_light <= 0 ?
	color = init_color(0.0, 0.0, 0.0);
	if (is_obj_exeists_extension_of_ray(scene, its_p, pos2light, light))
		return (color);
	color = color_add(color, diffuse_color());
	color = color_add(color, checker_color());
	color = color_add(color, image_color());
	return (color);
}

t_color	calc_diffuse_reflection(t_scene_info *scene, \
							t_intersection_point *its_p, t_ray eye2screen)
{
	t_color	color;
	t_list	*light_node;

	color = init_color(0.0, 0.0, 0.0);
	if (its_p->obj->obj_color.is_perfect_ref)
		return (color);
	light_node = scene->lights;
	while (light_node)
	{
		color = color_add(color, \
			calc_diffuse_each_light(scene, its_p, eye2screen, light_node->content));
		light_node = light_node->next;
	}
	return (color);
}