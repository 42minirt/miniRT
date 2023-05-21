/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_digits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
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
//	while (line[*idx + len] \
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

int	parse_double(const char *line, double *double_num, size_t *idx)
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
		return (FAILURE);
	}
	*idx += len;
	*double_num = ft_strtod(num_str, &is_success, NULL);
	x_free_1d_alloc((void **)&num_str);
	if (!is_success)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_vec(const char *line, t_vec *vec, size_t *idx)
{
	skip_spece(line, idx);
	if (parse_double(line, &vec->x, idx) == FAILURE)
		return (FAILURE);
	skip_delimiter(line, idx);
	if (parse_double(line, &vec->y, idx) == FAILURE)
		return (FAILURE);
	skip_delimiter(line, idx);
	if (parse_double(line, &vec->z, idx) == FAILURE)
		return (FAILURE);
	skip_spece(line, idx);
	return (SUCCESS);
}

int	parsing_color(const char *line, t_color *color, size_t *idx)
{
	skip_spece(line, idx);
	if (parse_double(line, &color->r, idx) == FAILURE)
		return (FAILURE);
	skip_delimiter(line, idx);
	if (parse_double(line, &color->g, idx) == FAILURE)
		return (FAILURE);
	skip_delimiter(line, idx);
	if (parse_double(line, &color->b, idx) == FAILURE)
		return (FAILURE);
	skip_spece(line, idx);
	return (SUCCESS);
}
