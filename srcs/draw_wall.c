/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:39:24 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:04:00 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_img	get_wall_tex(t_cub *cub, t_raycasting *rc)
{
	if (rc->side == 0)
	{
		if (rc->step.x == -1)
			return (cub->set.txeast);
		else
			return (cub->set.txwest);
	}
	else
	{
		if (rc->step.y == -1)
			return (cub->set.txsouth);
		else
			return (cub->set.txnorth);
	}
}

static void	get_wall_limits(t_cub *cub, t_raycasting *rc, t_wall *wall)
{
	int	height;
	int	top;
	int	bot;

	height = (int)(cub->set.resy / rc->perp_dist);
	top = -height / 2 + cub->set.resy / 2;
	if (top >= cub->set.resy || top < 0)
		top = 0;
	bot = height / 2 + cub->set.resy / 2;
	if (bot < 0 || bot >= cub->set.resy)
		bot = cub->set.resy - 1;
	wall->height = height;
	wall->top = top;
	wall->bot = bot;
}

static void	get_tex_coord(t_cub *cub, t_raycasting *rc, t_wall *wall,
				t_img tex)
{
	t_posmax	texel;
	double		step;
	double		texpos;

	texel.x = (int)(rc->hit * (double)(tex.width));
	if (rc->side == 0 && rc->ray.x < 0)
		texel.x = tex.width - texel.x - 1;
	if (rc->side == 1 && rc->ray.y > 0)
		texel.x = tex.width - texel.x - 1;
	step = 1.0 * tex.height / wall->height;
	texpos = (wall->top - cub->set.resy / 2 + wall->height / 2) * step;
	wall->texel = texel;
	wall->step = step;
	wall->texpos = texpos;
}

void	draw_wall(t_cub *cub, t_raycasting *rc, int x, t_img *frame)
{
	t_wall		wall;
	int			color;
	t_img		tex;
	intmax_t	index;
	int			y;

	ft_bzero(&wall, sizeof(wall));
	get_wall_limits(cub, rc, &wall);
	tex = get_wall_tex(cub, rc);
	get_tex_coord(cub, rc, &wall, tex);
	color = 0;
	vertline(x, get_pos(0, wall.top), cub->set.c_rgb, frame);
	vertline(x, get_pos(wall.top, cub->set.resy - 1), cub->set.f_rgb, frame);
	y = wall.top;
	while (y < wall.bot)
	{
		wall.texel.y = (intmax_t)wall.texpos;
		wall.texpos += wall.step;
		index = wall.texel.y * tex.linelen + wall.texel.x * (tex.bpp / 8);
		ft_memcpy(&color, &tex.addr[index], 4);
		my_mlx_pixel_put(frame, x, y, color);
		y++;
	}
}
