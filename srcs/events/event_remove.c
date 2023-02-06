/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 00:00:49 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:40:59 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	event_remove(t_cub *cub, t_event *event)
{
	t_list	*ev_ptr;
	t_list	*sp_ptr;

	sp_ptr = get_sprite_lst_by_id(cub->sp, event->sp_id);
	ev_ptr = get_event_lst_by_id(cub->event, event->id);
	ft_lstdelone(&cub->event, ev_ptr, &free);
	ft_lstdelone(&cub->sp, sp_ptr, &free);
	return (1);
}

int	add_event_remove(t_cub *cub, t_sprite sp)
{
	t_event	temp;

	ft_bzero(&temp, sizeof(temp));
	temp.sp_id = sp.id;
	temp.id = sp.ev_id;
	temp.type = EVENT_REMOVE;
	temp.hit = 1;
	temp.pos = sp.pos;
	temp.range = 0.5;
	if (add_event(cub, temp) < 0)
		return (ERR_MALLOC);
	return (SUCCESS);
}
