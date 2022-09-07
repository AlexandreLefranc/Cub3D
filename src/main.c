/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:13:37 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/07 11:43:26 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_all	*all;

	all = init_all();
	if (all == NULL)
		return (1);
	if (parser(argc, argv, all) != 0)
		return (destroy_all(all), 1);
	if (checker(all) != 0)
		return (destroy_all(all), 1);
	init_player(all);
	if (create_window(all) != 0)
		return (destroy_all(all), 1);
	if (create_texture_ea_we(all) != 0 || create_texture_no_so(all) != 0)
		return (destroy_all(all), 1);
	all->imgbuf.img = mlx_new_image(all->mlx, SCREENW, SCREENH);
	all->imgbuf.addr = (unsigned int *)mlx_get_data_addr(all->imgbuf.img,
			&all->imgbuf.bits_per_pixel, &all->imgbuf.line_length,
			&all->imgbuf.endian);
	mlx_hook(all->win, 02, (1L << 0), key_press, all);
	mlx_hook(all->win, 03, (1L << 1), key_release, all);
	mlx_hook(all->win, 17, 0, destroy_all_exit, all);
	mlx_loop_hook(all->mlx, loop_hook, all);
	mlx_loop(all->mlx);
	return (0);
}
