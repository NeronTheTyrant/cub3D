/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_handle_tex_anim.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:12:39 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:12:40 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	handle_textures(int fd, t_cub *cub, int limit, t_img *path)
{
	int		count;
	int		ret;
	int		texnbr;
	char	**args;

	count = 0;
	if (open_set(fd) < 0)
		return (setting_error(cub, NULL, ERR_SET_OPEN, "TEXTURES"));
	while (count < limit)
	{
		ret = get_next_setting(&args, fd);
		if (ret < 0)
			return (setting_error(cub, args, ret, "TEXTURES"));
		texnbr = check_tex(args[0], limit, path);
		if (texnbr < 0)
			return (setting_error(cub, args, texnbr, "TEXTURES"));
		ret = assign_texture(args, cub, &path[texnbr]);
		if (ret != 0)
			return (setting_error(cub, args, ret, "TEXTURES"));
		count++;
		ft_freeargs(args, ft_argcount(args));
	}
	if (close_set(fd) < 0)
		return (setting_error(cub, args, ERR_SET_CLOSE, "TEXTURES"));
	return (1);
}

void	set_anim(t_img *f1, t_img *f2, double delay)
{
	f1->next_tex = f2;
	f1->delay = (int)(CLOCKS_PER_SEC * delay);
}

int	add_anim(char **args, int limit, t_img *texpath)
{
	int		tex1;
	int		tex2;
	double	delay;

	if (ft_argcount(args) != 4)
		return (ERR_ARG_NB);
	tex1 = get_tex_nbr(args[0], limit);
	if (tex1 < 0)
		return (ERR_BAD_ARG);
	tex2 = get_tex_nbr(args[1], limit);
	if (tex2 < 0 && ft_strcmp(args[1], "END") != 0)
		return (ERR_BAD_ARG);
	if (ft_isfloat(args[2]) != 1)
		return (ERR_BAD_ARG);
	delay = atof(args[2]);
	if (delay == 0)
		return (ERR_BAD_ARG);
	if (tex2 >= 0)
		set_anim(&texpath[tex1], &texpath[tex2], delay);
	else
		set_anim(&texpath[tex1], NULL, delay);
	return (SUCCESS);
}

int	handle_anim(int fd, t_cub *cub, int limit, t_img *texpath)
{
	int		ret;
	char	**args;

	args = NULL;
	if (open_set(fd) < 0)
		return (setting_error(cub, args, ERR_SET_OPEN, cub->set_id));
	while (1)
	{
		ret = get_next_setting(&args, fd);
		if (ret < 0)
			return (setting_error(cub, args, ret, cub->set_id));
		if (ft_strcmp(args[0], "}") == 0)
			break ;
		ret = add_anim(args, limit, texpath);
		if (ret < 0)
			return (setting_error(cub, args, ret, cub->set_id));
		ft_freeargs(args, ft_argcount(args));
	}
	if (ft_argcount(args) != 2)
		return (setting_error(cub, args, ERR_SET_CLOSE, cub->set_id));
	ft_freeargs(args, ft_argcount(args));
	return (0);
}
