/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:07:25 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/30 15:15:45 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap(t_all *all, t_data *img)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < ft_strtabsize(all->map))
	{
		x = 0;
		while (x < ft_strlen(all->map[y]))
		{
			if (all->map[y][x] == '1')
				my_mlx_square(img, x * TILE, y * TILE, 0x00777777);
			else
				my_mlx_square(img, x * TILE, y * TILE, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	display_player(all, img);
}

int	display_minimap(t_all *all, int offsetx, int offsety)
{
	t_data	img;

	img.img = mlx_new_image(all->mlx, ft_strlen(all->map[0]) * TILE,
			ft_strtabsize(all->map) * TILE);
	printf("Create new image %lu x %lu\n", ft_strlen(all->map[0]) * TILE, ft_strtabsize(all->map) * TILE);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	draw_minimap(all, &img);
	mlx_put_image_to_window(all->mlx, all->win, img.img, offsetx, offsety);
	mlx_destroy_image(all->mlx, img.img);
	return (0);
}
