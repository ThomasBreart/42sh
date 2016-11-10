/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:35:00 by tbreart           #+#    #+#             */
/*   Updated: 2016/08/14 12:40:36 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	print_error_cd(char *s)
{
	struct stat	buf;
	int			i;

	if (s == NULL)
	{
		ft_putendl_fd("OLDPWD not set", STDERR_FILENO);
		return (-1);
	}
	else if (ft_strcmp(s, "HOME") == 0)
	{
		ft_putendl_fd("cd: No home directory.", STDERR_FILENO);
		return (-1);
	}
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	i = stat(s, &buf);
	if (access(s, F_OK) == -1)
		ft_putendl_fd("No such file or directory.", STDERR_FILENO);
	else if (i != -1 && S_ISDIR(buf.st_mode) == 0)
		ft_putendl_fd("Not a directory.", STDERR_FILENO);
	else
		ft_putendl_fd("Permission denied.", STDERR_FILENO);
	free(s);
	return (-1);
}

static int	cd_check_errors(char **argv)
{
	if (ft_tablen(argv) > 2)
	{
		ft_putendl_fd("cd: Too many arguments.", STDERR_FILENO);
		return (-1);
	}
	return (1);
}

static void	change_var_oldpwd(char ***env)
{
	char	**tmp;
	char	*s;

	if ((s = ft_getenv("PWD", *env)) == NULL)
	{
		tmp = fake_argv("OLDPWD", NULL);
		builtin_unsetenv(tmp, env);
	}
	else
	{
		tmp = fake_argv("OLDPWD", s);
		builtin_setenv(tmp, env);
		free(s);
	}
	free_double_tab(tmp);
}

/*
**	Modidife la variable PWD de l'environnement
*/

static void	change_var_pwd(char ***env)
{
	char	**tmp;
	char	*s;

	if ((s = getcwd(NULL, 0)) == NULL)
		s = s_strdup(".", __FILE__);
	tmp = fake_argv("PWD", s);
	builtin_setenv(tmp, env);
	free(s);
	free_double_tab(tmp);
}

/*
**	Built-in de la commande cd
**	Check erreurs arguments,
**	tente de changer de dossier
**	affiche erreur si fail du changement de dossier
**	Modifie variables env PWD et OLDPWD
*/

int			builtin_cd(char **argv, char ***env)
{
	int		i;
	char	*s;

	if (cd_check_errors(argv) == -1)
		return (-1);
	if (argv[1] == NULL)
	{
		if ((s = ft_getenv("HOME", *env)) == NULL)
			return (print_error_cd("HOME"));
	}
	else if (ft_strcmp("-", argv[1]) == 0)
	{
		if ((s = ft_getenv("OLDPWD", *env)) == NULL)
			return (print_error_cd(NULL));
	}
	else
		s = s_strdup(argv[1], __FILE__);
	i = chdir(s);
	if (i < 0)
		return (print_error_cd(s));
	change_var_oldpwd(env);
	change_var_pwd(env);
	free(s);
	return (1);
}
