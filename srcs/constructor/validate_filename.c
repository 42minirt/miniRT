/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_filename.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static const char	*get_filename(const char *path)
{
	char	*ptr;

	ptr = ft_strrchr(path, '/');
	if (!ptr)
		return (path);
	ptr += 1;
	return (ptr);
}

static int	try_open(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == OPEN_ERROR)
		return (FAILURE);
	if (x_close(fd) == CLOSE_ERROR)
		return (PROCESS_ERROR);
	return (SUCCESS);
}

int	validate_filename(const char *path, const char *extension)
{
	const char		*filename = get_filename(path);
	const size_t	filename_len = ft_strlen_ns(filename);
	const size_t	extension_len = ft_strlen_ns(extension);
	int				try_open_res;

	if (cnt_chr_in_str('.', filename) > 1)
		return (FAILURE);
	if (filename_len <= extension_len)
		return (FAILURE);
	if (!is_equal_strings(&filename[filename_len - extension_len], extension))
		return (FAILURE);
	try_open_res = try_open(path);
	return (try_open_res);
}
