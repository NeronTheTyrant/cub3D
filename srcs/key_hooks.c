/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 14:03:32 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:12:05 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		exit_done(cub);
	if (keycode == XK_w || keycode == XK_W)
		cub->keys |= KEY_W;
	else if (keycode == XK_a || keycode == XK_A)
		cub->keys |= KEY_A;
	else if (keycode == XK_s || keycode == XK_S)
		cub->keys |= KEY_S;
	else if (keycode == XK_d || keycode == XK_D)
		cub->keys |= KEY_D;
	else if (keycode == XK_Left)
		cub->keys |= KEY_LF_ARR;
	else if (keycode == XK_Right)
		cub->keys |= KEY_RG_ARR;
	else if (keycode == XK_Shift_L)
		cub->keys |= KEY_SHIFT;
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == XK_w || keycode == XK_W)
		cub->keys &= ~KEY_W;
	else if (keycode == XK_a || keycode == XK_A)
		cub->keys &= ~KEY_A;
	else if (keycode == XK_s || keycode == XK_S)
		cub->keys &= ~KEY_S;
	else if (keycode == XK_d || keycode == XK_D)
		cub->keys &= ~KEY_D;
	else if (keycode == XK_Left)
		cub->keys &= ~KEY_LF_ARR;
	else if (keycode == XK_Right)
		cub->keys &= ~KEY_RG_ARR;
	else if (keycode == XK_Shift_L)
		cub->keys &= ~KEY_SHIFT;
	return (0);
}

int	click_cross(t_cub *cub)
{
	exit_done(cub);
	return (0);
}
