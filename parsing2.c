#include "struct_cub3d.h"



int	ft_open_map2(char *file)
{
	int	fd;

	fd = -1;
	if (ft_check_extension(file) == -1)
	{
		return (fd);
	}
	fd = open(file, O_RDONLY);
	return (fd);
}


int	ft_check_extension2(char *map_name)
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

int	ft_nblines2(char *file)
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
	i++;
	close(fd);
	return (i);
}

int	ft_init2(t_map *map)
{
	// t_map	map;
	int		i;

	i = 0;
	map->p_imgs = malloc(sizeof(char*) * 7);
	if (!map->p_imgs) /////////// ca regle pas
		return (-1);
	while (i < 6) //////////
	{
		map->p_imgs[i] = NULL;
		i++;
	}
	map->p_imgs[i] = NULL;

	map->floor_color = -1;
	map->ceiling_color = -1;

	return (0);
}

int	ft_check_startmap2(char *line)  // tmoch
{
	int	i;

	//est ce qu'on au debut de la map
	//si c'est null on arrete
	//si il n'y a que des ' ' 1 0 arrette
	// si il n'y a pas que des " " 1 0 on continue
	// si il n'y a que un \n on continue
	//si il n'y a que des espace on continue
	i = 0;
	if (line == NULL)
		return (0); // on arrete
	while (line[i] != '\n' && line [i] != '\0')
	{
		if ((line[i] != ' ') && (line[i] != '1') && (line[i] != '0'))
			return (-1);
		i++;
	}
	if(i == 0)
		return -1;
	return (0);//on arrete
}


int	ft_fill_infos2(char **placeholder, char *line)
{
	char **temp;

	temp = ft_split(line, ' ');
	if (!temp || ft_tablength(temp) == -1 || ft_tablength(temp) != 2)
		return (printf("error: Invalid path format\n"));
	*placeholder = ft_strdup(temp[1]);
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

int	verif_parameters(char *line, t_map *map)
{
	int err;
	
	err = 0;
	if (ft_strncmp(line, "NO", 2) == 0)
		err -= ft_fill_infos2((&map->p_imgs[0]), line);
	else if (ft_strncmp(line, "SO", 2) == 0)
		err -= ft_fill_infos2((&map->p_imgs[1]), line);
	else if (ft_strncmp(line, "WE", 2) == 0)
		err -= ft_fill_infos2((&map->p_imgs[2]), line);
	else if (ft_strncmp(line, "EA", 2) == 0)
		err -= ft_fill_infos2((&map->p_imgs[3]), line);
	else if (ft_strncmp(line, "F", 1) == 0)
		err -= ft_fill_infos2((&map->p_imgs[4]), line);
	else if (ft_strncmp(line, "C", 1) == 0)
		err -= ft_fill_infos2((&map->p_imgs[5]), line);
	if (err < 0)
		return (printf("error: Invalid config file\n"));
	return (0);
}

void	m_line(char **line, int fd, int *i)
{
	if(*line != NULL)
		free(*line);
	*line = NULL;
	*line = get_next_line(fd);
	sleep(1);
	*i = *i + 1;
}

void	m_line_map(char **line, int fd,int *i, char **map)
{
	map[*i] = ft_strdup(*line);
	m_line(line, fd, i);
}

int first_parse(int fd, t_map *map, int nbline)
{
	char    *line;
	int		i;

	i = 0;
	printf("Rubis\n");
	line  = get_next_line(fd);
	printf("%s\n", line);
	while (ft_check_startmap2(line) == -1)
	{
		if (verif_parameters(line, map) < 0)
			return (printf("errueru\n"));
		/*if(line != NULL)
	 		free(line);
		line = NULL;
		line = get_next_line(fd);
		i++;*/
		m_line(&line, fd, &i);
		while (line[0] == '\n')
			m_line(&line, fd, &i);
		/*{
			free(line);
			line = get_next_line(fd);

			i++;
		}*/
			//printf("LINE : %s\n", line);
		printf("LIGNE : %s\n", line);
	}
	map->map = malloc(sizeof(char*) * (nbline - i + 1));
	printf("Aigue MArine\n");
	i = 0;
	while (line != NULL)
	{
		printf("Jaspe : %s\n", line);
		m_line_map(&line, fd, &i, map->map);
	}
	printf("Obscidienne\n");
	return (0);
}

/*int	second_parse(int fd, int index, int nbline, t_map *map)
{
	char	*line;
	//on sait ou commence la map donc on met tout dedans
	map->map = malloc(sizeof(char*) * (nbline - index + 1));

}*/


int ft_parsing2(char *file, t_map *map)
{
	int nbline;
	int fd;
	int index;

	(void)index;
 	(void)fd;
	(void)map;
	if(ft_check_extension2(file) == -1) // on verifie si l'extension .cup
		return(printf("erreur d'extension .cub\n"));
	nbline = ft_nblines2(file); // compte le nombre de ligne
	if (nbline <= 0)// si nombre ligne faux erreur nbline, files, map
		return (printf("erreur de fichier\n"));
	if(ft_init2(map) == -1) //initialiser toute les valeur de t_map a null
		return (printf("probleme init\n"));
	fd = ft_open_map2(file);
	if (fd < 0)// a debattre
	 	return (printf("erreur"));
	printf("Saphir\n");
	first_parse(fd, map, nbline);	// on verifie le haut de la map
	

	//on insert le bas de la map
	//on verifie si la map est valide
		//verifie si la map est fermer
		//on verifie si la map ne contient que les caractere rechercher
	//on retourne 0;
	return (0);
}