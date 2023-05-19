/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects_setting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
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
	obj->obj_color.ka = init_color(255, 255, 255); // tmp
	obj->obj_color.ks = init_color(255, 255, 255); // tmp
	obj->obj_color.kf = init_color(255, 255, 255); // tmp
	obj->obj_color.ia = 0.5; // tmp
	obj->obj_color.id = 1.0; // tmp
	obj->obj_color.is = 1.0; // tmp
	return (obj);
}

// #Sphere     center_point(xyz)                           diameter            RGB[0,255]  <bonus_options>
// #Plane      point(xyz)           normalized_vec[-1,1]                       RGB[0,255]  <bonus_options>
// #Cylinder   bottom_center(xyz)   normalized_vec[-1,1]   diameter   height   RGB[0,255]  <bonus_options>
// #Corn       bottom_center(xyz)   normalized_vec[-1,1]   diameter   height   RGB[0,255]  <bonus_options>

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
