/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallcasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:52:24 by mlebard           #+#    #+#             */
/*   Updated: 2021/04/24 15:40:11 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_dist(t_cub *cub, t_raycast *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->dist.x = (cub->play->render.x - ray->pos.x) * ray->delt.x;
	}
	else
	{
		ray->step.x = 1;
		ray->dist.x = (ray->pos.x + 1.0 - cub->play->render.x) * ray->delt.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->dist.y = (cub->play->render.y - ray->pos.y) * ray->delt.y;
	}
	else
	{
		ray->step.y = 1;
		ray->dist.y = (ray->pos.y + 1.0 - cub->play->render.y) * ray->delt.y;
	}
}

static void	do_dda(t_cub *cub, t_raycast *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->dist.x < ray->dist.y)
		{
			ray->dist.x += ray->delt.x;
			ray->pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->dist.y += ray->delt.y;
			ray->pos.y += ray->step.y;
			ray->side = 1;
		}
		if (ft_isin(cub->map[ray->pos.y][ray->pos.x], cub->wallc) != -1)
			hit = 1;
	}
}

static void	get_wall_hit(t_cub *cub, t_raycast *ray)
{
	double	distx;
	double	disty;

	if (ray->side == 0)
	{
		distx = ray->pos.x - cub->play->render.x;
		ray->perp_dist = (distx + (1 - ray->step.x) / 2) / ray->dir.x;
		ray->hit = cub->play->render.y + ray->perp_dist * ray->dir.y;
	}
	else
	{
		disty = ray->pos.y - cub->play->render.y;
		ray->perp_dist = (disty + (1 - ray->step.y) / 2) / ray->dir.y;
		ray->hit = cub->play->render.x + ray->perp_dist * ray->dir.x;
	}
	ray->hit -= floor((ray->hit));
}

void	wallcasting(t_cub *cub, t_raycast *ray, t_img *frame)
{
	double	camerax;
	int		x;

	x = 0;
	while (x < cub->res.x)
	{
		camerax = 2 * x / (double)(cub->res.x) - 1;
		ray->dir.x = cub->play->dir.x + cub->play->plane.x * camerax;
		ray->dir.y = cub->play->dir.y + cub->play->plane.y * camerax;
		ray->pos.x = (int)cub->play->render.x;
		ray->pos.y = (int)cub->play->render.y;
		ray->delt.x = ft_absd(1 / ray->dir.x);
		ray->delt.y = ft_absd(1 / ray->dir.y);
		get_dist(cub, ray);
		do_dda(cub, ray);
		get_wall_hit(cub, ray);
		draw_wall(cub, ray, x, frame);
		cub->z[x] = ray->perp_dist;
		floorcasting(cub, cub->floor, x, frame);
		x++;
	}
}
