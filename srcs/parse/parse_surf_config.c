/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_surf_config.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:13:10 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:13:10 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse_skybox(t_file config, t_cub *cub)
{
	int		ret;
	char	**args;

	ret = get_next_setting(&args, config.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	ret = handle_skybox(args, cub);
	if (ret < 0)
		return (setting_error(cub, args, ret, args[0]));
	ft_freeargs(args, ft_argcount(args));
	return (SUCCESS);
}

static int	parse_surface_config(t_file config, t_cub *cub)
{
	int	ret;

	cub->in_sf_config = 1;
	ret = parse_config_textures(config, cub->tex_sf, cub);
	if (ret < 0)
		return (ret);
	ret = parse_skybox(config, cub);
	if (ret < 0)
		return (ret);
	ret = parse_config_animation(config, cub->tex_sf, cub);
	if (ret < 0)
		return (ret);
	cub->in_sf_config = 0;
	return (0);
}

int	get_surface_config(int fd, t_cub *cub)
{
	int		ret;
	t_file	sf_config;
	char	**args;

	args = NULL;
	ret = get_next_setting(&args, fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, args[0]));
	if (ft_strcmp(args[0], "SF_CONFIG") != 0)
		return (setting_error(cub, args, ERR_WRONG_ID, args[0]));
	if (ft_argcount(args) != 3)
		return (setting_error(cub, args, ERR_ARG_NB, args[0]));
	if (check_file_extension(args[1], ".sfconfig") == 0)
		return (setting_error(cub, args, ERR_FILE_EXTENSION, args[1]));
	if (filecheck(args[1]) == -1)
		return (setting_error(cub, args, ERR_NOT_FILE, NULL));
	sf_config.path = args[1];
	sf_config.fd = open(sf_config.path, O_RDONLY);
	ft_freeargs(args, ft_argcount(args));
	ret = parse_surface_config(sf_config, cub);
	close(sf_config.fd);
	if (ret < 0)
		return (-1);
	return (0);
}
