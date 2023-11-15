/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/08/03 17:09:14 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

 bool	get_unique(char *line, t_scene *scene, char type)
{
	bool	unique;

	if (*line > 64 && *line < 91)
		unique = true;
	else if (*line > 96 && *line < 123)
		unique = false;
	else
		errors_handler("parser: the first character of the type must be a "\
			"letter", NULL, &scene);
	if (!t_scene_check_unique(scene, type, unique))
		errors_handler("parser: there can be a single object of the same type "\
			"if its type starts with a capital letter ", NULL, &scene);
	return (unique);
}

/*check extension (-3 stands for remove ".rt")*/
int	ft_check_file(char *scene)
{
	size_t	len;

	len = ft_strlen(scene) - 3;
	if (len > 3)
	{
		if (ft_strncmp(scene + len, ".rt", 3) == 0)
			return (1);
	}
	return (0);
}

/*read line, clean and check parameters correctness*/
void	ft_read_rt(t_scene *w, char *scene)
{
	char	*line;
	char	*full_rt;
	int		fd;
	char	**rt;

	full_rt = ft_calloc(1, 1);
	fd = open(scene, O_RDONLY);
	if (fd < 0)
		ft_print_error(NOFILE, &w, full_rt, NULL);
	line = get_next_line(fd);
	while (line)
	{
		full_rt = ft_strjoin2(full_rt, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	rt = ft_split(full_rt, '\n');
	free(full_rt);
	contchar(w, rt);
	ft_line_parser(&w, rt);
}

/*open argument file, check extension and send to read*/
int	ft_open_rt(t_scene *w, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_print_error(NOFILE,& w, NULL, NULL));
	if (ft_check_file(av[1]) == 0)
		return (ft_print_error(NO_RT, &w, NULL, NULL));
	ft_read_rt(w, av[1]);
	return (0);
}

int	ft_print_error(char *err, t_scene **w, void *del, char **rt)
{
	write(2, "Error\n ", 7);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	if (rt != NULL)
		free_mat(rt);
	if (del != NULL)
		free(del);
	t_scene_free(w);
	exit (1);
}