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

static bool	validate_extension(const char *input, const char *correct)
{
	size_t	idx;

	if (!input || !correct)
		return (false);
	idx = 0;
	while (input[idx] && (ft_tolower(input[idx]) == correct[idx]))
		idx++;
	return (input[idx] == correct[idx]);
}

// TODO: malloc error
static bool	is_dir(const char *path)
{
	const size_t	path_len = ft_strlen_ns(path);
	char			*test_path;
	int				try_open_res;

	if (path_len == 0)
		return (false);
	if (path[path_len - 1] == '/')
		return (true);
	test_path = (char *)ft_calloc(path_len + 2, sizeof(char));
	if (!test_path)
		return (false);
	ft_strlcat(test_path, path, path_len + 1);
	test_path[path_len] = '/';
	try_open_res = try_open(test_path);
	free(test_path);
	return (try_open_res == SUCCESS);
}

int	validate_filename(const char *path, const char *extension)
{
	const char		*filename = get_filename(path);
	const size_t	filename_len = ft_strlen_ns(filename);
	const size_t	extension_len = ft_strlen_ns(extension);
	int				try_open_res;

	if (is_dir(path))
		return (FAILURE);
	if (cnt_chr_in_str('.', filename) > 1)
		return (FAILURE);
	if (filename_len <= extension_len)
		return (FAILURE);
	if (!validate_extension(&filename[filename_len - extension_len], extension))
		return (FAILURE);
	try_open_res = try_open(path);
	return (try_open_res);
}
