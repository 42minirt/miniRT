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

static void	free_split_array(char **split)
{
	size_t	idx;

	idx = 0;
	while (split && split[idx])
	{
		free(split[idx]);
		idx++;
	}
	free(split);
}

static int	get_ppm_size(char **split, t_img *img)
{
	bool		is_atoi_success;

	if (get_arr_size(split) != 2)
		return (FAILURE);
	img->width = ft_atoi(split[0], &is_atoi_success);
	if (!is_atoi_success)
		return (FAILURE);
	img->height = ft_atoi(split[1], &is_atoi_success);
	if (!is_atoi_success)
		return (FAILURE);
	img->data = (int *)ft_calloc(sizeof(int), img->width * 3 * img->height);
	if (!img->data)
		return (FAILURE);
	return (SUCCESS);
}

static int	get_ppm_data(char **split, t_img *img, size_t *data_idx)
{
	size_t	row;
	bool	is_atoi_success;

	if (get_arr_size(split) == 0)
	{
		printf("PPM error : arrsize=0\n");//debug
		return (FAILURE);
	}
	row = 0;
	while (split[row])
	{
		if (*data_idx >= img->width * 3 * img->height)
		{
			printf("PPM error : index out of range\n");//debug
			return (FAILURE);
		}
		img->data[*data_idx] = ft_atoi(split[row], &is_atoi_success);
		if (!is_atoi_success)
			return (FAILURE);
		row++;
		*data_idx += 1;
	}
	return (SUCCESS);
}

static int	process_line_by_col(const char *line, \
								size_t file_col, t_img *img, size_t *data_idx)
{
	char	**split;
	int		res;

	if (file_col == 0 && !is_equal_strings(line, "P3"))
	{
		printf("PPM invalid format : col 0 is not 'P3'\n");//debug
		return (FAILURE);
	}
	if (file_col == 1 && !is_equal_strings(line, "# 8-bit ppm - RGB"))
	{
		printf("PPM invalid format : col 1 is not '# 8-bit ppm - RGB'\n");//debug
		return (FAILURE);
	}
	if (file_col == 3 && !is_equal_strings(line, "255"))
	{
		printf("PPM invalid format : col 3 is not '255'\n");//debug
		return (FAILURE);
	}
	if (file_col == 0 || file_col == 1 || file_col == 3)
		return (SUCCESS);
	split = ft_split(line, ' ');
	if (!split)
		return (FAILURE);
	res = FAILURE;
	if (file_col == 2)
		res = get_ppm_size(split, img);
	else
		res = get_ppm_data(split, img, data_idx);
	free_split_array(split);
	return (res);
}

// ppm file format
//   col 0: <file_format>
//   col 1: <comment>
//   col 2: <width> <height>
//   col 3: <color_range>
//   col 4: <r11> <g11> <b11> <r12> <g12> <b12> ...

t_parse_res	get_img(t_img *img, int fd)
{
	char		*line;
	size_t		file_col;
	size_t		data_idx;
	t_parse_res	res;

	img->data = NULL;
	res = PASS;
	file_col = 0;
	data_idx = 0;
	printf("1: %s\n", parse_result_char(res));//debug
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		if (res == PASS \
		&& process_line_by_col(line, file_col, img, &data_idx) == FAILURE)
			res = ERROR_FATAL;
		free(line);
		file_col++;
	}
	printf("2: %s\n", parse_result_char(res));//debug
	printf("idx:%zu, size:%zu\n", data_idx, img->width * 3 * img->height);
	if (res != PASS || data_idx != img->width * 3 * img->height)
	{
		free(img->data);
		img->data = NULL;
		printf("PPM error : size error\n");//debug
		return (ERROR_INVALID_ARG);
	}
	return (res);
}
