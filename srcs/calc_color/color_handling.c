/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:35:43 by user              #+#    #+#             */
/*   Updated: 2023/05/17 22:28:19 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	color_set(t_color *tgt, double R, double G, double B)
{
	tgt->r = R;
	tgt->g = G;
	tgt->b = B;
}

void	color_add_pointer(t_color *tgt, t_color *t1, t_color *t2)
{
	color_set(
		tgt,
		t1->r + t2->r,
		t1->g + t2->g,
		t1->b + t2->b
	);
}
