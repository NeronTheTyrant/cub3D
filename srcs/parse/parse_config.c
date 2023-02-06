/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:58:54 by mlebard           #+#    #+#             */
/*   Updated: 2021/05/07 18:50:36 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_config_textures(t_file config, t_textures *tx, t_cub *cub)
{
	int		ret;
	char	**args;

	ret = get_next_setting(&args, config.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	if (ft_strcmp(args[0], "TEXTURES") != 0)
		return (setting_error(cub, args, ERR_WRONG_ID, args[0]));
	if (ft_argcount(args) != 3)
		return (setting_error(cub, args, ERR_ARG_NB, "TEXTURES"));
	if (ft_strcheck_each(args[1], &ft_isdigit) == 0)
		return (setting_error(cub, args, ERR_BAD_ARG, "TEXTURES"));
	tx->texnbr = ft_atoi(args[1]);
	if (tx->texnbr == 0)
		return (setting_error(cub, args, ERR_BAD_ARG, "TEXTURES"));
	tx->tex = malloc(sizeof(*tx->tex) * tx->texnbr);
	if (tx->tex == NULL)
		return (setting_error(cub, args, ERR_MALLOC, "TEXTURES"));
	ft_bzero(tx->tex, sizeof(*tx->tex) * tx->texnbr);
	ret = handle_textures(config.fd, cub, tx->texnbr, tx->tex);
	ft_freeargs(args, ft_argcount(args));
	return (ret);
}

int	parse_config_animation(t_file config, t_textures *tx, t_cub *cub)
{
	int		ret;
	char	**args;

	ret = get_next_setting(&args, config.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	if (ft_strcmp(args[0], "ANIMATION") != 0)
		return (setting_error(cub, args, ERR_WRONG_ID, args[0]));
	if (ft_argcount(args) != 2)
		return (setting_error(cub, args, ERR_ARG_NB, "ANIMATION"));
	ret = handle_anim(config.fd, cub, tx->texnbr, tx->tex);
	ft_freeargs(args, ft_argcount(args));
	return (ret);
}
