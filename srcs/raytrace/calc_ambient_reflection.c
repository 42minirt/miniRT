/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ambient_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:53:39 by takira            #+#    #+#             */
/*   Updated: 2023/05/18 00:01:09 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	calc_ambient_reflection(t_scene_info *scene, t_intersection_point its_p)
{
	t_color	ret;

	ret = color_mul_k1c1k2c2(1.0, scene->ambient_color, its_p.obj->obj_color.ia, its_p.obj->obj_color.ka);
	return (ret);
}
