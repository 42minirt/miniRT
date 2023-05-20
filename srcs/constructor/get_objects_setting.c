/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects_setting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:29:04 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*init_obj(void)
{
	t_obj	*obj;

	obj = (t_obj *)ft_calloc(sizeof(t_obj), 1);
	if (!obj)
		return (FAILURE);
	obj->obj_color.is_perfect_ref = false;
	obj->obj_color.is_checker = false;
	obj->obj_color.is_texture = false;
	obj->obj_color.is_bump = false;
	obj->obj_color.texture_data.data = NULL;
	obj->obj_color.bump_data.data = NULL;
	obj->obj_color.shininess = 10.0; // tmp
	obj->obj_color.ka = init_color(255, 255, 255); // tmp -> 255/255=1.0
	obj->obj_color.ks = init_color(255, 255, 255); // tmp
	obj->obj_color.kf = init_color(255, 255, 255); // tmp
	obj->obj_color.ia = 0.01; // tmp 環境光の反射光の放射輝度Ra=ka*Ia, ka=ka*ia, Ia=given
	obj->obj_color.id = 1.0; // tmp
	return (obj);
}

// #Sphere     center_point(xyz)                     d       RGB[0,255]  <bonus>
// #Plane      point(xyz)           norm_vec[-1,1]           RGB[0,255]  <bonus>
// #Cylinder   bottom_center(xyz)   norm_vec[-1,1]   d   h   RGB[0,255]  <bonus>
// #Corn       bottom_center(xyz)   norm_vec[-1,1]   d   h   RGB[0,255]  <bonus>

// #bonus_options
//    < bonus id >    < parameters >
//    perfect_ref
//    checker         RGB[0,255]
//    image           "image_texture_path",   "bumpmap_path"

t_parse_res	get_objects_setting(const char *line, \
								t_scene_info *scene, int id_no)
{
	t_parse_res	parse_result;
	t_obj		*obj;
	t_list		*new_list;

	obj = init_obj();
	if (!obj)
		return (ERROR_FATAL);
	parse_result = get_obj_detail(line, id_no, obj);
	if (parse_result != PASS)
	{
		free(obj);
		return (parse_result);
	}
	new_list = ft_lstnew(obj);
	if (!new_list)
	{
		free(obj);
		return (ERROR_FATAL);
	}
	ft_lstadd_back(&scene->objs, new_list);
	return (PASS);
}
