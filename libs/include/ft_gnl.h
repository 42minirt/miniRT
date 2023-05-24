/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:57:14 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 23:50:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GNL_H
# define FT_GNL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>

# include "libft.h"

# define BUFFER_SIZE 256

/* gnl */
char		*get_next_line(int fd, bool is_include_nl);
char		*strjoin_and_free_dst(char *dst, char *src);

void		*ft_free_gnl(char **alloc1, char **alloc2);

size_t		ft_strlen_gnl(const char *str);
size_t		cnt_chr_in_str(const char c, const char *str);
size_t		ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);

#endif //FT_GNL_H
