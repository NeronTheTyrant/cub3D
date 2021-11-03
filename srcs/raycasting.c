/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 11:10:30 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 11:55:38 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	raycasting(t_cub *cub, t_img *frame)
{
	t_raycasting	rc;
	t_spritecasting	sc;

	ft_bzero(&rc, sizeof(rc));
	ft_bzero(&sc, sizeof(sc));
	wallcasting(cub, &rc, frame);
	spritecasting(cub, &sc, frame);
	return (0);
}
