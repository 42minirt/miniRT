/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_std.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:57:14 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 23:49:55 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STD_H
# define FT_STD_H

# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

# include "libft.h"
# include "ft_string.h"

/* itoa atoi */
char		*ft_itoa(int n);
int			ft_atoi(const char *str, bool *is_success);
long long	ft_strtoll(char *num, bool *is_success);
void		*ft_calloc(size_t count, size_t size);

#endif //FT_STD_H
