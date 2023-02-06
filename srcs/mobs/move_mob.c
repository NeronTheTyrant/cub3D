/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mob.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:14:14 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:14:15 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	mob_move_forward(t_cub *cub, t_mob *mob)
{
	int			stopflag;
	double		nexty;
	double		nextx;

	nexty = mob->pos.y + mob->dir.y * (mob->speed * cub->frametime);
	nextx = mob->pos.x + mob->dir.x * (mob->speed * cub->frametime);
	check_next_move(cub, &nextx, &nexty);
	stopflag = 0;
	if (ft_isin(cub->map[(int)(nexty)][(int)(mob->pos.x)], cub->wallc) == -1 &&
			check_sprite_collision(cub,
			get_dpos(mob->pos.x, nexty), mob->sp_id) == 0 &&
			in_range(get_dpos(mob->pos.x, nexty), cub->play->pos, 0.5) == 0)
		mob->pos.y = nexty;
	else
		stopflag = 1;
	if (ft_isin(cub->map[(int)(mob->pos.y)][(int)(nextx)], cub->wallc) == -1 &&
			check_sprite_collision(cub,
			get_dpos(nextx, mob->pos.y), mob->sp_id) == 0 &&
			in_range(get_dpos(nextx, mob->pos.y), cub->play->pos, 0.5) == 0)
		mob->pos.x = nextx;
	else
		stopflag = 1;
	if (stopflag == 1)
		return (-1);
	return (0);
}
