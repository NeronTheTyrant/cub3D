/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:50:31 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 11:56:10 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_dist(t_cub *cub, t_raycasting *rc)
{
	if (rc->ray.x < 0)
	{
		rc->step.x = -1;
		rc->dist.x = (cub->play.x - rc->pos.x) * rc->delt.x;
	}
	else
	{
		rc->step.x = 1;
		rc->dist.x = (rc->pos.x + 1.0 - cub->play.x) * rc->delt.x;
	}
	if (rc->ray.y < 0)
	{
		rc->step.y = -1;
		rc->dist.y = (cub->play.y - rc->pos.y) * rc->delt.y;
	}
	else
	{
		rc->step.y = 1;
		rc->dist.y = (rc->pos.y + 1.0 - cub->play.y) * rc->delt.y;
	}
}

static void	do_dda(t_cub *cub, t_raycasting *rc)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rc->dist.x < rc->dist.y)
		{
			rc->dist.x += rc->delt.x;
			rc->pos.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->dist.y += rc->delt.y;
			rc->pos.y += rc->step.y;
			rc->side = 1;
		}
		if (cub->map[rc->pos.y][rc->pos.x] == '1')
			hit = 1;
	}
}

static void	get_wall_hit(t_cub *cub, t_raycasting *rc)
{
	double	distx;
	double	disty;

	if (rc->side == 0)
	{
		distx = rc->pos.x - cub->play.x;
		rc->perp_dist = (distx + (1 - rc->step.x) / 2) / rc->ray.x;
		rc->hit = cub->play.y + rc->perp_dist * rc->ray.y;
	}
	else
	{
		disty = rc->pos.y - cub->play.y;
		rc->perp_dist = (disty + (1 - rc->step.y) / 2) / rc->ray.y;
		rc->hit = cub->play.x + rc->perp_dist * rc->ray.x;
	}
	rc->hit -= floor((rc->hit));
}

void	wallcasting(t_cub *cub, t_raycasting *rc, t_img *frame)
{
	double	camerax;
	int		x;

	x = 0;
	while (x < cub->set.resx)
	{
		camerax = 2 * x / (double)(cub->set.resx) - 1;
		rc->ray.x = cub->dir.x + cub->plane.x * camerax;
		rc->ray.y = cub->dir.y + cub->plane.y * camerax;
		rc->pos.x = (int)cub->play.x;
		rc->pos.y = (int)cub->play.y;
		rc->delt.x = ft_absd(1 / rc->ray.x);
		rc->delt.y = ft_absd(1 / rc->ray.y);
		get_dist(cub, rc);
		do_dda(cub, rc);
		get_wall_hit(cub, rc);
		draw_wall(cub, rc, x, frame);
		cub->z[x] = rc->perp_dist;
		x++;
	}
}
