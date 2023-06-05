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

#include "../../includes/minirt.h"

//static t_parse_res	get_ppm_size(char **split, t_img *img)
//{
//	bool	is_atoi_success;
//
//	if (get_arr_size(split) != 2)
//		return (ERROR_INVALID_PPM_FORMAT);
//	img->width = ft_atoi(split[0], &is_atoi_success);
//	if (!is_atoi_success)
//		return (ERROR_INVALID_PPM_FORMAT);
//	img->height = ft_atoi(split[1], &is_atoi_success);
//	if (!is_atoi_success)
//		return (ERROR_INVALID_PPM_FORMAT);
//	img->data = (int *)ft_calloc(sizeof(int), img->width * 3 * img->height);
//	if (!img->data)
//		return (ERROR_FATAL);
//	return (PASS);
//}
//
//size_t	debug_data_cnt = 0; // debug
//
//static t_parse_res	get_ppm_data(char **split, t_img *img, size_t *data_idx)
//{
//	size_t	row;
//	bool	is_atoi_success;
//
//	if (get_arr_size(split) == 0)
//	{
//		printf("[#DEBUG] PPM error : arrsize=0\n");//debug
//		return (ERROR_INVALID_PPM_FORMAT);
//	}
//	row = 0;
//	debug_data_cnt += get_arr_size(split); // debug
//	while (split[row])
//	{
//		if (*data_idx >= img->width * 3 * img->height)
//		{
//			printf("[#DEBUG] PPM error : index out of range\n");//debug
//			return (ERROR_INVALID_PPM_FORMAT);
//		}
//		img->data[*data_idx] = ft_atoi(split[row], &is_atoi_success);
//		if (!is_atoi_success)
//			return (ERROR_INVALID_PPM_FORMAT);
//		row++;
//		*data_idx += 1;
//	}
//	return (PASS);
//}
//
//static t_parse_res	process_line_by_col(const char *line, \
//								size_t file_col, t_img *img, size_t *data_idx)
//{
//	char		**split;
//	t_parse_res	res;
//
//	if (file_col == 0 && !is_equal_strings(line, "P3"))
//	{
//		printf("[#DEBUG] PPM invalid format : col 0 is not 'P3'\n");//debug
//		return (ERROR_INVALID_PPM_FORMAT);
//	}
//	if (file_col == 1 && !is_equal_strings(line, "# 8-bit ppm - RGB"))
//	{
//		printf("[#DEBUG] PPM invalid format : col 1 is not '# 8-bit ppm - RGB'\n");//debug
//		return (ERROR_INVALID_PPM_FORMAT);
//	}
//	if (file_col == 3 && !is_equal_strings(line, "255"))
//	{
//		printf("[#DEBUG] PPM invalid format : col 3 is not '255'\n");//debug
//		return (ERROR_INVALID_PPM_FORMAT);
//	}
//	if (file_col == 0 || file_col == 1 || file_col == 3)
//		return (PASS);
//	split = ft_split(line, ' ');
//	if (!split)
//		return (FAILURE);
//	if (file_col == 2)
//		res = get_ppm_size(split, img);
//	else
//		res = get_ppm_data(split, img, data_idx);
//	x_free_2d_alloc((void ***)&split);
//	return (res);
//}

// validate_p3_format
// get_width
// get_height
// get_color_range
// get_color_data

t_parse_res	get_p3_format(const char *line, t_ppm_param *p, size_t *idx)
{
	t_parse_res	result;
	int			px;

	skip_isspece(line, idx);
	if (!line[*idx] || line[*idx] == COMMENT_FLAG)
		return (PASS);
	if (line[*idx] != 'P')
	{
		printf("[#DEBUG] PPM err : PX\n");//debug
		return (ERROR_INVALID_PPM_FORMAT);
	}
	*idx += 1;
//	printf("[#debug] PPM format 1 : [%s]\n", &line[*idx]);
	result = parse_int(line, idx, &px);
//	printf("[#debug] PPM format 2 : [%s] -> %d\n", &line[*idx], px);
	if (result != PASS)
		return (ERROR_INVALID_PPM_FORMAT);
	if (px != PPM_X)
	{
		printf("[#DEBUG] PPM err : PX %d\n", px);//debug
		return (ERROR_INVALID_PPM_FORMAT);
	}
	p->px = px;
	return (PASS);
}

// width, height must in INT range
t_parse_res	get_image_size(const char *line, size_t *ret_size, size_t *idx)
{
	t_parse_res	result;
	int			size;

	size = 0;
	skip_isspece(line, idx);
	if (!line[*idx] || line[*idx] == COMMENT_FLAG)
		return (PASS);
	result = parse_int(line, idx, &size);
	if (result != PASS)
		return (ERROR_INVALID_PPM_FORMAT);
	if (size <= 0)
	{
		printf("[#DEBUG] PPM err : image width or height %d\n", size);//debug
		return (ERROR_INVALID_PPM_FORMAT);
	}
	*ret_size = (size_t)size;
	return (PASS);
}

