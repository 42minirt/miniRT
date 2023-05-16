#include "minirt.h"

static char	*get_path(const char *line, size_t *idx)
{
	char	*path;
	size_t	len;

	while (line[*idx] && ft_isspace(line[*idx]))
		*idx += 1;
	if (line[*idx] != '"')
		return (NULL);
	*idx += 1;
	len = 0;
	while (line[*idx + len] && line[*idx + len] != '"')
		len++;
	if (line[*idx + len] != '"')
		return (NULL);
	path = ft_substr(line, *idx, len);
	if (!path)
		return (NULL);
	*idx += len + 1;
	return (path);
}

static bool	is_filename_empty(const char *path)
{
	return (ft_strlen_ns(path) == 0);
}

static t_parse_res	validate_continuous_empty_path(bool *empty)
{
	if (*empty)
		return (ERROR_INVALID_ARG);
	*empty = true;
	return (PASS);
}

t_parse_res	get_image_texture(const char *line, t_img *img, size_t *idx, bool *empty)
{
	t_parse_res	res;
	char		*path;
	int			fd;

	res = ERROR_FATAL;
	path = get_path(line, idx);
	if (!path)
		return (res);
	if (is_filename_empty(path))
	{
		res = validate_continuous_empty_path(empty);
	}
	else
	{
		fd = open(path, O_RDONLY);
		if (fd != OPEN_ERROR)
		{
			res = get_img(img, fd);
			if (close(fd) == CLOSE_ERROR)
				res = ERROR_FATAL;
		}
	}
	free(path);
	return (res);
}
