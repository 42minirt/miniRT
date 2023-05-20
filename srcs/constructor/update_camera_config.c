#include "minirt.h"

void	update_camera_config(t_camera_info *camera)
{
	camera->direction = norm_vec(camera->direction);
}
