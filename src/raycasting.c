/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:04:31 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/06 16:42:55 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	draw_ceiling(t_all *all, int x)
{
	int	y;

	y = 0;
	while (y < all->rc.draw_start)
	{
		my_mlx_pixel_put(&all->imgbuf, x, y, all->ceiling.color);
		y++;
	}
}

static void	draw_column(t_all *all, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	draw_ceiling(all, x);
	y = all->rc.draw_start;
	step = 1.0 * all->rc.texture->height / all->rc.wall_height;
	tex_pos = (y - SCREENH / 2 + all->rc.wall_height / 2) * step;
	while (y <= all->rc.draw_end)
	{
		tex_y = (int)tex_pos & (all->rc.texture->height - 1);
		tex_pos += step;
		color = get_pixel_color(all->rc.texture, all->rc.texture_x, tex_y);
		my_mlx_pixel_put(&all->imgbuf, x, y, color);
		y++;
	}
	while (y < SCREENH)
	{
		my_mlx_pixel_put(&all->imgbuf, x, y, all->floor.color);
		y++;
	}
}

int	render_raycasting(t_all *all)
{
	int	x;

	x = 0;
	while (x < SCREENW)
	{
		get_ray(all, x);
		get_usefull_distances(all);
		find_wall(all);
		find_distance(all);
		find_texture(all);
		find_wall_height_and_texture_x(all);
		draw_column(all, x);
		x++;
	}
	if (all->minimap_display == true && ft_strlen(all->map[0]) * TILE < SCREENW
		&& ft_strtabsize(all->map) * TILE < SCREENH)
		draw_minimap(all, &all->imgbuf);
	mlx_put_image_to_window(all->mlx, all->win, all->imgbuf.img, 0, 0);
	return (0);
}
