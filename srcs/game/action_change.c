/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_change.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:14:59 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:15:00 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fireball(t_cub *cub)
{
	if (cub->play->act == 0)
		change_action_fireball(cub);
}

void	mace(t_cub *cub)
{
	if (cub->play->act == 0)
		change_action_mace(cub);
}

void	change_action_fireball(t_cub *cub)
{
	cub->play->act = ACT_FIREBALL;
	cub->hud->hands.tex = &cub->hud->hands_attack[0];
}

void	change_action_idle(t_cub *cub)
{
	cub->play->act = ACT_IDLE;
	cub->hud->hands.tex = &cub->hud->hands_idle[0];
	cub->hud->mace.tex = &cub->hud->mace_idle;
}

void	change_action_mace(t_cub *cub)
{
	cub->play->act = ACT_MACE;
	cub->hud->mace.last_update = cub->time;
	cub->hud->mace.tex = &cub->hud->mace_attack[0];
}
