#ifndef COLOR_H
# define COLOR_H

# include "minirt.h"

// color
t_color	color_mul_k1c1k2c2(const t_color *c, double k1, \
							const t_color *c1, double k2, const t_color *c2);
t_color	color_k1c1k2c2(double k1, const t_color *c1, \
						double k2, const t_color *c2);
t_color	color_k1c1(double k1, const t_color c1);
t_color	color_add(const t_color c1, const t_color c2);
t_color	init_color(double r, double g, double b);

#endif //COLOR_H
