/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_parse_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:43:43 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:44:00 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_tex_nbr(char *args, int limit)
{
	int	nb;

	if (ft_strcheck_each(args, &ft_isdigit) == 1)
	{
		nb = ft_atoi(args);
		if (nb > 0 && nb <= limit)
			return (nb - 1);
	}
	return (ERR_BAD_ARG);
}

int	check_tex(char *args, int limit, t_img *path)
{
	int	texnbr;

	texnbr = get_tex_nbr(args, limit);
	if (texnbr == ERR_BAD_ARG)
		return (ERR_BAD_ARG);
	if (path[texnbr].img != NULL)
		return (ERR_DUP_ID);
	return (texnbr);
}

int	assign_texture(char **args, t_cub *cub, t_img *img)
{
	t_img	tx;

	if (ft_argcount(args) != 3)
		return (ERR_ARG_NB);
	ft_bzero(&tx, sizeof(t_img));
	tx.img = mlx_xpm_file_to_image(cub->mlx, args[1], &tx.width, &tx.height);
	if (tx.img == NULL)
	{
		*img = tx;
		return (ERR_BAD_ARG);
	}
	tx.addr = mlx_get_data_addr(tx.img, &tx.bpp, &tx.linelen, &tx.endi);
	*img = tx;
	return (SUCCESS);
}

int	assign_texture_from_path(char *path, t_cub *cub, t_img *img)
{
	t_img	tx;

	ft_bzero(&tx, sizeof(t_img));
	tx.img = mlx_xpm_file_to_image(cub->mlx, path, &tx.width, &tx.height);
	if (tx.img == NULL)
	{
		*img = tx;
		return (ERR_BAD_ARG);
	}
	tx.addr = mlx_get_data_addr(tx.img, &tx.bpp, &tx.linelen, &tx.endi);
	*img = tx;
	return (SUCCESS);
}
