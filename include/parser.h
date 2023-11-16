/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvannin <anvannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/11/16 18:17:11 by anvannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// Libraries ------------------------------------------------------------------>

# include "minirt.h"
# include <stdbool.h>
# include <fcntl.h>

// Defines -------------------------------------------------------------------->

# define AMBIENT_LIGHTNING 1
# define CAMERA 2
# define LIGHT 3
# define SPHERE 4
# define PLANE 5
# define CYLINDER 6

// Errors -------------------------------------------------------------------->

# define NOARGS "check input, write:./minirt scenes/mandatory.rt"
# define NOSIZE "the last two args are size of win, so they can be only digits!"
# define NOINIT "something's wrong during initialization, try again"
# define NOFILE "no such file!"
# define NO_RT "ehy dude, only .rt file!"
# define MALLOC "oh no, error in malloc() on memory allocation"
# define ACL_ERR "check file rt! need 1 A, 1 C, and at least 1 L!"
# define CHECK_RT ",check your params!"

// Structures ----------------------------------------------------------------->

typedef struct s_scene	t_scene;

typedef struct s_rgb
{
	double	red;
	double	green;
	double	blue;
}	t_rgb;

typedef struct s_ambient_lightning
{
	double			ratio;
	t_rgb			*rgb;
}	t_ambient_lightning;

typedef struct s_camera
{
	t_v3			*origin;
	t_v3			*direction;
	double			fov;

	t_v3			u;
	t_v3			v;
	t_v3			w;
	double			d;
}	t_camera;

typedef struct s_light
{
	t_v3			*origin;
	double			brightness;
	t_rgb			*rgb;
}	t_light;

typedef struct s_sphere
{
	t_v3			*origin;
	double			diameter;
	t_rgb			*rgb;
}	t_sphere;

typedef struct s_plane
{
	t_v3			*origin;
	t_v3			*direction;
	t_rgb			*rgb;
}	t_plane;

typedef struct s_cylinder
{
	t_v3			*origin;
	t_v3			*direction;
	double			diameter;
	double			height;
	t_rgb			*rgb;
}	t_cylinder;

// Linked Lists --------------------------------------------------------------->

typedef struct s_scene
{
	int				id;
	unsigned char	type;
	bool			unique;
	bool			selected;
	void			*data;
	struct s_scene	*prev;
	struct s_scene	*next;
}	t_scene;

t_scene				*t_scene_new(int id, char type, bool unique, void *data);
void				t_scene_add_back(t_scene **lst, t_scene *new);
void				t_scene_set_to_head(t_scene **scene);
void				t_scene_free(t_scene **scene);
bool				t_scene_check_unique(t_scene *scene, char type, bool uniq);
t_camera			*t_scene_get_camera(t_scene *scene);
t_light				*t_scene_get_light(t_scene *scene);
t_ambient_lightning	*t_scene_get_ambient_light(t_scene *scene);

// Functions ------------------------------------------------------------------>

/*file check_rt.c*/
int					contchar(t_scene *w, char **rt);
char				*ft_strjoin2(char *s1, char *s2);

/*file read_rt.c*/
int					ft_check_file(char *scene);
bool				get_unique(char *line, t_scene *scene, char type);
void				ft_read_rt(t_scene **w, char *scene);
int					ft_open_rt(t_scene **w, char **av);

/*file parsing.c*/
double				tofloat(char **str);
t_rgb				*color_parse(char **line, t_scene *w, char **rt);
t_v3				*pos_parse(char **str, t_scene *w, void *s, char **rt);
void				ft_line_parser(t_scene **w, char **rt);

/*file parse_utils2.c*/
int					ft_char_digit(char *str);
void				*sux_malloc(unsigned int size, t_scene *w, char **rt);
void				next_val(char **str);
int					my_atoi(char **str);
int					ft_comma(char **str);

/*file parse_utils.c*/

void				free_obj(t_list *scene);
int					ft_print_error(char *err, t_scene **w,
						void *del, char **rt);
int					ft_checkset(char c, char *s);
t_v3				*v3d_normalize(t_v3 *in);
double				get_value(char **line, t_scene *scene);

/*file parse_data.c*/
void				*camera_update(t_scene *w);
void				*parse_res(t_scene *w, char **line, char **rt);
void				*parse_amb(t_scene *w, char **line, char **rt);
void				*parse_cam(t_scene *w, char **line, char **rt);
void				*parse_light(t_scene *w, char **line, char **rt);

/*file parse_obj.c*/
void				*parse_sphere(t_scene *w, char **line, char **rt);
void				*parse_plane(t_scene *w, char **line, char **rt);
void				*parse_cylinder(t_scene *w, char **line, char **rt);

#endif
