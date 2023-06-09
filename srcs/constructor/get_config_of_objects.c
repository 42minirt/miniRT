/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_of_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_obj	*init_obj_ptr(const char *id_str)
{
	t_obj	*obj;

	obj = (t_obj *)ft_calloc(sizeof(t_obj), 1);
	if (!obj)
		return (FAILURE);
	obj->id_str = id_str;
	obj->obj_color.is_perfect_ref = false;
	obj->obj_color.is_checker = false;
	obj->obj_color.is_texture = false;
	obj->obj_color.is_bump = false;
	obj->obj_color.texture_data.data = NULL;
	obj->obj_color.bump_data.data = NULL;
	obj->obj_color.shininess = SPECULAR_SHININESS;
	obj->obj_color.ka = init_color_hex(KA_COLOR);
	obj->obj_color.ks = init_color_hex(KS_COLOR);
	obj->obj_color.kf = init_color_hex(KF_COLOR);
	obj->obj_color.ia = INTENSITY_OF_AMBIENT;
	obj->obj_color.id = INTENSITY_OF_DIFFUSE;
	return (obj);
}

static void	free_fatal_obj(t_obj *obj)
{
	free(obj->obj_color.texture_data.data);
	free(obj->obj_color.bump_data.data);
	free(obj);
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

t_parse_res	get_config_of_objects(const char *line, \
									t_scene_info *scene, \
									const char *id_str)
{
	t_parse_res	parse_result;
	t_obj		*obj;
	t_list		*new_list;

	obj = init_obj_ptr(id_str);
	if (!obj)
		return (ERROR_FATAL);
	parse_result = get_config_of_each_obj(line, obj);
	if (parse_result != PASS)
	{
		free_fatal_obj(obj);
		return (parse_result);
	}
	new_list = ft_lstnew(obj);
	if (!new_list)
	{
		free_fatal_obj(obj);
		return (ERROR_FATAL);
	}
	ft_lstadd_back(&scene->objs, new_list);
	return (PASS);
}
