#include "minirt.h"

void	init_obj(t_obj *obj)
{
	obj->obj_color->is_perfect_ref = false;
	obj->obj_color->is_checker = false;
	obj->obj_color->texture_data = NULL;
	obj->obj_color->bump_data = NULL;

	obj->obj_color->shininess = 10.0;	// fix ?
	obj->obj_color->ks = init_color(1.0, 1.0, 1.0);
}

// sp   XYZ                    diameter            RGB[0,255]   <OPTION>
// pl   XYZ   norm_vec[-1,1]                       RGB[0,255]   <OPTION>
// cy   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION>
// co   XYZ   norm_vec[-1,1]   diameter   height   RGB[0,255]   <OPTION>

// <OPTION>
//    perfect_ref
//    checker         RGB[0,255]
//    image           "image_texture_path",   "bumpmap_path"

t_parse_res	get_objects_setting(const char *line, t_scene_info *scene, int id_no)
{
	t_parse_res	parse_result;
	t_obj		*obj;
	t_list		*new_list;

	obj = (t_obj *) ft_calloc(sizeof(t_obj), 1);
	if (!obj)
		return (FAILURE);
	init_obj(obj);
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
	printf("objs(id:%d) OK :)\n", id_no);
	return (PASS);
}