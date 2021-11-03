/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_target_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:13:55 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:13:56 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	get_dist(t_cub *cub, t_raycast *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->dist.x = (cub->play->pos.x - ray->pos.x) * ray->delt.x;
	}
	else
	{
		ray->step.x = 1;
		ray->dist.x = (ray->pos.x + 1.0 - cub->play->pos.x) * ray->delt.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->dist.y = (cub->play->pos.y - ray->pos.y) * ray->delt.y;
	}
	else
	{
		ray->step.y = 1;
		ray->dist.y = (ray->pos.y + 1.0 - cub->play->pos.y) * ray->delt.y;
	}
}

static int	do_dda(t_cub *cub, t_raycast *ray, double limit)
{
	while (1)
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
			return (0);
		else if ((ray->side == 1 && ray->dist.y >= limit)
			|| (ray->side == 0 && ray->dist.x >= limit))
			return (0);
		else if (ray->pos.y == (int)cub->play->pos.y
			&& ray->pos.x == (int)cub->play->pos.x)
			return (1);
	}
	return (0);
}

int	find_target(t_cub *cub, t_dpos pos, t_vect dir, double limit)
{
	t_raycast	ray;

	ray.dir.x = dir.x;
	ray.dir.y = dir.y;
	ray.pos.x = (int)pos.x;
	ray.pos.y = (int)pos.y;
	ray.delt.x = ft_absd(1 / ray.dir.x);
	ray.delt.y = ft_absd(1 / ray.dir.y);
	get_dist(cub, &ray);
	if (ray.pos.y == (int)cub->play->pos.y
		&& ray.pos.x == (int)cub->play->pos.x)
		return (1);
	else if (do_dda(cub, &ray, limit) == 1)
		return (1);
	else
		return (0);
}
