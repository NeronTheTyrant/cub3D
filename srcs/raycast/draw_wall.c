/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:48:58 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:32:34 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_img	get_wall_tex(t_cub *cub, t_raycast *ray)
{
	int	sfnb;

	sfnb = cub->map[ray->pos.y][ray->pos.x];
	if (ft_isdigit(sfnb) == 1)
		sfnb = sfnb - 48;
	else if (ft_islowercase(sfnb) == 1)
		sfnb = sfnb - 87;
	else if (ft_isuppercase(sfnb) == 1)
		sfnb = sfnb - 29;
	else
		sfnb = 0;
	if (sfnb >= cub->tex_sf->texnbr)
		sfnb = 0;
	return (*cub->sf[sfnb].tex);
}

static void	get_wall_limits(t_cub *cub, t_raycast *ray, t_player *play)
{
	int	height;
	int	top;
	int	bot;

	height = (int)(cub->res.y / ray->perp_dist);
	top = -height / 2 + cub->res.y / 2
		+ play->pitch + (play->renderz / ray->perp_dist);
	if (top >= cub->res.y || top < 0)
		top = 0;
	bot = height / 2 + cub->res.y / 2
		+ play->pitch + (play->renderz / ray->perp_dist);
	if (bot < 0 || bot >= cub->res.y)
		bot = cub->res.y - 1;
	ray->wallheight = height;
	ray->walltop = top;
	ray->wallbot = bot;
}

void	draw_wall(t_cub *cub, t_raycast *ray, int x, t_img *frame)
{
	t_img	tex;
	t_dpos	texel;
	double	step;
	int		y;

	get_wall_limits(cub, ray, cub->play);
	tex = get_wall_tex(cub, ray);
	texel.x = (int)(ray->hit * (double)(tex.width)) & (tex.width - 1);
	if (ray->side == 0 && ray->dir.x < 0)
		texel.x = tex.width - texel.x - 1;
	if (ray->side == 1 && ray->dir.y > 0)
		texel.x = tex.width - texel.x - 1;
	step = 1.0 * tex.height / (ray->wallheight);
	texel.y = (ray->walltop - cub->play->pitch - (cub->play->renderz
				/ ray->perp_dist) - cub->res.y / 2 + ray->wallheight / 2)
		* step;
	y = ray->walltop;
	while (y <= ray->wallbot)
	{
		my_mlx_pixel_put(frame, x, y, add_shade(ray->perp_dist,
				get_pixel((int)texel.x, (int)texel.y & (tex.height - 1), tex)));
		texel.y += step;
		y++;
	}
}
