/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_collect_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:10:22 by mlebard           #+#    #+#             */
/*   Updated: 2021/04/29 00:04:18 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	event_collect(t_cub *cub, t_event *event, t_list *lst)
{
	t_list	*sp;

	cub->play->sprites_collected += 1;
	sp = get_sprite_lst_by_id(cub->sp, event->sp_id);
	ft_lstdelone(&cub->event, lst, &free);
	ft_lstdelone(&cub->sp, sp, &free);
	return (1);
}

int	add_event_collect(t_cub *cub, t_sprite sp)
{
	t_event	temp;

	ft_bzero(&temp, sizeof(temp));
	temp.sp_id = sp.id;
	temp.id = sp.ev_id;
	temp.type = EVENT_COLLECT;
	temp.pos = sp.pos;
	temp.range = 0.5;
	if (add_event(cub, temp) < 0)
		return (ERR_MALLOC);
	return (SUCCESS);
}
