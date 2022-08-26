/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:07:25 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/26 18:12:21 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_square(t_data *data, int posx, int posy, int color, int length)
{
	int	x;
	int	y;

	y = 0;
	while (y < length)
	{
		x = 0;
		while (x < length)
		{
			my_mlx_pixel_put(data, posx + x, posy + y, color);
			x++;
		}
		y++;
	}
}

int	display_minimap(t_all *all, int offsetx, int offsety)
{
	size_t	x;
	size_t	y;
	t_data	img;

	img.img = mlx_new_image(all->mlx, ft_strlen(all->map[0]) * 8, ft_strtabsize(all->map) * 8);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	y = 0;
	while (y < ft_strtabsize(all->map))
	{
		x = 0;
		while (x < ft_strlen(all->map[y]))
		{
			if (all->map[y][x] == '1')
				my_mlx_square(&img, x * 8, y * 8, 0x00FF0000, 8);
			if (all->map[y][x] == '0')
				my_mlx_square(&img, x * 8, y * 8, 0x0000FF00, 8);
			if (all->map[y][x] == 'N' || all->map[y][x] == 'S' ||
				all->map[y][x] == 'E' || all->map[y][x] == 'W')
				my_mlx_square(&img, x * 8, y * 8, 0x000000FF, 8);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(all->mlx, all->win, img.img, offsetx, offsety);
	mlx_destroy_image(all->mlx, img.img);
	return (0);
}
