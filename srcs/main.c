/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:02:34 by user              #+#    #+#             */
/*   Updated: 2023/05/26 12:28:34 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	validate_argv(int argc, char **argv)
{
	const char	*rt_path;

	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, "Error\n : rt_file required :(\n");
		return (FAILURE);
	}
	rt_path = argv[1];
	if (validate_filename(rt_path, RT_EXTENSION) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, "Error\n : rt file invalid xo\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

// static t_color	get_gradation_background_color(double height_ratio)
// {
// 	t_color	color;

// 	color.r = 1.0 - height_ratio + height_ratio * 0.5;
// 	color.g = 1.0 - height_ratio + height_ratio * 0.7;
// 	color.b = 1.0 - height_ratio + height_ratio * 1.0;
// 	return (color);
// }

// screen_z = 0
// camera_pos(0,0,-5)
// camera_dir(0,0,1)
t_ray get_screen_vector(t_all_info info, size_t x, size_t y)
{
	t_vec	camera_pos_for_test;// = set(0.0, 0.0, -5.0);
	t_vec	screen_pos;
	t_ray	eye2screen;

	(void)info;
	camera_pos_for_test.x = 0.0;
	camera_pos_for_test.y = 0.0;
	camera_pos_for_test.z = -5.0;
//	screen_pos.x = 2.0 * (double)x / (WINDOW_WIDTH - 1.0) - 1.0;
	screen_pos.x = 4.0 * (double)x / (WINDOW_WIDTH - 1.0) - 2.0;
	screen_pos.y = -2.0 * (double)y / (WINDOW_HEIGHT - 1.0) + 1.0;
//	screen_pos.x = (double)x - (WINDOW_WIDTH / 2.0);
//	screen_pos.y = (WINDOW_HEIGHT / 2.0) - (double)y;
	screen_pos.z = 0.0;
	eye2screen.pos = camera_pos_for_test;
	eye2screen.unit_dir = sub(screen_pos, camera_pos_for_test);
	eye2screen.unit_dir = norm_vec(eye2screen.unit_dir);
	return (eye2screen);
}

int	draw(t_all_info info)
{
	t_ray	eye2screen_xy;
	t_color	color;
    size_t	y;
    size_t	x;
	//double	height_ratio = 1.0f;

	ft_dprintf(STDERR_FILENO, "        +---------+---------+ 100%%\n");
	ft_dprintf(STDERR_FILENO, "Drawing ");
	y = 0;
	while (y < WINDOW_HEIGHT)
    {
		x = 0;
		while (x < WINDOW_WIDTH)
		{
//			if ((250 <= y && y >= 500) && (500 <=x && x <= 1000))
//			{
//				color = get_gradation_background_color(height_ratio);
				color_set(&color, 0.0, 0.0, 0.0);
				//eye2screen_xy = get_screen_vector(info, x, y);
				eye2screen_xy = red_rayvec(info.camera_info, (double)x, (double)y);
				color = color_add(color, raytrace(&info, eye2screen_xy));
				put_pixel(info.mlx_info, x, y, color);
//			}
			x++;
        }
		if (y % (int)(WINDOW_HEIGHT / 20.0) == 0)
			ft_dprintf(STDERR_FILENO, "#");
        y++;
		//height_ratio = 1.0 - (double)y / WINDOW_HEIGHT;
	}
	ft_dprintf(STDERR_FILENO, "#\n");
	mlx_put_image_to_window(info.mlx_info->mlx, info.mlx_info->win, info.mlx_info->img, 0, 0);
	ft_dprintf(STDERR_FILENO, "Draw SUCCESS !\n");
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_all_info	info;

	if (validate_argv(argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	if (construct_info(&info, argv[1]) == FAILURE)
	{
		destruct_info(&info);
		return (EXIT_FAILURE);
	}
//	draw(info);
	mlx_hooks(&info);
	mlx_loop(info.mlx_info->mlx);
	destruct_info(&info);
    return (0);
}

#ifdef LEAKS

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q miniRT");
}

#endif