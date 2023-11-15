/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:24:02 by iragusa           #+#    #+#             */
/*   Updated: 2023/02/12 16:24:11 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	findchar(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	checkset(char *str, char *set)
{
	while (*str)
	{
		if (!findchar(*str, set))
			return (0);
		str++;
	}
	return (1);
}

char	*ft_char_append(char *s, char c, bool to_free)
{
	size_t	i;
	char	*str;

	if (!s)
	{
		str = (char *)malloc(sizeof(char) * 2);
		if (!str)
			return (0);
		str[0] = c;
		str[1] = 0;
		return (str);
	}
	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(sizeof(char) * ++i + 1);
	if (!str)
		return (0);
	str[i - 1] = c;
	str[i--] = 0;
	while (i--)
		str[i] = s[i];
	if (to_free && s)
		ft_free((void **)&s);
	return (str);
}

/*int main ()
{
	char	*s1 = "00C0EE10101PEPPPPEEEEEE";
	char	*set = "01PCE";
	
	printf("%d\n", checkset(s1, set));
	return (0);
}*/
