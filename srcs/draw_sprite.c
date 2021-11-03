/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:32:21 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:05:02 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_stripe(t_cub *cub, t_spritecasting *sc, t_img tex,
			t_img *frame)
{
	int	y;
	int	d;
	int	index;
	int	color;

	y = sc->top;
	while (y < sc->bot)
	{
		d = (y) * 256 - cub->set.resy * 128 + sc->height * 128;
		sc->texel.y = ((d * tex.height) / sc->height) / 256;
		index = sc->texel.y * tex.linelen + sc->texel.x * (tex.bpp / 8);
		color = 0;
		ft_memcpy(&color, &tex.addr[index], 4);
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(frame, sc->stripe, y, color);
		y++;
	}
}

static int	stripe_onscreen(t_cub *cub, t_spritecasting *sc)
{
	if (sc->transform.y <= 0)
		return (0);
	if (sc->stripe <= 0)
		return (0);
	if (sc->stripe >= cub->set.resx)
		return (0);
	if (sc->transform.y >= cub->z[sc->stripe])
		return (0);
	return (1);
}

void	draw_sprite(t_cub *cub, t_spritecasting *sc, t_img tex, t_img *frame)
{
	sc->stripe = sc->left;
	while (sc->stripe < sc->right)
	{
		sc->texel.x = (intmax_t)(256
				* (sc->stripe - (-sc->width / 2 + sc->screenx))
				* tex.width / sc->width) / 256;
		if (stripe_onscreen(cub, sc))
		{
			draw_stripe(cub, sc, tex, frame);
		}
		sc->stripe++;
	}
}
