/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:12:21 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:12:22 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	malloc_cub(t_cub *cub)
{
	cub->ray = malloc(sizeof(*cub->ray));
	cub->sprite = malloc(sizeof(*cub->sprite));
	cub->floor = malloc(sizeof(*cub->floor));
	cub->sky = malloc(sizeof(*cub->sky));
	cub->play = malloc(sizeof(*cub->play));
	cub->tex_sp = malloc(sizeof(*cub->tex_sp));
	cub->tex_sf = malloc(sizeof(*cub->tex_sf));
	cub->hud = malloc(sizeof(*cub->hud));
	cub->mini = malloc(sizeof(*cub->mini));
	if (!cub->ray || !cub->sprite || !cub->floor || !cub->sky || !cub->play
		|| !cub->tex_sf || !cub->tex_sp || !cub->hud || !cub->mini)
		return (-1);
	return (SUCCESS);
}

static void	bzero_cub(t_cub *cub)
{
	ft_bzero(cub->ray, sizeof(*cub->ray));
	ft_bzero(cub->sprite, sizeof(*cub->sprite));
	ft_bzero(cub->floor, sizeof(*cub->floor));
	ft_bzero(cub->sky, sizeof(*cub->sky));
	ft_bzero(cub->play, sizeof(*cub->play));
	ft_bzero(cub->tex_sf, sizeof(*cub->tex_sf));
	ft_bzero(cub->tex_sp, sizeof(*cub->tex_sp));
	ft_bzero(cub->hud, sizeof(*cub->hud));
	ft_bzero(cub->mini, sizeof(*cub->mini));
}

int	init_cub(t_cub *cub)
{
	char	*s;

	ft_bzero(cub, sizeof(*cub));
	if (malloc_cub(cub) == -1)
		exit_error(cub, ERR_MALLOC, NULL);
	bzero_cub(cub);
	s = "123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	cub->wallc = s;
	s = " NSWE0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	cub->wallplayc = s;
	return (1);
}
