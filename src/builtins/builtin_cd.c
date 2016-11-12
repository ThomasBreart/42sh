/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:35:00 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 13:23:03 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

void		update_oldpwd(char ***env)
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
		builtin_setenv(tmp, env, 0);
		free(s);
	}
	free_double_tab(tmp);
}

/*
**	Modidife la variable PWD de l'environnement
*/

void		update_pwd(char ***env)
{
	char	**tmp;
	char	*s;

	if ((s = getcwd(NULL, 0)) == NULL)
		s = s_strdup(".", __FILE__);
	tmp = fake_argv("PWD", s);
	builtin_setenv(tmp, env, 0);
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

static int	check_arg(char **argv, char *option)
{
	if (ft_tablen(argv) > 3)
	{
		ft_putendl_fd("cd: Too many arguments.", STDERR_FILENO);
		return (1);
	}
	else if (option && (option[0] == '-')
			&& ft_strcmp(option, "-L")
			&& ft_strcmp(option, "-P"))
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(option, STDERR_FILENO);
		ft_putendl_fd(": invalid option", STDERR_FILENO);
		ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int			builtin_cd(char **argv, char ***env)
{
	char	*option;
	char	*path;

	path = (argv[2] && argv[1] && argv[1][0] == '-') ? argv[2] : argv[1];
	option = (argv[2] && argv[1] && argv[1][0] == '-') ? argv[1] : NULL;
	if (check_arg(argv, option))
		return (-1);
	if (!path
			|| (!option && (!ft_strcmp(path, "-L") || !ft_strcmp(path, "-P"))))
		return (go_home(env));
	else if (!option && !ft_strcmp(path, "-"))
		return (go_oldpwd(env));
	else
		return (ft_chdir(argv, env));
}
