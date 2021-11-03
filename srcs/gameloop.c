/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 11:16:19 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:13:07 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	update_pos(t_cub *cub)
{
	double	speed;
	double	rotspeed;

	speed = 0.099;
	rotspeed = 0.05;
	if (cub->keys & KEY_SHIFT)
		speed = 0.2;
	if (cub->keys & KEY_W)
		move_forward(cub, speed);
	if (cub->keys & KEY_A)
		strafe_left(cub, speed);
	if (cub->keys & KEY_S)
		move_backwards(cub, speed);
	if (cub->keys & KEY_D)
		strafe_right(cub, speed);
	if (cub->keys & KEY_LF_ARR)
		turn_left(cub, rotspeed);
	if (cub->keys & KEY_RG_ARR)
		turn_right(cub, rotspeed);
	return (0);
}

int	gameloop(t_cub *cub)
{
	t_img	frame;

	frame = make_img(cub->mlx, cub->set.resx, cub->set.resy);
	if (cub->keys != 0)
		update_pos(cub);
	raycasting(cub, &frame);
	mlx_put_image_to_window(cub->mlx, cub->win, frame.img, 0, 0);
	mlx_destroy_image(cub->mlx, frame.img);
	return (0);
}

void	get_dir(t_cub *cub)
{
	char	c;

	c = cub->map[(int)cub->play.y][(int)cub->play.x];
	if (c == 'N')
	{
		cub->dir.y = -1;
		cub->plane.x = 0.66;
	}
	else if (c == 'S')
	{
		cub->dir.y = 1;
		cub->plane.x = -0.66;
	}
	else if (c == 'E')
	{
		cub->dir.x = 1;
		cub->plane.y = 0.66;
	}
	else if (c == 'W')
	{
		cub->dir.x = -1;
		cub->plane.y = -0.66;
	}
	cub->map[(int)cub->play.y][(int)cub->play.x] = '0';
}

void	start_gameloop(t_cub *cub)
{
	cub->play.x += 0.5;
	cub->play.y += 0.5;
	get_dir(cub);
	cub->z = malloc(sizeof(*cub->z) * cub->set.resx);
	if (cub->z == NULL)
	{
		setting_error(NULL, 0, MALLOC_ERR);
		exit_done(cub);
	}
	if (cub->save == 1)
		save_screenshot(cub);
	else
	{
		cub->win = mlx_new_window(cub->mlx, cub->set.resx, cub->set.resy,
				"cub3D");
		mlx_loop_hook(cub->mlx, gameloop, cub);
		mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
		mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
		mlx_hook(cub->win, 17, 1L << 17, click_cross, cub);
		mlx_loop(cub->mlx);
	}
}
