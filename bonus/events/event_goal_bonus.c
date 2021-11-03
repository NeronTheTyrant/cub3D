/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_goal_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:16:38 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:16:38 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	event_goal(t_cub *cub)
{
	if (cub->state == STATE_DEAD)
		return (0);
	if (cub->nextmap == NULL)
		cub->state = STATE_WIN;
	else
		cub->state = STATE_NEXT_LEVEL;
	return (0);
}

int	add_event_goal(t_cub *cub, t_sprite sp)
{
	t_event	temp;

	ft_bzero(&temp, sizeof(temp));
	temp.sp_id = sp.id;
	temp.id = sp.ev_id;
	temp.type = EVENT_GOAL;
	temp.pos = sp.pos;
	temp.range = 0.5;
	if (add_event(cub, temp) < 0)
		return (ERR_MALLOC);
	cub->goal++;
	return (SUCCESS);
}
