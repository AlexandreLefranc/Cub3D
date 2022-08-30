/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:48:18 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/30 14:13:26 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_all(t_all *all)
{
	if (all->texture_no.img != NULL)
		mlx_destroy_image(all->mlx, all->texture_no.img);
	if (all->texture_so.img != NULL)
		mlx_destroy_image(all->mlx, all->texture_so.img);
	if (all->texture_we.img != NULL)
		mlx_destroy_image(all->mlx, all->texture_we.img);
	if (all->texture_ea.img != NULL)
		mlx_destroy_image(all->mlx, all->texture_ea.img);
	if (all->mlx != NULL && all->win != NULL)
	{
		mlx_destroy_window(all->mlx, all->win);
		mlx_destroy_display(all->mlx);
		free(all->mlx);
	}
	ft_strtabfree(all->map);
	free(all->floor.raw);
	free(all->ceiling.raw);
	free(all->texture_no.path);
	free(all->texture_so.path);
	free(all->texture_we.path);
	free(all->texture_ea.path);
	free(all);
}

void	drain_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
