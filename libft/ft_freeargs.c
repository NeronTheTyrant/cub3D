/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeargs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:30:45 by mlebard           #+#    #+#             */
/*   Updated: 2021/06/27 19:54:41 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_freeargs(char **args, int argcount)
{
	int	i;

	i = 0;
	if (args == NULL || argcount < 0)
		return (0);
	while (i < argcount && args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (-1);
}
