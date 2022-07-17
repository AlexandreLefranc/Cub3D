#include "cub3d.h"

static int	is_cub_file(char *file)
{
	int	len;

	len = /*ft_*/strlen(file);
	if (len < 4)
		return (0);
	if (/*ft_*/strncmp(file + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

// static int	get_info(int fd, t_all *all)
// {
// 	char	*line;
// 	char	**splitted;
//
// 	while (missing_info(all) == 1)
// 	{
// 		line = get_next_line(fd);
// 		splitted = ft_split(line);
// 		free(line);
// 		is_valid_identifier(splittedp[0]);
//
// 	}
// }

int	parser(int argc, char **argv, t_all *all)
{
	// int	fd;

	if (argc != 2)
		return (/*ft_*/printf("Invalid number of argument\n"), 1);
	all->map_path = argv[1];
	if (is_cub_file(all->map_path) == 0)
		return (/*ft_*/printf("Invalid file name\n"), 1);
	// fd = open(all->map_path);
	// get_info(fd, all);
	return (0);
}
