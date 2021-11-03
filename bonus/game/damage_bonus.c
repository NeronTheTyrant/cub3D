/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:15:02 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:15:08 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	atk_type_to_damage(int atk_type)
{
	if (atk_type == ATK_FIREBALL)
		return (2);
	else if (atk_type == ATK_MACE)
		return (3);
	return (0);
}

void	damage_mob(t_cub *cub, t_mob *mob, int damage)
{
	t_sprite	*sp;

	sp = get_sprite_by_id(cub->sp, mob->sp_id);
	mob->hp = ft_ishigher(0, mob->hp - damage);
	if (mob->hp <= 0)
	{
		sp->collision = 0;
		change_behaviour_dying(cub, mob, sp);
	}
	else
		change_behaviour_hurt(cub, mob, sp);
}
