/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:17:35 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 11:57:49 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_cub(t_cub *cub)
{
	if (cub->set.txnorth.img != NULL)
		mlx_destroy_image(cub->mlx, cub->set.txnorth.img);
	if (cub->set.txsouth.img != NULL)
		mlx_destroy_image(cub->mlx, cub->set.txsouth.img);
	if (cub->set.txeast.img != NULL)
		mlx_destroy_image(cub->mlx, cub->set.txeast.img);
	if (cub->set.txwest.img != NULL)
		mlx_destroy_image(cub->mlx, cub->set.txwest.img);
	if (cub->set.txsprite.img != NULL)
		mlx_destroy_image(cub->mlx, cub->set.txsprite.img);
	if (cub->map != NULL)
		ft_freeargs(cub->map, ft_argcount(cub->map));
	if (cub->sp != NULL)
		free(cub->sp);
	if (cub->z != NULL)
		free(cub->z);
}

int	exit_done(t_cub *cub)
{
	free_cub(cub);
	if (cub->win != NULL)
		mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_file	mapfile;
	char	*temp;
	t_cub	cub;

	ft_bzero(&cub, sizeof(cub));
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		cub.save = 1;
	if (cub.save == 1 || argc == 2)
	{
		mapfile.path = argv[1];
		temp = ft_strrchr(mapfile.path, '.');
		if (temp == NULL || ft_strcmp(temp, ".cub") != 0)
			return (file_error(mapfile.path, 1));
		if (filecheck(mapfile.path) == -1)
			return (file_error(mapfile.path, 0));
		mapfile.fd = open(mapfile.path, O_RDONLY);
		cub.mlx = mlx_init();
		if (parse_cub(mapfile, &cub) == 0)
		{
			start_gameloop(&cub);
		}
	}
	exit_done(&cub);
	return (0);
}
