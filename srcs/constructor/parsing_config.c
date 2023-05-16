#include "minirt.h"
#include <fcntl.h>

static t_parse_res	get_config_controller(t_identifier id_no, const char *line, t_all_info *all)
{
	t_parse_res	result;

	result = ERROR_FATAL;
	if (id_no == id_camera)
	{
		result = get_camera_setting(line, all->camera_info);
		printf("  [DEBUG] get_params -> camera_ret=%d\n", result);
	}
	else if (id_no == id_ambient)
	{
		result = get_ambient_setting(line, all->scene_info);
		printf("  [DEBUG] get_params -> ambient_ret=%d\n", result);
	}
	else if (id_no == id_point_light || id_no == id_spot_light)
	{
		result = get_lights_setting(line, all->scene_info, id_no);
		printf("  [DEBUG] get_params -> light_ret=%d\n", result);
	}
	else if (id_no == id_plane || id_no == id_sphere || id_no == id_cylinder || id_no == id_corn)
	{
		result = get_objects_setting(line, all->scene_info, id_no);
		printf("  [DEBUG] get_params -> objects_ret=%d\n", result);
	}
	printf("  [DEBUG] get_params :: ret=%d\n", result);
	return (result);
}

// <space> <id> <space> <num1> <space> <num2> ... <numN>
static t_parse_res	parse_line(t_all_info *all, const char *line)
{
	size_t		idx;
	char		*id_str;
	t_parse_res	result;
	int			id_no;

	idx = 0;
	skip_spece(line, &idx);
	if (!line[idx])
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

// debug
void	print_parse_err(t_parse_res result)
{
	if (result == PASS)
		ft_dprintf(STDERR_FILENO, "rf_file : parse complete :)\n");
	else if (result == ERROR_FATAL)
		ft_dprintf(STDERR_FILENO, "rf_file : fatal error occurred X(\n");
	else if (result == ERROR_INVALID_TYPE)
		ft_dprintf(STDERR_FILENO, "rf_file : id invalid :(\n");
	else if (result == ERROR_LACK_INFO)
		ft_dprintf(STDERR_FILENO, "rf_file : line too shortage :o\n");
	else if (result == ERROR_TOO_MANY_INFO)
		ft_dprintf(STDERR_FILENO, "rf_file : line too long :o\n");
	else if (result == ERROR_INVALID_ARG)
		ft_dprintf(STDERR_FILENO, "rf_file : arg invalid ;<\n");
	else if (result == ERROR_OUT_OF_RANGE)
		ft_dprintf(STDERR_FILENO, "rf_file : arg out of range :(\n");
	else if (result == ERROR_MULTIPLE_ID)
		ft_dprintf(STDERR_FILENO, "rf_file : id duplicated :(\n");

}

static int	parse_config_line_by_line(t_all_info *all, int fd)
{
	char		*line;
	int			result;
	t_parse_res	parse_result;

	result = SUCCESS;
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		parse_result = parse_line(all, line);
		if (parse_result != PASS)
		{
			print_parse_err(result);
			result = FAILURE;
		}
		free(line);
	}
	return (result);
}

int	parsing_config(t_all_info *all, const char *rt_path)
{
	int	fd;
	int	result;

	errno = 0;
	fd = open(rt_path, O_RDONLY);
	if (fd == OPEN_ERROR)
	{
		perror("open");
		return (FAILURE);
	}
	result = parse_config_line_by_line(all, fd);
	errno = 0;
	if (close(fd) == CLOSE_ERROR)
	{
		perror("close");
		return (FAILURE);
	}
	return (result);
}

