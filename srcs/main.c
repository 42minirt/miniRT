/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:02:34 by user              #+#    #+#             */
/*   Updated: 2023/05/16 22:46:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_all_info construct_info(t_all_info *info)
{
	// init mlx

	// init scene & camera
	// rtfileのparse & validate; get scene, camera
	parsing_scene();
	validate_scene();
}

void	draw(t_all_info info)
{
	t_ray	eye2screen_xy;
	t_color color;
    size_t y = 0;
    size_t x = 0;

	while (y != WINDOW_HEIGHT)
    {
		while (x != WINDOW_WIDTH)
		{
			// スクリーン(y,x)に相当する視線ベクトルを計算
			eye2screen_xy = get_screen_vector(info);
			// 色の計算
			color = raytrace(info, eye2screen_xy);

			// mlx 描画
			mlx_put_pixel(color, x, y);
            x++;
        }
        y++;
	}
}

static	void	destruct_info(t_all_info *info)
{
	//destructor
}

//コマンドオプションFで置換

int main(void)
{
	// infoの初期化
	t_all_info	info;

	construct_info(&info); //init mlx

	// 描画
	draw(info);

	// free
	destruct_info(&info);

    return (0);
}
