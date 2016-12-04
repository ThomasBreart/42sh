/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:28:15 by mfamilar          #+#    #+#             */
/*   Updated: 2016/12/04 22:02:21 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			go_home(char ***env, int flag)
{
	char	*var;

	var = ft_getenv("HOME", *env);
	if (!var)
	{
		ft_putendl_fd("cd: No home directory.", STDERR_FILENO);
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
	return (0);
}
