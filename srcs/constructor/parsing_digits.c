/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_digits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/22 10:28:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//int	parse_int(const char *line, int *int_num, size_t *idx)
//{
//	size_t	len;
//	char	*num_str;
//	bool	is_success;
//
//	skip_spece(line, idx);
//	len = 0;
//	while (line[*idx + len]
//	&& !ft_isspace(line[*idx + len]) && line[*idx + len] != ',')
//		len++;
//	num_str = ft_substr(line, *idx, len);
//	if (!num_str)
//	{
//		perror("malloc");
//		return (FAILURE);
//	}
//	*idx += len;
//	*int_num = ft_atoi(num_str, &is_success);
//	free(num_str);
//	if (!is_success)
//		return (FAILURE);
//	return (SUCCESS);
//}

// todo int->parse_res
t_parse_res	parse_double(const char *line, double *double_num, size_t *idx)
{
	size_t	len;
	char	*num_str;
	bool	is_success;

	skip_spece(line, idx);
	len = 0;
	while (line[*idx + len] \
	&& !ft_isspace(line[*idx + len]) && line[*idx + len] != ',')
		len++;
	num_str = ft_substr(line, *idx, len);
	if (!num_str)
	{
		perror("malloc");
		return (ERROR_FATAL);
	}
	*idx += len;
	*double_num = ft_strtod(num_str, &is_success, NULL);
	x_free_1d_alloc((void **)&num_str);
	if (!is_success)
		return (ERROR_INVALID_ARG);
	return (PASS);
}

// todo int->parse_res
t_parse_res	parse_vec(const char *line, t_vec *vec, size_t *idx)
{
	size_t		comma_cnt;
	t_parse_res	res;

	skip_spece(line, idx);
	res = parse_double(line, &vec->x, idx);
	if (res != PASS)
		return (res);
	skip_delimiter_and_cnt_comma(line, idx, &comma_cnt);
	if (comma_cnt != 1)
		return (ERROR_INVALID_DELIMITER);
	res = parse_double(line, &vec->y, idx);
	if (res != PASS)
		return (res);
	skip_delimiter_and_cnt_comma(line, idx, &comma_cnt);
	if (comma_cnt != 1)
		return (ERROR_INVALID_DELIMITER);
	res = parse_double(line, &vec->z, idx);
	if (res != PASS)
		return (res);
	skip_spece(line, idx);
	return (PASS);
}

// todo int->parse_res

t_parse_res	parsing_color(const char *line, t_color *color, size_t *idx)
{
	size_t		comma_cnt;
	t_parse_res	res;

	skip_spece(line, idx);
	res = parse_double(line, &color->r, idx);
	if (res != PASS)
		return (res);
	skip_delimiter_and_cnt_comma(line, idx, &comma_cnt);
	if (comma_cnt != 1)
		return (ERROR_INVALID_DELIMITER);
	res = parse_double(line, &color->g, idx);
	if (res != PASS)
		return (res);
	skip_delimiter_and_cnt_comma(line, idx, &comma_cnt);
	if (comma_cnt != 1)
		return (ERROR_INVALID_DELIMITER);
	res = parse_double(line, &color->b, idx);
	if (res != PASS)
		return (res);
	skip_spece(line, idx);
	return (PASS);
}
