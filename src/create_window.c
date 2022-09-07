/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:53:04 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/07 16:34:34 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_window(t_all *all)
{
	all->mlx = mlx_init();
	if (all->mlx == NULL)
		return (printf("Error\nmlx_init() failed\n"), 1);
	all->win = mlx_new_window(all->mlx, SCREENW, SCREENH, "Cub3D!");
	if (all->win == NULL)
		return (printf("Error\nmlx_create_window() failed\n"), 1);
	return (0);
}
