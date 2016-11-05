/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:01:08 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/05 05:54:46 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	exec_and(t_list *elem, char ***env, t_save_fd *save)
{
	int		ret;

	ret = 42;
	if (elem->left->type == LEX_WORD)
		ret = exec_simple(elem->left, env, save);
	else if (elem->left->type == LEX_PIPE)
		ret = cmd_pipe(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_R_R)
		ret = exec_rc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_RR_R)
		ret = exec_rrc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_L_R)
		ret = exec_lc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_LL_R)
		ret = exec_llc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_SUBSH)
		ret = exec_subshell(elem->left);
	if (ret != -1)
	{
		restore_fd(save);
		ret = exec_cmd(elem->right, env);
	}
	return (ret);
}

static int	exec_or(t_list *elem, char ***env, t_save_fd *save)
{
	int		ret;

	ret = 42;
	if (elem->left->type == LEX_WORD)
		ret = exec_simple(elem->left, env, save);
	else if (elem->left->type == LEX_PIPE)
		ret = cmd_pipe(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_R_R)
		ret = exec_rc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_RR_R)
		ret = exec_rrc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_L_R)
		ret = exec_lc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_LL_R)
		ret = exec_llc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_SUBSH)
		ret = exec_subshell(elem->left);
	if (ret == -1)
	{
		restore_fd(save);
		ret = exec_cmd(elem->right, env);
	}
	return (ret);
}

static int	exec_coma(t_list *elem, char ***env, t_save_fd *save)
{
	int		ret;

	ret = 42;
	if (elem->left->type == LEX_WORD)
		exec_simple(elem->left, env, save);
	else if (elem->left->type == LEX_PIPE)
		cmd_pipe(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_R_R)
		exec_rc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_RR_R)
		exec_rrc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_L_R)
		exec_lc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_LL_R)
		exec_llc(elem->left, env, NULL, save);
	else if (elem->left->type == LEX_OR)
		exec_or(elem->left, env, save);
	else if (elem->left->type == LEX_AND)
		exec_and(elem->left, env, save);
	else if (elem->left->type == LEX_SUBSH)
		ret = exec_subshell(elem->left);
	restore_fd(save);
	ret = exec_cmd(elem->right, env);
	return (ret);
}

int			exec_cmd(t_list *first, char ***env)
{
	t_save_fd	save;
	int			ret;

	ret = -1;
	save_fd(&save);
	if (first->type == LEX_COMA)
		ret = exec_coma(first, env, &save);
	else if (first->type == LEX_PIPE)
		ret = cmd_pipe(first, env, NULL, &save);
	else if (first->type == LEX_OR)
		ret = exec_or(first, env, &save);
	else if (first->type == LEX_AND)
		ret = exec_and(first, env, &save);
	else if (first->type == LEX_R_R)
		ret = exec_rc(first, env, NULL, &save);
	else if (first->type == LEX_RR_R)
		ret = exec_rrc(first, env, NULL, &save);
	else if (first->type == LEX_L_R)
		ret = exec_lc(first, env, NULL, &save);
	else if (first->type == LEX_LL_R)
		ret = exec_llc(first, env, NULL, &save);
	else if (first->type == LEX_SUBSH)
		ret = exec_subshell(first);
	else if (first->type == LEX_WORD)
		ret = exec_simple(first, env, &save);
	close_fd(&save);
	return (ret);
}
