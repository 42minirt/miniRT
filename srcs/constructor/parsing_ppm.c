/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ppm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_parse_res	put_ppmerr_ret_res(char *err)
{
	ft_dprintf(STDERR_FILENO, "[PPM Error] : %s\n", err);
	return (ERROR_INVALID_PPM_FORMAT);
}

t_parse_res	init_data_array(t_img *img, t_ppm_param *p)
{
	if (img->width == PARSE_INIT || img->height == PARSE_INIT)
		return (PASS);
	p->img_pixel = img->width * img->height;
	if (p->img_pixel / img->width != img->height)
		return (put_ppmerr_ret_res("data size will overflow"));
	img->data = (int *)ft_calloc(p->img_pixel * COLOR_DATA_KIND, sizeof(int));
	if (!img->data)
		return (ERROR_FATAL);
	return (PASS);
}

t_parse_res	parse_ppm_data(t_img *img, int fd, t_ppm_param *p)
{
	t_parse_res	result;
	char		*line;

	result = PASS;
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		if (result == PASS)
			result = parse_ppm_data_line_by_line(line, p, img);
		free(line);
		p->file_col++;
	}
	return (result);
}
