/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:07:25 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/06 16:20:46 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_grid(t_all *all, t_data *img)
{
	size_t	x;
	size_t	y;
	size_t	xmax;
	size_t	ymax;

	y = 0;
	xmax = ft_strlen(all->map[y]);
	ymax = ft_strtabsize(all->map);
	while (y < ymax * TILE)
	{
		x = 0;
		while (x < xmax * TILE)
		{
			if (y % TILE == 0 || x % TILE == 0)
			my_mlx_pixel_put(img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_all *all, t_data *img)
{
	size_t	x;
	size_t	y;
	size_t	xmax;
	size_t	ymax;

	printf("here\n");
	y = 0;
	xmax = ft_strlen(all->map[y]);
	ymax = ft_strtabsize(all->map);
	while (y < ymax)
	{
		x = 0;
		while (x < xmax)
		{
			if (all->map[y][x] == '1' || all->map[y][x] == ' ')
				my_mlx_square(img, x * TILE, y * TILE, 0x00000000);
			else
				my_mlx_square(img, x * TILE, y * TILE, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	// draw_grid(all, img);
	display_player(all, img);
}


int	display_minimap(t_all *all, int offsetx, int offsety)
{
	t_data	img;

	img.img = mlx_new_image(all->mlx, ft_strlen(all->map[0]) * TILE,
			ft_strtabsize(all->map) * TILE);
	img.addr = (unsigned int*)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	draw_minimap(all, &img);
	draw_grid(all, &img);
	mlx_put_image_to_window(all->mlx, all->win, img.img, offsetx, offsety);
	mlx_destroy_image(all->mlx, img.img);
	return (0);
}
