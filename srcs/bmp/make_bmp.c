/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:50:23 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:35:11 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/bmp.h"

void	cub_bmp_init_header(t_cub *cub, t_img screen, t_bmp_head *head,
		t_bmp_info *info)
{
	head->fullsize = 54 + (cub->res.x * cub->res.y * (screen.bpp / 8));
	head->reserved = 0;
	head->offset = 54;
	info->size = 40;
	info->width = cub->res.x;
	info->height = -cub->res.y;
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
		return (-1);
	else
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
		return (-1);
	else
		return (0);
}

int	cub_img_to_bmp(t_img screen, const char *filename, t_cub *cub)
{
	t_bmp_head	head;
	t_bmp_info	info;
	int			fd;

	fd = open(filename, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		return (ERR_READ);
	cub_bmp_init_header(cub, screen, &head, &info);
	if (bmp_write_head(fd, head) == -1 || bmp_write_info(fd, info) == -1)
		return (ERR_WRITE);
	if (write(fd, screen.addr, screen.linelen * screen.height) == -1)
		return (ERR_WRITE);
	close(fd);
	return (0);
}

void	save_screenshot(t_cub *cub)
{
	t_img	screen;
	int		ret;

	update_world(cub);
	screen = make_img(cub->mlx, cub->res.x, cub->res.y);
	if (screen.img == NULL)
		exit_error(cub, ERR_MALLOC, NULL);
	raycasting(cub, &screen);
	draw_hud(cub, &screen);
	ret = cub_img_to_bmp(screen, "screenshot.bmp", cub);
	mlx_destroy_image(cub->mlx, screen.img);
	if (ret < 0)
		exit_error(cub, ret, "screenshot.bmp");
}
