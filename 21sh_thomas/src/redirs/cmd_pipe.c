/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 11:53:35 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/14 16:16:26 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	cmd_pipe_redirs(t_list *elem, char ***env, t_save_fd *save)
{
	int		ret;

	ret = 42;
	if (elem->right->type == LEX_WORD)
		ret = exec_simple(elem->right, env, save);
	else if (elem->right->type == LEX_SUBSH)
		ret = exec_subshell(elem->right);
	else if (elem->right->type == LEX_R_R)
		ret = exec_rc(elem->right, env, elem->right->left, save);
	else if (elem->right->type == LEX_RR_R)
		ret = exec_rrc(elem->right, env, elem->right->left, save);
	else if (elem->right->type == LEX_L_R)
		ret = exec_lc(elem->right, env, elem->right->left, save);
	else if (elem->right->type == LEX_LL_R)
		ret = exec_llc(elem->right, env, elem->right->left, save);
	return (ret);
}

/*
**	comme pour dup2, transforme newfd en une copie de oldfd
*/

static void	master_dup2(int oldfd, int newfd)
{
	t_historic	*termcaps;
	int			i;

	termcaps = get_termcaps();
	if (termcaps->stdout_modified == 0)
		dup2(oldfd, newfd);
	i = 0;
	while (i < termcaps->index_tab_aggrfd)
	{
		dup2(oldfd, termcaps->tab_aggrfd[i]);
		++i;
	}
}

static void	cmd_pipe_child(int pdes[2], t_list *prog, char ***env,
												t_save_fd *save)
{
	signals_reset();
	close(pdes[PIPE_EXIT]);
	master_dup2(pdes[PIPE_ENTRY], STDOUT_FILENO);
	if (prog->type == LEX_WORD)
		exec_simple(prog, env, save);// pas svg ret ?
	else if (prog->type == LEX_SUBSH)
		exec_subshell(prog);
	close(pdes[PIPE_ENTRY]);
	exit(42);
}

static int	cmd_pipe_father(int pdes[2], t_list *elem, char ***env,
															t_save_fd *save)
{
	int		ret;

	close(pdes[PIPE_ENTRY]);
	dup2(pdes[PIPE_EXIT], STDIN_FILENO);
	close(pdes[PIPE_EXIT]);
	if (elem->right->type == LEX_PIPE)
		ret = cmd_pipe(elem->right, env, NULL, save);
	else
		ret = cmd_pipe_redirs(elem, env, save);
	return (ret);
}

int			cmd_pipe(t_list *elem, char ***env, t_list *prog, t_save_fd *save)
{
	int			pdes[2];
	int			ret;
	pid_t		father;
	t_historic	*termcaps;

	fprintf(stderr, "yop\n");
	termcaps = get_termcaps();
	ret = 42;
	if (prog == NULL)
		prog = elem->left;
	if (pipe(pdes) == -1)
		return (internal_error("cmd_pipe", "create pipe", 0));
	father = fork();
	if (father == -1)
		return (internal_error("cmd_pipe", "fork", 0));
	if (father == 0)
		cmd_pipe_child(pdes, prog, env, save);
	else
	{
		save_pid(father);
		cmd_pipe_father(pdes, elem, env, save);
		waitpid(0, NULL, 0);
		kill_process_still_in_progress();
		init_var_aggrfd(termcaps);
	}
	return (ret);
}
