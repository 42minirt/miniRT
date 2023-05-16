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
//	printf(" parsing vec(1) %s\n", &line[*idx]);
	skip_spece(line, idx);
//	printf(" parsing vec(2) %s\n", &line[*idx]);
	if (parsing_double_num(line, &vec->x, idx) == FAILURE)
	{
//		printf("    parsing_vec NG :: parsing_double_num 1\n");
		return (FAILURE);
	}
//	printf(" parsing vec(3) %s\n", &line[*idx]);

	skip_delimiter(line, idx);

//	printf(" parsing vec(4) %s\n", &line[*idx]);

	if (parsing_double_num(line, &vec->y, idx) == FAILURE)
	{
//		printf("    parsing_vec NG :: parsing_double_num 2\n");
		return (FAILURE);
	}
//	printf(" parsing vec(5) %s\n", &line[*idx]);

	skip_delimiter(line, idx);
//	printf(" parsing vec(6) %s\n", &line[*idx]);

	if (parsing_double_num(line, &vec->z, idx) == FAILURE)
	{
//		printf("    parsing_vec NG :: parsing_double_num 3\n");
		return (FAILURE);
	}
//	printf(" parsing vec(7) %s\n", &line[*idx]);

	skip_spece(line, idx);
//	printf(" parsing vec(8) %s\n", &line[*idx]);

//	printf("    parsing_vec :: SUCCESS, (x,y,z)=(%f,%f,%f)\n", vec->x, vec->y, vec->z);

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
	{
//		printf("    parsing_color NG :: parsing_int_num 1, r:%d\n", int_r);
		return (FAILURE);
	}

	skip_delimiter(line, idx);

	if (parsing_int_num(line, &int_g, idx) == FAILURE)
	{
//		printf("    parsing_color NG :: parsing_int_num 2\n");
		return (FAILURE);
	}

	skip_delimiter(line, idx);

	if (parsing_int_num(line, &int_b, idx) == FAILURE)
	{
//		printf("    parsing_color NG :: parsing_int_num 3\n");
		return (FAILURE);
	}

	skip_spece(line, idx);

	*color = init_color((double)int_r, (double)int_g, (double)int_b);
//	printf("    parsing_color :: SUCCESS, (r,g,b)=(%f,%f,%f)\n", color->r, color->g, color->b);
	return (SUCCESS);
}
