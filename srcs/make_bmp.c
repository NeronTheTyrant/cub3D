/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 11:08:36 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:12:55 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/bmp.h"

void	cub_bmp_init_header(t_cub *cub, t_img screen, t_bmp_head *head,
		t_bmp_info *info)
{
	head->fullsize = 54 + (cub->set.resx * cub->set.resy * (screen.bpp / 8));
	head->reserved = 0;
	head->offset = 54;
	info->size = 40;
	info->width = cub->set.resx;
	info->height = -cub->set.resy;
	info->colorplanes = 1;
	info->bpp = screen.bpp;
	info->compression = 0;
	info->raw_data_size = 0;
	info->y_res = 0;
	info->x_res = 0;
	info->color_table = 0;
	info->important_colors = 0;
}

int	bmp_write_head(int fd, t_bmp_head head)
{
	int	ret;

	ret = write(fd, "BM", 2);
	if (sizeof(head) == 12)
		ret = write(fd, &head, 12);
	else
	{
		ret = write(fd, &head.fullsize, 4);
		ret = write(fd, &head.reserved, 4);
		ret = write(fd, &head.offset, 4);
	}
	if (ret == -1)
	{
		printf("Error\nWrite Error\n");
		return (-1);
	}
	return (0);
}

int	bmp_write_info(int fd, t_bmp_info info)
{
	int	ret;

	if (sizeof(info) == 40)
		ret = write(fd, &info, 40);
	else
	{
		ret = write(fd, &info.size, 4);
		ret = write(fd, &info.width, 4);
		ret = write(fd, &info.height, 4);
		ret = write(fd, &info.colorplanes, 2);
		ret = write(fd, &info.bpp, 2);
		ret = write(fd, &info.compression, 4);
		ret = write(fd, &info.raw_data_size, 4);
		ret = write(fd, &info.y_res, 4);
		ret = write(fd, &info.x_res, 4);
		ret = write(fd, &info.color_table, 4);
		ret = write(fd, &info.important_colors, 4);
	}
	if (ret == -1)
	{
		printf("Error\nWrite Error\n");
		return (-1);
	}
	return (0);
}

void	cub_img_to_bmp(t_img screen, const char *filename, t_cub *cub)
{
	t_bmp_head	head;
	t_bmp_info	info;
	int			fd;
	int			ret;

	fd = open(filename, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		return ;
	cub_bmp_init_header(cub, screen, &head, &info);
	bmp_write_head(fd, head);
	bmp_write_info(fd, info);
	ret = write(fd, screen.addr, screen.linelen * screen.height);
	if (ret == -1)
		printf("Error\nWrite Error\n");
	close(fd);
}

void	save_screenshot(t_cub *cub)
{
	t_img	screen;

	screen = make_img(cub->mlx, cub->set.resx, cub->set.resy);
	raycasting(cub, &screen);
	cub_img_to_bmp(screen, "screenshot.bmp", cub);
	mlx_destroy_image(cub->mlx, screen.img);
}
