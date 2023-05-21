/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ambient_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:53:39 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:19:55 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	calc_ambient_reflection(t_scene_info *scene, t_intersection_point its_p)
{
	t_color	ret;

	ret = color_mul_k1c1k2c2(scene->brightness, scene->ambient_color, \
							its_p.obj->obj_color.ia, its_p.obj->obj_color.ka);
	return (ret);
}
