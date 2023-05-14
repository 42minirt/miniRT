#include <stdio.h>
#include "minirt.h"

t_info init_info(void)
{
	// init mlx

	// init scene & camera
	// rtfileのparse & validate; get scene, camera
	parsing_scene();
	validate_scene();
}

t_eye get_screen_vector(t_info info)
{
	//todo:  後回し
}

t_color raytrace(t_info, t_eye eye2screen)
{

}

void	draw(t_info info)
{
	t_eye eye2screen_xy;
	t_color color;

	for (y)
		for (x)
		{
			// スクリーン(y,x)に相当する視線ベクトルを計算
			eye2screen_xy = get_screen_vector(info);
			// 色の計算
			color = raytrace(info, eye2screen_xy);

			// mlx 描画
			mlx_put_pixel(color, x, y);

		}
}



int main(void)
{
	// infoの初期化
	t_info info = construct_info(); //init mlx

	// 描画
	draw(info);

	// free
	destruct_info(info);

    return (0);
}
