/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:07:25 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:02:54 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_img	make_img(void *mlx, int x, int y)
{
	t_img	img;

	img.img = mlx_new_image(mlx, x, y);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endi);
	img.width = x;
	img.height = y;
	return (img);
}

void	fill_img(int limitx, int limity, t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < limity)
	{
		j = 0;
		while (j < limitx)
		{
			my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
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
