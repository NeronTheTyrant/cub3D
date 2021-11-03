/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hud_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:49:29 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:58:29 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	resize_health(t_cub *cub, t_hud *hud)
{
	int		size;
	t_img	hp_full;
	t_img	hp_empty;
	t_img	hp_half;
	t_img	crosshair;

	size = cub->res.x / 20;
	if (cub->res.y < size * 2)
		return (cub_error(cub, ERR_HUD_SMALL, NULL));
	hp_full = mlx_resize_img(cub->mlx, hud->hp_full, size, size);
	mlx_destroy_image(cub->mlx, hud->hp_full.img);
	hp_empty = mlx_resize_img(cub->mlx, hud->hp_empty, size, size);
	mlx_destroy_image(cub->mlx, hud->hp_empty.img);
	hp_half = mlx_resize_img(cub->mlx, hud->hp_half, size, size);
	mlx_destroy_image(cub->mlx, hud->hp_half.img);
	crosshair = mlx_resize_img(cub->mlx, hud->crosshair, size / 2, size / 2);
	mlx_destroy_image(cub->mlx, hud->crosshair.img);
	if (!hp_full.img || !hp_empty.img || !hp_half.img || !crosshair.img)
		return (cub_error(cub, ERR_MALLOC, NULL));
	hud->hp_full = hp_full;
	hud->hp_empty = hp_empty;
	hud->hp_half = hp_half;
	hud->crosshair = crosshair;
	return (SUCCESS);
}

static int	resize_hands_attack(t_cub *cub, t_hud *hud, int size)
{
	int		i;
	t_img	temp;

	i = 0;
	while (i < 7)
	{
		temp = mlx_resize_img(cub->mlx, hud->hands_attack[i], size, size);
		mlx_destroy_image(cub->mlx, hud->hands_attack[i].img);
		hud->hands_attack[i] = temp;
		if (temp.img == NULL)
			return (cub_error(cub, ERR_MALLOC, NULL));
		i++;
	}
	return (SUCCESS);
}

static int	resize_hands(t_cub *cub, t_hud *hud)
{
	int		size;
	t_img	temp;
	int		i;

	size = cub->res.x / 4;
	if (size > cub->res.y)
		return (cub_error(cub, ERR_HUD_SMALL, NULL));
	i = 0;
	while (i < 3)
	{
		temp = mlx_resize_img(cub->mlx, hud->hands_idle[i], size, size);
		mlx_destroy_image(cub->mlx, hud->hands_idle[i].img);
		hud->hands_idle[i] = temp;
		if (temp.img == NULL)
			return (cub_error(cub, ERR_MALLOC, NULL));
		i++;
	}
	resize_hands_attack(cub, hud, size);
	return (SUCCESS);
}

static int	resize_mace(t_cub *cub, t_hud *hud)
{
	int		size;
	t_img	temp;
	t_img	temp2[7];
	int		i;

	size = cub->res.x / 2;
	if (size > cub->res.y)
		return (cub_error(cub, ERR_HUD_SMALL, NULL));
	temp = mlx_resize_img(cub->mlx, hud->mace_idle, size, size);
	mlx_destroy_image(cub->mlx, hud->mace_idle.img);
	hud->mace_idle = temp;
	if (temp.img == NULL)
		return (cub_error(cub, ERR_MALLOC, NULL));
	i = 0;
	while (i < 7)
	{
		temp2[i] = mlx_resize_img(cub->mlx, hud->mace_attack[i], size, size);
		mlx_destroy_image(cub->mlx, hud->mace_attack[i].img);
		hud->mace_attack[i] = temp2[i];
		if (temp2[i].img == NULL)
			return (cub_error(cub, ERR_MALLOC, NULL));
		i++;
	}
	return (SUCCESS);
}

int	resize_hud(t_cub *cub, t_hud *hud)
{
	t_hudobj	*hands;
	t_hudobj	*mace;

	if (resize_health(cub, hud) < 0)
		return (-1);
	if (resize_hands(cub, hud) < 0)
		return (-1);
	if (resize_mace(cub, hud) < 0)
		return (-1);
	hands = &cub->hud->hands;
	mace = &cub->hud->mace;
	init_hud_obj(hands, cub->res.x / 5,
		cub->res.y - hud->hands_idle[0].height, &hud->hands_idle[0]);
	init_hud_obj(mace, (cub->res.x / 3) * 1.5,
		cub->res.y - hud->mace_idle.height, &hud->mace_idle);
	return (SUCCESS);
}
