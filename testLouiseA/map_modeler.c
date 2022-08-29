#include "cub3d.h"

int	is_map_square(char **map)
{
	int	i;
	int	first_line_length;

	first_line_length = (int)ft_strlen(map[0]);
	i = 1;
	while (map[i] && i < (int)ft_strtabsize(map))
	{
		if ((int)ft_strlen(map[i]) != first_line_length)
			return (0);
		i++;
	}
	return (1);
}

int	biggest_map_line(char **map)
{
	int	biggest_line_length;
	int	i;
	int	j;

	i = 0;
	biggest_line_length = (int)ft_strlen(map[i]);
	while (map[i])
	{
		j = i + 1;
		while (map[j])
		{
			if ((int)ft_strlen(map[j]) > biggest_line_length)
				biggest_line_length = (int)ft_strlen(map[j]);
			j++;
		}
		i++;
	}
	return (biggest_line_length);
}

// static char	**create_new_map(char **map)
// {
// 	char	**empty_squared_map;
// 	int		biggest_line_length;
// 	int		i;
//
// 	i = 0;
// 	biggest_line_length = biggest_map_line(map);
// 	empty_squared_map = ft_calloc((ft_strtabsize(map) + 1), sizeof(char *));
// 	if (empty_squared_map == NULL)
// 		return (NULL);
// 	empty_squared_map[ft_strtabsize(map)] = NULL;
// 	while (empty_squared_map[i] && i < (int)ft_strtabsize(map))
// 	{
// 		empty_squared_map[i] = ft_calloc((biggest_line_length + 1), sizeof(char));
// 		if (empty_squared_map[i] == NULL)
// 			return (NULL);
// 		i++;
// 	}
// 	return (empty_squared_map);
// }

static char	*add_spaces_to_line(char *line, char **map)
{
	int	i;

	i = 0;
	while (line[i] && i < biggest_map_line(map))
		i++;
	if (i == biggest_map_line(map))
		return (line);
	while (i < biggest_map_line(map))
	{
		line[i] = 32;
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char **change_map_format(char **map)
{
	char	**squared_map;
	int		biggest_line_length;
	int		i;

	i = 0;
	biggest_line_length = biggest_map_line(map);
	squared_map = ft_calloc((ft_strtabsize(map) + 1), sizeof(char *));
	if (squared_map == NULL)
		return (NULL);
	squared_map[ft_strtabsize(map)] = NULL;
	while (map[i] && squared_map[i] && i < biggest_line_length)
	{
		squared_map[i] = ft_calloc((biggest_line_length + 1), sizeof(char));
		if (squared_map[i] == NULL)
			return (NULL);
		ft_strlcpy(squared_map[i], map[i], ft_strlen(map[i]));
		squared_map[i] = add_spaces_to_line(squared_map[i], map);
		printf("%s\n", squared_map[i]);
		i++;
	}
	return (squared_map);
}

char	**map_modeler(char **map)
{
	char	**squared_map;

	if (is_map_square(map) == 1)
		return (map);
	squared_map = change_map_format(map);
	// free(map);
	return (squared_map);
}
