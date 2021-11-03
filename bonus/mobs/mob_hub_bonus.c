/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_hub_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:14:06 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:14:07 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	update_behaviour(t_cub *cub, t_mob *mob, t_sprite *sprite)
{
	int	inrange;
	int	can_attack;

	inrange = in_range(cub->play->pos, mob->pos, mob->attackrange);
	can_attack = cub->time - mob->lastattack >= mob->attackdelay;
	if (mob->behaviour == BH_IDLE)
	{
		if (inrange == 1 && can_attack == 1 && sprite->update == 1)
			change_behaviour_attack(cub, mob, sprite);
		else if (inrange == 0 && sprite->update == 1)
			change_behaviour_walk(cub, mob, sprite);
	}
	else if (mob->behaviour == BH_WALKING)
	{
		if (inrange == 1 && can_attack == 1 && sprite->update == 1)
			change_behaviour_attack(cub, mob, sprite);
		else if (inrange == 1 && can_attack == 0 && sprite->update == 1)
			change_behaviour_idle(cub, mob, sprite);
	}
}

void	update_dir(t_cub *cub, t_mob *mob)
{
	double	angle;

	angle = get_angle_from_pos(mob->pos, cub->play->pos);
	mob->dir = angle_to_vect(angle);
}

void	update_mob(t_cub *cub, t_mob *mob)
{
	t_sprite	*sprite;

	sprite = get_sprite_by_id(cub->sp, mob->sp_id);
	if (mob->ai != AI_FIGHTER
		|| (mob->ai == AI_FIGHTER && mob->behaviour != BH_ATTACKING))
		update_dir(cub, mob);
	if (find_target(cub, mob->pos, mob->dir, 10))
		update_behaviour(cub, mob, sprite);
	else if (mob->behaviour != BH_IDLE
		&& (cub->time - sprite->last_update >= sprite->tex->delay))
		change_behaviour_idle(cub, mob, sprite);
	mob_behave(cub, mob, sprite);
}

void	mob_hub(t_cub *cub, t_list *mob_lst)
{
	t_mob	*mob;
	t_list	*next;

	while (mob_lst)
	{
		next = mob_lst->next;
		mob = (t_mob *)mob_lst->content;
		update_mob(cub, mob);
		mob_lst = next;
	}
}

int	check_mob_pos(t_cub *cub)
{
	t_list	*ptr;
	t_mob	*mob;

	ptr = cub->mob;
	while (ptr)
	{
		mob = (t_mob *)ptr->content;
		if (mob->pos.x == 0 || mob->pos.x >= cub->map_w - 1
			|| mob->pos.y == 0 || mob->pos.y >= cub->map_h - 1)
			return (ERR_MOB_OUT_OF_BOUNDS);
		if (cub->map[(int)mob->pos.y][(int)mob->pos.x] != '0')
			return (ERR_MOB_WALL);
		ptr = ptr->next;
	}
	return (SUCCESS);
}
