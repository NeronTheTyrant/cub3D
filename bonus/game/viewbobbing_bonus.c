/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewbobbing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:15:46 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:15:47 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	bob_check(t_cub *cub)
{
	if (cub->keys & KEY_W && !(cub->keys & KEY_S))
		return (1);
	if (cub->keys & KEY_S && !(cub->keys & KEY_W))
		return (1);
	if (cub->keys & KEY_A && !(cub->keys & KEY_D))
		return (1);
	if (cub->keys & KEY_D && !(cub->keys & KEY_A))
		return (1);
	return (0);
}

static void	bob_hud(t_cub *cub, t_hud *hud, double timer)
{
	double	hudoffset;

	hudoffset = -(cos(timer * 1.5) * 20 * cub->play->bob);
	hud->hands.xcurroff = hud->hands.xbaseoff + hudoffset;
	hud->mace.xcurroff = hud->mace.xbaseoff + hudoffset;
	hud->hands.ycurroff = hud->hands.ybaseoff + fabs(hudoffset);
	hud->mace.ycurroff = hud->mace.ybaseoff + fabs(hudoffset);
}

static void	bob_screen(t_cub *cub, t_player *play, double timer)
{
	t_dpos	offset;

	play->render = play->pos;
	play->renderz = play->z;
	offset.y = ((cos((timer * 1.5)) * 0.1 * play->bob) * play->dir.x);
	offset.x = ((cos((timer * 1.5)) * 0.1 * play->bob) * play->dir.y);
	play->render.y += offset.y;
	play->render.x += offset.x;
	play->renderz += fabs(cos(timer) * 30 * play->bob);
	if (ft_isin(cub->map[(int)play->render.y][(int)play->render.x],
		cub->wallc) >= 0)
	{
		play->render = play->pos;
		play->renderz = play->z;
	}
}

void	update_viewbobbing(t_cub *cub, t_player *play)
{
	double			bobspeed;
	static double	timer = M_PI / 2;

	bobspeed = 4.8;
	if (bob_check(cub) == 1)
		play->bob = fmin(1, play->bob + 0.1);
	else
		play->bob = fmax(0, play->bob - 0.1);
	timer += (bobspeed * cub->frametime);
	bob_screen(cub, play, timer);
	bob_hud(cub, cub->hud, timer);
}
