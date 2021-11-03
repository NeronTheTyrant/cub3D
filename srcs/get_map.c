/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:19:29 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:02:10 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse_map_error(int errcode)
{
	printf("Error\n");
	printf("Map:\n");
	if (errcode == 0)
	{
		printf("Map Not Found\n");
	}
	if (errcode == -1)
	{
		printf("Malloc Error\n");
	}
	if (errno != 0)
	{
		perror("");
	}
	return (-1);
}

static int	remap(char **map, t_cub *cub)
{
	char	**newmap;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newmap = malloc(sizeof(*newmap) * (cub->map_h + 1));
	if (newmap == NULL)
		return (-1);
	while (*map[i] == '\0' || ft_strcheck_each(map[i], &ft_isspace) == 1)
		i++;
	while (map[i] && j < cub->map_h)
	{
		newmap[j] = strfill(map[i], cub->map_w, ' ');
		if (newmap[j] == NULL)
			return (ft_freeargs(newmap, j));
		j++;
		i++;
	}
	newmap[cub->map_h] = NULL;
	cub->map = newmap;
	return (0);
}

static int	adjust_linecount(char **map, int linecount)
{
	int	i;
	int	temp;

	i = 0;
	temp = linecount - 1;
	if (temp < 1)
		return (-1);
	while (map[i] && (*map[i] == '\0'
			|| ft_strcheck_each(map[i], &ft_isspace) == 1))
	{
		linecount--;
		i++;
	}
	while (temp > 0 && (*map[temp] == '\0'
			|| ft_strcheck_each(map[temp], &ft_isspace) == 1))
	{
		temp--;
		linecount--;
	}
	return (linecount);
}

static char	**get_map(t_file mapfile, int linecount, int *maxlen)
{
	char	**map;
	char	*line;
	int		i;
	int		ret;

	i = 0;
	map = malloc(sizeof(*map) * (linecount + 1));
	if (map == NULL)
		return (NULL);
	while (1)
	{
		ret = get_next_line(mapfile.fd, &line);
		map[i] = line;
		if (ret == -1)
		{
			ft_freeargs(map, ft_argcount(map));
			return (NULL);
		}
		*maxlen = ft_ishigher(*maxlen, ft_strlen(map[i]));
		i++;
		if (ret == 0)
			break ;
	}
	map[i] = NULL;
	return (map);
}

int	parse_map(t_file mapfile, int linecount, t_cub *cub)
{
	char	**map;
	int		maxlen;
	int		ret;

	maxlen = 0;
	map = get_map(mapfile, linecount, &maxlen);
	if (map == NULL)
		return (parse_map_error(-1));
	cub->map = map;
	linecount = adjust_linecount(cub->map, linecount);
	if (linecount <= 0)
		return (parse_map_error(0));
	cub->map_w = maxlen;
	cub->map_h = linecount;
	ret = remap(map, cub);
	ft_freeargs(map, ft_argcount(map));
	if (ret == -1)
		return (parse_map_error(-1));
	if (check_map(cub) == -1)
		return (-1);
	return (0);
}
