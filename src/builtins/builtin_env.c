/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 08:04:22 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/09 16:19:01 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	Modifie env en fonction des variables passes
**	Si les variables existent deja, les modifient,
**	sinon 'realloc' env en ajoutant les nouvelles variables a la fin de env
*/

static int	modify_newenv(char ***argv, char ***cpenv)
{
	char	**fake_tab;
	char	*key;
	char	*value;
	int		ret;

	while (**argv != NULL && ft_strchr(**argv, '=') != NULL)
	{
		key = s_strndup(**argv, len_before_thischar(**argv, '='), __FILE__);
		value = s_strdup(**argv + len_after_thischar(**argv, '='), __FILE__);
		fake_tab = fake_argv(key, value);
		ret = builtin_setenv(fake_tab, cpenv);
		free(key);
		free(value);
		free_double_tab(fake_tab);
		if (ret == -1)
			return (-1);
		*argv = *argv + 1;
	}
	return (1);
}

static int	show_env(char **cpenv)
{
	if (cpenv == NULL)
		return (1);
	while (*cpenv != NULL)
	{
		ft_putendl(*cpenv);
		cpenv++;
	}
	return (1);
}


/*
**	Built-in de la commande env
**	Copie l'environnement de base, et y ajoute (ou modifie)
**	les variables passees en parametre.
**	Affiche ensuite cette copie puis la free.
*/

int			builtin_env(char **argv, char **env)
{
	char	**cpenv;
	int		ret;

	ret = 42;
	argv++;
	if (builtin_env_options(argv) == -1)
		return (-1);
	if (env_check_option_i(argv))
		cpenv = shift_options(&argv);
	else
	{
		cpenv = s_tabdup(env, __FILE__);
		argv = env_exec_option_u(&cpenv, argv);
	}
	if (modify_newenv(&argv, &cpenv) == -1)
	{
		free_double_tab(cpenv);
		return (-1);
	}
	if (*argv == NULL)
		ret = show_env(cpenv);
	else
		ret = env_exec_bin(argv, cpenv, env);
	free_double_tab(cpenv);
	return (ret);
}
