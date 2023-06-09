/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyhooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:34:24 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// todo: tmp
static int	close_window(void *mlx)
{
	printf("close window\n");
	mlx_loop_end(mlx);
	return (0);
}

static int	key_hook(int keycode, void *mlx)
{
	if (keycode == KEY_ESC)
	{
		printf("ESC pressed\n");
		return (close_window(mlx));
	}
	if (keycode == 'w')
	{
		printf("up\n");
	}
	if (keycode == 'a')
	{
		printf("left\n");
	}
	if (keycode == 's')
	{
		printf("down\n");
	}
	if (keycode == 'd')
	{
		printf("right\n");
	}
	return (0);
}

void	mlx_hooks(t_all_info *info)
{
	const int	mask_key_press = 1L << 0;
	const int	mask_button_press = 1L << 17;

	mlx_hook(info->mlx_info->win, EVENT_KEY_PRESS, \
			mask_key_press, key_hook, info->mlx_info->mlx);
	mlx_hook(info->mlx_info->win, EVENT_DESTROY, \
			mask_button_press, close_window, info->mlx_info->mlx);
	mlx_expose_hook(info->mlx_info->win, draw, info);
}
