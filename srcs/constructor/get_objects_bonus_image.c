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

t_parse_res	get_image_texture(const char *line, t_img *img, size_t *idx)
{
	t_parse_res	res;
	char		*path;
	int			fd;

	res = ERROR_FATAL;
	path = get_path(line, idx);
	if (!path)
		return (res);
	fd = open(path, O_RDONLY);
	if (fd != OPEN_ERROR)
	{
		if (get_img(img, fd) == SUCCESS)
			res = PASS;
		if (close(fd) == CLOSE_ERROR)
			res = ERROR_FATAL;
	}
	free(path);
	return (res);
}
