/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:12:06 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:12:07 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	exit_done(t_cub *cub)
{
	if (cub != NULL)
	{
		free_cub(cub);
		if (cub->win != NULL)
			mlx_destroy_window(cub->mlx, cub->win);
		if (cub->mlx != NULL)
		{
			mlx_destroy_display(cub->mlx);
			free(cub->mlx);
		}
		free(cub);
	}
	exit(1);
}

void	exit_error(t_cub *cub, int errcode, char *errstring)
{
	cub_error(cub, errcode, errstring);
	exit_done(cub);
}
