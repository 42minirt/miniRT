/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:32:51 by user              #+#    #+#             */
/*   Updated: 2023/05/21 18:32:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYS_H
# define SYS_H

# include "minirt.h"

void	x_free_1d_alloc(void **alloc);
void	x_free_2d_alloc(void ***alloc);
int		x_open(const char *path, int oflag);
int		x_close(int fd);

#endif //SYS_H
