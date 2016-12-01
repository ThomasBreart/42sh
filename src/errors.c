/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/16 17:22:13 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/24 18:14:52 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int		error_fd_aggr(int fd_aggr)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putnbr_fd(fd_aggr, STDERR_FILENO);
	ft_putendl_fd(": Bad file descriptor", STDERR_FILENO);
	return (-1);
}

int		error_name(char *fullpath, char *content)
{
	struct stat	buf;
	int			i;

	i = stat(content, &buf);
	ft_putstr_fd(content, STDERR_FILENO);
	if (fullpath == NULL)
		ft_putendl_fd(": Command not found.", STDERR_FILENO);
	else if (i != -1 && S_ISDIR(buf.st_mode) == 1)
		ft_putendl_fd(": Is a directory.", STDERR_FILENO);
	else if (access(content, F_OK) == 0)
		ft_putendl_fd(": Permission denied.", STDERR_FILENO);
	else
		ft_putendl_fd(": No such file or directory.", STDERR_FILENO);
	return (-1);
}

int		internal_error(char *name_function, char *error, int dead)
{
	ft_putstr_fd("42sh[internal_error]: ", STDERR_FILENO);
	ft_putstr_fd(name_function, STDERR_FILENO);
	ft_putstr_fd(" : fail ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	if (dead == 1)
		exit(EXIT_FAILURE);
	return (-1);
}

void	errors(int a)
{
	if (a == ERR_ARGV)
		ft_putendl_fd("usage: ./42sh", STDERR_FILENO);
	else if (a == ERR_SETTERM)
		ft_putendl_fd("42sh cannot set termcaps", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
