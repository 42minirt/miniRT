/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_data_from_ppm.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constructor.h"
#include "typedef.h"

static t_parse_res	validate_acquired_size(t_ppm_param p)
{
	if (p.data_idx != p.img_pixel * COLOR_DATA_KIND)
		return (put_ppmerr_ret_res("img pixel less than size"));
	return (PASS);
}

static void	init_parse_ppm_param(t_ppm_param *p, t_img *img)
{
	p->px = PARSE_INIT;
	p->color_range = PARSE_INIT;
	p->file_col = 0;
	p->data_idx = 0;
	img->height = PARSE_INIT;
	img->width = PARSE_INIT;
}

t_parse_res	get_img_data(t_img *img, int fd)
{
	t_ppm_param	p;
	t_parse_res	result;

	init_parse_ppm_param(&p, img);
	result = parse_ppm_data(img, fd, &p);
	if (result == PASS)
		result = validate_acquired_size(p);
	if (result == PASS)
		return (result);
	return (ret_res_and_free(result, (void **)&img->data));
}
