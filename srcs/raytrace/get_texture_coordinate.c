#include "minirt.h"

// todo: 不要かも

// 0 <= row <= img.width
// 0 <= col <= img.height
t_tangetnt_map	get_planner_texture_coordinate(t_intersection_point *its_p, t_img img)
{
	t_tangetnt_map	map;

	map = get_planer_map(its_p);
	map.u *= (double)img.width * IMG_FREQUENCY;
	map.v *= -1.0 * (double)img.height * IMG_FREQUENCY;
	return (map);
}

t_tangetnt_map	get_spherical_texture_coordinate(t_intersection_point *its_p, t_img img)
{
	t_tangetnt_map	map;

	map = get_spherical_map(its_p);
	map.u *= (double)img.width * IMG_FREQUENCY;
	map.v *= (double)img.height * IMG_FREQUENCY;
	return (map);
}

t_tangetnt_map	get_cylindrical_texture_coordinate(t_intersection_point *its_p, t_img img)
{
	t_tangetnt_map	map;

	map = get_cylindrical_map(its_p);
	map.u *= (double)img.width * IMG_FREQUENCY;
	map.v *= -1.0 * (double)img.height * IMG_FREQUENCY;
	return (map);
}

t_tangetnt_map	get_conical_texture_coordinate(t_intersection_point *its_p, t_img img)
{
	t_tangetnt_map	map;

	map = get_conical_map(its_p);
	map.u *= (double)img.width * IMG_FREQUENCY;
	map.v *= -1.0 * (double)img.height * IMG_FREQUENCY;
	return (map);
}