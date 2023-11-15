/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/08/03 17:09:14 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*parse_sphere(t_scene *w, char **line, char **rt)
{
	t_sphere	*s;

	(*line)++;
	s = sux_malloc(sizeof(t_sphere), w, rt);
	next_val(line);
	s->origin = pos_parse(line, w, (t_sphere *)s, rt);
	next_val(line);
	s->diameter = tofloat(line);
	if (s->diameter <= 0)
		ft_print_error("sphere radius must be > 0", &w, (t_sphere *)s, rt);
	next_val(line);
	s->rgb = color_parse(line, w, s, rt);
	return ((void *)s);
}

void	*parse_plane(t_scene *w, char **line, char **rt)
{
	t_plane		*p;

	(*line)++;
	p = sux_malloc(sizeof(t_plane), w, rt);
	next_val(line);
	p->origin = pos_parse(line, w, p, rt);
	next_val(line);
	p->direction = pos_parse(line, w, p, rt);
	if (p->direction->x > 1 || p->direction->x < -1
		|| p->direction->y > 1 || p->direction->y < -1
		|| p->direction->z > 1 || p->direction->z < -1)
		ft_print_error("plane direction norme must be in the range -1.0 / 1.0\n", &w, p, rt);
	// p->direction = v3d_normalize(p->direction);
	next_val(line);
	p->rgb = color_parse(line, w, p, rt);
	return ((void *)p);
}

void	*parse_cylinder(t_scene *w, char **line, char **rt)
{
	t_cylinder	*c;

	(*line)++;
	c = sux_malloc(sizeof(t_cylinder), w, rt);
	next_val(line);
	c->origin = pos_parse(line, w, c, rt);
	next_val(line);
	c->direction = pos_parse(line, w, c, rt);
	if  (c->direction->x > 1 || c->direction->x < -1
		|| c->direction->y > 1 || c->direction->y < -1
		|| c->direction->z > 1 || c->direction->z < -1)
		ft_print_error("cylinder direction norme must be in the range -1.0 / 1.0\n", &w, c, rt);
	next_val(line);
	c->diameter = tofloat(line);
	if (c->diameter <= 0)
		ft_print_error("cylinder radious must be > 0", &w, c, rt);
	next_val(line);
	c->height = tofloat(line);
	if (c->height < 0)
		ft_print_error("cylinder heigh must be >= 0", &w, c, rt);
	c->rgb = color_parse(line, w, c, rt);
	return ((void *)c);
}