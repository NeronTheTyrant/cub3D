/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:50:14 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 11:03:38 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	load_map(t_cub *cub, char *path)
{
	t_file	mapfile;

	mapfile.path = path;
	if (check_file_extension(mapfile.path, ".cub") == 0)
		exit_error(cub, ERR_FILE_EXTENSION, mapfile.path);
	if (filecheck(mapfile.path) == -1)
		exit_error(cub, ERR_NOT_FILE, mapfile.path);
	mapfile.fd = open(mapfile.path, O_RDONLY);
	if (cub->nextmap != NULL)
	{
		free(cub->nextmap);
		cub->nextmap = NULL;
	}
	if (parse_cub(mapfile, cub) != 0)
		exit_done(cub);
	init_game_values(cub);
	return (0);
}

int	main(int argc, char **argv)
{
	t_file	mapfile;
	t_cub	*cub;

	cub = malloc(sizeof(*cub));
	if (cub == NULL)
		return (cub_error(cub, ERR_MALLOC, NULL));
	init_cub(cub);
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		cub->save = 1;
	else if (argc == 3)
		exit_error(cub, ERR_BAD_SAVE_ARG, argv[2]);
	if (cub->save == 1 || argc == 2)
	{
		mapfile.path = argv[1];
		if (check_file_extension(mapfile.path, ".cub") == 0)
			exit_error(cub, ERR_FILE_EXTENSION, mapfile.path);
		if (filecheck(mapfile.path) == -1)
			exit_error(cub, ERR_NOT_FILE, mapfile.path);
		mapfile.fd = open(mapfile.path, O_RDONLY);
		cub->mlx = mlx_init();
		if (parse_cub(mapfile, cub) == 0)
			init_game(cub);
	}
	exit_done(cub);
	return (0);
}
