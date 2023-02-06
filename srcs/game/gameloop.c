/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameloop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:18 by mlebard           #+#    #+#             */
/*   Updated: 2021/05/07 19:41:23 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	gameloop(t_cub *cub)
{
	t_img	frame;

	check_game_state(cub);
	update_world(cub);
	frame = make_img(cub->mlx, cub->res.x, cub->res.y);
	if (frame.img == NULL)
		exit_error(cub, ERR_MALLOC, NULL);
	raycasting(cub, &frame);
	draw_hud(cub, &frame);
	if (cub->mini->on == 1)
		display_minimap(cub, cub->mini, &frame);
	mlx_put_image_to_window(cub->mlx, cub->win, frame.img, 0, 0);
	mlx_destroy_image(cub->mlx, frame.img);
	return (0);
}
