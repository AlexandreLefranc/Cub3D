#include "cub3d.h"

int	init_all(t_all **all)
{
	*all = /*ft_*/calloc(sizeof(**all), 1);
	if (*all == NULL)
		return (1);
	return (0);
}
