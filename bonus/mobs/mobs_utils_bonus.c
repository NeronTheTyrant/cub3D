/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mobs_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 23:14:10 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/14 23:14:11 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	add_mob(t_mob mob, t_cub *cub)
{
	t_mob	*newmob;
	t_list	*new;

	newmob = malloc(sizeof(*newmob));
	if (newmob == NULL)
		return (ERR_MALLOC);
	ft_memcpy(newmob, &mob, sizeof(t_mob));
	new = ft_lstnew(newmob);
	if (new == NULL)
	{
		free(newmob);
		return (ERR_MALLOC);
	}
	ft_lstadd_back(&cub->mob, new);
	return (SUCCESS);
}

int	add_sprite_from_mob(t_cub *cub, t_mob mob)
{
	t_sprite	sp;

	ft_memcpy(&sp, &cub->sp_type[mob.sp_type], sizeof(t_sprite));
	sp.event = 0;
	sp.id = mob.sp_id;
	sp.pos = mob.pos;
	sp.mob_id = mob.id;
	if (add_sprite(sp, cub) < 0)
		return (ERR_MALLOC);
	return (SUCCESS);
}

t_list	*get_mob_lst_by_id(t_list *lst, int id)
{
	t_list	*ptr;
	t_mob	*mob;

	ptr = lst;
	while (ptr)
	{
		mob = (t_mob *)ptr->content;
		if (mob->id == id)
			return (ptr);
		ptr = ptr->next;
	}
	printf("Error\nNo mob found matching ID\n");
	return (NULL);
}

t_mob	*get_mob_by_id(t_list *lst, int id)
{
	t_list	*ptr;
	t_mob	*mob;

	ptr = lst;
	while (ptr)
	{
		mob = (t_mob *)ptr->content;
		if (mob->id == id)
			return (mob);
		ptr = ptr->next;
	}
	printf("Error\nNo mob found matching ID\n");
	return (NULL);
}

int	check_mob_type(char *args, t_cub *cub)
{
	int	mob_type_nbr;

	mob_type_nbr = get_tex_nbr(args, cub->mob_type_nb);
	if (mob_type_nbr == ERR_BAD_ARG)
		return (ERR_BAD_ARG);
	if (cub->mob_type[mob_type_nbr].attack != NULL)
		return (ERR_DUP_ID);
	return (mob_type_nbr);
}
