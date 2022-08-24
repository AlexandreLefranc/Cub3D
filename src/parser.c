#include "cub3d.h"

static int	is_cub_file(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

// static int	missing_info(t_all *all)
// {
// 	if (all->floor == NULL)
// 		return (1);
// 	if (all->ceiling == NULL)
// 		return (1);
// 	if (all->texture_NO == NULL)
// 		return (1);
// 	if (all->texture_SO == NULL)
// 		return (1);
// 	if (all->texture_WE == NULL)
// 		return (1);
// 	if (all->texture_EA == NULL)
// 		return (1);
// 	return (0);
// }



int	process_line(char *line, t_all *all)
{
	char	**strtab;

	strtab = ft_split(line, ' ');
	if (ft_strtabsize(strtab) > 0)
		printf("strtab first element = %s\n", strtab[0]);
	ft_strtabfree(strtab);
	(void)all;
	return (0);
}

int	parser(int argc, char **argv, t_all *all)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (printf("Invalid number of argument\n"), 1);
	all->map_path = argv[1];
	if (is_cub_file(all->map_path) == 0)
		return (printf("Invalid file name\n"), 1);
	fd = open(all->map_path, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		process_line(line, all);
		// if (is_metainfo_full(all) == 1)
		// 	break;
		free(line);
	}
	close(fd);

	return (0);
}
