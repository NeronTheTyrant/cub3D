/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:37:14 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 11:06:29 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	setting_error(char **args, t_set_id set_id, int err)
{
	printf("Error\n");
	if (err != MALLOC_ERR)
		printf("%s: ", args[0]);
	if (set_id == WRONG_ID)
		printf("Wrong ID\n");
	else if (set_id == DUP_ID)
		printf("Duplicate setting\n");
	else if (err != SUCCESS)
	{
		if (err == ARG_NB)
			printf("Invalid number of arguments\n");
		else if (err == BAD_ARG)
			printf("Invalid argument(s)\n");
		else
			printf("Malloc error\n");
	}
	if (errno != 0)
		perror("");
	if (args != NULL)
		ft_freeargs(args, ft_argcount(args));
	return (-1);
}

int	map_error(t_cub *cub, int y, int x, int errcode)
{
	int	i;

	i = 0;
	printf("Error\nMap:\n");
	if (errcode == 0)
		printf("Incorrect Borders:\nLine: %d\nCol: %d\n", y, x);
	else if (errcode == 1)
		printf("Invalid Character:\nLine: %d\nCol: %d\n", y, x);
	else if (errcode == 2)
		printf("Open Map/Invalid Character\nLine: %d\nCol: %d\n", y, x);
	else if (errcode == 3)
	{
		printf("Multiple Players:\nLine: %d\nCol: %d\n", y, x);
		printf("1st player:\nLine %.0f\nCol %.0f\n", cub->play.y, cub->play.x);
	}
	else if (errcode == 4)
		printf("Check reached end of map and found no player.\n");
	if (errcode != 4)
	{
		while (i <= y && cub->map[i])
			printf("%s\n", cub->map[i++]);
		printf("\033[1;31m%*c\n\033[0m", x + 1, '^');
	}
	return (-1);
}

int	file_error(char *path, int err)
{
	printf("Error\n");
	if (err == 1)
		printf("%s: Not a .cub file\n", path);
	else
		perror(path);
	return (-1);
}
