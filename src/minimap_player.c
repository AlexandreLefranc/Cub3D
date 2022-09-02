/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:30:39 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/02 14:22:50 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	DDA(t_data *img, t_point start, t_point end, int i)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	step;

	dx = (end.x - start.x);
	dy = (end.y - start.y);
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = start.x;
	y = start.y;
	i = 1;
	while (i <= step)
	{
		my_mlx_pixel_put(img, (int)x, (int)y, 0x000000FF);
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
}

static void	draw_player_box(t_data *img, t_point start, int color)
{
	int i;
	int j;

	i = -2;
	while (i < 3)
	{
		j = -2;
		while (j < 3)
		{
			my_mlx_pixel_put(img, start.x + i, start.y + j, color);
			j++;
		}
		i++;
	}
}

void	display_player(t_all *all, t_data *img)
{
	t_point start;
	t_point end;

	start.x = (int)(all->player.pos.x * TILE);
	start.y = (int)(all->player.pos.y * TILE);
	end.x = (int)((all->player.pos.x + all->player.dir.x) * TILE);
	end.y = (int)((all->player.pos.y + all->player.dir.y) * TILE);
	DDA(img, start, end, 0);

	start.x = (int)(all->player.pos.x * TILE);
	start.y = (int)(all->player.pos.y * TILE);
	end.x = (int)((all->player.pos.x + (all->player.dir.x + all->player.plane.x) / 2) * TILE);
	end.y = (int)((all->player.pos.y + (all->player.dir.y + all->player.plane.y) / 2) * TILE);
	DDA(img, start, end, 0);

	start.x = (int)(all->player.pos.x * TILE);
	start.y = (int)(all->player.pos.y * TILE);
	end.x = (int)((all->player.pos.x + (all->player.dir.x - all->player.plane.x) * 4) * TILE);
	end.y = (int)((all->player.pos.y + (all->player.dir.y - all->player.plane.y) * 4) * TILE);
	DDA(img, start, end, 0);
	draw_player_box(img, start, 0x00FF4500);
}

// int	main()
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	img;
//
// 	t_all all;
//
// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!");
// 	img.img = mlx_new_image(mlx, 800, 600);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 		&img.endian);
//
// 	all.player.pos.x = 10;
// 	all.player.pos.y = 20;
// 	all.player.dir.x = 0.25;
// 	all.player.dir.y = 0.66;
//
// 	display_player(&all, &img);
// 	my_mlx_pixel_put(&img, 10 * TILE, 20*TILE, 0x00FFFF00);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	sleep(5);
// 	mlx_destroy_window(mlx, mlx_win);
// 	mlx_destroy_image(mlx, img.img);
// 	mlx_destroy_display(mlx);
// 	return (0);
// }
