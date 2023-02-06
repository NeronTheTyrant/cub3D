/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_behaviour.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:13:38 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:13:39 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	change_behaviour_idle(t_cub *cub, t_mob *mob, t_sprite *sp)
{
	if (mob->behaviour == BH_DEATH)
		return ;
	mob->behaviour = BH_IDLE;
	update_sprite_tex(cub, sp, mob->base);
}

void	change_behaviour_walk(t_cub *cub, t_mob *mob, t_sprite *sp)
{
	if (mob->behaviour == BH_DEATH)
		return ;
	mob->behaviour = BH_WALKING;
	update_sprite_tex(cub, sp, mob->walking);
}

void	change_behaviour_attack(t_cub *cub, t_mob *mob, t_sprite *sp)
{
	if (mob->behaviour == BH_DEATH)
		return ;
	mob->behaviour = BH_ATTACKING;
	update_sprite_tex(cub, sp, mob->attack);
	mob->lastattack = cub->time;
}

void	change_behaviour_hurt(t_cub *cub, t_mob *mob, t_sprite *sp)
{
	if (mob->behaviour == BH_DEATH)
		return ;
	mob->behaviour = BH_HURT;
	update_sprite_tex(cub, sp, mob->hurt);
	mob->lastattack = cub->time - (mob->attackdelay / 2);
}

void	change_behaviour_dying(t_cub *cub, t_mob *mob, t_sprite *sp)
{
	mob->behaviour = BH_DEATH;
	update_sprite_tex(cub, sp, mob->death);
}
