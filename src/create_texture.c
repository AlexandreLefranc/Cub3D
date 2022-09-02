/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:23:19 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/02 15:32:37 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_texture(t_all *all)
{
	all->texture_no.img = mlx_xpm_file_to_image(all->mlx, all->texture_no.path,
			&all->texture_no.width, &all->texture_no.height);
	if (all->texture_no.img == NULL)
		return (printf("Error: Could not load image\n"), 1);

	// all->texture_no.img.addr = (char *)mlx_get_data_addr(all->texture_no.img,
	// 		&all->texture_no.img->bits_per_pixel, &all->texture_no->line_length,
	// 		&all->texture_no->endian);


	all->texture_so.img = mlx_xpm_file_to_image(all->mlx, all->texture_so.path,
			&all->texture_so.width, &all->texture_so.height);
	if (all->texture_so.img == NULL)
		return (printf("Error: Could not load image\n"), 1);
	all->texture_we.img = mlx_xpm_file_to_image(all->mlx, all->texture_we.path,
			&all->texture_we.width, &all->texture_we.height);
	if (all->texture_we.img == NULL)
		return (printf("Error: Could not load image\n"), 1);
	all->texture_ea.img = mlx_xpm_file_to_image(all->mlx, all->texture_ea.path,
			&all->texture_ea.width, &all->texture_ea.height);
	if (all->texture_ea.img == NULL)
		return (printf("Error: Could not load image\n"), 1);
	return (0);
}
