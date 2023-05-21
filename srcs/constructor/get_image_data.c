/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:36:32 by user              #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

//	printf("## width:%d, height:%d\n", img->width, img->height);

static int	get_ppm_data(char **split, t_img *img, size_t *data_idx)
{
	size_t	row;
	bool	is_atoi_success;

	row = 0;
	while (split[row])
	{
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
	char	*line;
	size_t	file_col;
	size_t	data_idx;

	img->data = NULL;
	file_col = 0;
	data_idx = 0;
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		if (process_line_by_col(line, file_col, img, &data_idx) == FAILURE)
		{
			free(line);
			free(img->data);
			img->data = NULL;
			return (ERROR_FATAL);
		}
		free(line);
		file_col++;
	}
	return (PASS);
}

//getnextlineは最後に開業を含まない
