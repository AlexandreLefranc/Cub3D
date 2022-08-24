#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_all *all;

	all = init_all();
	if (all == NULL)
		return (1);
	if (parser(argc, argv, all) != 0)
		return (free(all), 1);

	printf("Forgot to manage exit !\n");
	free(all);
	return (0);
}
