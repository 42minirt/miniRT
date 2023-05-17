#include "minirt.h"

static void	update_ambient_color(t_scene_info *scene)
{
	scene->ambient_color = \
	color_k1c1(scene->brightness / 255.0, scene->ambient_color);
}

static void	update_lights(t_scene_info *scene)
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

static void	update_shape_info(t_obj *obj)
{
	if (obj->type == PLANE)
		return ;
	if (obj->type == BALL)
		obj->shape_data.sphere.radius = obj->shape_data.sphere.diameter / 2.0;
	else if (obj->type == CYLINDER)
		obj->shape_data.cylinder.radius = \
		obj->shape_data.cylinder.diameter / 2.0;
	else
	{
		obj->shape_data.corn.radius = obj->shape_data.corn.diameter / 2.0;
		obj->shape_data.corn.origin = \
		add(obj->shape_data.corn.bottom_center,\
		k_vec(obj->shape_data.corn.height, obj->shape_data.corn.axis));
	}
}

static void	update_objs(t_scene_info *scene)
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
		update_shape_info(obj);
		node = node->next;
	}
}

void	update_scene(t_scene_info *scene)
{
	update_ambient_color(scene);
	update_lights(scene);
	update_objs(scene);
}
