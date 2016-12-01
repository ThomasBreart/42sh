/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:28:57 by mfamilar          #+#    #+#             */
/*   Updated: 2016/12/01 17:17:35 by mfamilar         ###   ########.fr       */
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

static char		*get_path(char ***env, char *oldpath, char *option)
{
	char	*path;

	path = NULL;
	if (!option || !ft_strcmp(option, "-L"))
		path = get_symbolink_path(env, oldpath);
	return (path);
}

static int		do_chdir(char *path, char *target)
{
	int		ret;

	if (path)
		ret = chdir(path);
	else
		ret = chdir(target);
	if (ret != 0)
	{
		ft_strdel(&path);
		return (print_error_cd(target));
	}
	return (0);
}

int				ft_chdir(char **argv, char ***env)
{
	char	*path;
	char	*option;
	char	*target;

	target = (argv[2] && argv[1] && argv[1][0] == '-') ? argv[2] : argv[1];
	option = (argv[2] && argv[1] && argv[1][0] == '-') ? argv[1] : NULL;
	path = get_path(env, target, option);
	if (do_chdir(path, target) == -1)
		return (-1);
	update_pwd_and_oldpwd(env, path);
	return (1);
}
