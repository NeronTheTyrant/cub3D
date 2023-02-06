/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_behave.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:13:59 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:14:00 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	behave_walking(t_cub *cub, t_mob *mob, t_sprite *sprite)
{
	mob_move_forward(cub, mob);
	sprite->pos = mob->pos;
}

static void	behave_attack(t_cub *cub, t_mob *mob, t_sprite *sprite)
{
	if (sprite->tex->next_tex == NULL && sprite->update == 1)
	{
		if (mob->ai == AI_TURRET)
			spawn_mob_projectile(cub, mob);
		if (mob->ai == AI_FIGHTER)
			mob_attack(cub, mob, sprite, 1.5);
		change_behaviour_idle(cub, mob, sprite);
	}
}

static void	behave_hurt(t_cub *cub, t_mob *mob, t_sprite *sprite)
{
	if (sprite->tex->next_tex == NULL && sprite->update == 1)
		change_behaviour_idle(cub, mob, sprite);
}

static void	behave_dying(t_cub *cub, t_mob *mob, t_sprite *sprite)
{
	sprite->collision = 0;
	if (sprite->hmove != mob->death_height)
		sprite->hmove = ft_islower(mob->death_height, sprite->hmove
				+ (sprite->tex->height / 4));
	if (sprite->tex->next_tex == NULL)
	{
		sprite->hmove = mob->death_height;
		sprite->mob_id = 0;
		ft_lstdelone(&cub->mob, get_mob_lst_by_id(cub->mob, mob->id), &free);
	}
}

void	mob_behave(t_cub *cub, t_mob *mob, t_sprite *sprite)
{
	if (mob->behaviour == BH_WALKING)
		behave_walking(cub, mob, sprite);
	else if (mob->behaviour == BH_ATTACKING)
		behave_attack(cub, mob, sprite);
	else if (mob->behaviour == BH_HURT)
		behave_hurt(cub, mob, sprite);
	else if (mob->behaviour == BH_DEATH)
		behave_dying(cub, mob, sprite);
}
