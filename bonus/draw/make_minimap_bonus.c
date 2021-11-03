/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:50:37 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:40:57 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	get_minimap_color(t_cub *cub, t_minimap *mini, t_dpos map_pos)
{
	char	maptile;

	if (map_pos.x < 0 || map_pos.x >= cub->map_w || map_pos.y < 0
		|| map_pos.y >= cub->map_h)
		return (mini->wall_color);
	else
		maptile = cub->map[(int)map_pos.y][(int)map_pos.x];
	if (maptile == '0')
		return (mini->floor_color);
	else
		return (mini->wall_color);
}

static int	make_minimap(t_cub *cub, t_minimap *mini, t_img *minimap,
		t_img *frame)
{
	t_pos	screen;
	t_dpos	map;

	screen.y = 0;
	while (screen.y < mini->limits.y)
	{
		map.y = cub->play->pos.y + ((screen.y - mini->limits.y / 2)
				/ (double)mini->tilesize);
		screen.x = 0;
		while (screen.x < mini->limits.x)
		{
			map.x = cub->play->pos.x + ((screen.x - mini->limits.x / 2)
					/ (double)mini->tilesize);
			my_mlx_pixel_put(minimap, screen.x, screen.y,
				add_alpha(get_pixel(cub->res.x - mini->limits.x
						+ screen.x, screen.y, *frame),
					get_minimap_color(cub, mini, map)));
			screen.x++;
		}
		screen.y++;
	}
	return (0);
}

static void	display_player(t_cub *cub, t_pos pos, int ratio, t_img *minimap)
{
	t_triangle	tri;
	int			color;

	tri.v1.x = (pos.x + cub->play->dir.x / 2) * ratio + ratio / 2;
	tri.v1.y = (pos.y + cub->play->dir.y / 2) * ratio;
	tri.v2.x = (pos.x - cub->play->dir.x / 2 + cub->play->plane.x / 1.6)
		* ratio + ratio / 2;
	tri.v2.y = (pos.y - cub->play->dir.y / 2 + cub->play->plane.y / 1.6)
		* ratio;
	tri.v3.x = (pos.x - cub->play->dir.x / 2 - cub->play->plane.x / 1.6)
		* ratio + ratio / 2;
	tri.v3.y = (pos.y - cub->play->dir.y / 2 - cub->play->plane.y / 1.6)
		* ratio;
	color = cub->mini->player_color;
	draw_line(tri.v1, tri.v2, color, minimap);
	draw_line(tri.v1, tri.v3, color, minimap);
	draw_line(tri.v3, tri.v2, color, minimap);
	draw_triangle(tri, color, minimap);
}

void	display_minimap(t_cub *cub, t_minimap *mini, t_img *frame)
{
	t_img	minimap;

	minimap.img = mlx_new_image(cub->mlx, mini->limits.x, mini->limits.y);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bpp,
			&minimap.linelen, &minimap.endi);
	minimap.height = mini->limits.y;
	minimap.width = mini->limits.x;
	make_minimap(cub, mini, &minimap, frame);
	display_player(cub, get_pos(mini->range.x, mini->range.y), mini->tilesize,
		&minimap);
	mlx_put_image_to_window(cub->mlx, cub->win, minimap.img,
		cub->res.x - mini->limits.x, 0);
	put_img_to_frame_alpha(frame, minimap, cub->res.x - mini->limits.x, 0);
	mlx_destroy_image(cub->mlx, minimap.img);
}

int	init_minimap(t_cub *cub, t_minimap *mini)
{
	mini->limits.x = cub->res.x / mini->ratio.x;
	mini->limits.y = cub->res.y / mini->ratio.y;
	mini->range.x = mini->limits.x / (mini->tilesize * 2);
	mini->range.y = mini->limits.y / (mini->tilesize * 2);
	if (mini->range.x == 0 || mini->range.y == 0)
		return (ERR_MINI_SMALL);
	return (SUCCESS);
}
