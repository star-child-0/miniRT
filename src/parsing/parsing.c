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

t_rgb	*color_parse(char **line, t_scene *w, void *s, char **rt)
{
	t_rgb	*rgb;

	rgb = sux_malloc(sizeof(t_rgb), w, rt);
	next_val(line);
	rgb->red = tofloat(line);
	ft_comma(line, w, s, rt);
	rgb->green = tofloat(line);
	ft_comma(line, w, s, rt);
	rgb->blue = tofloat(line);
	if (rgb->red < 0 || rgb->red > 255 || rgb->green < 0 || rgb->green > 255 \
		|| rgb->blue < 0 || rgb->blue > 255)
		{
			if(s)
				free(s);
			free_mat(rt);
			free(rgb);
			ft_print_error("color RGB out of range", &w, s, rt);
		}
	return (rgb);
}

double	tofloat(char **str)
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

	pos = (t_v3 *)ft_calloc(sizeof(t_v3), 1);
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
		if (*line == 'A' && *line++)
			t_scene_add_back(w, t_scene_new(i, AMBIENT_LIGHTNING, true, parse_amb(*w, &line, rt)));
		else if (*line == 'C' && *line++)
			t_scene_add_back(w, t_scene_new(i, CAMERA, true, (parse_cam(*w, &line, rt))));
		else if (*line == 'L' && *line++)
			t_scene_add_back(w, t_scene_new(i, LIGHT, true, (parse_light(*w, &line, rt))));
		else if (ft_strncmp(line, "sp", 2) == 0 && *line++)
			t_scene_add_back(w, t_scene_new(i, SPHERE, true, (parse_sphere(*w, &line, rt))));
		else if (ft_strncmp(line, "pl", 2) == 0 && *line++)
			t_scene_add_back(w, t_scene_new(i, PLANE, true,(parse_plane(*w, &line, rt))));
		else if (ft_strncmp(line, "cy", 2) == 0 && *line++)
			t_scene_add_back(w, t_scene_new(i, CYLINDER, true, (parse_cylinder(*w, &line, rt))));
		else
			ft_print_error("unexpected identifier in scene file", w, NULL, rt);
		i++;
	}
	free_mat(rt);
}
