/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	x_free_1d_alloc(void **alloc)
{
	if (!alloc)
		return ;
	free(*alloc);
	*alloc = NULL;
}

void	x_free_2d_alloc(void ***alloc)
{
	size_t	i;

	if (!alloc)
		return ;
	i = 0;
	while (*alloc && (*alloc)[i])
	{
		free((*alloc)[i]);
		i++;
	}
	free(*alloc);
	*alloc = NULL;
}
