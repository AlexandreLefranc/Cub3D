#include "cub3d.h"

int	biggest_map_line(char **map);
int	is_map_square(char **map);
char	**map_modeler(char **map);

int main(void)
{
	char	*map[] =
	{	"11111111111111111111111111",
		" 1111111111111111111111111",
		"11111000001110000000000001",
		"  111000000000000000000001",
		"11011000001110000000000001",
		"00011000001110111111111111",
		"10111111111011100000010001",
		"10111111111011101010010001",
		"00000110101011100000010001",
		"00000000000000110000010001",
		"00000000000001101010010001",
		"00011101010111110111100111",
		"     10111 1110101 101111010001",
		"11111 1111111 111111111111", NULL};

	printf("Is map square ? 1 = yes 0 = no ----> %d\n", is_map_square(map));
	printf("Map longest line = %d characters\n", biggest_map_line(map));

	char **newmap;

	newmap = map_modeler(map);
	int i = 0;

	while (newmap[i])
	{
		printf("%s\n", newmap[i]);
		i++;
	}
}
