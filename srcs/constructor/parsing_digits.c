#include "minirt.h"

int	parsing_int_num(const char *line, int *int_num, size_t *idx)
{
	size_t	len;
	char	*num_str;
	bool	is_success;

	skip_spece(line, idx);
	len = 0;
	while (line[*idx + len] && !ft_isspace(line[*idx + len]) && line[*idx + len] != ',')
		len++;
	num_str = ft_substr(line, *idx, len);
	if (!num_str)
	{
		perror("malloc");
		return (FAILURE);
	}
	*idx += len;
	*int_num = ft_atoi(num_str, &is_success);
	free(num_str);

	if (!is_success)
		return (FAILURE);
	return (SUCCESS);
}

int	parsing_double_num(const char *line, double *double_num, size_t *idx)
{
	size_t	len;
	char	*num_str;
	bool	is_success;

	skip_spece(line, idx);
	len = 0;
	while (line[*idx + len] && !ft_isspace(line[*idx + len]) && line[*idx + len] != ',')
		len++;
	num_str = ft_substr(line, *idx, len);
	if (!num_str)
	{
		perror("malloc");
		return (FAILURE);
	}
	*idx += len;
	*double_num = ft_strtod(num_str, &is_success, NULL);
	free(num_str);
	if (!is_success)
		return (FAILURE);
	return (SUCCESS);
}

int parsing_vec(const char *line, t_vec *vec, size_t *idx)
{
	skip_spece(line, idx);
	if (parsing_double_num(line, &vec->x, idx) == FAILURE)
		return (FAILURE);
	skip_delimiter(line, idx);
	if (parsing_double_num(line, &vec->y, idx) == FAILURE)
		return (FAILURE);
	skip_delimiter(line, idx);
	if (parsing_double_num(line, &vec->z, idx) == FAILURE)
		return (FAILURE);
	skip_spece(line, idx);
	return (SUCCESS);
}

// int_num1, int_num2, int_num3
int parsing_color(const char *line, t_color *color, size_t *idx)
{
	int	int_r;
	int	int_g;
	int	int_b;

	skip_spece(line, idx);
	if (parsing_int_num(line, &int_r, idx) == FAILURE)
		return (FAILURE);
	skip_delimiter(line, idx);
	if (parsing_int_num(line, &int_g, idx) == FAILURE)
		return (FAILURE);
	skip_delimiter(line, idx);
	if (parsing_int_num(line, &int_b, idx) == FAILURE)
		return (FAILURE);
	skip_spece(line, idx);
	*color = init_color((double)int_r, (double)int_g, (double)int_b);
	return (SUCCESS);
}
