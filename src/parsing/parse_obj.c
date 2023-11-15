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
	if (s->origin == NULL)
		ft_print_error("Bad formatted data in sphere", &w, s, rt);
	next_val(line);
	s->diameter = tofloat(line);
	if (s->diameter <= 0)
	{
		free (s->origin);
		ft_print_error("SPHERE: radius must be > 0", &w, (t_sphere *)s, rt);
	}
	next_val(line);
	s->rgb = color_parse(line, w, rt);
	if (s->rgb == NULL || **line != '\0')
	{
		if (s->rgb != NULL)
			free(s->rgb);
		free(s->origin);
		ft_print_error("Bad formatted data in rgb sphere", &w, s, rt);
	}
	return ((void *)s);
}

static t_plane	*parse_plane_help(t_plane *p, char **line,
	t_scene *w, char **rt)
{
	p->rgb = color_parse(line, w, rt);
	if (p->rgb == NULL || **line != '\0')
	{
		if (p->rgb != NULL)
			free(p->rgb);
		free(p->origin);
		free(p->direction);
		ft_print_error("Bad formatted data in rgb plane", &w, p, rt);
	}
	return (p);
}

void	*parse_plane(t_scene *w, char **line, char **rt)
{
	t_plane		*p;

	(*line)++;
	p = sux_malloc(sizeof(t_plane), w, rt);
	next_val(line);
	p->origin = pos_parse(line, w, p, rt);
	if (p->origin == NULL)
		ft_print_error("Bad formatted data in plane", &w, p, rt);
	next_val(line);
	p->direction = pos_parse(line, w, p, rt);
	if (p->direction == NULL || p->direction->x > 1 || p->direction->x < -1
		|| p->direction->y > 1 || p->direction->y < -1
		|| p->direction->z > 1 || p->direction->z < -1)
	{
		if (p->direction != NULL)
			free(p->direction);
		free (p->origin);
		ft_print_error("plane direction must be > -1.0 & < 1.0\n", &w, p, rt);
	}
	next_val(line);
	p = parse_plane_help(p, line, w, rt);
	return ((void *)p);
}

static t_cylinder	*parse_cylinder_help(t_cylinder *c, char **line,
	t_scene *w, char **rt)
{
	c->height = tofloat(line);
	if (c->height < 0 || c->diameter <= 0)
	{
		free(c->direction);
		free (c->origin);
		ft_print_error("cylinder height must be > 0 \
			& diameter >= 0", &w, c, rt);
	}
	c->rgb = color_parse(line, w, rt);
	if (c->rgb == NULL || **line != '\0')
	{
		if (c->rgb != NULL)
			free(c->rgb);
		free(c->origin);
		free(c->direction);
		ft_print_error("Bad formatted data in rgb cylinder", &w, c, rt);
	}
	return (c);
}

void	*parse_cylinder(t_scene *w, char **line, char **rt)
{
	t_cylinder	*c;

	(*line)++;
	c = sux_malloc(sizeof(t_cylinder), w, rt);
	next_val(line);
	c->origin = pos_parse(line, w, c, rt);
	if (c->origin == NULL)
		ft_print_error("Bad formatted data in cylinder", &w, c, rt);
	next_val(line);
	c->direction = pos_parse(line, w, c, rt);
	if (c->direction == NULL || c->direction->x > 1 || c->direction->x < -1
		|| c->direction->y > 1 || c->direction->y < -1
		|| c->direction->z > 1 || c->direction->z < -1)
	{
		if (c->direction != NULL)
			free(c->direction);
		free (c->origin);
		ft_print_error("cylinder direction must be \
			> -1.0 & < 1.0\n", &w, c, rt);
	}
	next_val(line);
	c->diameter = tofloat(line);
	next_val(line);
	c = parse_cylinder_help(c, line, w, rt);
	return ((void *)c);
}
