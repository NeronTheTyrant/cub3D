/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hub_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:11:35 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:40:09 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	event_hub(t_cub *cub, t_list *ev_lst)
{
	t_list	*next;
	t_event	*event;
	int		ret;

	ret = 0;
	while (ev_lst)
	{
		next = ev_lst->next;
		event = (t_event *)ev_lst->content;
		if (event->type < EVENT_PROXIMITY_THRESHOLD)
			ret += event_check_proximity(cub, event, ev_lst);
		else
			event_check_other(cub, event, ev_lst);
		ev_lst = next;
	}
	if (cub->play->teleport == 0 && ret == 0)
		cub->play->teleport = 1;
	return (1);
}

int	event_check_proximity(t_cub *cub, t_event *event, t_list *ev_lst)
{
	int	teleport_request;

	teleport_request = 0;
	if (in_range(cub->play->pos, event->pos, event->range) == 1)
	{
		if (event->type == EVENT_COLLECT)
			event_collect(cub, event, ev_lst);
		else if (event->type == EVENT_TELEPORT)
		{
			teleport_request = 1;
			event_teleport(&cub->play->pos, &cub->play->teleport, event);
		}
		else if (event->type == EVENT_HEAL_1)
			event_heal(cub, event, ev_lst);
		else if (event->type == EVENT_GOAL)
			event_goal(cub);
	}
	return (teleport_request);
}

int	event_check_other(t_cub *cub, t_event *event, t_list *ev_lst)
{
	if (event->type == EVENT_PROJECTILE)
		event_projectile(cub, event, ev_lst);
	else if (event->type == EVENT_MOB_PROJECTILE)
		event_mob_projectile(cub, event, ev_lst);
	return (0);
}
