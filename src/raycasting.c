/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:04:31 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/06 11:47:49 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

struct timeval t0;
struct timeval t1;

// static void	print_rc(t_all *all)
// {
// 	printf("ray\n");
// 	printf("  ray.x = %f\n", all->rc.ray.x);
// 	printf("  ray.y = %f\n", all->rc.ray.y);
// 	printf("\n");
// 	printf("side_x = %d\n", all->rc.side_x);
// 	printf("side_x = %d\n", all->rc.side_y);
// 	printf("\n");
// 	printf("deltaDistX = %f\n", all->rc.deltaDistX);
// 	printf("deltaDistY = %f\n", all->rc.deltaDistY);
// 	printf("sideDistX = %f\n", all->rc.sideDistX);
// 	printf("sideDistY = %f\n", all->rc.sideDistY);
// 	printf("\n");
// 	printf("side = %d\n", all->rc.side);
// 	printf("\n");
// 	printf("mapX = %d\n", all->rc.mapX);
// 	printf("mapY = %d\n", all->rc.mapY);
// }

static void	get_ray(t_all *all, int x)
{
	double	ray_deviance;
	double	norm_ray;

	ray_deviance = (2 * x / (double)SCREENW) - 1;
	all->rc.ray.x = all->player.dir.x + ray_deviance * all->player.plane.x;
	all->rc.ray.y = all->player.dir.y + ray_deviance * all->player.plane.y;
	norm_ray = norm(all->rc.ray);
	all->rc.ray.x = all->rc.ray.x / norm_ray;
	all->rc.ray.y = all->rc.ray.y / norm_ray;
	if (all->rc.ray.x < 0)
		all->rc.side_x = -1;
	else
		all->rc.side_x = 1;
	if (all->rc.ray.y < 0)
		all->rc.side_y = -1;
	else
		all->rc.side_y = 1;
}

static void	get_usefull_distances(t_all *all)
{
	double	ray_x;
	double	ray_y;
	double	pos_x;
	double	pos_y;

	pos_x = all->player.pos.x;
	pos_y = all->player.pos.y;
	ray_x = all->rc.ray.x;
	ray_y = all->rc.ray.y;
	all->rc.deltaDistX = 1 / fabs(ray_x);
	all->rc.deltaDistY = 1 / fabs(ray_y);
	if (all->rc.side_x < 0)
		all->rc.sideDistX = all->rc.deltaDistX * (pos_x - floor(pos_x));
	else
		all->rc.sideDistX = all->rc.deltaDistX * (floor(pos_x) + 1 - pos_x);
	if (all->rc.side_y < 0)
		all->rc.sideDistY = all->rc.deltaDistY * (pos_y - floor(pos_y));
	else
		all->rc.sideDistY = all->rc.deltaDistY * (floor(pos_y) + 1 - pos_y);
}

static void	find_wall(t_all *all)
{
	int	hit;

	hit = 0;
	all->rc.mapX = (int)all->player.pos.x;
	all->rc.mapY = (int)all->player.pos.y;
	while (hit == 0)
	{
		if (all->rc.sideDistX < all->rc.sideDistY)
		{
			// printf("Je vais sur le cote\n");
			all->rc.sideDistX += all->rc.deltaDistX;
			all->rc.mapX += all->rc.side_x;
			all->rc.side = 0;
		}
		else
		{
			// printf("Je vais en haut ou en bas\n");
			all->rc.sideDistY += all->rc.deltaDistY;
			all->rc.mapY += all->rc.side_y;
			all->rc.side = 1;
		}
		if (all->map[all->rc.mapY][all->rc.mapX] == '1')
		{
			hit = 1;
			// printf("Hit at mapX = %d, mapY = %d\n", all->rc.mapX,all->rc.mapY);
		}
	}
	// printf("dist=%f OU dist=%f\n", all->rc.sideDistX,all->rc.sideDistY);
}

static void	find_distance(t_all *all)
{
	if (all->rc.side == 0)
		all->rc.wall_dist = all->rc.sideDistX - all->rc.deltaDistX;
	else
		all->rc.wall_dist = all->rc.sideDistY - all->rc.deltaDistY;
	// printf("Distance =%f\n", all->rc.wall_dist);
}

