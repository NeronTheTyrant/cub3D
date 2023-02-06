/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:12:53 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:26:24 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_floorwall(t_floorcast *floor, t_raycast *ray)
{
	if (ray->side == 0 && ray->dir.x > 0)
	{
		floor->wall.x = ray->pos.x;
		floor->wall.y = ray->pos.y + ray->hit;
	}
	else if (ray->side == 0 && ray->dir.x < 0)
	{
		floor->wall.x = ray->pos.x + 1.0;
		floor->wall.y = ray->pos.y + ray->hit;
	}
	else if (ray->side == 1 && ray->dir.y > 0)
	{
		floor->wall.x = ray->pos.x + ray->hit;
		floor->wall.y = ray->pos.y;
	}
	else
	{
		floor->wall.x = ray->pos.x + ray->hit;
		floor->wall.y = ray->pos.y + 1.0;
	}
}

void	draw_ceiling(t_cub *cub, t_floorcast *floor, int x, t_img *frame)
{
	int		y;
	t_img	tex;
	double	wt;
	t_pos	texel;

	y = 0;
	while (y < cub->ray->walltop)
	{
		floor->currdist = (cub->res.y - (2.0 * cub->play->renderz))
			/ (cub->res.y - 2.0 * (y - cub->play->pitch));
		wt = floor->currdist / cub->ray->perp_dist;
		floor->pos.x = wt * floor->wall.x + (1.0 - wt) * cub->play->render.x;
		floor->pos.y = wt * floor->wall.y + (1.0 - wt) * cub->play->render.y;
		tex = get_ceil_tex(cub, floor);
		if (tex.img == cub->tex_sky.img)
			draw_skybox(cub, x, y, frame);
		else
		{
			texel.x = (int)(floor->pos.x * tex.width) & (tex.width - 1);
			texel.y = (int)(floor->pos.y * tex.height) & (tex.height - 1);
			my_mlx_pixel_put(frame, x, y, add_shade(floor->currdist,
					get_pixel(texel.x, texel.y, tex)));
		}
		y++;
	}
}

void	draw_floor(t_cub *cub, t_floorcast *floor, int x, t_img *frame)
{
	int		y;
	t_img	tex;
	double	wt;
	t_pos	texel;

	y = cub->ray->wallbot + 1;
	while (y < cub->res.y)
	{
		floor->currdist = (cub->res.y + (2.0 * cub->play->renderz))
			/ (2.0 * (y - cub->play->pitch) - cub->res.y);
		wt = floor->currdist / cub->ray->perp_dist;
		floor->pos.x = wt * floor->wall.x + (1.0 - wt) * cub->play->render.x;
		floor->pos.y = wt * floor->wall.y + (1.0 - wt) * cub->play->render.y;
		tex = get_floor_tex(cub, floor);
		texel.x = (int)(floor->pos.x * tex.width) & (tex.width - 1);
		texel.y = (int)(floor->pos.y * tex.height) & (tex.height - 1);
		my_mlx_pixel_put(frame, x, y, add_shade(floor->currdist,
				get_pixel(texel.x, texel.y, tex)));
		y++;
	}
}

void	floorcasting(t_cub *cub, t_floorcast *floor, int x,
				t_img *frame)
{
	get_floorwall(floor, cub->ray);
	cub->sky->texel.x = (cub->sky->leftside + cub->sky->step.x * x)
		* (cub->tex_sky.width - 1);
	if (cub->ray->wallbot < 0)
		cub->ray->wallbot = cub->res.y;
	draw_ceiling(cub, floor, x, frame);
	draw_floor(cub, floor, x, frame);
}
