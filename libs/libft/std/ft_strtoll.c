/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:11:40 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 21:41:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_std.h"

static bool	is_less_than_ll(long long before_x10, long long add, long long sign)
{
	long long	ov_div;
	long long	ov_mod;

	if (sign == 1)
	{
		ov_div = __LONG_LONG_MAX__ / 10;
		ov_mod = __LONG_LONG_MAX__ % 10;
	}
	// else
	// {
	// 	ov_div = ((unsigned long)-__LONG_LONG_MIN__) / 10;
	// 	ov_mod = ((unsigned long)-__LONG_LONG_MIN__) % 10;
	// }
	if (before_x10 > ov_div)
		return (false);
	if (before_x10 == ov_div && add > ov_mod)
		return (false);
	return (true);
}

static int	get_sign_and_increment_ptr(char *num, size_t *idx)
{
	long long	sign;

	sign = 1;
	if (num[*idx] == '-' || num[*idx] == '+')
	{
		if (num[*idx] == '-')
			sign = -1;
		*idx += 1;
	}
	return (sign);
}

static long long	ret_over_flow(long long sign)
{
	// if (sign > 0)
	(void)sign;
	return (__LONG_LONG_MAX__);
	// return (__LONG_LONG_MIN__);
}

long long	ft_strtoll(char *num, bool *is_success)
{
	long long	llnum;
	long long	sign;
	size_t		idx;

	*is_success = false;
	llnum = 0;
	idx = 0;
	while (ft_isspace(num[idx]))
		idx++;
	sign = get_sign_and_increment_ptr(num, &idx);
	if (!num[idx])
		return (0);
	while (num[idx] && ft_isdigit(num[idx]))
	{
		if (is_less_than_ll(llnum, num[idx] - '0', sign))
		{
			llnum = llnum * 10 + (long long)(num[idx] - '0');
			idx++;
			continue ;
		}
		return (ret_over_flow(sign));
	}
	if (!num[idx])
		*is_success = true;
	return (sign * llnum);
}
