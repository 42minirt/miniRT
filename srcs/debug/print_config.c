#include "minirt.h"

void	print_lights(t_scene_info *scene)
{
	t_list	*node;
	t_light	*light;
	t_vec	v;
	t_color	c;

	node = scene->lights;
	while (node)
	{
		light = node->content;
		v = light->point;
		c = light->light_color;
		if (light->type == LT_POINT)
			printf(" Point Light : (%03.1f, %03.1f, %03.1f),    %03.1f,    (%03.1f, %03.1f, %03.1f)\n", \
				   v.x, v.y, v.z, light->brightness, c.r, c.g, c.b);
		else
			printf(" Spot Light  : (%03.1f, %03.1f, %03.1f),    %03.1f,   %03.1f,   (%03.1f, %03.1f, %03.1f)\n", \
				   v.x, v.y, v.z, light->brightness, light->sl_angle, c.r, c.g, c.b);
		node = node->next;
	}
}

void	print_bonus(t_obj_color *o)
{
	t_color c;
	if (o->is_perfect_ref)
		printf(", perfect_ref");
	if (o->is_checker)
	{
	 	c = o->checker_color;
		printf(",   checker (%03.1f, %03.1f, %03.1f)", c.r, c.g, c.b);
	}
	if (o->texture_data)
		printf(",   img_texture");
	if (o->bump_data)
		printf(",   img_bump");
}

void	print_sphere(t_obj *obj)
{
	t_vec	pos;
	t_color	c;

	pos = obj->shape_data->sphere->center;
	c = obj->obj_color->kd;
	printf(" Sphere      : (%03.1f, %03.1f, %03.1f),    %03.1f,    (%03.1f, %03.1f, %03.1f)", \
	pos.x, pos.y, pos.z, \
	obj->shape_data->sphere->diameter, \
	c.r, c.g, c.b);
	print_bonus(obj->obj_color);
	printf("\n");
}

void	print_plane(t_obj *obj)
{
	t_vec	pos;
	t_vec	nor;
	t_color	c;

	pos = obj->shape_data->plane->center;
	nor = obj->shape_data->plane->normal;
	c = obj->obj_color->kd;

	printf(" Plane       : (%03.1f, %03.1f, %03.1f),    (%03.1f, %03.1f, %03.1f),    (%03.1f, %03.1f, %03.1f)", \
	pos.x, pos.y, pos.z, \
	nor.x, nor.y, nor.z, \
	c.r, c.g, c.b);
	print_bonus(obj->obj_color);
	printf("\n");
}

void	print_cylinder(t_obj *obj)
{
	t_vec	pos;
	t_vec	nor;
	t_color	c;

	pos = obj->shape_data->cylinder->bottom_center;
	nor = obj->shape_data->cylinder->axis;
	c = obj->obj_color->kd;

	printf(" Plane       : (%03.1f, %03.1f, %03.1f),    (%03.1f, %03.1f, %03.1f),   %03.1f,   %03.1f,   (%03.1f, %03.1f, %03.1f)", \
	pos.x, pos.y, pos.z, \
	nor.x, nor.y, nor.z, \
	obj->shape_data->cylinder->diameter, \
	obj->shape_data->cylinder->height, \
	c.r, c.g, c.b);
	print_bonus(obj->obj_color);
	printf("\n");
}

void	print_corn(t_obj *obj)
{
	t_vec	pos;
	t_vec	nor;
	t_color	c;

	pos = obj->shape_data->corn->bottom_center;
	nor = obj->shape_data->corn->axis;
	c = obj->obj_color->kd;

	printf(" Plane       : (%03.1f, %03.1f, %03.1f),    (%03.1f, %03.1f, %03.1f),   %03.1f,   %03.1f,   (%03.1f, %03.1f, %03.1f)", \
	pos.x, pos.y, pos.z, \
	nor.x, nor.y, nor.z, \
	obj->shape_data->corn->diameter, \
	obj->shape_data->corn->height, \
	c.r, c.g, c.b);
	print_bonus(obj->obj_color);
	printf("\n");
}

void	print_objects(t_scene_info *scene)
{
	t_list	*node;
	t_obj	*obj;

	node = scene->objs;
	while (node)
	{
		obj = node->content;
		if (obj->type == BALL)
			print_sphere(obj);
		else if (obj->type == PLANE)
			print_plane(obj);
		else if (obj->type == CYLINDER)
			print_cylinder(obj);
		else
			print_corn(obj);
		node = node->next;
	}

}
void	debug_print_config(t_all_info *info)
{
	t_color	c;

	printf("====== [DEBUG PRINT CONFIG] ======\n");
	c = info->scene_info->ambient_color;
	printf("Ambient      : %03.1f,   (%03.1f, %03.1f, %03.1f)\n", info->scene_info->brightness, c.r, c.b, c.g);

	printf("Camera       : \n");

	printf("Lights\n");
	print_lights(info->scene_info);

	printf("Objects\n");
	print_objects(info->scene_info);
	printf("====== ==================== ======\n");
}