/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:35:00 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/02 17:58:38 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

int			builtin_cd(char **argv, char ***env)
{
	int		ret;
	char	*begin;
	char	*target;
	int		flag;

	flag = 0;
	target = reverse_split(argv, 1);
	begin = target;
	ret = cd_parse_flag(&target, &flag);
	if (ret)
		ret = -1;
	else if (check_arg(target))
		ret = -1;
	else if (!ft_strlen(target))
		ret = go_home(env);
	else if (!ft_strcmp(target, "-"))
		ret = go_oldpwd(env);
	else
		ret = ft_chdir(target, env, flag);
	ft_strdel(&begin);
	ret = (ret == 1) || (ret == -1) ? -1 : 1;
	return (ret);
}
