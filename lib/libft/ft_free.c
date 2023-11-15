/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 20:57:58 by iragusa           #+#    #+#             */
/*   Updated: 2022/10/29 20:59:29 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = 0;
	}
	return (*ptr);
}

int	free_mat(char **matrix)
{
	int	y;

	y = 0;
	if (matrix)
	{
		while (matrix[y] != NULL)
		{
			ft_free((void **)&matrix[y]);
			y++;
		}
		ft_free ((void **)matrix);
	}
	return (0);
}