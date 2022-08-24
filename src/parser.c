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

static char *read_file_to_str(char *file)
{
	int	 fd;
	ssize_t ret;
	char	buffer[1024];
	char	*old_str;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	ret = read(fd, buffer, 1023);
	if (ret <= 0)
		return (NULL);
	old_str = ft_strdup("");
	if (old_str == NULL)
		return (NULL);
	while (ret != 0)
	{
		buffer[ret] = '\0';
		str = ft_strjoin(old_str, buffer);
		free(old_str);
		old_str = str;
		ret = read(fd, buffer, 1023);
	}
	close(fd);
	return (str);
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

static int	get_info(char *line, t_all *all)
{
	char	**tab;


}

static int	missing_info(t_all *all)
{
	if (all->floor == NULL)
		return (1);
	if (all->ceiling == NULL)
		return (1);
	if (all->texture_NO == NULL)
		return (1);
	if (all->texture_SO == NULL)
		return (1);
	if (all->texture_WE == NULL)
		return (1);
	if (all->texture_EA == NULL)
		return (1);
	return (0);
}

int	parser(int argc, char **argv, t_all *all)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (ft_printf("Invalid number of argument\n"), 1);
	all->map_path = argv[1];
	if (is_cub_file(all->map_path) == 0)
		return (ft_printf("Invalid file name\n"), 1);
	fd = open(all->map_path, O_RDONLY);
	while (missing_info(all) == 1)
	{
		line = get_next_line(fd);
		if (only_white_space(line) == 0)
		{
			get_info(line, all);
		}
		free(line);
	}

	return (0);
}
