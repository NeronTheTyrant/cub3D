/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:09:21 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 14:39:51 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	add_sprite(t_sprite sp, t_cub *cub)
{
	t_sprite	*newsprite;
	t_list		*new;

	newsprite = malloc(sizeof(*newsprite));
	if (newsprite == NULL)
		return (ERR_MALLOC);
	ft_memcpy(newsprite, &sp, sizeof(*newsprite));
	new = ft_lstnew(newsprite);
	if (new == NULL)
	{
		free(newsprite);
		return (ERR_MALLOC);
	}
	ft_lstadd_back(&cub->sp, new);
	return (SUCCESS);
}

t_list	*get_sprite_lst_by_id(t_list *lst, int id)
{
	t_list		*ptr;
	t_sprite	*sp;

	ptr = lst;
	while (ptr)
	{
		sp = (t_sprite *)ptr->content;
		if (sp->id == id)
			return (ptr);
		ptr = ptr->next;
	}
	printf("Error\nNo sprite found matching ID\n");
	return (NULL);
}

t_sprite	*get_sprite_by_id(t_list *lst, int id)
{
	t_list		*ptr;
	t_sprite	*sp;

	ptr = lst;
	while (ptr)
	{
		sp = (t_sprite *)ptr->content;
		if (sp->id == id)
			return (sp);
		ptr = ptr->next;
	}
	printf("Error\nNo sprite found matching ID\n");
	return (NULL);
}

void	get_sprite_dist(t_cub *cub, t_list *lst)
{
	t_sprite	*sp;

	while (lst)
	{
		sp = (t_sprite *)lst->content;
		sp->dist = (cub->play->pos.x - sp->pos.x)
			* (cub->play->pos.x - sp->pos.x)
			+ (cub->play->pos.y - sp->pos.y)
			* (cub->play->pos.y - sp->pos.y);
		lst = lst->next;
	}
}

int	sort_sprites(t_sprite *sp1, t_sprite *sp2)
{
	if (sp1->dist < sp2->dist)
		return (1);
	else
		return (0);
}
