#include "struct_cub3d.h"

int	ft_err(char *errmsg)
{
	int	i;

	i = 0;
	while (errmsg[i])
	{
		write(2, &errmsg[i], 1);
		i++;
	}
	return (-1);
}

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
int	ft_tablength(char **tchoup)
{
	int	i;

	i = 0;
	if (!tchoup)
		return (-1);
	while (tchoup[i])
		i++;
	return (i);
}

int	ft_fill_infos(char **placeholder, char *line)
{
	// (void)placeholder;
	char **temp;

	// printf("line : %s", line);
	temp = ft_split(line, ' ');
	if (!temp || ft_tablength(temp) == -1 || ft_tablength(temp) != 2)
		return (ft_err("error: Invalid path format\n"));
	*placeholder = ft_strdup(temp[1]);
	// printf("placeholder : %s", *placeholder);
	int i;
	i= 0;
	while(temp[i] != NULL)
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	return (0);
}

int	ft_open_map()
{
	int	fd;

	fd = -1;
	if (ft_check_extension("map.cub") == -1)
	{
		return (fd);
	}
	fd = open("map.cub", O_RDONLY);
	// if (fd == -1)
	// 	printf("ERROR: CANNOT OPEN FILE\n");
	return (fd);
}

int	ft_check_startmap(char *line, int j)
{
	int	i;
	int	len;

	i = 0;
	if(j == 1)
		return(1);
	if (line == NULL)
		return (2);
	len = ft_strlen(line);
	while (i < (len - 1))
	{
		if ((line[i] != ' ') && (line[i] != '1') && (line[i] != '0'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_parse_map(int fd, int filesize, t_map *map)
{
	char	*line;
	int		err;
	// filesize;
	// (map;
	int	i;
	int	j;

	err = 0;
	i = 1;
	j = 0;
		while (ft_check_startmap(line, i) != -1)
		{
			if(line != NULL)
		 		free(line);
			line = NULL;
			line = get_next_line(fd);
			i++;
			while (line[0] == '\n')
			{
				free(line);
				line = get_next_line(fd);
				i++;
				printf("NEW LINE\n");
			}
			if (ft_strncmp(line, "NO", 2) == 0)
				err -= ft_fill_infos((&map->p_imgs[0]), line);
			else if (ft_strncmp(line, "SO", 2) == 0)
				err -= ft_fill_infos((&map->p_imgs[1]), line);
			else if (ft_strncmp(line, "WE", 2) == 0)
				err -= ft_fill_infos((&map->p_imgs[2]), line);
			else if (ft_strncmp(line, "EA", 2) == 0)
				err -= ft_fill_infos((&map->p_imgs[3]), line);
			else if (ft_strncmp(line, "F", 1) == 0)
				err -= ft_fill_infos((&map->p_imgs[4]), line);
			else if (ft_strncmp(line, "C", 1) == 0)
				err -= ft_fill_infos((&map->p_imgs[5]), line);
			if (err < 0)
				return (ft_err("error: Invalid config file\n"));
		}
	if (ft_check_startmap(line, i) == 2)
	{
		free(line);
		return(ft_err("error: Invalid config file\n"));
	}
	else
	{
		map->map = malloc(sizeof(char*) * (filesize - i) + 1);
		while (line != NULL)
		{

			line = get_next_line(fd);
			j++;
		}
		map->map[j] = NULL;
	}
	free(line);
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
	// ft_parse_map(map);
	return (0);
}

void	ft_debug_map(char **map)
{
	int		i;

	i = 0;
	// if (data->map_check[data->exit.posy][data->exit.posx] !=
	// 	data->map_check[data->player.posy][data->player.posx])
	// 	data->map_check[data->exit.posy][data->exit.posx] = EXIT_ID;
	printf("\nMAMAAAAAP :\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	ft_print_infos(t_map map)
{
	// ft_read_map(&map);
	printf("\nINFOS :\n\n");
	int	i;

	i = 0;
	while (map.p_imgs[i])
	{
	
		printf("%s\n", map.p_imgs[i]);
		i++;
		// sleep(1);

	}
	ft_debug_map(map.map);
}

int	ft_init(t_map *map)
{
	// t_map	map;
	int		i;

	i = 0;
	map->p_imgs = malloc(sizeof(char*) * 7);
	if (!map->p_imgs) /////////// ca regle pas
		return (-1);
	while (i < 4)
	{
		map->p_imgs[i] = NULL;
		i++;
	}
	map->p_imgs[i] = NULL;

	map->floor_color = -1;
	map->ceiling_color = -1;

	return (0);
	// char	**map;	map->
}

int	ft_parsing(char *file, t_map *map)
{
	// (void)file;
	int	fd;
	fd = 0;
	int	nblines;
	int i = 0;///////////////////

	if (ft_init(map) == -1)
		return (-1);
	nblines = ft_nblines(file);

	fd = ft_open_map();
	printf("%d\n", i++);////////////////
	if (fd == -1)
		return (ft_err("error: cannot open map\n"));
	ft_parse_map(fd, nblines, map);
	i = 0;
	while (i < 7)
	{
		if (map->p_imgs[i] != NULL)
			free(map->p_imgs[i]);
		i++;
	}
	free(map->p_imgs);
	return (0);
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



// SPLIT LES COULURS
// CHECKER LA MAP :
//		1 PLAYER
//		MURS TOUT AUTOUR