/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keyhooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:34:24 by takira            #+#    #+#             */
/*   Updated: 2023/06/14 21:34:36 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../../libs/include/ft_printf.h"
#include "typedef.h"
#include "minirt.h"

static int	close_window(void *mlx)
{
	ft_dprintf(STDERR_FILENO, "Good bye\n");
	mlx_loop_end(mlx);
	return (0);
}

static int	key_hook(int keycode, void *mlx)
{
	if (keycode == KEY_ESC)
		return (close_window(mlx));
	return (0);
}

void	mlx_hooks(t_all_info *info)
{
	static const int	mask_key_press = 1L << 0;
	static const int	mask_button_press = 1L << 17;

	mlx_hook(info->mlx_info->win, EVENT_KEY_PRESS, \
			mask_key_press, key_hook, info->mlx_info->mlx);
	mlx_hook(info->mlx_info->win, EVENT_DESTROY, \
			mask_button_press, close_window, info->mlx_info->mlx);
	mlx_expose_hook(info->mlx_info->win, draw, (void *)info);
}
