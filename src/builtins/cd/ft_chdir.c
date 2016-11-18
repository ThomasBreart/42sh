/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:28:57 by mfamilar          #+#    #+#             */
/*   Updated: 2016/11/18 16:24:58 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	symlink_handler(char ***env, char *pwd, char *path)
{
	char	**fake_arg;
	char	*tmp;

	while (ft_strchr(path, '/'))
	{
		path = ft_strchr(path, '/');
		path++;
	}
	pwd = ft_strjoin(pwd, "/");
	tmp = pwd;
	pwd = ft_strjoin(pwd, path);
	fake_arg = fake_argv("PWD", pwd);
	builtin_setenv(fake_arg, env, 0);
	free_double_tab(fake_arg);
	ft_strdel(&tmp);
	ft_strdel(&pwd);
}

int			ft_chdir(char **argv, char ***env)
{
	char	*option;
	char	*path;
	char	*pwd;

	path = (argv[2] && argv[1] && argv[1][0] == '-') ? argv[2] : argv[1];
	option = (argv[2] && argv[1] && argv[1][0] == '-') ? argv[1] : NULL;
	update_pwd(env);
	pwd = ft_getenv("PWD", *env);
	if (0 != chdir(path))
	{
		ft_strdel(&pwd);
		return (print_error_cd(path));
	}
	update_oldpwd(env);
	if (option && !ft_strcmp(option, "-L"))
	{
		symlink_handler(env, pwd, path);
		ft_strdel(&pwd);
		return (1);
	}
	update_pwd(env);
	ft_strdel(&pwd);
	return (1);
}
