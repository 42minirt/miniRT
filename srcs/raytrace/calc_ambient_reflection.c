/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ambient_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:53:39 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:11:32 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	calc_ambient_reflection(t_scene_info *scene, t_intersection_point its_p)
{
	t_color	ret;

	ret = color_mul_k1c1k2c2(scene->ambient_color, scene->brightness, \
							its_p.obj->obj_color.ka, its_p.obj->obj_color.ia);
	return (ret);
}
