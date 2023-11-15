/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/08/03 17:09:14 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

double	get_value(char **line, t_scene *scene)
{
	char	*tmp;
	double	value;

	tmp = ft_calloc(1, sizeof(char));
	if (!tmp)
		errors_handler("parser: calloc()", NULL, &scene);
	while (line && *line && (**line == 9 || **line == 32))
		(*line)++;
	while (line && *line && **line && **line != 44 && **line != 32 && \
		**line != 9)
	{
		tmp = ft_char_append(tmp, **line, true);
		(*line)++;
	}
	if (line && *line && **line)
		(*line)++;
	value = ft_atof(tmp);
	ft_free((void **)&tmp);
	return (value);
}

t_rgb	*color_parse(char **line, t_scene *w, void *s, char **rt)
{
	t_rgb	*rgb;

	rgb = sux_malloc(sizeof(t_rgb), w, rt);
	next_val(line);
	rgb->red = get_value(line, w);
	rgb->green = get_value(line, w);
	rgb->blue = get_value(line, w);
	if (rgb->red < 0 || rgb->red > 255 || rgb->green < 0 || rgb->green > 255 \
		|| rgb->blue < 0 || rgb->blue > 255)
		{
			if(s)
				free(s);
			free_mat(rt);
			free(rgb);
			ft_print_error("color RGB out of range", w, s, rt);
		}
	return (rgb);
}

float	tofloat(char **str)
{
	int		w;
	double	d;
	int		neg;

	w = 0;
	neg = 1;
	if (**str == '-' && *((*str)++))
		neg = -1;
	while (ft_isdigit(**str))
		w = w * 10 + (*((*str)++) - '0');
	if (**str == '.')
		(*str)++;
	d = 0.0;
	while (ft_isdigit(**str))
		d = d * 10 + (*((*str)++) - '0');
	while (d >= 1)
		d /= 10;
	d += w;
	next_val(str);
	return (d * neg);
}

t_v3	*pos_parse(char **str, t_scene *w, void *s, char **rt)
{
	t_v3	*pos;

	pos = (t_v3 *)malloc(sizeof(t_v3));
	pos->x = 0;
	pos->y = 0;
	pos->z = 0;
	next_val(str);
	pos->x = tofloat(str);
	ft_comma(str, w, s, rt);
	pos->y = tofloat(str);
	ft_comma(str, w, s, rt);
	pos->z = tofloat(str);
	return (pos);
}

void	ft_line_parser(t_scene **w, char **rt)
{
	int i;
	char *line;

	i = 0;
	while (rt[i])
	{
		line = rt[i];
		if (*line == 'R' && *line++)
			parse_res(*w, &line, rt);
		if (*line == 'A' && *line++)
			t_scene_add_back(w, t_scene_new(i, AMBIENT_LIGHTNING, get_unique(line, *w, \
			AMBIENT_LIGHTNING), parse_amb(*w, &line, rt)));
		if (*line == 'C' && *line++)
			t_scene_add_back(w, t_scene_new(i, CAMERA, get_unique(line, *w, \
			CAMERA), (parse_cam(*w, &line, rt))));
		if (*line == 'L' && *line++)
			t_scene_add_back(w, t_scene_new(i, LIGHT, get_unique(line, *w, \
			LIGHT), (parse_light(w, &line, rt))));
		if (ft_strncmp(line, "sp", 2) == 0 && *line++)
			t_scene_add_back(w, t_scene_new(i, SPHERE, get_unique(line, *w, \
			SPHERE), (parse_sphere(w, &line, rt))));
		if (ft_strncmp(line, "pl", 2) == 0 && *line++)
			t_scene_add_back(w, t_scene_new(i, PLANE, get_unique(line, *w, \
			PLANE),(parse_plane(w, &line, rt))));
		if (ft_strncmp(line, "cy", 2) == 0 && *line++)
			t_scene_add_back(w, t_scene_new(i, CYLINDER, get_unique(line, *w, \
			CYLINDER), (parse_cylinder(w, &line, rt))));
		ft_print_error("unexpected identifier in scene file", w, NULL, rt);
		i++;
	}
	free_mat(rt);
}
