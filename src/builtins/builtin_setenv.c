/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 16:13:40 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/08 16:26:25 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	setenv_check_errors(char **argv)
{
	int		i;

	i = 0;
	if (ft_tablen(argv) > 3)
	{
		ft_putendl_fd("setenv: Too many arguments.", STDERR_FILENO);
		return (-1);
	}
	if (argv[1] != NULL && !ft_isalpha(argv[1][0]))
	{
		ft_putstr_fd("setenv: Variable name must begin with ", STDERR_FILENO);
		ft_putendl_fd("a letter.", STDERR_FILENO);
		return (-1);
	}
	if (argv[1] != NULL)
		while (argv[1][i++] != '\0')
			if (!ft_isalnum(argv[1][i - 1]))
			{
				ft_putstr_fd("setenv: Variable name must ", STDERR_FILENO);
				ft_putstr_fd("contain ", STDERR_FILENO);
				ft_putendl_fd("alphanumeric characters.", STDERR_FILENO);
				return (-1);
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
*/

int			builtin_setenv(char **argv, char ***env)
{
	char		**tkey;
	char		*key;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (setenv_check_errors(argv) == -1)
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
