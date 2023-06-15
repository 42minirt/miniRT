/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_open.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/17 23:19:51 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys.h"

int	x_open(const char *path, int oflag)
{
	int	ret;

	errno = 0;
	ret = open(path, oflag);
	if (ret == OPEN_ERROR)
		perror("open");
	return (ret);
}
