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

static t_parse_res	get_p3_format(const char *line, t_ppm_param *p, size_t *idx)
{
	t_parse_res	result;
	int			px;

	skip_isspece(line, idx);
	if (!line[*idx] || line[*idx] == COMMENT_FLAG)
		return (PASS);
	if (line[*idx] != 'P')
		return (put_ppmerr_ret_res("invalid PX format"));
	*idx += 1;
	result = parse_int(line, idx, &px);
	if (result != PASS)
		return (put_ppmerr_ret_res("invalid value"));
	if (px != PPM_X)
		return (put_ppmerr_ret_res("invalid PX format"));
	p->px = px;
	return (PASS);
}

// width, height must in INT range
static t_parse_res	get_image_size(const char *line, \
									size_t *ret_size, \
									size_t *idx)
{
	t_parse_res	result;
	int			size;

	size = 0;
	skip_isspece(line, idx);
	if (!line[*idx] || line[*idx] == COMMENT_FLAG)
		return (PASS);
	result = parse_int(line, idx, &size);
	if (result != PASS)
		return (put_ppmerr_ret_res("invalid value"));
	if (size <= 0)
		return (put_ppmerr_ret_res("invalid image size"));
	*ret_size = (size_t)size;
	return (PASS);
}

static t_parse_res	get_color_range(const char *line, \
									t_ppm_param *p, \
									size_t *idx)
{
	t_parse_res	result;
	int			color_range;

	skip_isspece(line, idx);
	if (!line[*idx] || line[*idx] == COMMENT_FLAG)
		return (PASS);
	result = parse_int(line, idx, &color_range);
	if (result != PASS)
		return (put_ppmerr_ret_res("invalid value"));
	if (color_range < COLOR_MIN || COLOR_MAX < color_range)
		return (put_ppmerr_ret_res("invalid range of color"));
	p->color_range = color_range;
	return (PASS);
}

static t_parse_res	get_color_data(const char *line, \
									t_ppm_param *p, \
									t_img *img, \
									size_t *idx)
{
	t_parse_res	result;
	int			color_value;

	skip_isspece(line, idx);
	if (!line[*idx] || line[*idx] == COMMENT_FLAG)
		return (PASS);
	while (line[*idx] && line[*idx] != COMMENT_FLAG)
	{
		if (p->data_idx >= p->img_pixel * COLOR_DATA_KIND)
			return (put_ppmerr_ret_res("too many data"));
		result = parse_int(line, idx, &color_value);
		if (result != PASS)
			return (put_ppmerr_ret_res("invalid color value"));
		if (color_value < COLOR_MIN || p->color_range < color_value)
			return (put_ppmerr_ret_res("color value out of range"));
		img->data[p->data_idx] = color_value;
		p->data_idx++;
		skip_isspece(line, idx);
	}
	return (PASS);
}

t_parse_res	parse_ppm_data_line_by_line(const char *line, \
										t_ppm_param *p, \
										t_img *img)
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
	if (result == PASS && !img->data)
		result = init_data_array(img, p);
	if (result == PASS && p->color_range == PARSE_INIT)
		result = get_color_range(line, p, &idx);
	if (result == PASS)
		result = get_color_data(line, p, img, &idx);
	return (result);
}
