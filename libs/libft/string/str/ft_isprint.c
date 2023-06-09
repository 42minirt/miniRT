/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:30:15 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 23:56:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ft_string.h"

int	ft_isprint(int c)
{
	return ('\040' <= c && c <= '\176');
}
