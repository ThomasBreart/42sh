/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:49:11 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/26 18:49:16 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>
#include "../../include/minishell.h"

int			test_access(char *name)
{
	DIR				*d;
	int				ret;

	ret = 0;
	if ((d = opendir(name)))
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		write(2, "Is a directory\n", 15);
		ft_putstr_fd(RESET, 2);
		ret = 1;
		closedir(d);
	}
	else if (!access(name, F_OK))
		if (access(name, X_OK))
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ", 2);
			write(2, "Permission denied\n", 18);
			ft_putstr_fd(RESET, 2);
			ret = 1;
		}
	return (ret);
}

void		start_prgm(char **env, char **argv)
{
	char	*hash;

	hash = NULL;
	if (!ft_strncmp("./", argv[0], 2))
	{
		if (test_access(argv[0]))
			exit(1);
	}
	else if ((hash = hash_cmd(argv[0])))
	{
		if (test_access(hash))
			exit(1);
	}
	else if (test_access(argv[0]))
		exit(1);
	if (!ft_strncmp("./", argv[0], 2))
		execve(argv[0] + 2, argv, env);
	else if (hash)
		execve(hash, argv, env);
	else if (*argv[0] == '/')
		execve(argv[0], argv, env);
	command_not_find(argv[0]);
}

void		stop_cmd(t_list *pipeline)
{
	t_list	*tmp;

	while (pipeline)
	{
		tmp = pipeline->next;
		free_command(pipeline->content);
		free(pipeline);
		pipeline = tmp;
	}
}

int			execution__simple_command(t_command *c, t_env *e)
{
	pid_t			p;
	int				ret;
	int				stat;

	ret = 0;
	p = 0;
	if (!check_bultins(c, e) && !(p = fork()))
	{
		if (c->need_redir)
			do_redirections(&c->redirs, STDIN_FILENO, STDOUT_FILENO);
		start_prgm(e->environ, c->argv);
	}
	else
	{
		waitpid(p, &stat, WUNTRACED | WCONTINUED);
		ret = WEXITSTATUS(stat);
	}
	return (ret);
}

int			execution(t_list *pipeline, t_env *e)
{
	int		ret;
	pid_t	p;

	ret = 0;
	g_father = 0;
	if (pipeline && !verification_pipeline(pipeline))
	{
		if (pipeline->next)
		{
			if (!(p = fork()))
				execute_pipes(pipeline, e);
			wait(NULL);
			ret = WEXITSTATUS(p);
		}
		else
			ret = execution__simple_command(pipeline->content, e);
		wait(NULL);
	}
	g_father = 1;
	return (ret);
}
