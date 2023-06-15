/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:02:34 by user              #+#    #+#             */
/*   Updated: 2023/06/14 21:29:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minilibx-linux/mlx.h"
#include "constructor.h"
#include "typedef.h"
#include "minirt.h"
#include "raytrace.h"

static int	validate_argv(int argc, char **argv)
{
	const char	*rt_path;

	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, "%s\n : %s\n", MSG_ERROR, MSG_MISSING_ARG);
		return (FAILURE);
	}
	rt_path = argv[1];
	if (validate_filename(rt_path, RT_EXTENSION) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, "%s\n : %s\n", MSG_ERROR, MSG_INVALID_RT);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_all_info	info;

	if (validate_argv(argc, argv) == FAILURE)
		return (EXIT_FAILURE);
	if (construct_info(&info, argv[1]) == FAILURE)
	{
		destruct_info(&info);
		return (EXIT_FAILURE);
	}
	if (conflict_ch(&info))
	{
		destruct_info(&info);
		ft_dprintf(STDERR_FILENO, "%s\n : %s\n", MSG_ERROR, MSG_OVERLAP);
		return (EXIT_FAILURE);
	}
	mlx_hooks(&info);
	mlx_loop(info.mlx_info->mlx);
	destruct_info(&info);
	return (EXIT_SUCCESS);
}

#ifdef LEAKS

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q miniRT");
}

#endif