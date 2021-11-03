/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_to_img_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:41:12 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:41:16 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	put_img_to_frame(t_img *frame, t_img img, int startx, int starty)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < img.height && starty + i < frame->height)
	{
		j = 0;
		while (j < img.width && startx + j < frame->width)
		{
			color = get_pixel(j, i, img);
			my_mlx_pixel_put(frame, startx + j, starty + i, color);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	put_img_to_frame_alpha(t_img *frame, t_img img, int startx, int starty)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < img.height && starty + i < frame->height)
	{
		j = 0;
		while (j < img.width && startx + j < frame->width)
		{
			color = get_pixel(j, i, img);
			if (color != 0)
				my_mlx_pixel_put(frame, startx + j, starty + i, color);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

t_img	mlx_resize_img(void *mlx, t_img img, int sizex, int sizey)
{
	t_img	new;
	t_dpos	ratio;
	t_pos	pixel;
	int		i;
	int		j;

	new = make_img(mlx, sizex, sizey);
	if (new.img == NULL)
		return (new);
	ratio.x = img.width / (double)new.width;
	ratio.y = img.height / (double)new.height;
	i = 0;
	while (i < new.height)
	{
		pixel.y = i * ratio.y;
		j = 0;
		while (j < new.width)
		{
			pixel.x = j * ratio.x;
			my_mlx_pixel_put(&new, j, i, get_pixel(pixel.x, pixel.y, img));
			j++;
		}
		i++;
	}
	return (new);
}
