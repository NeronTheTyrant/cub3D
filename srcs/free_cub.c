/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:12:11 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:12:12 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_hud(t_cub *cub, t_hud *hud)
{
	int	i;

	if (hud == NULL)
		return ;
	free_mlx_image(cub, hud->hp_full.img);
	free_mlx_image(cub, hud->hp_empty.img);
	free_mlx_image(cub, hud->hp_half.img);
	free_mlx_image(cub, hud->crosshair.img);
	free_mlx_image(cub, hud->mace_idle.img);
	i = 0;
	while (i < 3)
	{
		free_mlx_image(cub, hud->hands_idle[i].img);
		i++;
	}
	i = 0;
	while (i < 7)
	{
		free_mlx_image(cub, hud->hands_attack[i].img);
		free_mlx_image(cub, hud->mace_attack[i].img);
		i++;
	}
	free(hud);
}

static void	free_generic(t_cub *cub)
{
	if (cub->ray != NULL)
		free(cub->ray);
	if (cub->floor != NULL)
		free(cub->floor);
	if (cub->sprite != NULL)
		free(cub->sprite);
	if (cub->sky != NULL)
		free(cub->sky);
	if (cub->play != NULL)
		free(cub->play);
	if (cub->mini != NULL)
		free(cub->mini);
	if (cub->z != NULL)
		free(cub->z);
	if (cub->tex_sp != NULL)
		free(cub->tex_sp);
	if (cub->tex_sf != NULL)
		free(cub->tex_sf);
	if (cub->nextmap != NULL)
		free(cub->nextmap);
}

void	free_cub(t_cub *cub)
{
	free_map_specific(cub);
	free_hud(cub, cub->hud);
	free_generic(cub);
}
