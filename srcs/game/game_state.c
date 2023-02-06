/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:15:12 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:15:13 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	game_over(t_cub *cub)
{
	(void)cub;
	return ;
}

void	game_win(t_cub *cub)
{
	(void)cub;
	return ;
}

void	load_next_level(t_cub *cub)
{
	free_map_specific(cub);
	ft_bzero(cub->play, sizeof(*cub->play));
	if (cub->nextmap != NULL)
		load_map(cub, cub->nextmap);
	change_action_idle(cub);
	cub->state = 0;
}

void	check_game_state(t_cub *cub)
{
	if (cub->state == STATE_DEAD)
		game_over(cub);
	if (cub->state == STATE_WIN)
		game_win(cub);
	if (cub->state == STATE_NEXT_LEVEL)
		load_next_level(cub);
}