static void	find_texture(t_all *all)
{
	if (all->rc.side_x == 1 && all->rc.side == 0)
		all->rc.texture = &all->texture_we;
	else if ((all->rc.side_x == 1 && all->rc.side == 1)
		|| (all->rc.side_x == -1 && all->rc.side == 1))
	{
		if (all->rc.side_y == 1)
			all->rc.texture = &all->texture_no;
		else if (all->rc.side_y == -1)
			all->rc.texture = &all->texture_so;
	}
	else if (all->rc.side_x == -1 && all->rc.side == 0)
		all->rc.texture = &all->texture_ea;
	// printf("Texture = %s\n", all->rc.texture->path);
}

static void	find_wall_height_and_texture_x(t_all *all)
{
	all->rc.wall_height = (int)(SCREENH / all->rc.wall_dist);
	all->rc.draw_start = -all->rc.wall_height / 2 + SCREENH / 2;
	if(all->rc.draw_start < 0)
		all->rc.draw_start = 0;
	all->rc.draw_end = all->rc.wall_height / 2 + SCREENH / 2;
	if(all->rc.draw_end >= SCREENH)
		all->rc.draw_end = SCREENH - 1;

	// printf("pos.y = %f | wall_dist = %f | ray.y = %f\n", all->player.pos.y, all->rc.wall_dist, all->rc.ray.y);
	if (all->rc.side == 0)
		all->rc.wall_x = all->player.pos.y + all->rc.wall_dist * all->rc.ray.y;
	else
		all->rc.wall_x = all->player.pos.x + all->rc.wall_dist * all->rc.ray.x;
	all->rc.wall_x -= floor((all->rc.wall_x));
	// printf("wall_x = %f\n", all->rc.wall_x);

	all->rc.texture_x = (int)(all->rc.wall_x * all->rc.texture->width);
	// printf("texture_x = %d\n", all->rc.texture_x);

	if(all->rc.side == 0 && all->rc.ray.x > 0)
		all->rc.texture_x = all->rc.texture->width - all->rc.texture_x - 1;
	if(all->rc.side == 1 && all->rc.ray.y < 0)
		all->rc.texture_x = all->rc.texture->width - all->rc.texture_x - 1;
	// printf("texture_x = %d\n", all->rc.texture_x);
}

static void	draw_column(t_all *all, t_data *img, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	y = 0;
	while (y < all->rc.draw_start)
	{
		my_mlx_pixel_put(img, x, y, all->ceiling.color);
		y++;
	}
	y = all->rc.draw_start;
	step = 1.0 * all->rc.texture->height / all->rc.wall_height;
	tex_pos = (y - SCREENH / 2 + all->rc.wall_height / 2) * step;
	while (y <= all->rc.draw_end)
	{
		tex_y = (int)tex_pos & (all->rc.texture->height - 1);
		tex_pos += step;
		color = get_pixel_color(all->rc.texture, all->rc.texture_x, tex_y);
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
	while (y < SCREENH)
	{
		my_mlx_pixel_put(img, x, y, all->floor.color);
		y++;
	}
}

int	render_raycasting(t_all *all)
{
	int	x;
	t_data	img;

	gettimeofday(&t0, NULL);
	img.img = mlx_new_image(all->mlx, SCREENW, SCREENH);
	img.addr = (unsigned int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	x = 0;
	while (x < SCREENW)
	{
		get_ray(all, x);
		get_usefull_distances(all);
		find_wall(all);
		find_distance(all);
		find_texture(all);
		find_wall_height_and_texture_x(all);
		draw_column(all, &img, x);
		x++;
	}

	if (ft_strlen(all->map[0]) * TILE < SCREENW &&
			ft_strtabsize(all->map) * TILE < SCREENH)
		draw_minimap(all, &img);

	mlx_put_image_to_window(all->mlx, all->win, img.img, 0, 0);

	mlx_destroy_image(all->mlx, img.img);
	gettimeofday(&t1, NULL);
	printf("Elapsed time: %ld microseconds\n", (t1.tv_sec - t0.tv_sec) * 1000000 + (t1.tv_usec - t0.tv_usec));
	return (0);
}
