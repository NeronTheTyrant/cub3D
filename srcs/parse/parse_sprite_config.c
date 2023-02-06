/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_config.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:13:14 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:13:15 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse_config_sprite_info(t_file config, t_cub *cub)
{
	int		ret;
	char	**args;

	ret = get_next_setting(&args, config.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	if (ft_strcmp(args[0], "INFO") != 0)
		return (setting_error(cub, args, ERR_WRONG_ID, args[0]));
	if (ft_argcount(args) != 3)
		return (setting_error(cub, args, ERR_ARG_NB, "INFO"));
	if (ft_strcheck_each(args[1], &ft_isdigit) == 0)
		return (setting_error(cub, args, ERR_BAD_ARG, "INFO"));
	cub->sp_type_nb = ft_atoi(args[1]);
	if (cub->sp_type_nb == 0)
		return (setting_error(cub, args, ERR_BAD_ARG, "INFO"));
	cub->sp_type = malloc(sizeof(*cub->sp_type) * cub->sp_type_nb);
	if (cub->sp_type == NULL)
		return (setting_error(cub, args, ERR_MALLOC, "INFO"));
	ft_bzero(cub->sp_type, sizeof(*cub->sp_type) * cub->sp_type_nb);
	ret = handle_sprite_info(config.fd, cub);
	ft_freeargs(args, ft_argcount(args));
	return (ret);
}

static int	parse_player_projectile(t_file config, t_cub *cub)
{
	int		ret;
	char	**args;

	ret = get_next_setting(&args, config.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	if (ft_argcount(args) != 3)
		return (setting_error(cub, args, ERR_ARG_NB, args[0]));
	if (ft_strcmp(args[0], "PLAYER_PROJECTILE") != 0)
		return (setting_error(cub, args, ERR_WRONG_ID, args[0]));
	ret = get_tex_nbr(args[1], cub->tex_sp->texnbr);
	if (ret < 0)
		return (setting_error(cub, args, ret, args[0]));
	cub->play->proj = ret;
	ft_freeargs(args, ft_argcount(args));
	return (SUCCESS);
}

static int	parse_player_projectile_explosion(t_file config, t_cub *cub)
{
	int		ret;
	char	**args;

	ret = get_next_setting(&args, config.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	if (ft_argcount(args) != 3)
		return (setting_error(cub, args, ERR_ARG_NB, args[0]));
	if (ft_strcmp(args[0], "PLAYER_PROJECTILE_EXPLOSION") != 0)
		return (setting_error(cub, args, ERR_WRONG_ID, args[0]));
	ret = get_tex_nbr(args[1], cub->tex_sp->texnbr);
	if (ret < 0)
		return (setting_error(cub, args, ret, args[0]));
	cub->play->proj_expl = ret;
	ft_freeargs(args, ft_argcount(args));
	return (SUCCESS);
}

static int	parse_sprite_config(t_file config, t_cub *cub)
{
	int	ret;

	cub->in_sp_config = 1;
	ret = parse_config_textures(config, cub->tex_sp, cub);
	if (ret < 0)
		return (ret);
	ret = parse_player_projectile(config, cub);
	if (ret < 0)
		return (ret);
	ret = parse_player_projectile_explosion(config, cub);
	if (ret < 0)
		return (ret);
	ret = parse_config_animation(config, cub->tex_sp, cub);
	if (ret < 0)
		return (ret);
	ret = parse_config_sprite_info(config, cub);
	if (ret < 0)
		return (ret);
	ret = parse_config_mob_info(config, cub);
	if (ret < 0)
		return (ret);
	cub->in_sp_config = 0;
	return (0);
}

int	get_sprite_config(int fd, t_cub *cub)
{
	int		ret;
	t_file	sp_config;
	char	**args;

	args = NULL;
	ret = get_next_setting(&args, fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, args[0]));
	if (ft_strcmp(args[0], "SP_CONFIG") != 0)
		return (setting_error(cub, args, ERR_WRONG_ID, args[0]));
	if (ft_argcount(args) != 3)
		return (setting_error(cub, args, ERR_ARG_NB, args[0]));
	if (check_file_extension(args[1], ".spconfig") == 0)
		return (setting_error(cub, args, ERR_FILE_EXTENSION, args[1]));
	if (filecheck(args[1]) == -1)
		return (setting_error(cub, args, ERR_NOT_FILE, NULL));
	sp_config.path = args[1];
	sp_config.fd = open(sp_config.path, O_RDONLY);
	ft_freeargs(args, ft_argcount(args));
	ret = parse_sprite_config(sp_config, cub);
	close(sp_config.fd);
	if (ret < 0)
		return (-1);
	return (0);
}
