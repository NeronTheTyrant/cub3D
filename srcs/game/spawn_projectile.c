/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_projectile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:24:17 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 15:24:35 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	spawn_projectile_sprite(t_cub *cub, t_sprite temp)
{
	temp.id = ++cub->sp_nb;
	temp.ev_id = ++cub->event_count;
	if (add_sprite(temp, cub) < 0)
		return (ERR_MALLOC);
	else
		return (SUCCESS);
}

static int	add_projectile_event(t_cub *cub, t_dpos pos, int type, t_img *expl)
{
	t_event		event;

	ft_bzero(&event, sizeof(event));
	event.id = cub->event_count;
	event.sp_id = cub->sp_nb;
	event.type = type;
	event.pos = pos;
	event.range = 0.3;
	event.data = expl;
	event.val1 = 1;
	if (add_event(cub, event) < 0)
		return (ERR_MALLOC);
	else
		return (SUCCESS);
}

int	spawn_player_projectile(t_cub *cub, t_player *play)
{
	t_sprite	temp;

	ft_bzero(&temp, sizeof(t_sprite));
	temp.pos.x = play->pos.x + (0.09 * play->dir.x);
	temp.pos.y = play->pos.y + (0.09 * play->dir.y);
	temp.tex = &cub->tex_sp->tex[play->proj];
	temp.dir = play->dir;
	temp.speed = 5;
	temp.hmove = 0;
	temp.hdiv = 2;
	temp.wdiv = 2;
	if (spawn_projectile_sprite(cub, temp) < 0)
		exit_error(cub, ERR_MALLOC, NULL);
	if (add_projectile_event(cub, play->pos, EVENT_PROJECTILE,
			&cub->tex_sp->tex[play->proj_expl]) < 0)
		exit_error(cub, ERR_MALLOC, NULL);
	return (SUCCESS);
}

int	spawn_mob_projectile(t_cub *cub, t_mob *mob)
{
	t_sprite	temp;

	ft_bzero(&temp, sizeof(t_sprite));
	temp.pos.x = mob->pos.x + (0.09 * mob->dir.x);
	temp.pos.y = mob->pos.y + (0.09 * mob->dir.y);
	temp.tex = mob->projectile;
	temp.dir = mob->dir;
	temp.speed = mob->proj_speed;
	temp.hmove = 0;
	temp.hdiv = 2;
	temp.wdiv = 2;
	if (spawn_projectile_sprite(cub, temp) < 0)
		exit_error(cub, ERR_MALLOC, NULL);
	if (add_projectile_event(cub, mob->pos, EVENT_MOB_PROJECTILE,
			mob->explosion) < 0)
		exit_error(cub, ERR_MALLOC, NULL);
	return (SUCCESS);
}

int	spawn_projectile_explosion(t_cub *cub, t_event *proj, t_sprite *sp)
{
	t_sprite	temp;

	ft_bzero(&temp, sizeof(t_sprite));
	temp.pos.x = sp->pos.x - (0.2 * sp->dir.x);
	temp.pos.y = sp->pos.y - (0.2 * sp->dir.y);
	temp.tex = (t_img *)proj->data;
	temp.last_update = cub->time;
	temp.hmove = 0;
	temp.hdiv = 2;
	temp.wdiv = 2;
	temp.event = EVENT_ANIMATION;
	temp.id = ++cub->sp_nb;
	if (add_sprite(temp, cub) < 0)
		return (ERR_MALLOC);
	return (SUCCESS);
}
