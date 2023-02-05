/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:31:47 by mlebard           #+#    #+#             */
/*   Updated: 2020/12/21 23:33:26 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return: returns absolute value of argument n
*/

intmax_t	ft_abs(intmax_t n)
{
	if (n < 0)
		n *= -1;
	return (n);
}