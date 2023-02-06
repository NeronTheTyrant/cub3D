/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:49:29 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 13:48:28 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		{
			ft_freeargs(newmap, j);
			return (-1);
		}
		j++;
		i++;
	}
	newmap[cub->map_h] = NULL;
	cub->map = newmap;
	return (0);
}

static int	fill_map(char ***map, t_file mapfile, t_cub *cub)
{
	char	**temp;
	char	*line;
	int		i;
	int		ret;

	i = 0;
	temp = malloc(sizeof(*temp) * (cub->map_h + 1));
	if (temp == NULL)
		return (ERR_MALLOC);
	while (i < cub->map_h)
	{
		ret = get_next_line(mapfile.fd, &line);
		if (ret != 1)
			break ;
		temp[i] = line;
		cub->map_w = ft_ishigher(cub->map_w, ft_strlen(temp[i++]));
		if (ft_strcmp(line, "}") == 0)
		{
			ret = ERR_MAP_SMALL;
			break ;
		}
	}
	temp[i] = NULL;
	*map = temp;
	return (ret);
}

static int	get_map(char ***map, t_file mapfile, t_cub *cub)
{
	int	ret;

	ret = fill_map(map, mapfile, cub);
	if (ret != 1)
	{
		ft_freeargs(*map, ft_argcount(*map));
		*map = NULL;
		if (ret == -1)
			return (ERR_MALLOC);
		if (ret == 0)
			return (ERR_EOF);
		if (ret == ERR_MAP_SMALL)
			return (ERR_MAP_SMALL);
	}
	return (ret);
}

int	handle_map(char **args, t_file mapfile, t_cub *cub)
{
	char	**map;
	int		ret;

	map = NULL;
	ret = check_map_id(args, cub, ID_MAP);
	if (ret != 0)
		return (setting_error(cub, args, ret, NULL));
	ret = open_set(mapfile.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	ret = get_map(&map, mapfile, cub);
	cub->map = map;
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	ret = close_set(mapfile.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	ret = remap(map, cub);
	ft_freeargs(map, ft_argcount(map));
	if (ret == -1)
		return (setting_error(cub, args, ERR_MALLOC, NULL));
	ft_freeargs(args, ft_argcount(args));
	if (check_map(cub) == -1)
		return (-1);
	return (0);
}

int	parse_map(t_file mapfile, t_cub *cub)
{
	char	**args;
	int		ret;

	args = NULL;
	ret = get_next_setting(&args, mapfile.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	if (handle_map(args, mapfile, cub) < 0)
		return (-1);
	ret = get_next_setting(&args, mapfile.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	ret = handle_map_floor(args, mapfile, cub);
	if (ret < 0)
		return (setting_error(cub, args, ret, args[0]));
	ft_freeargs(args, ft_argcount(args));
	ret = get_next_setting(&args, mapfile.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	ret = handle_map_ceil(args, mapfile, cub);
	if (ret < 0)
		return (setting_error(cub, args, ret, args[0]));
	ft_freeargs(args, ft_argcount(args));
	return (0);
}
