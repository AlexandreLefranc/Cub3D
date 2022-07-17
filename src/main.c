#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_all *all;

	init_all(&all);
	parser(argc, argv, all);
	return (0);
}
