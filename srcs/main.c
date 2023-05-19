/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:02:34 by user              #+#    #+#             */
/*   Updated: 2023/05/17 22:24:26 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	get_gradation_background_color(double height_ratio)
{
	t_color	color;

	color.r = 1.0 - height_ratio + height_ratio * 0.5;
	color.g = 1.0 - height_ratio + height_ratio * 0.7;
	color.b = 1.0 - height_ratio + height_ratio * 1.0;
	return (color);
}

// pos(0,0,0)
// dir(0,0,1)
t_ray get_screen_vector(t_all_info info, size_t x, size_t y)
{
	t_ray	ret;
	t_vec	pos_for_test = set(0.0, 0.0, -5.0);

	ret.pos.x = 2.0 * (double)x / (WINDOW_WIDTH - 1.0) - 1.0;
	ret.pos.y = -2.0 * (double)y / (WINDOW_HEIGHT - 1.0) + 1.0;
	ret.pos.z = 0.0;
	ret.unit_dir = sub(ret.pos, pos_for_test);
	ret.unit_dir = norm_vec(ret.unit_dir);
	return (ret);
}

void	draw(t_all_info info)
{
	t_ray	eye2screen_xy;
	t_color	color;
    size_t	y = 0;
    size_t	x = 0;
	double	height_ratio = 1.0f;

	while (y < WINDOW_HEIGHT)
    {
		while (x < WINDOW_WIDTH)
		{
			color = get_gradation_background_color(height_ratio);
			eye2screen_xy = get_screen_vector(info, x, y);
			raytrace(&info, eye2screen_xy, &color);
			put_pixel(info.mlx_info, x, y, color);
            x++;
        }
        y++;
		height_ratio = 1.0 - (double)y / WINDOW_HEIGHT;
	}
}

int main(int argc, char **argv)
{
	t_all_info	info;

	if (argc != 2)
	{
		// todo: error msg
		ft_dprintf(STDERR_FILENO, "Error : rt_file required :(\n");
		return (EXIT_FAILURE);
	}
	if (construct_info(&info, argv[1]) == FAILURE)
	{
		// todo: error msg
		destruct_info(&info);
		ft_dprintf(STDERR_FILENO, "Error : init error :(\n");
		return (EXIT_FAILURE);
	}
	draw(info);
	destruct_info(&info);
    return (0);
}

//#ifdef LEAKS

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q miniRT");
}

//#endif