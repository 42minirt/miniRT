/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_close.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	x_close(int fd)
{
	int	ret;

	errno = 0;
	ret = close(fd);
	if (ret == CLOSE_ERROR)
		perror("close");
	return (ret);
}
