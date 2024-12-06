/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogullar <finarfin40@hotmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:44:31 by mogullar          #+#    #+#             */
/*   Updated: 2024/03/06 23:29:46 by mogullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "./mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	int				player_count;
	int				width;
	int				height;
	int				length;
	int				first_x;
	int				first_y;
	int				widgth;
	char			*buff;
	int				j;
	char			**map;
	char			**c_map;
	int				*new_map;
}					t_map;

typedef struct s_ray
{
	int				player_x;
	int				player_y;
	int				width;
	int				height;
	float			new_px;
	float			new_py;
	char			p_fov;
	float			px;
	float			py;
	float			pa;
	float			pdx;
	float			pdy;
	float			*ray;
	char			*drc;
	float			**ray_xy;
	float			ra;
	float			tan;
	int				check;
	int				i;
	float			disv;
	float			dish;
	float			rx;
	float			ry;
	float			xo;
	float			yo;
	int				mx;
	int				my;
	int				mp;
	float			vx;
	float			vy;
	int				ca;
	int				maps;
}					t_ray;

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

typedef struct s_image
{
	void			*image;
	int				**pixel_array;
	char			*data;
	int				width;
	int				height;
	int				bpp;
	int				sizeline;
	int				endian;
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_image;

typedef struct s_main
{
	t_rgb			*color;
	t_image			*image_w;
	t_image			*image_e;
	t_image			*image_s;
	t_image			*image_n;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	struct s_map	*map;
	struct s_ray	*ray;
	float			*pixel_n;
	int				*which_pixel;
	int				*f;
	int				*c;
	int				i;
	int				j;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			**full_cub;
	int				full_length;
	int				color_f;
	int				color_c;
	int				prev_block;
	int				next_block;
	int				line_count;
	char			*map_name;
	char			*map_path;
	char			**whole_map;
	char			direction;
	char			*floor;
	char			*ceiling;
}					t_main;

char				*get_next_line(int fd);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
void				get_map(t_main *main);
int					ft_strlen(const char *string);
char				*ft_strdup(char *s1);
char				*ft_strchr(const char *s, int c);
char				**ft_split(const char *s, char c);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
static int			ft_len(long int nbr);
char				*ft_itoa(int n);
static size_t		ft_word_count(const char *s, char c);
int					map_control(t_map *map);
void				get_info(t_main *main, int flag, char **new_map);
int					ft_atoi(char *str);
float				deg_to_rad(int a);
int					fix_ang(int a);
float				*ray_casting(t_main *main);
void				mlx_func(t_main *main);
void				put_pixel(t_main *main, int x, int y, int color);
void				assigment_fov(t_ray *ray);
void				assault_map(t_main *main);
void				xpm_to_int_array(t_image *image);
int					*length_of_collumns(t_main *data);
void				pixel_n_calc(t_main *data, int *length);
void				which_pixel_calc(t_main *data);
void				image_creater(t_main *data);
void				image_putter(t_main *data);
void				draw_background(t_main *data);
void				draw_wall(t_main *data, int **pixel_array);
int					handle_key_press(int keycode, t_main *main);
void				ft_free(t_main *main);
void				map_len(t_map *map);
void				check_file_name(t_main *main, char *name);
void				wrong_argument_exit(t_main *main, int error_code);
void				check_map(t_main *main);
int					is_line_empty(char *line);
void				allocation_exit(t_main *main);
void				player_position(t_main *main);
void				lower_wall(t_main *data, int *length, int p, int x);
void				upper_wall(t_main *data, int *length, int p, int x);
void				fov_func(t_main *main, int y, int x);
void				fov_func(t_main *main, int y, int x);
int					is_it_ws(int c);
void				wrong_map_exit(t_main *main, int code);
void				clear_map(t_main *main);
void				check_rgb(t_main *main);
char				**ft_split_special(const char *s, t_main *main);
int					ft_isdigit(int x);
void				set_ceiling_floor(t_main *main, char **splitted, int flag);
void				free_double_char(char **ptr);
char				*ft_strtrim(const char *s1, const char *set);
void				vertical_left_right(t_ray *ray);
void				vertical_loop(t_main *main);
char				**handle_fc(const char *s, t_main *main);
char				**handle_texture(const char *s, t_main *map_data);
void				if_flag_one(char **splitted, t_main *main, int flag);
int					get_line_count(t_main *main);
void				check_empty_lines(t_main *main, char **map);
int					close_window(void);
void				draw_wall(t_main *data, int **pixel_array);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
char				*ft_strdup(char *s1);
int					ft_strlen(const char *string);
char				**ft_deallocate(char **result, size_t i);
void				xpm_init(t_image *image);
int					check_path(char *str, char *drc);
#endif
