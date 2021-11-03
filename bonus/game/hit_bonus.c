/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:24:46 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 15:24:55 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	hit_event(t_cub *cub, int atk_type, t_event *hit)
{
	(void)atk_type;
	if (hit->type == EVENT_REMOVE)
		event_remove(cub, hit);
	return (0);
}

void	hit_mob(t_cub *cub, int atk_type, t_mob *mob)
{
	int	damage;

	damage = atk_type_to_damage(atk_type);
	if (mob->behaviour != BH_DEATH)
		damage_mob(cub, mob, damage);
}

void	hit_player(t_cub *cub, t_event *ev)
{
	remove_health(cub, ev->val1);
}
