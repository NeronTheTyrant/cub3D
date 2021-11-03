/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:19:57 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 20:43:26 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	get_linecount(t_file *map)
{
	int		linecount;
	int		ret;
	int		i;
	char	buf[BUFFER_SIZE + 1];

	linecount = 1;
	while (1)
	{
		ret = read(map->fd, buf, BUFFER_SIZE);
		if (ret < 1)
			break ;
		buf[ret] = '\0';
		i = 0;
		while (buf[i])
		{
			if (buf[i] == '\n')
				linecount++;
			i++;
		}
	}
	close(map->fd);
	map->fd = open(map->path, O_RDONLY);
	return (linecount);
}

static int	check_ret(int ret, char *line, int *check)
{
	if (ret == 0 && ft_tabint(check, 0, 8) != -1)
	{
		free(line);
		printf("Error\nMissing Settings\n");
		return (-1);
	}
	else if (ret == -1)
	{
		printf("Error\nMalloc Error\n");
		return (-1);
	}
	return (0);
}

static int	parse_settings(t_file mapfile, t_cub *cub, int *linecount)
{
	char	*line;
	int		ret;
	int		set_ret;
	int		check[8];

	ft_bzero(check, sizeof(check));
	while (ft_tabint(check, 0, 8) != -1)
	{
		ret = get_next_line(mapfile.fd, &line);
		if (ret != 1)
			break ;
		(*linecount)--;
		set_ret = get_settings(line, check, cub);
		free(line);
		if (set_ret >= 0)
			check[set_ret] = 1;
		if (set_ret == -1)
			return (-1);
	}
	if (check_ret(ret, line, check) < 0)
		return (-1);
	return (0);
}

int	parse_cub(t_file mapfile, t_cub *cub)
{
	int		ret;
	int		linecount;

	linecount = get_linecount(&mapfile);
	ret = parse_settings(mapfile, cub, &linecount);
	if (ret == -1)
	{
		close(mapfile.fd);
		return (-1);
	}
	ret = parse_map(mapfile, linecount, cub);
	close(mapfile.fd);
	return (ret);
}
