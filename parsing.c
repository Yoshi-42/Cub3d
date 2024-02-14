#include "struct_cub3d.h"

int	ft_check_extension(char *map_name)
{
	int			i;
	int			j;
	static char	extension[] = {".cub"};

	i = 0;
	j = 0;
	if (!map_name || ft_strlen(map_name) < 4)
		return (-1);
	
	while (map_name[i] && i < (ft_strlen(map_name) - 4))
		i++;

	
	while (map_name[i] && extension[j])
	{
		if (map_name[i] != extension[j])
			return (-1);
		i++;
		j++;
	}
	return (0);
}

int	ft_nblines(char *file)
{
	int		i;
	int		fd;
	char	buff;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	while (read(fd, &buff, 1))
		if (buff == '\n')
			i++;
	close(fd);
	return (i);
}

int	ft_fill_infos(t_map *map, int id)
{
	(void)map;
	printf("info id : %d\n", id);
	return (0);
}

int	ft_open_map()
{
	int	fd;

	fd = -1;
	if (ft_check_extension("map.cub") == -1)
	{
		printf("ERROR : INVALID MAP EXTENSION\n");
		exit(1);
	}
	fd = open("map.cub", O_RDONLY);
	// if (fd == -1)
	// 	printf("ERROR: CANNOT OPEN FILE\n");
	return (fd);
}

int	ft_parse_map(t_map *map)
{
	int	i;
	// int	j;

	i = 0;
	// j = 0;
	while (map->map[i] && (map->map[i][0] != '1' && map->map[i][0] != ' '))
	{
		if (ft_strncmp(map->map[i], "NO", 2) != 0)
			ft_fill_infos(map, 1);
		else if (ft_strncmp(map->map[i], "SO", 2) != 0)
			ft_fill_infos(map, 2);
		else if (ft_strncmp(map->map[i], "WE", 2) != 0)
			ft_fill_infos(map, 3);
		else if (ft_strncmp(map->map[i], "EA", 2) != 0)
			ft_fill_infos(map, 4);
		else if (ft_strncmp(map->map[i], "F", 2) != 0)
			ft_fill_infos(map, 5);
		else if (ft_strncmp(map->map[i], "C", 2) != 0)
			ft_fill_infos(map, 6);
		i++;
	}
	if (map->map[i][0] == '1' || map->map[i][0] == ' ')
	{
		map->map = &map->map[i];
	}
	printf("Parse map i : %d\n", i);

	return (0);
}

int	ft_read_map(int fd, t_map *map)
{
	int		bytes_read;
	char	*buf;

	
	buf = NULL;
	if (fd == -1)
	{
		printf("ERROR: CANNOT OPEN FILE\n");
		exit(1);
	}
	buf = malloc(sizeof(char) * 5000);
	if (!buf)
		return (0);
	bytes_read = read(fd, buf, 5000);
	if (ft_strlen(buf) <= 0)
	{
		free(buf);
		return (1);
	}
	if (bytes_read != -1)
	{
		map->map = ft_split(buf, '\n');
	}
	free(buf);
	ft_parse_map(map);
	return (0);
}

void	ft_debug_map(char **map)
{
	int		i;

	i = 0;
	// if (data->map_check[data->exit.posy][data->exit.posx] !=
	// 	data->map_check[data->player.posy][data->player.posx])
	// 	data->map_check[data->exit.posy][data->exit.posx] = EXIT_ID;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	ft_print_infos(t_map map)
{
	// ft_read_map(&map);
	ft_debug_map(map.map);
}

void	ft_init(t_map *map)
{
	// t_map	map;
	int		i;

	i = 0;
	map->p_imgs = malloc(sizeof(char*) * 5);
	while (i < 4)
	{
		map->p_imgs[i] = ft_strdup("0");
		i++;
	}
	map->p_imgs[i] = NULL;

	map->floor_color = -1;
	map->ceiling_color = -1;

	// char	**map;	map->
}

int	ft_parsing(char *file, t_map *map)
{
	int	nblines;

	ft_init(map);
	nblines = ft_nblines(file);
	
}

// typedef struct s_map
// {
// 	t_data	*imgN;
// 	t_data	*imgS;
// 	t_data	*imgO;
// 	t_data	*imgE;
// 	t_color	floor_color;
// 	t_color	ceiling_color;
// 	char	**map;
// }	t_map;


// DONE
// MAP EXTENSION



//OPEN FICHIER
//INITIALISE T_MAP NULL
//COMPTER LES LIGNES AVEC SHERPA
//UTILISER GNL AVEC LE FD
//TANT QUE != ' ' OU '1' ON INITIALISE LES VALEURS
//CHAQUE LIGNE VERIFIE SI C'EST LES BONS IDENTIFIANTS OU SI C'EST NULL
//SINON ON PASSE A LA PROCHAINE LIGNE