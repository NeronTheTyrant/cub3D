/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mob_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:14:22 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:14:23 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	set_mob_posxy(double x, double y, t_mob *mob)
{
	mob->pos.x = x;
	mob->pos.y = y;
}

int	set_mob_ai(char *arg, t_mob *mob)
{
	mob->behaviour = BH_IDLE;
	if (ft_strcmp(arg, "TURRET") == 0)
		set_mob_ai_turret(mob);
	else if (ft_strcmp(arg, "FIGHTER") == 0)
		set_mob_ai_fighter(mob);
	else
		return (ERR_BAD_ARG);
	return (SUCCESS);
}

static int	set_tex(char *arg, int limit, t_img *src, t_img **dst)
{
	int	temp;

	temp = get_tex_nbr(arg, limit);
	if (temp == ERR_BAD_ARG)
		return (ERR_BAD_ARG);
	*dst = &src[temp];
	return (SUCCESS);
}

int	set_mob(char **args, t_mob *mob, t_cub *cub)
{
	t_img	*texs;

	texs = cub->tex_sp->tex;
	mob->sp_type = get_tex_nbr(args[1], cub->sp_type_nb);
	if (mob->sp_type == ERR_BAD_ARG)
		return (ERR_BAD_ARG);
	if (set_tex(args[2], cub->tex_sp->texnbr, texs, &mob->walking) < 0)
		return (ERR_BAD_ARG);
	if (set_tex(args[3], cub->tex_sp->texnbr, texs, &mob->attack) < 0)
		return (ERR_BAD_ARG);
	if (set_tex(args[4], cub->tex_sp->texnbr, texs, &mob->projectile) < 0)
		return (ERR_BAD_ARG);
	if (set_tex(args[5], cub->tex_sp->texnbr, texs, &mob->explosion) < 0)
		return (ERR_BAD_ARG);
	if (set_tex(args[6], cub->tex_sp->texnbr, texs, &mob->hurt) < 0)
		return (ERR_BAD_ARG);
	if (set_tex(args[7], cub->tex_sp->texnbr, texs, &mob->death) < 0)
		return (ERR_BAD_ARG);
	if (set_mob_ai(args[8], mob) == ERR_BAD_ARG)
		return (ERR_BAD_ARG);
	mob->base = cub->sp_type[mob->sp_type].tex;
	mob->death_height = mob->death->height
		* (cub->sp_type[mob->sp_type].hdiv + 1);
	return (SUCCESS);
}
