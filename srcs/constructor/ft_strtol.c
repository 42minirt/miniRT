/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:38:53 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 20:14:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	get_sign(const char *str, size_t *idx, int *sign)
{
	*sign = 1;
	if (str[*idx] != '+' && str[*idx] != '-')
		return ;
	if (str[*idx] == '+')
	{
		*idx += 1;
		return ;
	}
	if (str[*idx] == '-')
	{
		*idx += 1;
		*sign = -1;
	}
}

static bool	is_overflow(long before_x10_val, int add_val, int sign)
{
	long	ov_div;
	long	ov_mod;

	if (sign == 1)
	{
		ov_div = LONG_MAX / 10;
		ov_mod = LONG_MAX % 10;
	}
	else
	{
		ov_div = -(LONG_MIN / 10);
		ov_mod = -(LONG_MIN % 10);
	}
	if (before_x10_val > ov_div)
		return (true);
	if (before_x10_val == ov_div && add_val > ov_mod)
		return (true);
	return (false);
}

static long	get_long_num(const char *str, size_t *idx, int sign, bool *is_of)
{
	long	ret_num;
	int		digit;

	ret_num = 0;
	*is_of = false;
	while (ft_isdigit(str[*idx]))
	{
		digit = str[*idx] - '0';
		if (is_overflow(ret_num, digit, sign))
		{
			*is_of = true;
			while (ft_isdigit(str[*idx]))
				*idx += 1;
			if (sign == 1)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		ret_num = ret_num * 10 + digit;
		*idx += 1;
	}
	ret_num *= sign;
	return (ret_num);
}

long	ft_strtol(const char *str, bool *is_of, char **endptr)
{
	long	ret_num;
	int		sign;
	size_t	idx;

	*is_of = false;
	ret_num = 0;
	idx = 0;
	if (endptr)
		*endptr = (char *)&str[idx];
	while (str[idx] && ft_isspace(str[idx]))
		idx++;
	get_sign(str, &idx, &sign);
	if (!ft_isdigit(str[idx]))
		return (ret_num);
//	printf(" 1 %s str:%s, ret_num:%ld\n", __func__, str, ret_num);
	ret_num = get_long_num(str, &idx, sign, is_of);
//	printf(" 1 %s ret_num:%ld\n", __func__, ret_num);
	if (endptr)
		*endptr = (char *)&str[idx];
	return (ret_num);
}

//bool	ft_strtol(const char *str, long *ret_num, char **endptr)
//{
//	int		sign;
//	size_t	idx;
//	bool	is_overflow_occurred;
//
//	*ret_num = 0;
//	idx = 0;
//	if (endptr)
//		*endptr = (char *)&str[idx];
//	while (is_space(str[idx]))
//		idx++;
//	get_sign(str, &idx, &sign);
//	if (!ft_isdigit(str[idx]))
//		return (false);
//	*ret_num = get_long_num(str, &idx, sign, &is_overflow_occurred);
//	if (endptr)
//		*endptr = (char *)&str[idx];
//	if (is_overflow_occurred)
//		return (false);
//	return (true);
//}

