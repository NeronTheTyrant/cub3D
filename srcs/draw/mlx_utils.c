/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:50:52 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:36:39 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(intmax_t x, intmax_t y, t_img img)
{
	intmax_t	index;
	int			color;

	index = y * img.linelen + x * (img.bpp / 8);
	ft_memcpy(&color, &img.addr[index], 4);
	return (color);
}

t_img	make_img(void *mlx, int x, int y)
{
	t_img	img;

	img.img = mlx_new_image(mlx, x, y);
	if (img.img == NULL)
		return (img);
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

void	free_mlx_image(t_cub *cub, void *img)
{
	if (img != NULL)
		mlx_destroy_image(cub->mlx, img);
}
