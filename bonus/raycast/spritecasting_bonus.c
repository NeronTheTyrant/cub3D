/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecasting_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:52:07 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:31:20 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	get_sprite_pos(t_cub *cub, t_spritecast *sprite, t_sprite *sp)
{
	t_dpos	pos;
	double	invdet;
	t_dpos	transform;
	int		screenx;

	pos.x = sp->pos.x - cub->play->render.x;
	pos.y = sp->pos.y - cub->play->render.y;
	invdet = 1.0 / (cub->play->plane.x * cub->play->dir.y
			- cub->play->dir.x * cub->play->plane.y);
	transform.x = invdet * (cub->play->dir.y * pos.x
			- cub->play->dir.x * pos.y);
	transform.y = invdet * (-cub->play->plane.y * pos.x
			+ cub->play->plane.x * pos.y);
	screenx = (int)((cub->res.x / 2) * (1 + transform.x / transform.y));
	sprite->transform = transform;
	sprite->screenx = screenx;
}

static void	get_sprite_dim(t_cub *cub, t_spritecast *sprite, t_player *play,
			t_sprite *sp)
{
//	printf("sp->hmove = %d\nsp->trans.y = %f\n", sp->hmove, sprite->transform.y);
	sprite->move_screen = (int)(sp->hmove / pow(sprite->transform.y, 2)/*sprite->transform.y*/)
		+ play->pitch + (int)(play->renderz / sprite->transform.y);
//	printf("sprite->move_screen = %d\n", sprite->move_screen);
	sprite->height = abs((int)(cub->res.y / (sprite->transform.y))) / (float)sp->hdiv;
	sprite->top = -sprite->height / 2 + cub->res.y / 2 + sprite->move_screen;
	if (sprite->top < 0)
		sprite->top = 0;
	sprite->bot = sprite->height / 2 + cub->res.y / 2 + sprite->move_screen;
	if (sprite->bot >= cub->res.y)
		sprite->bot = cub->res.y - 1;
	sprite->width = ft_abs((int)(cub->res.y / (sprite->transform.y)))
		/ (float)sp->wdiv;
	sprite->left = -sprite->width / 2 + sprite->screenx;
	if (sprite->left < 0)
		sprite->left = 0;
	sprite->right = sprite->width / 2 + sprite->screenx;
	if (sprite->right >= cub->res.x)
		sprite->right = cub->res.x - 1;
}

void	spritecasting(t_cub *cub, t_spritecast *sprite, t_img *frame)
{
	t_list	*lst;

	lst = cub->sp;
	ft_lstsortif(&cub->sp, &sort_sprites);
	while (lst)
	{
		get_sprite_pos(cub, sprite, lst->content);
		get_sprite_dim(cub, sprite, cub->play, lst->content);
		draw_sprite(cub, sprite, lst->content, frame);
		lst = lst->next;
	}
}
