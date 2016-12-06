/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:42:57 by mfamilar          #+#    #+#             */
/*   Updated: 2016/12/02 18:29:01 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			print_error_cd(char *s)
{
	struct stat	buf;
	int			i;

	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	i = stat(s, &buf);
	if (access(s, F_OK) == -1)
		ft_putendl_fd("No such file or directory.", STDERR_FILENO);
	else if (i != -1 && S_ISDIR(buf.st_mode) == 0)
		ft_putendl_fd("Not a directory.", STDERR_FILENO);
	else
		ft_putendl_fd("Permission denied.", STDERR_FILENO);
	return (-1);
}

int			cd_usage(char *args)
{
	char	*option;

	if (args)
		option = get_tokenn(args);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(option, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", STDERR_FILENO);
	ft_strdel(&option);
	return (1);
}

/*
**	Built-in de la commande cd
**	Check erreurs arguments,
**	tente de changer de dossier
**	affiche erreur si fail du changement de dossier
**	Modifie variables env PWD et OLDPWD
*/

int			check_arg(char *target)
{
	char	**ar;

	ar = ft_strsplit(target, ' ');
	if (ft_tablen(ar) > 1)
	{
		ft_putendl_fd("cd: Too many arguments.", STDERR_FILENO);
		free_double_tab(ar);
		return (1);
	}
	free_double_tab(ar);
	return (0);
}
