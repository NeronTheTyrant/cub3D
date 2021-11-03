/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:49:35 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:59:02 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_weapons(t_cub *cub, t_img *frame)
{
	t_hudobj	hands;
	t_hudobj	mace;

	hands = cub->hud->hands;
	put_img_to_frame_alpha(frame, *hands.tex, hands.xcurroff, hands.ycurroff);
	mace = cub->hud->mace;
	put_img_to_frame_alpha(frame, *mace.tex, mace.xcurroff, mace.ycurroff);
}

int	draw_hud(t_cub *cub, t_img *frame)
{
	t_img	cross;

	draw_weapons(cub, frame);
	draw_health(cub, frame);
	cross = cub->hud->crosshair;
	put_img_to_frame_alpha(frame, cross, cub->res.x / 2 - (cross.width / 2),
		cub->res.y / 2 - (cross.height / 2));
	return (SUCCESS);
}
