/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:46:22 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 23:53:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_gnl.h"
# include "ft_math.h"
# include "ft_printf.h"
# include "ft_put.h"
# include "ft_std.h"
# include "ft_string.h"
# include "ft_list.h"

# define FAILURE		0
# define SUCCESS		1
# define PROCESS_ERROR	(-1)
# define CONTINUE		(-2)
# define BREAK			(-3)

int	ft_isdigit(int c);

#endif
