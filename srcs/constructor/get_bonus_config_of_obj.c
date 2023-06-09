/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bonus_config_of_obj.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_parse_res	get_checker_info(const char *line, \
									t_obj_color *obj_color, \
									size_t *idx)
{
	t_parse_res	res;

	obj_color->is_checker = true;
	if (!ft_isdigit(line[*idx]))
		return (ERROR_INVALID_ARG);
	res = parse_color(line, &obj_color->checker_color, idx);
	if (res != PASS)
		return (res);
	skip_isspece(line, idx);
	return (PASS);
}

static t_parse_res	get_perfect_ref_info(const char *line, \
										t_obj_color *obj_color, \
										size_t *idx)
{
	obj_color->is_perfect_ref = true;
	obj_color->kf = init_color(1.0, 1.0, 1.0);
	skip_isspece(line, idx);
	return (PASS);
}

//todo: cnt != 1 ?
static t_parse_res	get_image_texture_info(const char *line, \
											t_obj_color *obj_color, \
											size_t *idx)
{
	t_parse_res	res;
	bool		is_empty;
	size_t		comma_cnt;

	is_empty = false;
	obj_color->texture_data.data = NULL;
	obj_color->bump_data.data = NULL;
	res = get_image_texture(line, &obj_color->texture_data, idx, &is_empty);
	if (res != PASS)
		return (res);
	skip_delimiter_and_cnt_comma(line, idx, &comma_cnt);
	if (comma_cnt != 0)
		return (ERROR_INVALID_DELIMITER);
	res = get_image_texture(line, &obj_color->bump_data, idx, &is_empty);
	if (res != PASS)
		return (res);
	skip_isspece(line, idx);
	if (obj_color->texture_data.data)
		obj_color->is_texture = true;
	if (obj_color->bump_data.data)
		obj_color->is_bump = true;
	return (PASS);
}

t_parse_res	get_bonus_config_of_obj(const char *line, t_obj *obj, size_t *idx)
{
	char		*option_id;
	t_parse_res	res;

	option_id = get_identifier_str(line, *idx);
	if (!option_id)
		return (ERROR_FATAL);
	increment_idx_to_next_format(line, idx, option_id);
	if (is_equal_strings(option_id, OP_CHECKER_TEXTURE))
		res = get_checker_info(line, &obj->obj_color, idx);
	else if (is_equal_strings(option_id, OP_PERFECT_REF))
		res = get_perfect_ref_info(line, &obj->obj_color, idx);
	else if (is_equal_strings(option_id, OP_IMAGE_TEXTURE))
		res = get_image_texture_info(line, &obj->obj_color, idx);
	else
	{
		res = ERROR_INVALID_TYPE;
		printf("[DEBUG]invalid bonus option:[%s]\n", option_id);
	}
	x_free_1d_alloc((void **)&option_id);
	if (res == PASS && line[*idx])
		return (ERROR_TOO_MANY_INFO);
	return (res);
}
