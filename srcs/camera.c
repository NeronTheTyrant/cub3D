/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 11:57:40 by mlebard           #+#    #+#             */
/*   Updated: 2021/02/27 11:44:34 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	turn_left(t_cub *cub, double rotspeed)
{
	double	old_dirx;
	double	old_planex;
	t_vect	dir;
	t_vect	plane;

	dir = cub->dir;
	plane = cub->plane;
	old_dirx = dir.x;
	old_planex = plane.x;
	dir.x = dir.x * cos(-rotspeed) - dir.y * sin(-rotspeed);
	dir.y = old_dirx * sin(-rotspeed) + dir.y * cos(-rotspeed);
	plane.x = plane.x * cos(-rotspeed) - plane.y * sin(-rotspeed);
	plane.y = old_planex * sin(-rotspeed) + plane.y * cos(-rotspeed);
	cub->dir = dir;
	cub->plane = plane;
}

void	turn_right(t_cub *cub, double rotspeed)
{
	double	old_dirx;
	double	old_planex;
	t_vect	dir;
	t_vect	plane;

	dir = cub->dir;
	plane = cub->plane;
	old_dirx = dir.x;
	old_planex = plane.x;
	dir.x = dir.x * cos(rotspeed) - dir.y * sin(rotspeed);
	dir.y = old_dirx * sin(rotspeed) + dir.y * cos(rotspeed);
	plane.x = plane.x * cos(rotspeed) - plane.y * sin(rotspeed);
	plane.y = old_planex * sin(rotspeed) + plane.y * cos(rotspeed);
	cub->dir = dir;
	cub->plane = plane;
}
