#include "cub3d.h"

static void	print_all(t_all *all)
{
	printf("map_path: %s\n\n", all->map_path);

	printf("map: %p\n", all->map);
	if (all->map != NULL)
	{
		for (int i = 0; all->map[i] != NULL; i++)
		printf("%s\n", all->map[i]);
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

	printf("texture_NO:\n");
	printf("  path = %s\n", all->texture_NO.path);
	printf("  img = %p\n", all->texture_NO.img);
	printf("  width = %d\n", all->texture_NO.width);
	printf("  height = %d\n", all->texture_NO.height);
	printf("\n");

	printf("texture_SO:\n");
	printf("  path = %s\n", all->texture_SO.path);
	printf("  img = %p\n", all->texture_SO.img);
	printf("  width = %d\n", all->texture_SO.width);
	printf("  height = %d\n", all->texture_SO.height);
	printf("\n");

	printf("texture_WE:\n");
	printf("  path = %s\n", all->texture_WE.path);
	printf("  img = %p\n", all->texture_WE.img);
	printf("  width = %d\n", all->texture_WE.width);
	printf("  height = %d\n", all->texture_WE.height);
	printf("\n");

	printf("texture_EA:\n");
	printf("  path = %s\n", all->texture_EA.path);
	printf("  img = %p\n", all->texture_EA.img);
	printf("  width = %d\n", all->texture_EA.width);
	printf("  height = %d\n", all->texture_EA.height);
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
	if (all->map != NULL)
	{
		ft_strtabfree(all->map);
	}
	free(all->floor.raw);
	free(all->ceiling.raw);
	free(all->texture_NO.path);
	free(all->texture_SO.path);
	free(all->texture_WE.path);
	free(all->texture_EA.path);
	free(all);
}

int	main(int argc, char **argv)
{
	t_all *all;

	all = init_all();
	if (all == NULL)
		return (1);
	if (parser(argc, argv, all) != 0)
		return (destroy_all(all), 1);

	print_all(all);
	// printf("Forgot to manage exit !\n");
	destroy_all(all);
	return (0);
}