t_parse_res	get_color_range(const char *line, t_ppm_param *p, size_t *idx)
{
	t_parse_res	result;
	int			color_range;

	skip_isspece(line, idx);
	if (!line[*idx] || line[*idx] == COMMENT_FLAG)
		return (PASS);
	result = parse_int(line, idx, &color_range);
	if (result != PASS)
		return (ERROR_INVALID_PPM_FORMAT);
	if (color_range < COLOR_MIN || COLOR_MAX < color_range)
	{
		printf("[#DEBUG] PPM err : color range %d\n", color_range);//debug
		return (ERROR_INVALID_PPM_FORMAT);
	}
	p->color_range = color_range;
	return (PASS);
}

t_parse_res	get_color_data(const char *line, t_ppm_param *p, t_img *img, size_t *idx)
{
	t_parse_res	result;
	int			color_value;

	skip_isspece(line, idx);
	if (!line[*idx] || line[*idx] == COMMENT_FLAG)
		return (PASS);
	while (line[*idx] && line[*idx] != COMMENT_FLAG)
	{
		if (p->data_idx >= p->img_pixel * COLOR_DATA_KIND)
		{
			printf("[#DEBUG] PPM err : index out of range idx:%zu, size:%zu\n", p->data_idx, p->img_pixel * COLOR_DATA_KIND);//debug
			return (ERROR_INVALID_PPM_FORMAT);
		}
		result = parse_int(line, idx, &color_value);
		if (result != PASS)
		{
			printf("[#DEBUG] PPM err : color invalid arg\n");//debug
			return (ERROR_INVALID_PPM_FORMAT);
		}
		if (color_value < COLOR_MIN || p->color_range < color_value)
		{
			printf("[#DEBUG] PPM err : color not in range %d\n", color_value);//debug
			return (ERROR_INVALID_PPM_FORMAT);
		}
		img->data[p->data_idx] = color_value;
		p->data_idx++;
		skip_isspece(line, idx);
	}
	return (PASS);
}

t_parse_res	init_data_array(t_img *img, t_ppm_param *p)
{
	if (img->width == PARSE_INIT || img->height == PARSE_INIT)
		return (PASS);

	p->img_pixel = img->width * img->height;
//	printf("width:%zu, height:%zu\n", img->width, img->height);
	if (p->img_pixel / img->width != img->height)
	{
		printf("[#DEBUG] PPM err : img_pixel overflow\n");//debug
		return (ERROR_INVALID_PPM_FORMAT);
	}
	img->data = (int *)ft_calloc(p->img_pixel * COLOR_DATA_KIND, sizeof(int));
	if (!img->data)
		return (ERROR_FATAL);
	return (PASS);
}

t_parse_res	parse_ppm_data_line_by_line(const char *line, t_ppm_param *p, t_img *img)
{
	t_parse_res	result;
	size_t		idx;

	result = PASS;
	idx = 0;
	if (p->px == PARSE_INIT)
		result = get_p3_format(line, p, &idx);
	if (result == PASS && img->width == PARSE_INIT)
		result = get_image_size(line, &img->width, &idx);
	if (result == PASS && img->height == PARSE_INIT)
		result = get_image_size(line, &img->height, &idx);
	if (result == PASS && !img->data) // for comment
		result = init_data_array(img, p);
	if (result == PASS && p->color_range == PARSE_INIT)
		result = get_color_range(line, p, &idx);
	if (result == PASS)
		result = get_color_data(line, p, img, &idx);
	return (result);
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

t_parse_res	validate_acquired_size(t_ppm_param p)
{
	if (p.data_idx != p.img_pixel * COLOR_DATA_KIND)
	{
		printf("[#DEBUG] PPM err : img pixel less than size\n");//debug
		return (ERROR_INVALID_PPM_FORMAT);
	}
	return (PASS);
}

void	init_parse_ppm_param(t_ppm_param *p, t_img *img)
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

// ppm file format
//   col 0: <file_format>
//   col 1: <comment>
//   col 2: <width> <height>
//   col 3: <color_range>
//   col 4: <r11> <g11> <b11> <r12> <g12> <b12> ...

//t_parse_res	get_img_data(t_img *img, int fd)
//{
//	char		*line;
//	size_t		file_col;
//	size_t		data_idx;
//	t_parse_res	res;
//
//	res = PASS;
//	file_col = 0;
//	data_idx = 0;
//	while (true)
//	{
//		line = get_next_line(fd, false);
//		if (!line)
//			break ;
//		if (res == PASS)
//			res = process_line_by_col(line, file_col, img, &data_idx);
//		x_free_1d_alloc((void **)&line);
//		file_col++;
//	}
//	if (data_idx != img->width * 3 * img->height)
//		res = ERROR_INVALID_PPM_FORMAT;
//	printf("[#DEBUG] get_img_data result:%s, idx:%zu, size:%zu, debug_data_cnt:%zu\n", \
//		get_parse_result_char(res), data_idx, img->width * 3 * img->height, debug_data_cnt);//debug
//	if (res != PASS)
//		return (ret_res_and_free(res, (void **)&img->data));
//	return (res);
//}
