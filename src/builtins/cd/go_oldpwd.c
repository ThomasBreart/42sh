/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_oldpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:28:46 by mfamilar          #+#    #+#             */
/*   Updated: 2016/12/04 22:00:26 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			go_oldpwd(char ***env, int flag)
{
	char	*var;

	var = ft_getenv("OLDPWD", *env);
	if (!var)
	{
		ft_putendl_fd("OLDPWD not set", STDERR_FILENO);
		return (-1);
	}
	if (0 != chdir(var))
	{
		print_error_cd(var);
		ft_strdel(&var);
		return (-1);
	}
	if (!flag)
		update_pwd_and_oldpwd(env, var);
	else
	{
		update_oldpwd(env);
		update_pwd(env);
		ft_strdel(&var);
	}
	ft_putendl(ft_strchr(*ft_getenvadress("PWD", *env), '=') + 1);
	return (0);
}
