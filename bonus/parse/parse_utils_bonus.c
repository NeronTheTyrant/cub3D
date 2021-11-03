/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:02:03 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:43:32 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	open_set(int fd)
{
	char	**args;
	int		ret;

	ret = get_next_setting(&args, fd);
	if (ret < 0)
		return (ret);
	if (ft_argcount(args) == 2 && ft_strcmp(args[0], "{") == 0)
	{
		ft_freeargs(args, ft_argcount(args));
		return (1);
	}
	else
	{
		ft_freeargs(args, ft_argcount(args));
		return (ERR_SET_OPEN);
	}
}

int	close_set(int fd)
{
	char	**args;
	int		ret;

	ret = get_next_setting(&args, fd);
	if (ret <= 0)
		return (ret);
	if (ft_argcount(args) == 2 && ft_strcmp(args[0], "}") == 0)
	{
		ft_freeargs(args, ft_argcount(args));
		return (1);
	}
	else
	{
		ft_freeargs(args, ft_argcount(args));
		return (ERR_SET_CLOSE);
	}
}
