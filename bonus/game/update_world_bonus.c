/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_world_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:15:41 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:15:42 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	update_world(t_cub *cub)
{
	cub->timeref = cub->time;
	cub->time = clock();
	cub->frametime = ((cub->time - cub->timeref) / 1000000.0);
	cub->play->movspeed = cub->frametime * 4.0;
	cub->play->rotspeed = cub->frametime * 2.5;
	update_action(cub);
	update_sprite_status(cub, cub->sp);
	event_hub(cub, cub->event);
	mob_hub(cub, cub->mob);
	get_sprite_dist(cub, cub->sp);
	update_sprite_textures(cub);
	update_surface_textures(cub);
	if (cub->keys != 0)
		update_pos(cub, cub->play);
	update_viewbobbing(cub, cub->play);
}

void	update_sprite_status(t_cub	*cub, t_list *sp_lst)
{
	t_list		*ptr;
	t_sprite	*sp;

	ptr = sp_lst;
	while (ptr)
	{
		sp = (t_sprite *)ptr->content;
		check_sprite_update(cub, sp);
		ptr = ptr->next;
	}
}

int	update_pos(t_cub *cub, t_player *play)
{
	if (cub->keys & KEY_SHIFT)
	{
		play->movspeed *= 2;
		play->rotspeed *= 2;
	}
	if (cub->keys & KEY_W)
		move_forward(cub, &play->pos, play->dir, play->movspeed);
	if (cub->keys & KEY_S)
		move_backwards(cub, &play->pos, play->dir, play->movspeed);
	if (cub->keys & KEY_A)
		strafe_left(cub, &play->pos, play->plane, play->movspeed);
	if (cub->keys & KEY_D)
		strafe_right(cub, &play->pos, play->plane, play->movspeed);
	if (cub->keys & KEY_Q)
		turn_left(cub, play->rotspeed);
	if (cub->keys & KEY_E)
		turn_right(cub, play->rotspeed);
	if (cub->keys & KEY_UP_ARR)
		look_up(cub, play->rotspeed);
	if (cub->keys & KEY_DW_ARR)
		look_down(cub, play->rotspeed);
	return (0);
}

int	update_sprite_textures(t_cub *cub)
{
	t_list		*sp_lst;
	t_list		*next;
	t_sprite	*sp;
	t_img		*tex;

	sp_lst = cub->sp;
	while (sp_lst)
	{
		sp = (t_sprite *)sp_lst->content;
		tex = sp->tex;
		next = sp_lst->next;
		if (tex->next_tex != NULL)
		{
			while (tex->next_tex != NULL && sp->update == 1)
				update_sprite_tex(cub, sp, tex->next_tex);
		}
		else if (sp->event == EVENT_ANIMATION && sp->update == 1)
			ft_lstdelone(&cub->sp, sp_lst, &free);
		sp_lst = next;
	}
	return (0);
}

int	update_surface_textures(t_cub *cub)
{
	int			i;
	t_img		*tex;
	t_surface	*sf;

	i = 0;
	while (i < WALL_NBR)
	{
		sf = &cub->sf[i];
		tex = sf->tex;
		if (tex->next_tex != NULL && cub->time - sf->last_update >= tex->delay)
		{
			sf->last_update += tex->delay;
			sf->tex = tex->next_tex;
		}
		i++;
	}
	return (SUCCESS);
}
