#include "minirt.h"

// A   lightning_ratio[0,1]   RGB[0,255]
t_parse_res	get_ambient_setting(const char *line, t_scene_info *scene)
{
	size_t	idx;

	if (scene->brightness >= 0)
		return (ERROR_MULTIPLE_ID);

	idx = 0;
	if (parsing_double_num(line, &scene->brightness, &idx) == FAILURE)
	{
		printf("   [DEBUG] ambient NG :: parsing_double_num\n");
		return (ERROR_INVALID_ARG);
	}
	if (parsing_color(line, &scene->ambient_color, &idx) == FAILURE)
	{
		printf("   [DEBUG] ambient NG :: parsing_color\n");
		return (ERROR_INVALID_ARG);
	}
	if (line[idx])
	{
		printf("   [DEBUG] ambient NG :: invalid string=[%s]\n", &line[idx]);
		return (ERROR_TOO_MANY_INFO);
	}
	printf("   [DEBUG] ambient OK :)\n");
	return (PASS);
}
