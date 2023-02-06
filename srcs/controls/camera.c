/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:46:11 by mlebard           #+#    #+#             */
/*   Updated: 2021/04/12 16:26:54 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	turn_left(t_cub *cub, double rotspeed)
{
	double	old_dirx;
	double	old_planex;
	t_vect	dir;
	t_vect	plane;

	dir = cub->play->dir;
	plane = cub->play->plane;
	old_dirx = dir.x;
	old_planex = plane.x;
	dir.x = dir.x * cos(-rotspeed) - dir.y * sin(-rotspeed);
	dir.y = old_dirx * sin(-rotspeed) + dir.y * cos(-rotspeed);
	plane.x = plane.x * cos(-rotspeed) - plane.y * sin(-rotspeed);
	plane.y = old_planex * sin(-rotspeed) + plane.y * cos(-rotspeed);
	cub->play->dir = dir;
	cub->play->plane = plane;
}

void	turn_right(t_cub *cub, double rotspeed)
{
	double	old_dirx;
	double	old_planex;
	t_vect	dir;
	t_vect	plane;

	dir = cub->play->dir;
	plane = cub->play->plane;
	old_dirx = dir.x;
	old_planex = plane.x;
	dir.x = dir.x * cos(rotspeed) - dir.y * sin(rotspeed);
	dir.y = old_dirx * sin(rotspeed) + dir.y * cos(rotspeed);
	plane.x = plane.x * cos(rotspeed) - plane.y * sin(rotspeed);
	plane.y = old_planex * sin(rotspeed) + plane.y * cos(rotspeed);
	cub->play->dir = dir;
	cub->play->plane = plane;
}

void	look_up(t_cub *cub, double rotspeed)
{
	int	half_resy;

	half_resy = cub->res.y / 2;
	cub->play->pitch += 400 * rotspeed;
	if (cub->play->pitch > half_resy)
		cub->play->pitch = half_resy;
}

void	look_down(t_cub *cub, double rotspeed)
{
	int	half_resy;

	half_resy = cub->res.y / 2;
	cub->play->pitch -= 400 * rotspeed;
	if (cub->play->pitch < -half_resy)
		cub->play->pitch = -half_resy;
}
