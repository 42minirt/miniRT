#include "minirt.h"

static bool	is_obj_exists_extension_of_ray(t_scene_info *scene, \
											t_diffuse_param p)
{

}

static t_color	calc_diffuse_ref_by_light(t_scene_info *scene, \
								t_intersection_point *its_p, \
								t_ray eye2screen, t_light *light)
{
	t_color			ret_color;
	t_diffuse_param	p;

	calc_diffuse_param(&p, its_p, eye2screen, light);
	ret_color = init_color(0.0, 0.0, 0.0);
	if (is_obj_exists_extension_of_ray(scene, p))
		return (ret_color);
	ret_color = color_add(ret_color, get_diffuse_color(p));
	ret_color = color_add(ret_color, get_checker_color(p));
	ret_color = color_add(ret_color, get_image_color(its_p));
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
