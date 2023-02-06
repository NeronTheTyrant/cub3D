/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:49:48 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:49:48 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_hud_obj(t_hudobj *obj, int xoffset, int yoffset, t_img *tex)
{
	obj->xbaseoff = xoffset;
	obj->ybaseoff = yoffset;
	obj->xcurroff = xoffset;
	obj->ycurroff = yoffset;
	obj->tex = tex;
	obj->last_update = clock();
}

static void	set_hud_animation(t_hud *hud)
{
	set_anim(&hud->hands_idle[0], &hud->hands_idle[1], 0.1);
	set_anim(&hud->hands_idle[1], &hud->hands_idle[2], 0.1);
	set_anim(&hud->hands_idle[2], &hud->hands_idle[0], 0.1);
	set_anim(&hud->hands_attack[0], &hud->hands_attack[1], 0.07);
	set_anim(&hud->hands_attack[1], &hud->hands_attack[2], 0.07);
	set_anim(&hud->hands_attack[2], &hud->hands_attack[3], 0.1);
	set_anim(&hud->hands_attack[3], &hud->hands_attack[4], 0.1);
	set_anim(&hud->hands_attack[4], &hud->hands_attack[5], 0.1);
	set_anim(&hud->hands_attack[5], &hud->hands_attack[6], 0.07);
	set_anim(&hud->hands_attack[6], NULL, 0.07);
	set_anim(&hud->mace_attack[0], &hud->mace_attack[1], 0.05);
	set_anim(&hud->mace_attack[1], &hud->mace_attack[2], 0.05);
	set_anim(&hud->mace_attack[2], &hud->mace_attack[3], 0.05);
	set_anim(&hud->mace_attack[3], &hud->mace_attack[4], 0.05);
	set_anim(&hud->mace_attack[4], &hud->mace_attack[5], 0.05);
	set_anim(&hud->mace_attack[5], &hud->mace_attack[6], 0.05);
	set_anim(&hud->mace_attack[6], NULL, 0.05);
}

int	init_hud(t_cub *cub)
{
	if (get_hud_tex(cub, cub->hud) < 0)
		return (-1);
	if (resize_hud(cub, cub->hud) < 0)
		return (-1);
	set_hud_animation(cub->hud);
	return (0);
}
