/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:35:43 by user              #+#    #+#             */
/*   Updated: 2023/05/16 23:42:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void	color_set(t_color *tgt, double R, double G, double B)
{
	tgt->R = R;
	tgt->G = G;
	tgt->B = B;
}

void	color_add(t_color *tgt, t_color *t1, t_color *t2)
{
	color_set(
		tgt,
		t1->R + t2->R,
		t1->G + t2->G,
		t1->B + t2->B
	);
}