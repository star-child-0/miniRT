/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/08/03 17:09:14 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


// int	parse_res(t_scene *w, char **line)
// {
// 	next_val(line);
// 	w->size.x = my_atoi(line);
// 	next_val(line);
// 	if (w->size.x < 1 || w->size.x > INFINITY)
// 		ft_print_error("resolution x out of range!", w, NULL);
// 	w->size.y = my_atoi(line);
// 	if (w->size.y < 1 || w->size.y > INFINITY)
// 		ft_print_error("resolution y out of range!", w, NULL);
// 	next_val(line);
// 	if (**line != '\0')
// 		ft_print_error("bad formatted parameter in parse data", w, NULL);
// 	return (0);
// }

void	*parse_amb(t_scene *w, char **line, char **rt)
{
	t_ambient_lightning	*am;

	am = sux_malloc(sizeof(t_ambient_lightning), w, rt);

	next_val(line);
	am->ratio = tofloat(line);
	next_val(line);
	if (am->ratio  < 0 || am->ratio  > 1)
		ft_print_error("ambient light out of range!", &w, am, rt);
	if (am->ratio < 0.01)
		am->ratio = 0.01;
	am->rgb = color_parse(line, w, am, rt);
	am->rgb->red /= 255;
	am->rgb->green /= 255;
	am->rgb->blue /= 255;
	next_val(line);
	if (**line != '\0')
		ft_print_error("bad formatted parameter in parse data", &w, am, rt);
	return ((void *)am);
}

// t_vec2_d	ft_get_rot(t_vec3_d v)
// {
// 	double		tz;
// 	double		cosy;
// 	double		cosx;
// 	t_vec2_d	res;

// 	tz = sqrt(v.x * v.x + v.z * v.z);
// 	cosy = tz * v.z / (v.x * v.x + v.z * v.z);
// 	cosx = tz / (v.y * v.y + tz * tz);
// 	if (!(cosx <= 1 && cosx >= -1))
// 		cosx = 1;
// 	if (!(cosy <= 1 && cosy >= -1))
// 		cosy = 1;
// 	res = (t_vec2_d){acos(cosx), acos(cosy)};
// 	if (v.y > 0)
// 		res.x = -res.x;
// 	if (v.x < 0)
// 		res.y = -res.y;
// 	return (res);
// }

void *parse_cam(t_scene *w, char **line, char **rt)
{
	t_camera	*cam = NULL;

	cam = sux_malloc(sizeof(t_camera), w, rt);
	cam->origin = pos_parse(line, w, (t_camera *)cam, rt);
	next_val(line);
	cam->direction = pos_parse(line, w, NULL, rt);
	next_val(line);
	if (cam->direction->x > 1 || cam->direction->x < -1
		|| cam->direction->y > 1 || cam->direction->y < -1
		|| cam->direction->z > 1 || cam->direction->z < -1)
		ft_print_error("cam orientation out of range!", &w, cam, rt);
	next_val(line);
	cam->fov = tofloat(line);
	if (cam->fov < 0 || cam->fov > 180)
		ft_print_error("cam FOV out of range", &w, cam, rt);
	cam->w = v_unit(v_sub_vec((*cam->origin), (t_v3){0, 0, 0}));
	cam->u = v_unit(v_cross(v_unit((*cam->direction)), cam->w));
	cam->v = v_cross(cam->w, cam->u);
	cam->d = 1.0 / tanf(cam->fov * 0.5 * 3.1415 / 180.0);
	next_val(line);
	if (**line != '\0')
		ft_print_error("bad formatted parameter in parse data", &w, cam, rt);
	return ((void *)cam);
}

void 	*parse_light(t_scene *w, char **line, char **rt)
{
	t_light	*light;

	light = sux_malloc(sizeof(t_light), w, rt);
	light->origin = pos_parse(line, w, (t_light *)light, rt);
	next_val(line);
	light->brightness = tofloat(line);
	if (light->brightness < 0 || light->brightness > 1)
		ft_print_error("light intensity out of range!", &w, light, rt);
	if (light->brightness < 0.01)
		light->brightness = 0.01;
	next_val(line);
	light->rgb = color_parse(line, w, light, rt);
	light->rgb->red /= 255;
	light->rgb->green /= 255;
	light->rgb->blue /= 255;
	next_val(line);
	if (**line != '\0')
		ft_print_error("bad formatted parameter in parse data", &w, light, rt);
	return ((void *)light);
}
