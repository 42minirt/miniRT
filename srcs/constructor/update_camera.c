#include "minirt.h"

void	update_camera(t_camera_info *camera)
{
	camera->direction = norm_vec(camera->direction);
}
