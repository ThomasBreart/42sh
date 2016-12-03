/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:35:00 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/03 17:56:03 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
