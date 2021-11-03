/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:27:05 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:27:06 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_img	get_floor_tex(t_cub *cub, t_floorcast *floor)
{
	int		sfnb;
	t_pos	pos;

	pos.y = (int)floor->pos.y;
	pos.x = (int)floor->pos.x;
	if (pos.y >= cub->map_h || pos.y < 0)
		pos.y = 1;
	if (pos.x >= cub->map_w || pos.x < 0)
		pos.x = 1;
	sfnb = cub->mapf[pos.y][pos.x];
	if (ft_isdigit(sfnb) == 1)
		sfnb = sfnb - 48;
	else if (ft_islowercase(sfnb) == 1)
		sfnb = sfnb - 87;
	else if (ft_isuppercase(sfnb) == 1)
		sfnb = sfnb - 29;
	if (sfnb >= cub->tex_sf->texnbr)
		sfnb = 0;
	return (*cub->sf[sfnb].tex);
}

t_img	get_ceil_tex(t_cub *cub, t_floorcast *floor)
{
	int		sfnb;
	t_pos	pos;

	pos.y = (int)floor->pos.y;
	pos.x = (int)floor->pos.x;
	if (pos.y >= cub->map_h || pos.y < 0)
		pos.y = 1;
	if (pos.x >= cub->map_w || pos.x < 0)
		pos.x = 1;
	sfnb = cub->mapc[pos.y][pos.x];
	if (ft_isdigit(sfnb) == 1)
		sfnb = sfnb - 48;
	else if (ft_islowercase(sfnb) == 1)
		sfnb = sfnb - 87;
	else if (ft_isuppercase(sfnb) == 1)
		sfnb = sfnb - 29;
	else
		return (cub->tex_sky);
	return (*cub->sf[sfnb].tex);
}
