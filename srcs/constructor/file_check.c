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

static const char	*get_filename(const char *path)
{
	char	*ptr;

	ptr = ft_strrchr(path, '/');
	if (!ptr)
		return (path);
	ptr += 1;
	return (ptr);
}

int	validate_file(const char *path, const char *extension)
{
	const char		*filename = get_filename(path);
	const size_t	filename_len = ft_strlen_ns(filename);
	const size_t	extension_len = ft_strlen_ns(extension);
	int				fd;

	printf(" DEBUG(validate_file): path:[%s] -> filename:[%s]\n", path, filename);
	if (cnt_chr_in_str('.', path) > 1)
		return (FAILURE);
	if (filename_len <= extension_len)
		return (FAILURE);
	printf(" DEBUG(validate_file) extension: file[%s]\n", &filename[filename_len - extension_len]);
	if (!is_equal_strings(&filename[filename_len - extension_len], extension))
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
