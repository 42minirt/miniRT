/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:19:51 by takira            #+#    #+#             */
/*   Updated: 2023/05/21 18:09:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "typedef.h"

void		debug_print_config(t_all_info *info);
const char	*get_parse_result_char(t_parse_res res);
void		print_sphere(t_obj *obj);
void		print_plane(t_obj *obj);
void		print_cylinder(t_obj *obj);
void		print_corn(t_obj *obj);

#endif //DEBUG_H
