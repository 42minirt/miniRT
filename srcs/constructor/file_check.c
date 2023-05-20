/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filecheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/20 15:27:45 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_file(const char *path, const char *extension)
{
	const size_t	path_len = ft_strlen_ns(path);
	const size_t	extension_len = ft_strlen_ns(extension);
	int				fd;

	if (path_len < extension_len)
		return (FAILURE);
	if (cnt_chr_in_str('.', path) > 1)
		return (FAILURE);
	printf("same_str: s1[%s], s2[%s]\n", &path[path_len - extension_len], extension);
	if (!is_same_str(&path[path_len - extension_len], extension))
		return (FAILURE);
	fd = open(path, O_RDONLY);
	if (fd == OPEN_ERROR)
		return (FAILURE);
	if (close(fd) == CLOSE_ERROR)
	{
		perror("close");
		return (PROCESS_ERROR);
	}
	return (SUCCESS);
}
