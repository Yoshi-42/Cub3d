

void	ft_check_walls(t_data *data, int x, int y, char **map)
{
	if (map[y][x] != '1' && map[y][x] != 'v')
	{
		printf("\033[H\033[J");
		ft_debug_map(data);
		usleep(50000);

		data->map_check[y][x] = 'v';
		if (!data->map_check[y + 1][x] || !data->map_check[y - 1][x] || !data->map_check[y][x + 1] || !data->map_check[y][x - 1])
			printf("TROU\n");
		ft_check_walls(data, x, y + 1, data->map_check);
		ft_check_walls(data, x + 1, y, data->map_check);
		ft_check_walls(data, x, y - 1, data->map_check);
		ft_check_walls(data, x - 1, y, data->map_check);
	}
}