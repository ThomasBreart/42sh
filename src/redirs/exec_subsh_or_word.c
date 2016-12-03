/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subsh_or_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 18:31:49 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/03 18:32:16 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int			exec_subsh_or_word(t_list *prog, char ***env, t_save_fd *save)
{
	int		ret;

	if (prog->type == LEX_SUBSH)
		ret = exec_subshell(prog, save);
	else
		ret = exec_simple(prog, env, save);
	return (ret);
}
