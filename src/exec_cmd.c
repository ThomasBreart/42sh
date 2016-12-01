/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:01:08 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 02:38:21 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int		exec_and(t_list *elem, char ***env, t_save_fd *save)
{
	int		ret;

	ret = exec_token(elem->left, env, save);
	if (ret != -1)
	{
		restore_fd(save);
		ret = exec_cmd(elem->right, env);
	}
	return (ret);
}

static int		exec_or(t_list *elem, char ***env, t_save_fd *save)
{
	int		ret;

	ret = exec_token(elem->left, env, save);
	if (ret == -1)
	{
		restore_fd(save);
		ret = exec_cmd(elem->right, env);
	}
	return (ret);
}

static int		exec_coma(t_list *elem, char ***env, t_save_fd *save)
{
	int		ret;

	ret = exec_token(elem->left, env, save);
	restore_fd(save);
	ret = exec_cmd(elem->right, env);
	return (ret);
}

int				exec_token(t_list *elem, char ***env, t_save_fd *save)
{
	int		ret;

	ret = -1;
	if (elem->type == LEX_COMA)
		ret = exec_coma(elem, env, save);
	else if (elem->type == LEX_PIPE)
		ret = cmd_pipe(elem, env, NULL, save);
	else if (elem->type == LEX_OR)
		ret = exec_or(elem, env, save);
	else if (elem->type == LEX_AND)
		ret = exec_and(elem, env, save);
	else if (elem->type == LEX_R_R)
		ret = exec_rc(elem, env, NULL, save);
	else if (elem->type == LEX_RR_R)
		ret = exec_rrc(elem, env, NULL, save);
	else if (elem->type == LEX_L_R)
		ret = exec_lc(elem, env, NULL, save);
	else if (elem->type == LEX_LL_R)
		ret = exec_llc(elem, env, NULL, save);
	else if (elem->type == LEX_SUBSH)
		ret = exec_subshell(elem);
	else if (elem->type == LEX_WORD)
		ret = exec_simple(elem, env, save);
	return (ret);
}

int				exec_cmd(t_list *first, char ***env)
{
	t_save_fd	save;
	int			ret;

	save_fd(&save);
	get_set_save_fd(&save);
	ret = exec_token(first, env, &save);
	close_fd(&save);
	return (ret);
}
