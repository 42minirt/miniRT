#include "minirt.h"

static t_parse_res	get_checker_info(const char *line, t_obj_color *obj_color, size_t *idx)
{
	obj_color->is_checker = true;
	if (!ft_isdigit(line[*idx]))
		return (ERROR_INVALID_ARG);
	if (parsing_color(line, &obj_color->checker_color, idx) == FAILURE)
		return (ERROR_INVALID_ARG);
	skip_spece(line, idx);
	return (PASS);
}

static t_parse_res	get_perfect_ref_info(const char *line, t_obj_color *obj_color, size_t *idx)
{
	obj_color->is_perfect_ref = true;
	obj_color->perfect_ref_color = init_color(1.0, 1.0, 1.0);
	skip_spece(line, idx);
	return (PASS);
}

static t_parse_res	get_image_texture_info(const char *line, t_obj_color *obj_color, size_t *idx)
{
	t_parse_res	res;
	bool		filename_empty;

	filename_empty = false;
	res = get_image_texture(line, &obj_color->texture_data, idx, &filename_empty);
	if (res != PASS)
		return (ERROR_FATAL);

	skip_delimiter(line, idx);

	res = get_image_texture(line, &obj_color->bump_data, idx, &filename_empty);
	if (res != PASS)
		return (ERROR_FATAL);
	skip_spece(line, idx);
	return (PASS);
}

t_parse_res	get_bonus_detail(const char *line, t_obj *obj, size_t *idx)
{
	char		*option_id;
	t_parse_res	res;

	option_id = get_identifier_str(line, *idx);
	increment_idx_to_next_format(line, idx, option_id);
	if (!option_id)
		return (ERROR_FATAL);
	res = ERROR_FATAL;
	if (is_same_str(option_id, OP_CHECKER_TEXTURE))
		res = get_checker_info(line, &obj->obj_color, idx);
	else if (is_same_str(option_id, OP_PERFECT_REF))
		res = get_perfect_ref_info(line, &obj->obj_color, idx);
	else if (is_same_str(option_id, OP_IMAGE_TEXTURE))
		res = get_image_texture_info(line, &obj->obj_color, idx);
	else
	{
		printf("[DEBUG]invalid bonus option:[%s]\n", option_id);
	}
	free(option_id);
	if (line[*idx])
		return (ERROR_TOO_MANY_INFO);
//	printf("[DEBUG] get_bonus_op SUCCESS\n");
	return (res);
}