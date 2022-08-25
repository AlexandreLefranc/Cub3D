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

static char	*read_file_to_str(char *file)
{
	int		fd;
	ssize_t	ret;
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

//
// static bool	is_valid_identifier(char **strtab)
// {
// 	if (strtab[1] == NULL)
// 		return (false);
// 	if (ft_strcmp(strtab[0], "NO") == 0)
// 		return (true);
// 	if (ft_strcmp(strtab[0], "SO") == 0)
// 		return (true);
// 	if (ft_strcmp(strtab[0], "WE") == 0)
// 		return (true);
// 	if (ft_strcmp(strtab[0], "EA") == 0)
// 		return (true);
// 	if (ft_strcmp(strtab[0], "F") == 0)
// 		return (true);
// 	if (ft_strcmp(strtab[0], "C") == 0)
// 		return (true);
// 	return (false);
// }
//
// static int	process_line(char *line, t_all *all)
// {
// 	char	**strtab;
//
// 	*ft_strrchr(line, '\n') = '\0';
// 	strtab = ft_split(line, ' ');
// 	if (ft_strtabsize(strtab) > 0)
// 	{
// 		if (is_valid_identifier(strtab) == true)
// 		{
// 			printf("strtab first element = %s\n", strtab[0]);
//
// 		}
// 		else
// 		{
// 			ft_strtabfree(strtab);
// 			return (printf("Error\nInvalid identifier:%s\n", strtab[0]), 1);
// 		}
// 	}
//
// 	ft_strtabfree(strtab);
// 	(void)all;
// 	return (0);
// }

int	extract_info_from_file(char **file, t_all *all)
{
	int	i;

	i = 0;
	while (file[i] != NULL)
	{
		printf("%s\n", file[i]);
		i++;
	}
	(void)all;
	return (0);
}

int	parser(int argc, char **argv, t_all *all)
{
	char	*file_str;
	char	**file;

	if (argc != 2)
		return (printf("Invalid number of argument\n"), 1);
	all->map_path = argv[1];
	if (is_cub_file(all->map_path) == 0)
		return (printf("Invalid file name\n"), 1);
	file_str = read_file_to_str(all->map_path);
	if (file_str == NULL || file_str[0] == '\0')
		return (free(file_str), printf("Error\nInvalid file.\n"), 1);
	file = ft_split(file_str, '\n');
	free(file_str);
	if (extract_info_from_file(file, all) != 0)
	{
		return (ft_strtabfree(file), 1);
	}
	// fd = open(all->map_path, O_RDONLY);
	// while ((line = get_next_line(fd)) != NULL)
	// {
	// 	// printf("%s", line);
	// 	if (process_line(line, all) != 0)
	// 		return (free(line), 1);
	// 	// if (is_metainfo_full(all) == 1)
	// 	// 	save_map();
	// 	free(line);
	// }
	// close(fd);

	ft_strtabfree(file);
	return (0);
}
