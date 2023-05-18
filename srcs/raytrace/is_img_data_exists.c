#include "minirt.h"

bool	is_bump_data_exists(t_obj_color obj_color)
{
	return (obj_color.bump_data.data != NULL);
}

bool	is_image_data_exists(t_obj_color obj_color)
{
	return (obj_color.texture_data.data != NULL);
}
