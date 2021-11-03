/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:37:16 by mlebard           #+#    #+#             */
/*   Updated: 2021/07/13 12:15:21 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <stdint.h>

typedef struct s_bmp_head
{
	uint32_t	fullsize;
	uint32_t	reserved;
	uint32_t	offset;
}				t_bmp_head;

typedef struct s_bmp_info
{
	uint32_t	size;
	int32_t		width;
	int32_t		height;
	uint16_t	colorplanes;
	uint16_t	bpp;
	uint32_t	compression;
	uint32_t	raw_data_size;
	int32_t		y_res;
	int32_t		x_res;
	uint32_t	color_table;
	uint32_t	important_colors;
}				t_bmp_info;

#endif
