/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_projectile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 01:58:46 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:46:21 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	move_mob_proj_forward(t_cub *cub, t_sprite *sp, double speed)
{
	int		stopflag;
	double	nexty;
	double	nextx;

	nexty = sp->pos.y + sp->dir.y * speed;
	nextx = sp->pos.x + sp->dir.x * speed;
	check_next_move(cub, &nextx, &nexty);
	stopflag = 0;
	if (ft_isin(cub->map[(int)(nexty)][(int)(sp->pos.x)], cub->wallc) == -1
			&& check_sprite_collision_ignore_mobs(cub,
			get_dpos(sp->pos.x, nexty)) == 0
			&& in_range(get_dpos(sp->pos.x, nexty), cub->play->pos, 0.5) == 0)
		sp->pos.y = nexty;
	else
		stopflag = 1;
	if (ft_isin(cub->map[(int)(sp->pos.y)][(int)(nextx)], cub->wallc) == -1
			&& check_sprite_collision_ignore_mobs(cub,
				get_dpos(nextx, sp->pos.y)) == 0
			&& in_range(get_dpos(nextx, sp->pos.y), cub->play->pos, 0.5) == 0)
		sp->pos.x = nextx;
	else
		stopflag = 1;
	if (stopflag == 1)
		return (-1);
	return (0);
}

int	event_mob_projectile(t_cub *cub, t_event *event, t_list *ev_ptr)
{
	t_list		*sp_ptr;
	t_sprite	*sp;
	double		speed;

	sp_ptr = get_sprite_lst_by_id(cub->sp, event->sp_id);
	sp = (t_sprite *)sp_ptr->content;
	speed = sp->speed * cub->frametime;
	if (move_mob_proj_forward(cub, sp, speed) == -1)
	{
		sp->pos.x += (sp->dir.x * speed);
		sp->pos.y += (sp->dir.y * speed);
		spawn_projectile_explosion(cub, event, sp);
		event->pos = sp->pos;
		check_mob_hit(cub, event);
		ft_lstdelone(&cub->sp, sp_ptr, &free);
		ft_lstdelone(&cub->event, ev_ptr, &free);
	}
	else
	{
		if (check_teleport(cub->event, &sp->pos, &sp->teleport) == 1)
			sp->speed += sp->speed;
		event->pos = sp->pos;
	}
	return (SUCCESS);
}

int	event_projectile(t_cub *cub, t_event *event, t_list *ev_ptr)
{
	t_list		*sp_ptr;
	t_sprite	*sp;
	double		speed;

	sp_ptr = get_sprite_lst_by_id(cub->sp, event->sp_id);
	sp = (t_sprite *)sp_ptr->content;
	speed = sp->speed * cub->frametime;
	if (move_forward(cub, &sp->pos, sp->dir, speed) == -1)
	{
		sp->pos.x += (sp->dir.x * speed);
		sp->pos.y += (sp->dir.y * speed);
		spawn_projectile_explosion(cub, event, sp);
		event->pos = sp->pos;
		check_hit(cub, event);
		ft_lstdelone(&cub->sp, sp_ptr, &free);
		ft_lstdelone(&cub->event, ev_ptr, &free);
	}
	else
	{
		if (check_teleport(cub->event, &sp->pos, &sp->teleport) == 1)
			sp->speed += sp->speed;
		event->pos = sp->pos;
	}
	return (SUCCESS);
}

int	check_teleport(t_list *ev_lst, t_dpos *pos, int *teleport_flag)
{
	t_event	*event;
	int		teleport_request;
	int		teleport_happened;

	teleport_request = 0;
	teleport_happened = 0;
	while (ev_lst)
	{
		event = (t_event *)ev_lst->content;
		if (event->type == EVENT_TELEPORT && in_range(*pos, event->pos,
				event->range) == 1)
		{
			teleport_request = 1;
			teleport_happened += event_teleport(pos, teleport_flag, event);
		}
		ev_lst = ev_lst->next;
	}
	if (*teleport_flag == 0 && teleport_request == 0)
		*teleport_flag = 1;
	if (teleport_happened)
		return (1);
	else
		return (0);
}
