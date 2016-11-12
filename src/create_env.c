/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 21:44:56 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/12 13:34:02 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	create_ret_val(char ***newenv)
{
	char	**tmptab;

	tmptab = fake_argv("?", "0");
	builtin_setenv(tmptab, newenv, 1);
	free_double_tab(tmptab);
}

/*
**	remet a jour les variables pwd, shell et shlvl de l'env
**	stok aussi la variable pwd dans les variables du shell
*/

static void	edit_env(char ***newenv)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	**tmptab;

	tmp1 = getcwd(NULL, 0);
	tmptab = fake_argv("PWD", tmp1);
	builtin_setenv(tmptab, newenv, 0);
	free_double_tab(tmptab);
	tmp2 = s_strdup("/minishell", __FILE__);
	tmp3 = s_strjoin(tmp1, tmp2, __FILE__);
	tmptab = fake_argv("SHELL", tmp3);
	builtin_setenv(tmptab, newenv, 0);
	free_double_tab(tmptab);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	tmp1 = find_shlvl(*newenv);
	tmptab = fake_argv("SHLVL", tmp1);
	builtin_setenv(tmptab, newenv, 0);
	free_double_tab(tmptab);
	free(tmp1);
	create_ret_val(newenv);
}

/*
**	Cree une copie de l'env de base
*/

char		**create_env(char **environ)
{
	char	**tmp;
	char	**newenv;
	int		i;

	tmp = environ;
	i = 0;
	while (*tmp != NULL)
	{
		i++;
		tmp++;
	}
	newenv = (char**)s_memalloc(sizeof(char**) * (i + 1), __FILE__);
	i = 0;
	tmp = environ;
	while (*tmp != NULL)
	{
		newenv[i] = s_strdup(*tmp, __FILE__);
		tmp++;
		i++;
	}
	newenv[i] = NULL;
	edit_env(&newenv);
	return (newenv);
}
