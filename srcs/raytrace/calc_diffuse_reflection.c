/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_diffuse_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:39:36 by takira            #+#    #+#             */
/*   Updated: 2023/06/01 00:06:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	is_in_range_spotlight(t_diffuse_param p)
{
	double	angle_pos2light;

	angle_pos2light \
	= acos(dot(p.unit_light2pos, p.light->sl_dir)) * (180.0 / (2.0 * M_PI));
	if (angle_pos2light < 0)
		angle_pos2light *= -1.0; //todo: check
	return (angle_pos2light <= p.light->sl_angle_half);
}

static t_color	get_diffuse_ref_color(t_diffuse_param p, t_color kd)
{
	t_color	ret_color;

	if (p.dot_n_unit_pos2light <= 0.0)
	{
		return (init_color(0.0, 0.0, 0.0));
		p.dot_n_unit_pos2light = ch_degrrralation(&p.its_p, &p.unit_pos2light, &p.ray.pos);
		if (p.dot_n_unit_pos2light - 0.0 < EPSIRON)
			return (init_color(0.0, 0.0, 0.0));
	}
	if (is_equal_strings(p.light->id_type, ID_SPOTLIGHT) \
	&& !is_in_range_spotlight(p))
		return (init_color(0.0, 0.0, 0.0));
	ret_color = color_k1c1k2c2(p.its_p.obj->obj_color.id, kd, \
							p.dot_n_unit_pos2light, p.light->light_color);
	return (ret_color);
}

static t_color	calc_diffuse_ref_by_light(t_scene_info *scene, \
								t_intersection_point its_p, \
								t_ray eye2screen, t_light *light)
{
	t_color			ret_color;
	t_color			kd;
	t_diffuse_param	p;

	p = calc_diffuse_param(&its_p, &eye2screen, light);
	ret_color = init_color(0.0, 0.0, 0.0);
	if (is_obj_exists_between_itspos_and_light(scene, p))
		return (ret_color);
	kd = p.its_p.obj->obj_color.kd;
	if (is_obj_checker(its_p.obj->obj_color))
		kd = get_itspos_checker_color(p);
	else if (is_obj_image_texture(its_p.obj->obj_color))
		kd = get_itspos_image_texture_color(p);
	ret_color = get_diffuse_ref_color(p, kd);
	return (ret_color);
}

t_color	calc_diffuse_reflection(t_scene_info *scene, \
							t_intersection_point its_p, t_ray eye2screen)
{
	t_color	ret_color;
	t_list	*node;
	t_light	*light;

	ret_color = init_color(0.0, 0.0, 0.0);
	if (is_obj_perfect_ref(its_p.obj->obj_color))
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
