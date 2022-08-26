/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:13:37 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/26 15:24:12 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_all(t_all *all)
{
	printf("map_path: %s\n\n", all->map_path);

	printf("map: %p\n", all->map);
	if (all->map != NULL)
	{
		for (int i = 0; all->map[i] != NULL; i++)
		printf("[%s]\n", all->map[i]);
	}
	printf("\n");

	printf("floor:\n");
	printf("  raw = %s\n", all->floor.raw);
	printf("  red = %d\n", all->floor.red);
	printf("  green = %d\n", all->floor.green);
	printf("  blue = %d\n", all->floor.blue);
	printf("\n");

	printf("ceiling:\n");
	printf("  raw = %s\n", all->ceiling.raw);
	printf("  red = %d\n", all->ceiling.red);
	printf("  green = %d\n", all->ceiling.green);
	printf("  blue = %d\n", all->ceiling.blue);
	printf("\n");

	printf("texture_no:\n");
	printf("  path = %s\n", all->texture_no.path);
	printf("  img = %p\n", all->texture_no.img);
	printf("  width = %d\n", all->texture_no.width);
	printf("  height = %d\n", all->texture_no.height);
	printf("\n");

	printf("texture_so:\n");
	printf("  path = %s\n", all->texture_so.path);
	printf("  img = %p\n", all->texture_so.img);
	printf("  width = %d\n", all->texture_so.width);
	printf("  height = %d\n", all->texture_so.height);
	printf("\n");

	printf("texture_we:\n");
	printf("  path = %s\n", all->texture_we.path);
	printf("  img = %p\n", all->texture_we.img);
	printf("  width = %d\n", all->texture_we.width);
	printf("  height = %d\n", all->texture_we.height);
	printf("\n");

	printf("texture_ea:\n");
	printf("  path = %s\n", all->texture_ea.path);
	printf("  img = %p\n", all->texture_ea.img);
	printf("  width = %d\n", all->texture_ea.width);
	printf("  height = %d\n", all->texture_ea.height);
	printf("\n");

	printf("player:\n");
	printf("  pos:\n");
	printf("    x = %f\n", all->player.pos.x);
	printf("    y = %f\n", all->player.pos.y);
	printf("  dir:\n");
	printf("    x = %f\n", all->player.dir.x);
	printf("    y = %f\n", all->player.dir.y);
	printf("  plane:\n");
	printf("    x = %f\n", all->player.plane.x);
	printf("    y = %f\n", all->player.plane.y);
	printf("\n");
}

static void	destroy_all(t_all *all)
{
	ft_strtabfree(all->map);
	free(all->floor.raw);
	free(all->ceiling.raw);
	free(all->texture_no.path);
	free(all->texture_so.path);
	free(all->texture_we.path);
	free(all->texture_ea.path);
	free(all);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	all = init_all();
	if (all == NULL)
		return (1);
	if (parser(argc, argv, all) != 0)
		return (destroy_all(all), 1);
	if (check_all_rgb(all) != 0)
		return (destroy_all(all), 1);
	print_all(all);
	destroy_all(all);
	return (0);
}
