/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_fc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:05:02 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:24:40 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	fill_map_fc_2(t_cub *cub, char *line, char **dest)
{
	char	*temp;
	int		ret;

	ret = 1;
	temp = strfill(line, cub->map_w, ' ');
	if (temp == NULL)
		ret = ERR_MALLOC;
	if (ft_strcmp(line, "}") == 0)
		ret = ERR_MAP_SMALL;
	if ((int)ft_strlen(temp) > cub->map_w)
		ret = ERR_MAP_LINE;
	free(line);
	*dest = temp;
	return (ret);
}

static int	fill_map_fc(char ***map, t_file mapfile, t_cub *cub)
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
		ret = fill_map_fc_2(cub, line, &temp[i]);
		i++;
		if (ret != 1)
			break ;
	}
	temp[i] = NULL;
	*map = temp;
	return (ret);
}

static int	get_map_fc(char ***map, t_file mapfile, t_cub *cub)
{
	int	ret;

	ret = fill_map_fc(map, mapfile, cub);
	if (ret != 1)
	{
		ft_freeargs(*map, ft_argcount(*map));
		*map = NULL;
		if (ret == -1 || ret == ERR_MALLOC)
			return (ERR_MALLOC);
		if (ret == 0)
			return (ERR_EOF);
		if (ret == ERR_MAP_SMALL)
			return (ERR_MAP_SMALL);
		if (ret == ERR_MAP_LINE)
			return (ERR_MAP_LINE);
	}
	return (ret);
}

int	handle_map_floor(char **args, t_file mapfile, t_cub *cub)
{
	char	**map;
	int		ret;

	map = NULL;
	ret = check_map_id(args, cub, ID_MAPF);
	if (ret != 0)
		return (ret);
	ret = open_set(mapfile.fd);
	if (ret < 0)
		return (ret);
	ret = get_map_fc(&map, mapfile, cub);
	cub->mapf = map;
	if (ret < 0)
		return (ret);
	ret = close_set(mapfile.fd);
	if (ret < 0)
		return (ret);
	return (0);
}

int	handle_map_ceil(char **args, t_file mapfile, t_cub *cub)
{
	char	**map;
	int		ret;

	map = NULL;
	ret = check_map_id(args, cub, ID_MAPC);
	if (ret != 0)
		return (ret);
	ret = open_set(mapfile.fd);
	if (ret < 0)
		return (ret);
	ret = get_map_fc(&map, mapfile, cub);
	cub->mapc = map;
	if (ret < 0)
		return (ret);
	ret = close_set(mapfile.fd);
	if (ret < 0)
		return (ret);
	return (0);
}
