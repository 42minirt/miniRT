/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_config_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_bonus(t_obj_color o)
{
	t_color	c;

	if (o.is_perfect_ref)
		printf(",   perfect_ref");
	if (o.is_checker)
	{
		c = o.checker_color;
		printf(",   checker(%5.1f, %5.1f, %5.1f)", c.r, c.g, c.b);
	}
	if (o.texture_data.data)
		printf(",   img_texture");
	if (o.bump_data.data)
		printf(",   img_bump");
}

void	print_sphere(t_obj *obj)
{
	t_vec	pos;
	t_color	c;

	pos = obj->shape_data.sphere.center;
	c = obj->obj_color.kd;
	printf("  ● Sphere    : (%5.1f, % 5.1f, % 5.1f),"\
	"                                    %5.1f,           (%5.1f, %5.1f, %5.1f)", \
	pos.x, pos.y, pos.z, \
	obj->shape_data.sphere.diameter, \
	c.r, c.g, c.b);
	print_bonus(obj->obj_color);
	printf("\n");
}

void	print_plane(t_obj *obj)
{
	t_vec	pos;
	t_vec	nor;
	t_color	c;

	pos = obj->shape_data.plane.center;
	nor = obj->shape_data.plane.normal;
	c = obj->obj_color.kd;
	printf("  ■ Plane     : (%5.1f, %5.1f, %5.1f),    (%5.1f, %5.1f, %5.1f),"\
	"                           (%5.1f, %5.1f, %5.1f)", \
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

	pos = obj->shape_data.cylinder.bottom_center;
	nor = obj->shape_data.cylinder.axis;
	c = obj->obj_color.kd;
	printf("  ○ Cylinder  : (%5.1f, %5.1f, %5.1f),    (%5.1f, %5.1f, %5.1f),"\
	"          %5.1f,  %5.1f,   (%5.1f, %5.1f, %5.1f)", \
	pos.x, pos.y, pos.z, \
	nor.x, nor.y, nor.z, \
	obj->shape_data.cylinder.diameter, \
	obj->shape_data.cylinder.height, \
	c.r, c.g, c.b);
	print_bonus(obj->obj_color);
	printf("\n");
}

void	print_corn(t_obj *obj)
{
	t_vec	pos;
	t_vec	nor;
	t_vec	ori;
	t_color	c;

	pos = obj->shape_data.corn.bottom_center;
	nor = obj->shape_data.corn.axis;
	ori = obj->shape_data.corn.origin;
	c = obj->obj_color.kd;
	printf("  △ Corn      : (%5.1f, %5.1f, %5.1f),    (%5.1f, %5.1f, %5.1f),"\
	"          %5.1f,  %5.1f,   (%5.1f, %5.1f, %5.1f)", \
	pos.x, pos.y, pos.z, \
	nor.x, nor.y, nor.z, \
	obj->shape_data.corn.diameter, \
	obj->shape_data.corn.height, \
	c.r, c.g, c.b);
	print_bonus(obj->obj_color);
	printf("\n");
	printf("       origin   (%5.1f, %5.1f, %5.1f)\n", ori.x, ori.y, ori.z);
}
