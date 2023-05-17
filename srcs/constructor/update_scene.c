#include "minirt.h"

static void	update_scene_ambient_color(t_scene_info *scene)
{
	scene->ambient_color = \
	color_k1c1(scene->brightness / 255.0, scene->ambient_color);
}

static void	update_scene_lights(t_scene_info *scene)
{
	t_list	*node;
	t_light	*light;

	node = scene->lights;
	while (node)
	{
		light = node->content;
		light->light_color = \
		color_k1c1(light->brightness / 255.0, light->light_color);
		node = node->next;
	}
}

static void	update_scene_each_obj(t_obj *obj)
{
	if (obj->type == BALL)
		update_scene_sphere_info(&obj->shape_data.sphere);
	else if (obj->type == PLANE)
		update_scene_plane_info(&obj->shape_data.plane);
	else if (obj->type == CYLINDER)
		update_scene_cylinder_info(&obj->shape_data.cylinder);
	else if (obj->type == CORN)
		update_scene_corn_info(&obj->shape_data.corn);
}

static void	update_scene_objs(t_scene_info *scene)
{
	t_list	*node;
	t_obj	*obj;

	node = scene->objs;
	while (node)
	{
		obj = node->content;
		obj->obj_color.kd = color_k1c1(1.0 / 255.0, obj->obj_color.kd);
		if (obj->obj_color.is_checker)
			obj->obj_color.checker_color = \
			color_k1c1(1.0 / 255.0, obj->obj_color.checker_color);
		update_scene_each_obj(obj);
		node = node->next;
	}
}

void	update_scene(t_scene_info *scene)
{
	update_scene_ambient_color(scene);
	update_scene_lights(scene);
	update_scene_objs(scene);
}
