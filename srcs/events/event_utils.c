/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 03:12:56 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:40:45 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	add_event_from_sprite(t_cub *cub, t_sprite sp)
{
	int	ret;

	ret = 0;
	if (sp.event == EVENT_COLLECT)
		ret = add_event_collect(cub, sp);
	else if (sp.event == EVENT_REMOVE)
		ret = add_event_remove(cub, sp);
	else if (sp.event == EVENT_HEAL_1)
		ret = add_event_heal(cub, sp);
	else if (sp.event == EVENT_GOAL)
		ret = add_event_goal(cub, sp);
	if (ret < 0)
		return (cub_error(cub, ret, NULL));
	return (SUCCESS);
}

int	add_event(t_cub *cub, t_event ev)
{
	t_event	*newevent;
	t_list	*new;

	newevent = malloc(sizeof(*newevent));
	if (newevent == NULL)
		return (ERR_MALLOC);
	ft_memcpy(newevent, &ev, sizeof(*newevent));
	new = ft_lstnew(newevent);
	if (new == NULL)
	{
		free(newevent);
		return (ERR_MALLOC);
	}
	ft_lstadd_back(&cub->event, new);
	return (SUCCESS);
}

t_list	*get_event_lst_by_id(t_list *ev_ptr, int id)
{
	t_event	*ev;

	while (ev_ptr)
	{
		ev = (t_event *)ev_ptr->content;
		if (ev->id == id)
			return (ev_ptr);
		ev_ptr = ev_ptr->next;
	}
	printf("Error\nNo event found with matching ID\n");
	return (NULL);
}

t_event	*get_event_by_id(t_list *ev_ptr, int id)
{
	t_event	*ev;

	while (ev_ptr)
	{
		ev = (t_event *)ev_ptr->content;
		if (ev->id == id)
			return (ev);
		ev_ptr = ev_ptr->next;
	}
	printf("Error\nNo event found with matching ID\n");
	return (NULL);
}

int	in_range(t_dpos pos, t_dpos pos2, double range)
{
	if ((pos.y < pos2.y + range && pos.y > pos2.y - range)
		&& (pos.x < pos2.x + range && pos.x > pos2.x - range))
		return (1);
	else
		return (0);
}
