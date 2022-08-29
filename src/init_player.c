#include "cub3d.h"

static char	find_player_position(char **map, int *x, int *y)
{
	while (map[*x])
	{
		*y = 0;
		while (map[*x][*y])
		{
			if (map[*x][*y] == 'N' || map[*x][*y] == 'S' || map[*x][*y] == 'W'
				|| map[*x][*y] == 'E')
				return (map[*x][*y]);
			(*y)++;
		}
		(*x)++;
	}
	return ('\0');
}

static void	init_player_pos(char **map, t_vec *pos)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (find_player_position(map, &x, &y) != '\0')
	{
		pos->x = x + 0.5;
		pos->y = y + 0.5;
	}
}

static void	init_player_dir(char **map, t_vec *dir)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (find_player_position(map, &x, &y) == 'N')
	{
		dir->x = 0;
		dir->y = -1;
	}
	if (find_player_position(map, &x, &y) == 'S')
	{
		dir->x = 0;
		dir->y = 1;
	}
	if (find_player_position(map, &x, &y) == 'E')
	{
		dir->x = 1;
		dir->y = 0;
	}
	if (find_player_position(map, &x, &y) == 'W')
	{
		dir->x = -1;
		dir->y = 0;
	}
}

void	player_plane(t_vec dir, t_vec *plane)
{
	plane->x = -0.66 * dir.y;
	plane->y = 0.66 * dir.x;
}

void	remove_player_map_position(t_all *all)
{
	size_t x;
	size_t y;

	y = 0;
	while (y < ft_strtabsize(all->map))
	{
		x = 0;
		while (x < ft_strlen(all->map[y]))
		{
			if (all->map[y][x] == 'N' ||all->map[y][x] == 'S' ||all->map[y][x] == 'W' ||all->map[y][x] == 'E' )
				all->map[y][x] = '0';
			x++;
		}
		y++;
	}
}

// 	init_player(&all->player, all->map);
void	init_player(t_player *player, char **map)
{
	init_player_pos(map, &player->pos);
	init_player_dir(map, &player->dir);
	player_plane(player->dir, &player->plane);
}
//
// void	print_map(char **map)
// {
// 	int i;
//
// 	i = 0;
// 	while (map[i] != NULL)
// 	{
// 		printf("%s\n", map[i]);
// 		i++;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	// t_all	all;
// 	// char	*valid_map2[] =
// 	// {   "       11111111111111111111111111",
// 	// 	"       1111111111111111111111111",
// 	// 	"       11111W00001110000111111111",
// 	// 	"111111100000000000000001         ",
// 	// 	"111111111011000001110000111111111",
// 	// 	"100000000011000001110111111111111",
// 	// 	"11110111111111011100000010001    ",
// 	// 	"11110111111111011101010010001    ",
// 	// 	"11111000110101011100000010001    ",
// 	// 	"     1000000000000000110000011111",
// 	// 	"11111000000000001101010010001",
// 	// 	"110000011101010111110111100111",
// 	// 	"11110111 1110101 101111010001",
// 	// 	"11111111 1111111 111111111111", NULL};
// 	//
// 	// t_player player;
// 	// all.map = valid_map2;
//
// 	t_all	*all;
//
// 	all = init_all();
// 	if (all == NULL)
// 		return (1);
// 	if (parser(argc, argv, all) != 0)
// 		return (destroy_all(all), 1);
//
// 	// all.player = player;
// 	print_map(all->map);
// 	remove_player_map_position(all);
// 	print_map(all->map);
// 	destroy_all(all);
// 	// printf("pos.x = %f\n", player.pos.x);
// 	// printf("pos.y = %f\n", player.pos.y);
// 	// printf("dir.x = %f\n", player.dir.x);
// 	// printf("dir.y = %f\n", player.dir.y);
// 	// printf("plane.x = %f\n", player.plane.x);
// 	// printf("plane.y = %f\n", player.plane.y);
// }
