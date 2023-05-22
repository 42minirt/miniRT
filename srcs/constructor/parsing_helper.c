/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/22 10:27:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	skip_spece(const char *line, size_t *idx)
{
	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;
}

void	skip_delimiter(const char *line, size_t *idx)
{
	skip_spece(line, idx);
	if (line[*idx] == ',')
		*idx += 1;
	skip_spece(line, idx);
}

void	increment_idx_to_next_format(const char *line, \
									size_t *idx, char *prev_str)
{
	*idx += ft_strlen_ns(prev_str);
	skip_spece(line, idx);
}

char	*get_identifier_str(const char *line, size_t idx)
{
	char	*id_str;
	size_t	str_len;

	str_len = 0;
	skip_spece(line, &idx);
	while (line[idx + str_len] && !ft_isspace(line[idx + str_len]))
		str_len++;
	id_str = ft_substr(line, idx, str_len);
	if (!id_str)
		return (NULL);
	return (id_str);
}

//t_id	get_identifier_no(const char *id_type)
//{
//	size_t		idx;
//	const char	*ids[] = {
//	ID_CAMERA, ID_AMBIENT, ID_LIGHT, ID_SPOTLIGHT,
//	ID_SPHERE, ID_PLANE, ID_CYLINDER, ID_CORN, NULL};
//
//	idx = 0;
//	while (ids[idx])
//	{
//		if (is_equal_strings(id_type, ids[idx]))
//			return ((int)idx);
//		idx++;
//	}
//	return (id_invalid);
//}
