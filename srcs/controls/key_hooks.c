/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:59 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 11:56:45 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	key_press_mov(int keycode, t_cub *cub)
{
	if (keycode == XK_w || keycode == XK_W)
		cub->keys |= KEY_W;
	else if (keycode == XK_s || keycode == XK_S)
		cub->keys |= KEY_S;
	else if (keycode == XK_a || keycode == XK_A)
		cub->keys |= KEY_A;
	else if (keycode == XK_d || keycode == XK_D)
		cub->keys |= KEY_D;
	else if (keycode == XK_q || keycode == XK_Q)
		cub->keys |= KEY_Q;
	else if (keycode == XK_e || keycode == XK_E)
		cub->keys |= KEY_E;
	else if (keycode == XK_Shift_L)
		cub->keys |= KEY_SHIFT;
	else if (keycode == XK_Up)
		cub->keys |= KEY_UP_ARR;
	else if (keycode == XK_Down)
		cub->keys |= KEY_DW_ARR;
	else if (keycode == XK_space)
		cub->keys |= KEY_SPACE;
	else if (keycode == XK_Control_L)
		cub->keys |= KEY_CTRL;
	else
		return (-1);
	return (0);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		exit_done(cub);
	else if (key_press_mov(keycode, cub) == -1)
	{
		if (keycode == XK_m && cub->mini->off != 1)
			cub->mini->on = !cub->mini->on;
		else if (keycode == XK_p || keycode == XK_P)
			fireball(cub);
		else if (keycode == XK_o || keycode == XK_O)
			mace(cub);
	}
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
	else if (keycode == XK_q || keycode == XK_Q)
		cub->keys &= ~KEY_Q;
	else if (keycode == XK_e || keycode == XK_E)
		cub->keys &= ~KEY_E;
	else if (keycode == XK_Up)
		cub->keys &= ~KEY_UP_ARR;
	else if (keycode == XK_Down)
		cub->keys &= ~KEY_DW_ARR;
	else if (keycode == XK_space)
		cub->keys &= ~KEY_SPACE;
	else if (keycode == XK_Control_L)
		cub->keys &= ~KEY_CTRL;
	else if (keycode == XK_Shift_L)
		cub->keys &= ~KEY_SHIFT;
	return (0);
}

int	click_cross(t_cub *cub)
{
	exit_done(cub);
	return (0);
}
