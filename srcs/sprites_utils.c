/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:21:28 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 11:56:44 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	add_sprite(t_cub *cub, t_pos pos)
{
	size_t	len;
	size_t	newlen;

	len = sizeof(t_sprite) * cub->sp_nb;
	newlen = sizeof(t_sprite) * (cub->sp_nb + 1);
	cub->sp = ft_realloc(cub->sp, len, newlen);
	if (cub->sp == NULL)
		return (-1);
	ft_bzero(&cub->sp[cub->sp_nb], sizeof(t_sprite));
	cub->sp[cub->sp_nb].x = (double)pos.x + 0.5;
	cub->sp[cub->sp_nb].y = (double)pos.y + 0.5;
	cub->sp_nb++;
	return (0);
}

static void	get_sprite_dist(t_cub *cub)
{
	int	i;
	int	dx;
	int	dy;

	i = 0;
	while (i < cub->sp_nb)
	{
		dx = (cub->play.x - cub->sp[i].x) * (cub->play.x - cub->sp[i].x);
		dy = (cub->play.y - cub->sp[i].y) * (cub->play.y - cub->sp[i].y);
		cub->sp[i].dist = dx + dy;
		i++;
	}
}

void	sort_sprites(t_cub *cub)
{
	t_sprite	temp;
	int			i;
	int			j;

	get_sprite_dist(cub);
	i = 0;
	while (i < cub->sp_nb)
	{
		j = i + 1;
		while (j < cub->sp_nb)
		{
			if (cub->sp[i].dist < cub->sp[j].dist)
				ft_memswap(&cub->sp[i], &cub->sp[j], &temp, sizeof(t_sprite));
			j++;
		}
		cub->sp[i].order = i;
		i++;
	}
}
