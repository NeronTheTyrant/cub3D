/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:09:27 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:39:10 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	set_sprite_posz(char *arg, t_sprite *sp, int texnbr, t_cub *cub)
{
	(void)texnbr;
	(void)cub;
	if (ft_strcmp(arg, "UP") == 0)
		sp->hmove = -32/*-cub->tex_sp->tex[texnbr].height*/;
	else if (ft_strcmp(arg, "DOWN") == 0)
		sp->hmove = 32/*cub->tex_sp->tex[texnbr].height*/;
	else if (ft_strcmp(arg, "MID") == 0)
		sp->hmove = 0;
	else
		return (ERR_BAD_ARG);
	return (SUCCESS);
}

int	set_sprite_event(char *arg, t_sprite *sp)
{
	if (ft_strcmp(arg, "COLLECTIBLE") == 0)
		sp->event = EVENT_COLLECT;
	else if (ft_strcmp(arg, "TELEPORT") == 0)
		sp->event = EVENT_TELEPORT;
	else if (ft_strcmp(arg, "REMOVEABLE") == 0)
		sp->event = EVENT_REMOVE;
	else if (ft_strcmp(arg, "HEAL_1") == 0)
		sp->event = EVENT_HEAL_1;
	else if (ft_strcmp(arg, "GOAL") == 0)
		sp->event = EVENT_GOAL;
	else if (ft_strcmp(arg, "NONE") == 0)
		sp->event = 0;
	else
		return (ERR_BAD_ARG);
	return (SUCCESS);
}

int	set_sprite(char **args, t_sprite *sp, t_cub *cub)
{
	int	texnbr;

	texnbr = get_tex_nbr(args[1], cub->tex_sp->texnbr);
	if (texnbr == ERR_BAD_ARG)
		return (ERR_BAD_ARG);
	sp->tex = &cub->tex_sp->tex[texnbr];
	if (set_sprite_posz(args[2], sp, texnbr, cub) != 0)
		return (ERR_BAD_ARG);
	if (ft_strcheck_each(args[3], &ft_isdigit)
		&& ft_strcheck_each(args[4], &ft_isdigit))
	{
		set_sprite_div(ft_atoi(args[3]), ft_atoi(args[4]), sp);
		if (sp->hdiv <= 0 || sp->wdiv <= 0)
			return (ERR_BAD_ARG);
	}
	else
		return (ERR_BAD_ARG);
//	printf("before : sp->hmove = %d\n", sp->hmove);
	sp->hmove *= sp->hdiv;
//	printf("after : sp->hmove = %d\n", sp->hmove);
	if (ft_strcmp(args[5], "Y") == 0)
		sp->collision = 1;
	else if (ft_strcmp(args[5], "N") != 0)
		return (ERR_BAD_ARG);
	if (set_sprite_event(args[6], sp) != 0)
		return (ERR_BAD_ARG);
	return (SUCCESS);
}

void	set_sprite_posxy(double x, double y, t_sprite *sp)
{
	sp->pos.x = x;
	sp->pos.y = y;
}

void	set_sprite_div(int hdiv, int wdiv, t_sprite *sp)
{
	sp->hdiv = hdiv;
	sp->wdiv = wdiv;
}
