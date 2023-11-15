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

t_v3	*v3d_normalize(t_v3 *in)
{
	double	temp;

	temp = in->x * in->x + in->y * in ->y + in->z * in->z;
	if (temp == 1)
		return (in);
	temp = sqrt(temp);
	return (&(t_v3){in->x / temp, in->y / temp, in->z / temp});
}