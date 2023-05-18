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

//t_ray get_screen_vector(t_all_info info)
//{
//	//todo:  後回し
//}

/* **********************

 Coordinates : Left hand

   +y
   |  +z
   | /
   |/_____ +x

 ********************** */

void	draw(t_all_info info)
{
	t_ray	eye2screen_xy;
	t_color color;
    size_t y = 0;
    size_t x = 0;

	while (y < WINDOW_HEIGHT)
    {
		while (x < WINDOW_WIDTH)
		{
			// スクリーン(y,x)に相当する視線ベクトルを計算
//			eye2screen_xy = get_screen_vector(info);
			// 色の計算
//			color = raytrace(info, eye2screen_xy);

			// mlx 描画
//			put_pixel(info.mlx_info, x, y, color);
            x++;
        }
        y++;
	}
}

//コマンドオプションFで置換

// int main(void)
// {
// 	// infoの初期化
// 	t_all_info	info;

// 	construct_info(&info); //init mlx
// =======
int main(int argc, char **argv)
{
	t_all_info	info;

	if (argc != 2)
	{
		// todo: error msg
		ft_dprintf(STDERR_FILENO, "Error : rt_file required.\n");
		return (EXIT_FAILURE);
	}
	if (construct_info(&info, argv[1]) == FAILURE)
	{
		// todo: error msg
		destruct_info(&info);
		ft_dprintf(STDERR_FILENO, "Error : init error\n");
		return (EXIT_FAILURE);
	}
	printf("main\n");
//	draw(info);
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