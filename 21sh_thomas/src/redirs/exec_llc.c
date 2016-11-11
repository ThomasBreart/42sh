/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_llc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 11:00:04 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/22 07:04:33 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	termcaps_redir_llc(t_historic *termcaps, t_list *elem)
{
	char	*s;
	int		fd;

	signals_reset();
	termcaps->prompt_current = termcaps->prompt_in_llr;
	if ((fd = open("/tmp/.buf_21sh", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		exit(EXIT_FAILURE);
	ft_putstr(termcaps->prompt_in_llr);
	while (get_command(termcaps, &s) != 0)
	{
		if (s != NULL && ft_strcmp(s, elem->content) == 0)
		{
			free(s);
			break ;
		}
		if (s != NULL)
		{
			ft_putendl_fd(s, fd);
			free(s);
		}
		else
			ft_putchar_fd('\n', fd);
		ft_putstr(termcaps->prompt_in_llr);
	}
	exit(EXIT_SUCCESS);
}

static int	redir_buffer_llc(t_save_fd *save)
{
	int		fd;
	int		fd_tmp;

	fd = open("/tmp/.buf_21sh", O_RDONLY);
	if (fd == -1)
		return (error_name(".buf_21sh", ".buf_21sh"));
	fd_tmp = fcntl(fd, F_DUPFD, 10);
	close(fd);
	save->index_file++;
	save->fd_file[save->index_file] = fd_tmp;
	if (save->fd_parent == '&')
	{
		dup2(fd_tmp, STDOUT_FILENO);
		dup2(fd_tmp, STDERR_FILENO);
	}
	else
		dup2(fd_tmp, save->fd_parent);
	return (fd_tmp);
}

static void	close_fd_save_llc(int fd_save_output, int fd_save_input)
{
	dup2(fd_save_output, STDOUT_FILENO);
	close(fd_save_output);
	dup2(fd_save_input, STDIN_FILENO);
	close(fd_save_input);
}

int			redir_file_llc(t_list *elem, t_save_fd *save)
{
	t_historic	*termcaps;
	int			fd_save_output;
	int			ret;
	int			fd_save_input;
	int			father;

	termcaps = get_termcaps();
	termcaps->in_llr = 1;
	fd_save_input = dup(STDIN_FILENO);
	dup2(save->save_stdin, STDIN_FILENO);
	fd_save_output = dup(STDOUT_FILENO);
	dup2(save->save_stdout, STDOUT_FILENO);
	father = fork();
	if (father == -1)
		return (internal_error("redir_file_llc", "fork", 0));
	else if (father == 0)
		termcaps_redir_llc(termcaps, elem);
	waitpid(father, &ret, 0);
	close_fd_save_llc(fd_save_output, fd_save_input);
	termcaps->len_prompt = ft_strlen(termcaps->prompt);
	termcaps->in_llr = 0;
	termcaps->prompt_current = termcaps->prompt;
	if (WEXITSTATUS(ret) == EXIT_FAILURE)
		return (internal_error("termcaps_redir_llc", "open", 0));
	return (redir_buffer_llc(save));
}

int			exec_llc(t_list *elem, char ***env, t_list *prog, t_save_fd *save)
{
	t_vars_redirs	vars;

	redirs_init(&vars, elem, &prog);
	check_fd_parent(elem->content, save);
	if (elem->right->type == LEX_WORD)
	{
		if ((vars.fd_file = redir_file_llc(elem->right, save)) != -1)
			vars.ret = exec_simple(prog, env, save);
	}
	else if ((vars.fd_file = redir_file_llc(elem->right->left, save)) != -1)
	{
		if (is_a_redir(elem->right->type))
		{
			vars.ret = exec_redir_sub(elem->right, save, &vars.current);
			if (vars.ret != -1 && vars.current->type != LEX_PIPE)
				vars.ret = exec_simple(prog, env, save);
		}
		else if (elem->right->type == LEX_PIPE)
			vars.ret = cmd_pipe(vars.current, env, prog, save);
	}
	if (elem->right->type != LEX_PIPE && vars.current->type == LEX_PIPE &&
										vars.fd_file != -1 && vars.ret != -1)
		vars.ret = cmd_pipe(vars.current, env, prog, save);
	return (check_return_redirs(&vars));
}