/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/08/03 17:09:14 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_char_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	*sux_malloc(unsigned int size, t_scene *w, char **rt)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		ft_print_error(MALLOC, &w, NULL, rt);
	return (ptr);
}

void	next_val(char **str)
{
	while (*str && (**str == 32 || **str == 9))
		(*str)++;
}

int	my_atoi(char **str)
{
	int	i;
	int	neg;

	i = 0;
	neg = 1;
	if (**str == '-' && *((*str)++))
		neg = -1;
	while (ft_isdigit(**str))
		i = i * 10 + (*((*str)++) - '0');
	next_val(str);
	return (i * neg);
}

void	ft_comma(char **str, t_scene *w, void *s, char **rt)
{
	if (**str != ',')
		ft_print_error("parameters bad formatted\n", &w, s, rt);
	(*str)++;
}
