/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:28:53 by mlebard           #+#    #+#             */
/*   Updated: 2021/03/27 14:25:28 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	get_sprite_pos(t_cub *cub, t_spritecasting *sc, int i)
{
	t_dpos	sprite;
	double	invdet;
	t_dpos	transform;
	int		screenx;

	sprite.x = cub->sp[i].x - cub->play.x;
	sprite.y = cub->sp[i].y - cub->play.y;
	invdet = 1.0 / (cub->plane.x * cub->dir.y - cub->dir.x * cub->plane.y);
	transform.x = invdet * (cub->dir.y * sprite.x - cub->dir.x * sprite.y);
	transform.y = invdet * (-cub->plane.y * sprite.x + cub->plane.x * sprite.y);
	screenx = (int)((cub->set.resx / 2) * (1 + transform.x / transform.y));
	sc->transform = transform;
	sc->screenx = screenx;
}

static void	get_sprite_dim(t_cub *cub, t_spritecasting *sc)
{
	sc->height = abs((int)(cub->set.resy / (sc->transform.y)));
	sc->top = -sc->height / 2 + cub->set.resy / 2;
	if (sc->top < 0)
		sc->top = 0;
	sc->bot = sc->height / 2 + cub->set.resy / 2;
	if (sc->bot >= cub->set.resy)
		sc->bot = cub->set.resy - 1;
	sc->width = ft_abs((int)(cub->set.resy / (sc->transform.y)));
	sc->left = -sc->width / 2 + sc->screenx;
	if (sc->left < 0)
		sc->left = 0;
	sc->right = sc->width / 2 + sc->screenx;
	if (sc->right >= cub->set.resx)
		sc->right = cub->set.resx - 1;
}

void	spritecasting(t_cub *cub, t_spritecasting *sc, t_img *frame)
{
	int	i;

	i = 0;
	sort_sprites(cub);
	while (i < cub->sp_nb)
	{
		get_sprite_pos(cub, sc, i);
		get_sprite_dim(cub, sc);
		draw_sprite(cub, sc, cub->set.txsprite, frame);
		i++;
	}
}
