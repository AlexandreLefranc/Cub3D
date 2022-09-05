/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:41:08 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/05 16:30:14 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	unsigned int	*dst;

	dst = data->addr + (y * data->line_length / sizeof(*dst) + x);
	*dst = color;
}

unsigned int	get_pixel_color(t_texture *tex, int x, int y)
{
	return (tex->data[y * tex->line_length / sizeof(unsigned int) + x]);
}

void	my_mlx_square(t_data *data, int posx, int posy, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < TILE)
	{
		x = 0;
		while (x < TILE)
		{
			my_mlx_pixel_put(data, posx + x, posy + y, color);
			x++;
		}
		y++;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
