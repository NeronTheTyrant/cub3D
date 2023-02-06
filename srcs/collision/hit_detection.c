/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:16:20 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:16:21 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	circle_overlap(t_dpos p1, t_dpos p2, double r1, double r2)
{
	double	dist;

	dist = pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
	dist = sqrt(dist);
	if (dist <= r1 + r2)
		return (1);
	else
		return (0);
}

int	check_mob_hit(t_cub *cub, t_event *proj)
{
	t_list	*ptr;
	t_list	*next;
	t_event	*ev;

	if (circle_overlap(proj->pos, cub->play->pos, proj->range, 0.5) == 1)
		hit_player(cub, proj);
	ptr = cub->event;
	while (ptr)
	{
		ev = (t_event *)ptr->content;
		next = ptr->next;
		if (ev->id != proj->id && ev->hit == 1
			&& circle_overlap(proj->pos, ev->pos, proj->range, ev->range) == 1)
			hit_event(cub, ATK_FIREBALL, ev);
		ptr = next;
	}
	return (0);
}

int	check_hit(t_cub *cub, t_event *proj)
{
	t_list	*ptr;
	t_list	*next;
	t_event	*ev;
	t_mob	*mob;

	ptr = cub->event;
	while (ptr)
	{
		ev = (t_event *)ptr->content;
		next = ptr->next;
		if (ev->id != proj->id && ev->hit == 1
			&& circle_overlap(proj->pos, ev->pos, proj->range, ev->range) == 1)
			hit_event(cub, ATK_FIREBALL, ev);
		ptr = next;
	}
	ptr = cub->mob;
	while (ptr)
	{
		mob = (t_mob *)ptr->content;
		if (circle_overlap(proj->pos, mob->pos, proj->range, 0.5) == 1)
			hit_mob(cub, ATK_FIREBALL, mob);
		ptr = ptr->next;
	}
	return (0);
}
