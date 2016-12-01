/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 21:37:11 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/30 18:33:08 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	argv_env_match(char *name, char **argv, int error)
{
	if (name == NULL)
		return (-1);
	while (*argv != NULL)
	{
		if (ft_strncmp_complete(name, *argv,
					len_before_thischar(name, '=')) == 0)
		{
			if (ft_strcmp(*argv, "?") == 0)
			{
				if (error)
					ft_putstr("42sh: read-only variable: ?\n");
				return (-1);
			}
			else
				return (1);
		}
		argv++;
	}
	return (-1);
}

static int	len_newenv(char **argv, char **env)
{
	int		i;

	argv++;
	i = ft_tablen(env);
	while (*env != NULL)
	{
		if (argv_env_match(*env, argv, 1) == 1)
			i--;
		env++;
	}
	return (i);
}

/*
**	malloc du newenv a newtaille + copie sans les variables a supprimer
*/

static void	delete_vars(char **argv, char **env, char **newenv)
{
	argv++;
	while (*env != NULL)
	{
		if (argv_env_match(*env, argv, 0) == -1)
		{
			*newenv = s_strdup(*env, __FILE__);
			newenv++;
		}
		env++;
	}
	*newenv = NULL;
}

static int	unsetenv_check_errors(char **argv)
{
	if (argv[1] == NULL)
	{
		ft_putendl_fd("unsetenv: Too few arguments.", STDERR_FILENO);
		return (-1);
	}
	return (1);
}

/*
**	Built-in de la commande unsetenv
**	Check si il y a bien des variables de env a retirer,
**	SI oui, 'realloc' env sans les variables a retirer.
*/

int			builtin_unsetenv(char **argv, char ***env)
{
	char	**newenv;
	int		i;

	if (unsetenv_check_errors(argv) == -1)
		return (-1);
	i = len_newenv(argv, *env);
	if (i == ft_tablen(*env))
		return (1);
	newenv = (char**)s_memalloc(sizeof(char*) * (i + 1), __FILE__);
	delete_vars(argv, *env, newenv);
	free_double_tab(*env);
	*env = newenv;
	return (1);
}
