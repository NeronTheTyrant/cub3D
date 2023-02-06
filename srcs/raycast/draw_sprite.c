/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:48:36 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:38:31 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_stripe(t_cub *cub, t_spritecast *sprite, t_img tex,
		t_img *frame)
{
	int	y;
	int	d;
	int	color;

	y = sprite->top;
	while (y < sprite->bot)
	{
		d = (y - sprite->move_screen) * 256 - cub->res.y * 128
			+ sprite->height * 128;
		sprite->texel.y = ((d * tex.height) / sprite->height) / 256;
		color = get_pixel(sprite->texel.x, sprite->texel.y, tex);
		if (color != 0)
			my_mlx_pixel_put(frame, sprite->stripe, y,
				add_shade(sprite->transform.y, color));
		y++;
	}
}

static int	stripe_onscreen(t_cub *cub, t_spritecast *sprite)
{
	if (sprite->transform.y <= 0)
		return (0);
	if (sprite->stripe <= 0)
		return (0);
	if (sprite->stripe >= cub->res.x)
		return (0);
	if (sprite->transform.y >= cub->z[sprite->stripe])
		return (0);
	return (1);
}

void	draw_sprite(t_cub *cub, t_spritecast *sprite, t_sprite *sp,
		t_img *frame)
{
	t_img	tex;

	tex = *sp->tex;
	sprite->stripe = sprite->left;
	while (sprite->stripe < sprite->right)
	{
		sprite->texel.x = (intmax_t)(256
				* (sprite->stripe - (-sprite->width / 2 + sprite->screenx))
				* tex.width / sprite->width) / 256;
		if (stripe_onscreen(cub, sprite))
		{
			draw_stripe(cub, sprite, tex, frame);
		}
		sprite->stripe++;
	}
}
