/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cub3d.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgonon <bgonon@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:48:54 by bgonon            #+#    #+#             */
/*   Updated: 2024/02/24 17:07:21 by bgonon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CUB3D_H
# define STRUCT_CUB3D_H

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

typedef struct s_ipoint
{
	int	i;
	int	j;
}	t_ipoint;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	t_point	p_screen;
	t_point	move;
	double	rotate;
}	t_player;

typedef struct s_ray
{
	t_point	ray_dir_xy;
	t_point	map_xy;
	t_point	side_dist_xy;
	t_point	delta_dist_xy;
	t_point	step;
	int		side;
}	t_ray;

////MiniLibx forever !!!!
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_data;

typedef struct s_texture
{
	t_data	*tex;
	t_point	tex_xy;
	double	tex_pos;
	double	step;
}	t_tex;

typedef struct s_map
{
	t_data	img_n;
	t_data	img_s;
	t_data	img_o;
	t_data	img_e;
	char	**p_img_s;
	int		floor_color;
	int		ceiling_color;
	char	**map;
}	t_map;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_data		*img;
	t_map		m_map;
	t_player	p;
}	t_vars;
/////END of Minilibx forever !!!

//render
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_wall_col(t_vars *vars, int sx, t_ray *ray);
int			update(t_vars *vars);

//Raycastdouble	
void		raycasting(t_vars *game, t_ray *ray, int sx, char target);
void		display_wall(t_vars *vars);

//color
int			create_trgb(int t, int r, int g, int b);
int			ft_split_colors(t_map *map);
int			char_to_rgb(int t, char *r, char *g, char *b);

////Utils
//void 	define_point (t_point *p, double _x , double _y);

//ray
t_point		init_delta(t_point ray_dir_xy);
void		init_side(t_vars *vars, t_ray *ray);
void		init_ray(t_vars *vars, t_ray *ray, int sx);

//input key
int			input_manag(t_vars *vars);
void		player_movement(t_vars *vars);
int			key_press(int keycode, t_vars *vars);
int			key_release(int keycode, t_vars *vars);
void		player_move(int keycode, t_vars *vars, double movement);
void		player_rotation(int keycode, t_vars *vars, double movement);

//debug
t_player	init_player(char orientation, t_point position);
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
int			ft_maxlen(char **map);
int			ft_err(char *errmsg);
int			ft_tablength(char **tchoup);
void		m_line(char **line, int fd, int *i);
void		m_line_map(char **line, int fd, int *i, char **map);

//close
int			close_everything(t_vars *vars);
int			free_array(char **array);

//point.c
void		revers_pt(t_point *pt);
void		neg_pt(t_point *pt);
void		define_point(t_point *p, double _x, double _y);
t_point		create_point(double _x, double _y);

#endif
