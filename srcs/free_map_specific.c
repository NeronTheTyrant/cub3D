/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map_specific.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:11:56 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:11:57 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	cub_free_tex(t_cub *cub, t_textures *tex)
{
	int	i;

	i = 0;
	while (i < tex->texnbr)
	{
		if (tex->tex[i].img == NULL)
			break ;
		mlx_destroy_image(cub->mlx, tex->tex[i].img);
		i++;
	}
	free(tex->tex);
}

static void	free_entities(t_cub *cub)
{
	if (cub->sp_type != NULL)
	{
		free(cub->sp_type);
		cub->sp_type = NULL;
	}
	if (cub->mob_type != NULL)
	{
		free(cub->mob_type);
		cub->mob_type = NULL;
	}
	if (cub->sp != NULL)
	{
		ft_lstclear(&cub->sp, &free);
		cub->sp = NULL;
	}
	if (cub->event != NULL)
	{
		ft_lstclear(&cub->event, &free);
		cub->event = NULL;
	}
	if (cub->mob != NULL)
	{
		ft_lstclear(&cub->mob, &free);
		cub->mob = NULL;
	}
}

static void	free_maps(t_cub *cub)
{
	if (cub->map != NULL)
	{
		ft_freeargs(cub->map, ft_argcount(cub->map));
		cub->map = NULL;
	}
	if (cub->mapf != NULL)
	{
		ft_freeargs(cub->mapf, ft_argcount(cub->mapf));
		cub->mapf = NULL;
	}
	if (cub->mapc != NULL)
	{
		ft_freeargs(cub->mapc, ft_argcount(cub->mapc));
		cub->mapc = NULL;
	}
}

void	free_map_specific(t_cub *cub)
{
	free_entities(cub);
	free_maps(cub);
	if (cub->tex_sp->tex != NULL)
	{
		cub_free_tex(cub, cub->tex_sp);
		cub->tex_sp->tex = NULL;
	}
	if (cub->tex_sf->tex != NULL)
	{
		cub_free_tex(cub, cub->tex_sf);
		cub->tex_sf->tex = NULL;
	}
	free_mlx_image(cub, cub->tex_sky.img);
}
