/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_handle_mobs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:12:32 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:12:33 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	assign_mob_info(char **args, t_cub *cub, int typenbr)
{
	t_mob	temp;
	int		ret;

	if (ft_argcount(args) != 10)
		return (ERR_ARG_NB);
	ret = set_mob(args, &temp, cub);
	if (ret != SUCCESS)
		return (ret);
	cub->mob_type[typenbr] = temp;
	return (SUCCESS);
}

int	handle_mob_info(int fd, t_cub *cub)
{
	int		count;
	int		ret;
	int		typenbr;
	char	**args;

	count = 0;
	if (open_set(fd) < 0)
		return (setting_error(cub, NULL, ERR_SET_OPEN, cub->set_id));
	while (count < cub->mob_type_nb)
	{
		ret = get_next_setting(&args, fd);
		if (ret < 0)
			return (setting_error(cub, args, ret, "MOB INFO"));
		typenbr = check_mob_type(args[0], cub);
		if (typenbr < 0)
			return (setting_error(cub, args, typenbr, "MOB INFO"));
		ret = assign_mob_info(args, cub, typenbr);
		if (ret != 0)
			return (setting_error(cub, args, ret, "MOB INFO"));
		count++;
		ft_freeargs(args, ft_argcount(args));
	}
	if (close_set(fd) < 0)
		return (setting_error(cub, args, ERR_SET_CLOSE, "MOB INFO"));
	return (SUCCESS);
}

int	add_mob_from_type(char **args, t_cub *cub)
{
	t_mob	temp;
	int		typenbr;

	if (ft_argcount(args) != 4)
		return (ERR_ARG_NB);
	ft_bzero(&temp, sizeof(t_mob));
	typenbr = get_tex_nbr(args[0], cub->mob_type_nb);
	if (typenbr < 0)
		return (typenbr);
	ft_memcpy(&temp, &cub->mob_type[typenbr], sizeof(t_mob));
	if (ft_isfloat(args[1]) == 1 && ft_isfloat(args[2]) == 1)
		set_mob_posxy(ft_atof(args[1]), ft_atof(args[2]), &temp);
	else
		return (ERR_BAD_ARG);
	temp.id = ++cub->mob_nb;
	temp.sp_id = ++cub->sp_nb;
	if (add_mob(temp, cub) < 0)
		return (ERR_MALLOC);
	if (add_sprite_from_mob(cub, temp) < 0)
		return (ERR_MALLOC);
	return (SUCCESS);
}

int	handle_mobs(int fd, t_cub *cub)
{
	int		ret;
	char	**args;

	args = NULL;
	if (open_set(fd) < 0)
		return (setting_error(cub, args, ERR_SET_OPEN, "MOB"));
	while (1)
	{
		ret = get_next_setting(&args, fd);
		if (ret < 0)
			return (setting_error(cub, args, ret, "MOB"));
		if (ft_strcmp(args[0], "}") == 0)
			break ;
		ret = add_mob_from_type(args, cub);
		if (ret < 0)
			return (setting_error(cub, args, ret, "MOB"));
		ft_freeargs(args, ft_argcount(args));
	}
	if (ft_argcount(args) != 2)
		return (setting_error(cub, args, ERR_SET_CLOSE, "MOB"));
	ft_freeargs(args, ft_argcount(args));
	return (1);
}

int	parse_config_mob_info(t_file config, t_cub *cub)
{
	int		ret;
	char	**args;

	ret = get_next_setting(&args, config.fd);
	if (ret < 0)
		return (setting_error(cub, args, ret, NULL));
	if (ft_strcmp(args[0], "MOB") != 0)
		return (setting_error(cub, args, ERR_WRONG_ID, args[0]));
	if (ft_argcount(args) != 3)
		return (setting_error(cub, args, ERR_ARG_NB, "MOB"));
	if (ft_strcheck_each(args[1], &ft_isdigit) == 0)
		return (setting_error(cub, args, ERR_BAD_ARG, "MOB"));
	cub->mob_type_nb = ft_atoi(args[1]);
	if (cub->mob_type_nb == 0)
		return (setting_error(cub, args, ERR_BAD_ARG, "MOB"));
	cub->mob_type = malloc(sizeof(*cub->mob_type) * cub->mob_type_nb);
	if (cub->mob_type == NULL)
		return (setting_error(cub, args, ERR_MALLOC, "MOB"));
	ft_bzero(cub->mob_type, sizeof(*cub->mob_type) * cub->mob_type_nb);
	ret = handle_mob_info(config.fd, cub);
	ft_freeargs(args, ft_argcount(args));
	return (ret);
}
