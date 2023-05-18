/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_perfect_reflection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:32:12 by user              #+#    #+#             */
/*   Updated: 2023/05/19 08:03:43 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

static	bool	calc_refrectvec(t_intersection_point itsp, t_ray ray, t_vec *rev_vec)
{
	t_vec	its_n;
	t_vec	inv_ray;
	double	v_n;
	t_vec	ref_vec;

	its_n = itsp.normal;
	inverse_vec(&inv_ray, &ray.unit_dir);
	v_n = dot_vec(&its_n, &inv_ray);
	if (v_n <= 0.0)
		return (false);
	ref_vec = vec_k1v1_k2v2(2.0 * v_n, its_n, -1.0, inv_ray);
	normalize(rev_vec, &ref_vec);
	return (true);
}

static	void	set_rayset(t_ray *ref_ray, t_intersection_point its_p, t_vec rev_vec)
{
	t_mix_vec_all(&ref_ray->unit_dir, 1.0, &its_p.position, EPSIRON, &rev_vec);
	ref_ray->unit_dir = rev_vec;
}

t_color	calc_perfect_reflection(t_all_info info, t_intersection_point its_p, t_ray eye2screen, size_t counter)
{
	t_color	color;
	t_vec	reverse_vec;
	t_ray	refrect_ray;

	color_set(&color, 0.0, 0.0, 0.0);
	if (false == calc_refrectvec(its_p, eye2screen, &reverse_vec))
		return (color);
	set_raystart(&refrect_ray, its_p, reverse_vec);
	return (recursive_raytrace(&info, refrect_ray, counter));
}