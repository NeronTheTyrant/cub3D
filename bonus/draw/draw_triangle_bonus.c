/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:48:47 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:36:22 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	fill_bot_flat_triangle(t_triangle tri, int color, t_img *img)
{
	float	invslope1;
	float	invslope2;
	float	curx1;
	float	curx2;
	int		scanline;

	invslope1 = (float)(tri.v2.x - tri.v1.x) / (float)(tri.v2.y - tri.v1.y);
	invslope2 = (float)(tri.v3.x - tri.v1.x) / (float)(tri.v3.y - tri.v1.y);
	curx1 = tri.v1.x;
	curx2 = tri.v1.x;
	scanline = tri.v1.y;
	while (scanline <= tri.v2.y)
	{
		horline(scanline, get_pos((int)curx1, (int)curx2), color, img);
		curx1 += invslope1;
		curx2 += invslope2;
		scanline++;
	}
}

void	fill_top_flat_triangle(t_triangle tri, int color, t_img *img)
{
	float	invslope1;
	float	invslope2;
	float	curx1;
	float	curx2;
	int		scanline;

	invslope1 = (float)(tri.v3.x - tri.v1.x) / (float)(tri.v3.y - tri.v1.y);
	invslope2 = (float)(tri.v3.x - tri.v2.x) / (float)(tri.v3.y - tri.v2.y);
	curx1 = tri.v3.x;
	curx2 = tri.v3.x;
	scanline = tri.v3.y;
	while (scanline > tri.v1.y)
	{
		horline(scanline, get_pos((int)curx1, (int)curx2), color, img);
		curx1 -= invslope1;
		curx2 -= invslope2;
		scanline--;
	}
}

void	draw_triangle(t_triangle tri, int color, t_img *img)
{
	t_pos	temp;
	t_pos	v4;

	if (tri.v1.y > tri.v2.y)
		ft_memswap(&tri.v1, &tri.v2, &temp, sizeof(t_pos));
	if (tri.v1.y > tri.v3.y)
		ft_memswap(&tri.v1, &tri.v3, &temp, sizeof(t_pos));
	if (tri.v2.y > tri.v3.y)
		ft_memswap(&tri.v2, &tri.v3, &temp, sizeof(t_pos));
	if (tri.v2.y == tri.v3.y)
		fill_bot_flat_triangle(tri, color, img);
	else if (tri.v1.y == tri.v2.y)
		fill_top_flat_triangle(tri, color, img);
	else
	{
		v4.x = (int)((float)tri.v1.x + ((float)(tri.v2.y - tri.v1.y)
					/ (float)(tri.v3.y - tri.v1.y))
				* (float)(tri.v3.x - tri.v1.x));
		v4.y = tri.v2.y;
		fill_bot_flat_triangle(get_triangle(tri.v1, tri.v2, v4), color, img);
		fill_top_flat_triangle(get_triangle(tri.v2, v4, tri.v3), color, img);
	}
}
