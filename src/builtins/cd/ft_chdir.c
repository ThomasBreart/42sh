/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:28:57 by mfamilar          #+#    #+#             */
/*   Updated: 2016/12/03 17:30:06 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static char		*get_pwd(void)
{
	char	*ret;

	if ((ret = getcwd(NULL, 0)) == NULL)
		ret = s_strdup(".", __FILE__);
	return (ret);
}

static void		update_pwd_and_oldpwd(char ***env, char *pwd)
{
	char	**tmp;
	char	*oldpwd;

	if (!pwd)
		pwd = get_pwd();
	oldpwd = ft_getenv("PWD", *env);
	if (!oldpwd)
		oldpwd = get_pwd();
	tmp = fake_argv("PWD", pwd);
	builtin_setenv(tmp, env, 0);
	free_double_tab(tmp);
	tmp = fake_argv("OLDPWD", oldpwd);
	builtin_setenv(tmp, env, 0);
	free_double_tab(tmp);
	ft_strdel(&oldpwd);
	ft_strdel(&pwd);
}

static char		*get_path(char ***env, char *oldpath, int flag)
{
	char	*path;

	path = NULL;
	if (!flag)
		path = get_symbolink_path(env, oldpath);
	return (path);
}

static int		do_chdir(char *path, char *target)
{
	int		ret;

	ret = 1;
	if (path)
		ret = chdir(path);
	else if (target)
		ret = chdir(target);
	if (ret != 0)
	{
		ft_strdel(&path);
		return (print_error_cd(target));
	}
	return (0);
}

int				ft_chdir(char *target, char ***env, int flag)
{
	char	*path;

	path = get_path(env, target, flag);
	if (do_chdir(path, target) == -1)
		return (-1);
	update_pwd_and_oldpwd(env, path);
	return (0);
}
