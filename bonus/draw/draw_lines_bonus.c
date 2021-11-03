/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:48:25 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:16:52 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	draw_circle(t_pos pos, int r, int color, t_img *img)
{
	double	i;
	double	angle;
	double	x1;
	double	y1;

	while (r > 0)
	{
		i = 0;
		while (i < 360)
		{
			angle = i;
			x1 = r * cos(angle * M_PI / 180);
			y1 = r * sin(angle * M_PI / 180);
			my_mlx_pixel_put(img, pos.x + x1, pos.y + y1, color);
			i += 0.1;
		}
		r--;
	}
}
