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

// camera, ambient は free
// listに追加できなかったlight, objもこの段階でfree
// listに格納されているlight, objは list_clearでfreeされる
static bool	is_free_needed(char *id_str, t_parse_res result)
{
	if (is_equal_strings(id_str, ID_CAMERA))
		return (true);
	if (is_equal_strings(id_str, ID_AMBIENT))
		return (true);
	if (result != PASS)
		return (true);
	return (false);
}

static t_parse_res	ret_res_and_free(t_parse_res ret, char *id_str)
{
	x_free_1d_alloc((void **)&id_str);
	return (ret);
}

// spaces <id> spaces <num1> spaces <num2> ... <numN>
static t_parse_res	parse_line(t_all_info *all, const char *line, t_id_cnt *cnt)
{
	size_t		idx;
	char		*id_str;
	t_parse_res	result;

	idx = 0;
	skip_spece(line, &idx);
	if (!line[idx] || is_comment_line(line[idx]))
		return (PASS);
	id_str = get_identifier_str(line, idx);
	if (!id_str)
		return (ERROR_FATAL);
	increment_idx_to_next_format(line, &idx, id_str);
	skip_spece(line, &idx);
	if (validate_id(id_str) != PASS)
		return (ret_res_and_free(ERROR_INVALID_TYPE, id_str));
	if (!line[idx])
		return (ret_res_and_free(ERROR_LACK_INFO, id_str));
	result = get_config(id_str, &line[idx], all);
	if (result == PASS)
		increment_id_cnt(id_str, cnt);
	if (is_free_needed(id_str, result))
		x_free_1d_alloc((void **)&id_str);
	return (result);
}

// errorがあればparseせずgnlを空にする
static t_parse_res	parse_config_line_by_line(t_all_info *all, int fd, t_id_cnt *cnt)
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
		if (ret_res == PASS)
			parse_result = parse_line(all, line, cnt);
		if (parse_result != PASS)
			ret_res = parse_result;
		x_free_1d_alloc((void **)&line);
	}
	return (ret_res);
}

t_parse_res	parsing_config(t_all_info *all, const char *rt_path)
{
	int			fd;
	t_parse_res	result;
	t_id_cnt	cnt;

	errno = 0;
	fd = open(rt_path, O_RDONLY);
	if (fd == OPEN_ERROR)
	{
		perror("open");
		return (ERROR_FATAL);
	}
	result = ERROR_FATAL;
	cnt = init_id_cnt();
	result = parse_config_line_by_line(all, fd, &cnt);
	errno = 0;
	if (close(fd) == CLOSE_ERROR)
	{
		perror("close");
		return (ERROR_FATAL);
	}
	if (result == PASS)
		result = validate_id_cnt(cnt);
	return (result);
}

