/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:38:53 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	handle_before_num(const char *str, \
								double *sign, size_t *idx, size_t *i)
{
	while (ft_isspace(str[*idx]))
		*idx += 1;
	if (str[*idx] == '-')
		*sign = -1.0;
	*i = 0;
	if (str[*idx + *i] == '-' || str[*idx + *i] == '+')
		*i += 1;
}

static int	get_num_part(const char *str, \
						double *num, double *sign, size_t *idx)
{
	double	scale;
	size_t	i;

	handle_before_num(str, sign, idx, &i);
	if (!str[*idx + i] || !(ft_isdigit(str[*idx + i]) \
		|| (str[*idx + i] == '.' && ft_isdigit(str[*idx + i + 1]))))
		return (FAILURE);
	*idx += i;
	while (ft_isdigit(str[*idx]))
	{
		*num = *num * 10 + str[*idx] - '0';
		*idx += 1;
	}
	if (str[*idx] == '.')
	{
		*idx += 1;
		scale = 0.1;
		while (ft_isdigit(str[*idx]))
		{
			*num += scale * (double)(str[*idx] - '0');
			scale *= 0.1;
			*idx += 1;
		}
	}
	return (SUCCESS);
}

static int	get_exp_part(const char *str, double *num, size_t *idx)
{
	double	exp;
	double	exp_sign;
	size_t	i;

	exp = 0.0;
	exp_sign = 1.0;
	if (!str[*idx] || !(str[*idx] == 'e' || str[*idx] == 'E'))
		return (SUCCESS);
	i = 1;
	if (!str[*idx + i])
		return (FAILURE);
	if (str[*idx + 1] == '-')
		exp_sign = -1.0;
	if (str[*idx + i] == '-' || str[*idx + i] == '+')
		i++;
	if (!str[*idx + i] || !ft_isdigit(str[*idx + i]))
		return (FAILURE);
	while (ft_isdigit(str[*idx + i]))
	{
		exp = exp * 10 + str[*idx + i] - '0';
		i++;
	}
	*num *= pow(10, exp * exp_sign);
	*idx += i;
	return (SUCCESS);
}

static double	ret_num_and_err(double num, const char *str, char **err)
{
	if (err)
		*err = (char *)str;
	return (num);
}

double	ft_strtod(const char *str, bool *is_success, char **err)
{
	double	num;
	double	num_sign;
	size_t	idx;

	idx = 0;
	num = 0.0;
	num_sign = 1.0;
	*is_success = false;
	if (!str)
		return (ret_num_and_err(num, &str[idx], err));
	if (get_num_part(str, &num, &num_sign, &idx) == FAILURE)
		return (ret_num_and_err(num, &str[idx], err));
	if (get_exp_part(str, &num, &idx) == FAILURE)
		return (ret_num_and_err(num_sign * num, &str[idx], err));
	if (!str[idx])
		*is_success = true;
	return (ret_num_and_err(num_sign * num, &str[idx], err));
}
