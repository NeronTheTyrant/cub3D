/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_heal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:16:45 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:16:45 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	event_heal(t_cub *cub, t_event *event, t_list *lst)
{
	t_list	*sp;

	add_health(cub, 1);
	sp = get_sprite_lst_by_id(cub->sp, event->sp_id);
	ft_lstdelone(&cub->event, lst, &free);
	ft_lstdelone(&cub->sp, sp, &free);
	return (1);
}

int	add_event_heal(t_cub *cub, t_sprite sp)
{
	t_event	temp;

	ft_bzero(&temp, sizeof(temp));
	temp.sp_id = sp.id;
	temp.id = sp.ev_id;
	temp.type = EVENT_HEAL_1;
	temp.pos = sp.pos;
	temp.range = 0.5;
	if (add_event(cub, temp) < 0)
		return (ERR_MALLOC);
	return (SUCCESS);
}
