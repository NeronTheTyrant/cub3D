/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud_health_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:49:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:59:20 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	display_current_health(t_cub *cub, t_img *frame,
		int *xoffset, int *yoffset)
{
	int	i;
	int	hp_dim;

	i = 0;
	hp_dim = cub->hud->hp_full.width;
	while (i < cub->play->health)
	{
		put_img_to_frame_alpha(frame, cub->hud->hp_full, *xoffset, *yoffset);
		*xoffset += hp_dim;
		if (*yoffset == 0 && i >= 4)
		{
			*xoffset = 0;
			*yoffset += hp_dim;
		}
		i++;
	}
}

static void	display_max_health(t_cub *cub, t_img *frame, int *xoffset,
		int *yoffset)
{
	int	i;
	int	hp_dim;

	i = cub->play->health;
	hp_dim = cub->hud->hp_full.width;
	while (i < cub->play->maxhealth)
	{
		put_img_to_frame_alpha(frame, cub->hud->hp_empty, *xoffset, *yoffset);
		*xoffset += hp_dim;
		if (*yoffset == 0 && i >= 4)
		{
			*xoffset = 0;
			*yoffset += hp_dim;
		}
		i++;
	}
}

int	draw_health(t_cub *cub, t_img *frame)
{
	int	xoffset;
	int	yoffset;

	xoffset = 0;
	yoffset = 0;
	display_current_health(cub, frame, &xoffset, &yoffset);
	display_max_health(cub, frame, &xoffset, &yoffset);
	return (SUCCESS);
}
