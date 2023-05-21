/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
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
