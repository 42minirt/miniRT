/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:02:34 by user              #+#    #+#             */
/*   Updated: 2023/06/14 21:29:33 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	start_progress(void)
{
	ft_dprintf(STDERR_FILENO, "        +---------+---------+ 100%%\n");
	ft_dprintf(STDERR_FILENO, "Drawing ");
}

static void	make_progress(size_t y)
{
	if (y % (int)(WINDOW_HEIGHT / 20.0) == 0)
		ft_dprintf(STDERR_FILENO, "#");
}

static void	fin_progress(void)
{
	ft_dprintf(STDERR_FILENO, "#\n");
	ft_dprintf(STDERR_FILENO, "Draw SUCCESS !\n");
}

int	draw(t_all_info *info)
{
	t_ray	eye2screen_xy;
	t_color	color;
	size_t	y;
	size_t	x;

	start_progress();
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			color_set(&color, 0.0, 0.0, 0.0);
			eye2screen_xy = red_rayvec(info->camera_info, (double)x, (double)y);
			color = color_add(color, raytrace(info, eye2screen_xy));
			put_pixel(info->mlx_info, x, y, color);
			x++;
		}
		make_progress(y);
		y++;
	}
	mlx_put_image(*info);
	fin_progress();
	return (EXIT_SUCCESS);
}
