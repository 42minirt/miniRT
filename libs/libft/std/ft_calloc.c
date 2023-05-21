/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:33:05 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 21:32:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_std.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret_ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (count > SSIZE_MAX / size)
		return (NULL);
	ret_ptr = malloc(count * size);
	if (ret_ptr == NULL)
		return (NULL);
	ft_bzero(ret_ptr, count * size);
	return (ret_ptr);
}
