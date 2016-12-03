/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:28:15 by mfamilar          #+#    #+#             */
/*   Updated: 2016/12/03 17:53:09 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			go_home(char ***env)
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
	update_pwd_and_oldpwd(env, var);
	return (0);
}
