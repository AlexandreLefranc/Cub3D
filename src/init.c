#include "cub3d.h"

t_all	*init_all()
{
	t_all	*all;

	all = ft_calloc(sizeof(*all), 1);
	if (all == NULL)
		return (NULL);
	return (all);
}
