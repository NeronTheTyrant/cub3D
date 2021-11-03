/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collision_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:16:24 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:16:25 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	sprite_id_is_mob(t_list *mob_lst, int id)
{
	t_mob	*mob;

	while (mob_lst)
	{
		mob = (t_mob *)mob_lst->content;
		if (id == mob->sp_id)
			return (1);
		mob_lst = mob_lst->next;
	}
	return (0);
}

int	check_sprite_collision_ignore_mobs(t_cub *cub, t_dpos pos)
{
	t_list		*lst;
	t_sprite	*sp;

	lst = cub->sp;
	while (lst)
	{
		sp = (t_sprite *)lst->content;
		if (sp->collision == 1 && sprite_id_is_mob(cub->mob, sp->id) == 0)
		{
			if ((pos.y < sp->pos.y + 0.5 && pos.y > sp->pos.y - 0.5)
				&& (pos.x < sp->pos.x + 0.5 && pos.x > sp->pos.x - 0.5))
				return (-1);
		}
		lst = lst->next;
	}
	return (0);
}

int	check_sprite_collision(t_cub *cub, t_dpos pos, int id_ignore)
{
	t_list		*lst;
	t_sprite	*sp;

	lst = cub->sp;
	while (lst)
	{
		sp = (t_sprite *)lst->content;
		if (sp->collision == 1 && sp->id != id_ignore)
		{
			if ((pos.y < sp->pos.y + 0.5 && pos.y > sp->pos.y - 0.5)
				&& (pos.x < sp->pos.x + 0.5 && pos.x > sp->pos.x - 0.5))
				return (-1);
		}
		lst = lst->next;
	}
	return (0);
}
