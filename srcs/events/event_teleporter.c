/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_teleporter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:04:01 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:41:15 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	event_teleport(t_dpos *pos, int *teleport_flag, t_event *event)
{
	if (*teleport_flag == 1)
	{
		pos->x = event->tp.x;
		pos->y = event->tp.y;
		*teleport_flag = 0;
		return (1);
	}
	return (0);
}

int	add_event_teleport(t_cub *cub, t_sprite sp, t_dpos tp)
{
	t_event	temp;

	ft_bzero(&temp, sizeof(temp));
	temp.id = sp.ev_id;
	temp.sp_id = sp.id;
	temp.type = EVENT_TELEPORT;
	temp.pos = sp.pos;
	temp.tp = tp;
	temp.range = 0.5;
	if (add_event(cub, temp) < 0)
		return (ERR_MALLOC);
	return (SUCCESS);
}

int	check_teleport_pos(t_cub *cub)
{
	t_list	*ptr;
	t_event	*event;
	t_pos	tp;

	ptr = cub->event;
	while (ptr)
	{
		event = (t_event *)ptr->content;
		if (event->type == EVENT_TELEPORT)
		{
			tp.x = event->tp.x;
			tp.y = event->tp.y;
			if (tp.x == 0 || tp.x >= cub->map_w - 1
				|| tp.y == 0 || tp.y >= cub->map_h)
				return (ERR_TP_OUT_OF_BOUNDS);
			if (cub->map[tp.y][tp.x] != '0')
				return (ERR_TP_WALL);
		}
		ptr = ptr->next;
	}
	return (SUCCESS);
}
