/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ambient_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:53:39 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 21:29:33 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	calc_ambient_reflection(t_scene_info *scene, \
								t_intersection_point its_p)
{
	t_color	ret;
	t_color	ka;

	if (is_obj_checker(its_p.obj->obj_color))
		ka = get_itspos_checker_color(its_p);
	else if (is_obj_image_texture(its_p.obj->obj_color))
		ka = get_itspos_image_texture_color(its_p);
	else
		ka = its_p.obj->obj_color.ka;
	ret = color_k1c1k2c2(scene->brightness, scene->ambient_color, \
							its_p.obj->obj_color.ia, ka);
	return (ret);
}
