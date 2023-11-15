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

void	*parse_amb(t_scene *w, char **line, char **rt)
{
	t_ambient_lightning	*am;

	am = sux_malloc(sizeof(t_ambient_lightning), w, rt);
	next_val(line);
	am->ratio = tofloat(line);
	next_val(line);
	if (am->ratio < 0 || am->ratio > 1)
		ft_print_error("AMBIENT: ambient light out of range!", &w, am, rt);
	if (am->ratio < 0.01)
		am->ratio = 0.01;
	am->rgb = color_parse(line, w, rt);
	if (am->rgb == NULL)
		ft_print_error("Bad formatted rgb in ambient light",
			&w, (t_ambient_lightning *)am, rt);
	am->rgb->red /= 255;
	am->rgb->green /= 255;
	am->rgb->blue /= 255;
	next_val(line);
	if (**line != '\0')
	{
		free(am->rgb);
		ft_print_error("AMBIENT: bad formatted data", &w, am, rt);
	}
	return ((void *)am);
}

static t_camera	*parse_cam_help(t_camera *cam, char **line,
	t_scene *w, char **rt)
{
	cam->fov = tofloat(line);
	if (cam->fov < 0 || cam->fov > 180)
	{
		free(cam->origin);
		free(cam->direction);
		ft_print_error("CAMERA: FOV out of range", &w, cam, rt);
	}
	cam->w = v_unit(v_sub_vec((*cam->origin), (t_v3){0, 0, 0}));
	cam->u = v_unit(v_cross(v_unit((*cam->direction)), cam->w));
	cam->v = v_cross(cam->w, cam->u);
	cam->d = 1.0 / tanf(cam->fov * 0.5 * 3.1415 / 180.0);
	next_val(line);
	if (**line != '\0')
	{
		free(cam->origin);
		free(cam->direction);
		ft_print_error("CAMERA: bad formatted parameter \
			in parse data", &w, cam, rt);
	}
	return (cam);
}

void	*parse_cam(t_scene *w, char **line, char **rt)
{
	t_camera	*cam;

	cam = sux_malloc(sizeof(t_camera), w, rt);
	cam->origin = pos_parse(line, w, (t_camera *)cam, rt);
	if (cam->origin == NULL)
		ft_print_error("Bad formatted data in cam", &w, cam, rt);
	next_val(line);
	cam->direction = pos_parse(line, w, NULL, rt);
	if (cam->direction == NULL)
	{
		free(cam->origin);
		ft_print_error("Bad formatted data in cam", &w, cam, rt);
	}
	next_val(line);
	if (cam->direction->x > 1 || cam->direction->x < -1
		|| cam->direction->y > 1 || cam->direction->y < -1
		|| cam->direction->z > 1 || cam->direction->z < -1)
	{
		free(cam->origin);
		free(cam->direction);
		ft_print_error("CAMERA: orientation out of range!", &w, cam, rt);
	}
	next_val(line);
	cam = parse_cam_help(cam, line, w, rt);
	return ((void *)cam);
}

static t_light	*parse_light_help(t_light *light, char **line,
	t_scene *w, char **rt)
{
	light->rgb = color_parse(line, w, rt);
	if (light->rgb == NULL)
	{
		free(light->origin);
		ft_print_error("Bad formatted rgb in light", &w, (t_light *)light, rt);
	}
	light->rgb->red /= 255;
	light->rgb->green /= 255;
	light->rgb->blue /= 255;
	next_val(line);
	if (**line != '\0')
	{
		free(light->origin);
		free(light->rgb);
		ft_print_error("LIGHT: bad formatted parameter data", &w, light, rt);
	}
	return (light);
}

void	*parse_light(t_scene *w, char **line, char **rt)
{
	t_light	*light;

	light = sux_malloc(sizeof(t_light), w, rt);
	light->origin = pos_parse(line, w, (t_light *)light, rt);
	if (light->origin == NULL)
		ft_print_error("Bad formatted data in light", &w, light, rt);
	next_val(line);
	light->brightness = tofloat(line);
	if (light->brightness < 0 || light->brightness > 1)
	{
		free(light->origin);
		ft_print_error("LIGHT: light intensity out of range!", &w, light, rt);
	}
	if (light->brightness < 0.01)
		light->brightness = 0.01;
	next_val(line);
	light = parse_light_help(light, line, w, rt);
	return ((void *)light);
}
