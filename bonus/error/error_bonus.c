/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:08 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:54:05 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	cub_error3(int errcode, char *str)
{
	if (errcode == ERR_READ)
		perror(str);
	else if (errcode == ERR_WRITE)
		perror(str);
	else if (errcode == ERR_HUD_SMALL)
		printf("Screen resolution is too small for some HUD elements.\n");
	else if (errcode == ERR_BAD_SAVE_ARG)
		printf("%s: Bad argument; expected \"--save\"\n", str);
	else if (errcode == ERR_MOB_OUT_OF_BOUNDS)
		printf("%s: Mob spawnpoint is out of boundaries\n", str);
	else if (errcode == ERR_MOB_WALL)
		printf("%s: Mob spawnpoint is a wall.\n", str);
}

static void	cub_error2(int errcode, char *str)
{
	if (errcode < ERR_TP_WALL)
		cub_error3(errcode, str);
	if (errcode == ERR_SET_CLOSE)
		printf("%s: Bad lump setting close\n", str);
	else if (errcode == ERR_EOF)
		printf("Unexpected End Of File\nMissing some or all settings/maps\n");
	else if (errcode == ERR_MAP_BORDERS)
		printf("Incorrect borders\n");
	else if (errcode == ERR_MAP_INVALID)
		printf("Invalid character\n");
	else if (errcode == ERR_MAP_OPEN)
		printf("Open map or invalid character\n");
	else if (errcode == ERR_MAP_PLAYERS)
		printf("Multiple players\n");
	else if (errcode == ERR_MAP_NOPLAYER)
		printf("Check reached end of map and found no player\n");
	else if (errcode == ERR_MAP_SMALL)
		printf("%s: Map is too small\n", str);
	else if (errcode == ERR_MAP_LINE)
		printf("%s: At least one line in this map is too big\n", str);
	else if (errcode == ERR_TP_OUT_OF_BOUNDS)
		printf("%s: Teleporter destination is out of boundaries\n", str);
	else if (errcode == ERR_TP_WALL)
		printf("%s: Teleporter destionation is a wall.\n", str);
}

int	cub_error(t_cub *cub, int errcode, char *str)
{
	printf("Error\n");
	if (cub->in_sf_config == 1)
		printf("SURFACE CONFIG\n");
	if (cub->in_sp_config == 1)
		printf ("SPRITE CONFIG\n");
	if (errcode <= ERR_SET_CLOSE)
		cub_error2(errcode, str);
	else if (errcode == ERR_MALLOC)
		printf("Malloc error\n");
	else if (errcode == ERR_FILE_EXTENSION)
		printf("%s: Not of the expected file extension\n", str);
	else if (errcode == ERR_NOT_FILE)
		perror(str);
	else if (errcode == ERR_WRONG_ID)
		printf("%s: Wrong ID\n", str);
	else if (errcode == ERR_DUP_ID)
		printf("%s: Duplicate setting\n", str);
	else if (errcode == ERR_ARG_NB)
		printf("%s: Invalid number of arguments\n", str);
	else if (errcode == ERR_BAD_ARG)
		printf("%s: Invalid argument(s)\n", str);
	else if (errcode == ERR_SET_OPEN)
		printf("%s: Bad lump setting open\n", str);
	return (-1);
}

int	setting_error(t_cub *cub, char **args, int errcode, char *str)
{
	cub_error(cub, errcode, str);
	if (args != NULL)
		ft_freeargs(args, ft_argcount(args));
	return (-1);
}

int	map_error(t_cub *cub, int y, int x, int errcode)
{
	int	i;

	cub_error(cub, errcode, NULL);
	if (errcode != ERR_MAP_NOPLAYER)
		printf("Line: %d\nCol:  %d\n", y, x);
	if (errcode == ERR_MAP_PLAYERS)
		printf("1st player:\nLine %.0f\nCol  %.0f\n",
			cub->play->pos.y, cub->play->pos.x);
	if (errcode != ERR_MAP_NOPLAYER)
	{
		i = 0;
		while (i <= y && cub->map[i])
			printf("%s\n", cub->map[i++]);
		printf("\033[1;31m%*c\n\033[0m", x + 1, '^');
		while (i <= cub->map_h && cub->map[i])
			printf("%s\n", cub->map[i++]);
	}
	return (-1);
}
