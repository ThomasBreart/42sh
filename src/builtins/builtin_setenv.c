/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 16:13:40 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 05:32:32 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	setenv_check_errors(char **argv, int forced)
{
	int		i;

	i = -1;
	if (ft_tablen(argv) > 3)
	{
		ft_putendl_fd("setenv: Too many arguments.", STDERR_FILENO);
		return (-1);
	}
	while (argv[1][++i])
	{
		if (!ft_isalnum(argv[1][i]) && !forced)
		{
			if (0 == i)
				ft_putendl_fd("setenv: Variable name must begin with a letter.",
						STDERR_FILENO);
			else
			{
				ft_putstr_fd("setenv: Variable name must ", STDERR_FILENO);
				ft_putendl_fd("contain alphanumeric characters.",
						STDERR_FILENO);
			}
			return (-1);
		}
	}
	return (0);
}

/*
**	Prepare une variable pour env de type :
**	key=		ou
**	key=value
*/

static char	*construct_env_var(char *key, char *value)
{
	char	*tmp;

	if (value == NULL)
	{
		tmp = s_strnew(ft_strlen(key) + 1, __FILE__);
		ft_strcpy(tmp, key);
		ft_strcat(tmp, "=");
	}
	else
	{
		tmp = s_strnew(ft_strlen(key) + ft_strlen(value) + 1, __FILE__);
		ft_strcpy(tmp, key);
		ft_strcat(tmp, "=");
		ft_strcat(tmp, value);
	}
	return (tmp);
}

/*
**	Built-in de la commande setenv
**	Check erreurs arguments,
**	SI pas d'arguments : affichage de env
**	SINON modification de env en fonction des arguments,
**	'realloc' si besoin
** the forced arg, forces var's writting for the '?' case
*/

int			builtin_setenv(char **argv, char ***env, int forced)
{
	char		**tkey;
	char		*key;

	if (setenv_check_errors(argv, forced) == -1)
		return (-1);
	if (argv[1] == NULL)
		ft_print_tab(*env);
	else if ((tkey = ft_getenvadress(argv[1], *env)) != NULL)
	{
		free(*tkey);
		*tkey = construct_env_var(argv[1], argv[2]);
	}
	else
	{
		key = construct_env_var(argv[1], argv[2]);
		*env = s_realloc_tab_end(*env, key, __FILE__);
	}
	return (1);
}
