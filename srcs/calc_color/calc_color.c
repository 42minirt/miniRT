#include "minirt.h"

// c + k1c1 * k2c2
t_color	color_mul_k1c1k2c2(const t_color *c, double k1, const t_color *c1, double k2, const t_color *c2)
{
	t_color	color;

	color.r = c->r + k1 * c1->r * k2 * c2->r;
	color.g = c->g + k1 * c1->g * k2 * c2->g;
	color.b = c->b + k1 * c1->b * k2 * c2->b;
	return (color);
}

t_color	color_k1c1k2c2(double k1, const t_color *c1, double k2, const t_color *c2)
{
	t_color	color;

	color.r = k1 * c1->r * k2 * c2->r;
	color.g = k1 * c1->g * k2 * c2->g;
	color.b = k1 * c1->b * k2 * c2->b;
	return (color);
}

t_color	color_k1c1(double k1, const t_color c1)
{
	t_color	color;

	color.r = k1 * c1.r;
	color.g = k1 * c1.g;
	color.b = k1 * c1.b;
	return (color);
}

t_color	color_add(const t_color c1, const t_color c2)
{
	t_color	color;

	color.r = c1.r + c2.r;
	color.g = c1.g + c2.g;
	color.b = c1.b + c2.b;
	return (color);
}

t_color	init_color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}
