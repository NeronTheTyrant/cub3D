/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:47:53 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:10:50 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_pos	get_pos(int x, int y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

void	horline(int hor, t_pos coord, int color, t_img *img)
{
	int	temp;

	if (coord.x > coord.y)
	{
		temp = coord.x;
		coord.x = coord.y;
		coord.y = temp;
	}
	while (coord.x <= coord.y)
	{
		my_mlx_pixel_put(img, coord.x, hor, color);
		coord.x++;
	}
}

void	vertline(int vert, t_pos coord, int color, t_img *img)
{
	int	temp;

	if (coord.x > coord.y)
	{
		temp = coord.x;
		coord.x = coord.y;
		coord.y = temp;
	}
	while (coord.x < coord.y)
	{
		my_mlx_pixel_put(img, vert, coord.x, color);
		coord.x++;
	}
}

void	draw_line(t_pos v1, t_pos v2, int color, t_img *img)
{
	t_pos	delt;
	t_pos	step;
	t_pos	err;

	delt.x = ft_abs(v2.x - v1.x);
	delt.y = -ft_abs(v2.y - v1.y);
	step.x = ((v1.x < v2.x) * 2) - 1;
	step.y = ((v1.y < v2.y) * 2) - 1;
	err.x = delt.x + delt.y;
	while (v1.x != v2.x && v1.y != v2.y)
	{
		my_mlx_pixel_put(img, v1.x, v1.y, color);
		err.y = err.x * 2;
		if (err.y >= delt.y)
		{
			err.x += delt.y;
			v1.x += step.x;
		}
		if (err.y <= delt.x)
		{
			err.x += delt.x;
			v1.y += step.y;
		}
	}
	my_mlx_pixel_put(img, v1.x, v1.y, color);
}
