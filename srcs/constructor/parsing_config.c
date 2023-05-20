/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <fcntl.h>

static t_parse_res	get_config_controller(t_identifier id_no, \
										const char *line, t_all_info *all)
{
	t_parse_res	result;

	result = ERROR_FATAL;
	if (id_no == id_camera)
		result = get_camera_setting(line, all->camera_info);
	else if (id_no == id_ambient)
		result = get_ambient_setting(line, all->scene_info);
	else if (id_no == id_point_light || id_no == id_spot_light)
		result = get_lights_setting(line, all->scene_info, id_no);
	else if (id_no == id_plane || id_no == id_sphere \
	|| id_no == id_cylinder || id_no == id_corn)
		result = get_objects_setting(line, all->scene_info, id_no);
	return (result);
}

static bool	is_comment_line(char c)
{
	return (c == '#');
}

// spaces <id> spaces <num1> spaces <num2> ... <numN>
static t_parse_res	parse_line(t_all_info *all, const char *line)
{
	size_t		idx;
	char		*id_str;
	t_parse_res	result;
	int			id_no;

	idx = 0;
	skip_spece(line, &idx);
	if (!line[idx] || is_comment_line(line[idx]))
		return (PASS);
	id_str = get_identifier_str(line, idx);
	if (!id_str)
		return (ERROR_FATAL);
	increment_idx_to_next_format(line, &idx, id_str);
	id_no = get_identifier_no(id_str);
	free(id_str);
	if (id_no == ERROR_INVALID_TYPE)
		return (ERROR_INVALID_TYPE);
	skip_spece(line, &idx);
	if (!line[idx])
		return (ERROR_LACK_INFO);
	result = get_config_controller(id_no, &line[idx], all);
	return (result);
}

static t_parse_res	parse_config_line_by_line(t_all_info *all, int fd)
{
	char		*line;
	t_parse_res	parse_result;
	t_parse_res	ret_res;

	ret_res = PASS;
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		parse_result = parse_line(all, line);
		if (parse_result != PASS)
			ret_res = parse_result;
		free(line);
	}
	return (ret_res);
}

t_parse_res	parsing_config(t_all_info *all, const char *rt_path)
{
	int			fd;
	t_parse_res	result;

	errno = 0;
	fd = open(rt_path, O_RDONLY);
	if (fd == OPEN_ERROR)
	{
		perror("open");
		return (ERROR_FATAL);
	}
	result = parse_config_line_by_line(all, fd);
	errno = 0;
	if (close(fd) == CLOSE_ERROR)
	{
		perror("close");
		return (ERROR_FATAL);
	}
	return (result);
}
