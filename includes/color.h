/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:32:47 by user              #+#    #+#             */
/*   Updated: 2023/05/20 20:32:49 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "minirt.h"

// color
t_color	color_mul_k1c1k2c2(t_color *c, double k1, \
							 t_color *c1, double k2, t_color *c2);
t_color	color_k1c1k2c2(double k1, t_color *c1, \
						double k2, t_color *c2);
t_color	color_k1c1(double k1, t_color c1);
t_color	color_add(t_color c1, t_color c2);
t_color	init_color(double r, double g, double b);


void	color_set(t_color *tgt, double R, double G, double B);
void	color_add_pointer(t_color *tgt, t_color *t1, t_color *t2);

#endif //COLOR_H
