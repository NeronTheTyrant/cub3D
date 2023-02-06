/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:13:55 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:27:18 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static double	get_sky_dir(double dirx, double diry)
{
	return (fabs(atan2(dirx, diry) * 180 / M_PI - 180) / 360);
}

void	draw_skybox(t_cub *cub, int x, int y, t_img *frame)
{
	t_skybox	*sky;
	t_img		sky_tex;

	sky = cub->sky;
	sky_tex = cub->tex_sky;
	sky->texel.y = (sky->pitch_adjust + y * sky->step.y) * (sky_tex.height - 1);
	my_mlx_pixel_put(frame, x, y,
		get_pixel(sky->texel.x, sky->texel.y, sky_tex));
}

void	init_skybox(t_cub *cub, t_skybox *sky, t_player *play)
{
	double	rightside;

	sky->raydirmin.x = cub->play->dir.x - cub->play->plane.x;
	sky->raydirmin.y = cub->play->dir.y - cub->play->plane.y;
	sky->raydirmax.x = cub->play->dir.x + cub->play->plane.x;
	sky->raydirmax.y = cub->play->dir.y + cub->play->plane.y;
	sky->leftside = get_sky_dir(sky->raydirmin.x, sky->raydirmin.y);
	sky->pitch_adjust = (cub->res.y - play->pitch) * sky->step.y;
	if (!sky->step.x)
	{
		rightside = get_sky_dir(sky->raydirmax.x, sky->raydirmax.y);
		sky->step.x = fabs(rightside - sky->leftside) / cub->res.x;
		sky->step.y = 1.0 / (cub->res.y * 1.5);
	}
}
