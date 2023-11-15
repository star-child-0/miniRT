/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:14:31 by iragusa           #+#    #+#             */
/*   Updated: 2023/11/15 20:14:33 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free(void **ptr)
{
	if (ptr == NULL)
		return (0);
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
