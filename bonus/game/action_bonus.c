/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:14:52 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:14:53 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	act_fireball(t_cub *cub, t_hudobj *hands)
{
	while (hands->tex != NULL && cub->time - hands->last_update
		>= hands->tex->delay)
	{
		if (hands->tex == &cub->hud->hands_attack[2])
			spawn_player_projectile(cub, cub->play);
		hands->last_update += hands->tex->delay;
		hands->tex = hands->tex->next_tex;
	}
	if (hands->tex == NULL)
		change_action_idle(cub);
}

static void	act_mace(t_cub *cub, t_hudobj *mace)
{
	while (mace->tex != NULL && cub->time - mace->last_update
		>= mace->tex->delay)
	{
		if (mace->tex == &cub->hud->mace_attack[2])
			player_attack(cub, 1.5);
		mace->last_update += mace->tex->delay;
		mace->tex = mace->tex->next_tex;
	}
	if (mace->tex == NULL)
		change_action_idle(cub);
}

void	update_action(t_cub *cub)
{
	t_hudobj	*hands;
	t_hudobj	*mace;

	hands = &cub->hud->hands;
	mace = &cub->hud->mace;
	if (cub->play->act == ACT_FIREBALL)
		act_fireball(cub, hands);
	else
	{
		while (hands->tex != NULL && cub->time - hands->last_update
			>= hands->tex->delay)
		{
			hands->last_update += hands->tex->delay;
			hands->tex = hands->tex->next_tex;
		}
	}
	if (cub->play->act == ACT_MACE)
		act_mace(cub, mace);
}
