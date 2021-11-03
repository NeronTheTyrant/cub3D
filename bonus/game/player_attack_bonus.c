/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_attack_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:15:34 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:15:35 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	player_attack(t_cub *cub, double dist)
{
	t_sprite	*sp;
	t_list		*sp_ptr;
	t_vect		dir;

	sp_ptr = cub->sp;
	while (sp_ptr)
	{
		sp = (t_sprite *)sp_ptr->content;
		if (sp->event == EVENT_REMOVE || sp->mob_id > 0)
		{
			dir = angle_to_vect(get_angle_from_pos(cub->play->pos, sp->pos));
			if (sqrt(sp->dist) <= dist && angle_diff(dir, cub->play->dir, 0.35))
			{
				if (sp->event == EVENT_REMOVE)
					event_remove(cub, get_event_by_id(cub->event, sp->ev_id));
				else
					hit_mob(cub, ATK_MACE, get_mob_by_id(cub->mob, sp->mob_id));
			}
		}
		sp_ptr = sp_ptr ->next;
	}
}

void	mob_attack(t_cub *cub, t_mob *mob, t_sprite *mob_sp, double dist)
{
	t_sprite	*sp;
	t_list		*sp_ptr;
	t_vect		dir;

	sp_ptr = cub->sp;
	dir = angle_to_vect(get_angle_from_pos(mob->pos, cub->play->pos));
	if (sqrt(mob_sp->dist) <= dist && angle_diff(dir, mob->dir, 0.35))
		remove_health(cub, 2);
	while (sp_ptr)
	{
		sp = (t_sprite *)sp_ptr->content;
		if (sp->event == EVENT_REMOVE)
		{
			dir = angle_to_vect(get_angle_from_pos(mob->pos, sp->pos));
			if (sqrt(sp->dist) <= dist && angle_diff(dir, mob->dir, 0.35))
				if (sp->event == EVENT_REMOVE)
					event_remove(cub, get_event_by_id(cub->event, sp->ev_id));
		}
		sp_ptr = sp_ptr ->next;
	}
}
