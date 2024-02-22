
#ifndef STRUCT_CUB3D
# define STRUCT_CUB3D

# include <stdio.h>
# include <math.h>
# include "minilibx/mlx.h"
# include "minilibx/mlx_int.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define WIDTH 1920
# define HEIGHT 1080

# define KEY_Z 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_RIGHT 65363 
# define KEY_LEFT 65361

/*extern char *_map[]; = {
"111111",
"100101",
"101001",
"1100N1",
"111111",
NULL
};*/

typedef struct s_point
{
	double x;
	double y;
}	t_point;

typedef	struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}	t_color;


typedef struct s_player
{
	t_point pos;
	t_point dir;
	t_point p_screen;
	t_point	move;
	double	rotate;
}	t_player;

typedef	struct s_ray
{
	t_point rayDirXY; //direction initial du rayon (direction de personnage + champ de vision)
	t_point	mapXY; // point sur la map ou se situe le point
	t_point	sideDistXY; //le cote vers lequel il va toucher la case visee
	t_point	deltaDistXY; // le delta ???
	t_point step; // la direction de la prochaine case
	int		side; //la c'est pour savoir si ca va toucher le NS ou le EW
}	t_ray;


////MiniLibx forever !!!!
typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}				t_data;


typedef struct s_map
{
	t_data	imgN;
	t_data	imgS;
	t_data	imgO;
	t_data	imgE;
	char	**p_imgs;
	int		floor_color;
	int		ceiling_color;
	char	**map;
}	t_map;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_data	*img;
	char	**map;
	t_map	m_map;
	t_player	p;
}	t_vars;
/////END of Minilibx forever !!!

//render
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_wall_col(t_vars *vars, int sx, t_ray *ray);
int		update(t_vars *vars);

//Raycastdouble	
void	raycasting(t_vars *game, t_ray *ray, int sx, char target);
void	display_wall(t_vars *vars);

//color
int		create_trgb(int t, int r, int g, int b);
int		ft_split_colors(t_map *map);
int	char_to_rgb(int t, char *r, char *g, char *b);

////Utils
void 	define_point (t_point *p, double _x , double _y);

//ray
t_point	init_delta(t_point rayDirXY);
void	init_side(t_vars *vars, t_ray *ray);
void	init_ray(t_vars *vars, t_ray *ray, int sx);

//input
int		input_manag(t_vars *vars);
void	player_movement(t_vars *vars);

//debug


t_player	initPlayer(char orientation, t_point position);
void		print_player(t_player p);
t_point		find_player(char **map);
char		find_orientation(t_point position, char **map);
void		set_img(t_vars *vars);

//texture
int			init_tex(t_vars *vars, char **tex_file);

//parsing parsmap
int			ft_parsing(char *file, t_map *map);
int			first_parse(int fd, t_map *map, int nbline);
//Checkmap
int			is_map_vailable(t_map *map);

//utils.c
int			ft_err(char *errmsg);
int			ft_tablength(char **tchoup);

//close
int			close_everything(t_vars *vars);

#endif
