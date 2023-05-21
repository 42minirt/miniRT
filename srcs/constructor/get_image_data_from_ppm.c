/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:13:00 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_parse_res	get_ppm_size(char **split, t_img *img)
{
	bool		is_atoi_success;

	if (get_arr_size(split) != 2)
		return (ERROR_INVALID_PPM_FORMAT);
	img->width = ft_atoi(split[0], &is_atoi_success);
	if (!is_atoi_success)
		return (ERROR_INVALID_PPM_FORMAT);
	img->height = ft_atoi(split[1], &is_atoi_success);
	if (!is_atoi_success)
		return (ERROR_INVALID_PPM_FORMAT);
	img->data = (int *)ft_calloc(sizeof(int), img->width * 3 * img->height);
	if (!img->data)
		return (ERROR_FATAL);
	return (PASS);
}

static t_parse_res	get_ppm_data(char **split, t_img *img, size_t *data_idx)
{
	size_t	row;
	bool	is_atoi_success;

	if (get_arr_size(split) == 0)
	{
		printf("PPM error : arrsize=0\n");//debug
		return (ERROR_INVALID_PPM_FORMAT);
	}
	row = 0;
	while (split[row])
	{
		if (*data_idx >= img->width * 3 * img->height)
		{
			printf("PPM error : index out of range\n");//debug
			return (ERROR_INVALID_PPM_FORMAT);
		}
		img->data[*data_idx] = ft_atoi(split[row], &is_atoi_success);
		if (!is_atoi_success)
			return (ERROR_INVALID_PPM_FORMAT);
		row++;
		*data_idx += 1;
	}
	return (PASS);
}

static t_parse_res	process_line_by_col(const char *line, \
								size_t file_col, t_img *img, size_t *data_idx)
{
	char		**split;
	t_parse_res	res;

	if (file_col == 0 && !is_equal_strings(line, "P3"))
	{
		printf("PPM invalid format : col 0 is not 'P3'\n");//debug
		return (ERROR_INVALID_PPM_FORMAT);
	}
	if (file_col == 1 && !is_equal_strings(line, "# 8-bit ppm - RGB"))
	{
		printf("PPM invalid format : col 1 is not '# 8-bit ppm - RGB'\n");//debug
		return (ERROR_INVALID_PPM_FORMAT);
	}
	if (file_col == 3 && !is_equal_strings(line, "255"))
	{
		printf("PPM invalid format : col 3 is not '255'\n");//debug
		return (ERROR_INVALID_PPM_FORMAT);
	}
	if (file_col == 0 || file_col == 1 || file_col == 3)
		return (PASS);
	split = ft_split(line, ' ');
	if (!split)
		return (FAILURE);
	if (file_col == 2)
		res = get_ppm_size(split, img);
	else
		res = get_ppm_data(split, img, data_idx);
	x_free_2d_alloc((void ***)&split);
	return (res);
}

// ppm file format
//   col 0: <file_format>
//   col 1: <comment>
//   col 2: <width> <height>
//   col 3: <color_range>
//   col 4: <r11> <g11> <b11> <r12> <g12> <b12> ...

t_parse_res	get_img_data(t_img *img, int fd)
{
	char		*line;
	size_t		file_col;
	size_t		data_idx;
	t_parse_res	res;

	res = PASS;
	file_col = 0;
	data_idx = 0;
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		if (res == PASS \
		&& process_line_by_col(line, file_col, img, &data_idx) == FAILURE)
			res = ERROR_FATAL;
		x_free_1d_alloc((void **)&line);
		file_col++;
	}
	if (data_idx != img->width * 3 * img->height)
		res = ERROR_INVALID_PPM_FORMAT;
	printf("get_img_data result:%s, idx:%zu, size:%zu\n", \
		get_parse_result_char(res), data_idx, img->width * 3 * img->height);//debug
	if (res != PASS)
		return (ret_res_and_free(res, (void **)&img->data));
	return (res);
}
