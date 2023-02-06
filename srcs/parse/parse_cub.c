/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:51:11 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:43:06 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_next_setting(char ***args, int fd)
{
	char	*line;
	int		ret;

	line = NULL;
	*args = NULL;
	ret = get_next_line(fd, &line);
	while (ret != -1)
	{
		*args = ft_splitset(line, " \t\n\v\f\r");
		free(line);
		if (*args == NULL)
			return (ERR_MALLOC);
		if (ret == 1 && (*(args)[0] == NULL
			|| ft_strncmp(*(args)[0], "#", 1) == 0))
		{
			ft_freeargs(*args, ft_argcount(*args));
			ret = get_next_line(fd, &line);
			continue ;
		}
		break ;
	}
	if (ret == 0)
		return (ERR_EOF);
	return (ret);
}

static int	parse_settings(t_file mapfile, t_cub *cub)
{
	char	**args;
	int		ret;
	int		check[SET_NBR];

	ret = 0;
	args = NULL;
	ft_bzero(check, sizeof(*check) * SET_NBR);
	while (ft_tabint(check, 0, SET_NBR) != -1)
	{
		ret = get_next_setting(&args, mapfile.fd);
		if (ret < 0)
			return (-1);
		ret = get_settings(args, mapfile.fd, check, cub);
		if (ret == -1)
			return (-1);
	}
	if (ret == 0 && ft_tabint(check, 0, SET_NBR) != -1)
		return (cub_error(cub, ERR_EOF, NULL));
	return (ret);
}

int	check_file_extension(char *path, char *extension)
{
	char	*temp;

	temp = ft_strrchr(path, '.');
	if (temp == NULL || ft_strcmp(temp, extension) != 0)
		return (0);
	else
		return (1);
}

int	parse_cub(t_file mapfile, t_cub *cub)
{
	int		ret;

	if (get_sprite_config(mapfile.fd, cub) == -1)
	{
		close(mapfile.fd);
		return (-1);
	}
	if (get_surface_config(mapfile.fd, cub) == -1)
	{
		close(mapfile.fd);
		return (-1);
	}
	ret = parse_settings(mapfile, cub);
	if (ret == -1)
	{
		close(mapfile.fd);
		return (-1);
	}
	ret = parse_map(mapfile, cub);
	close(mapfile.fd);
	if (ret < 0)
		return (-1);
	return (ret);
}
