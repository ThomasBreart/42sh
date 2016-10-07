/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analysis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:08:05 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/07 21:02:50 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	show_list(t_list *first)
{
	while (first != NULL)
	{
		printf("->%s\n", first->content);
		first = first->next;
	}
}



int		exec_bacquotes(t_list *elem)
{
	t_historic		*termcaps;
	int		pdes[2];
	char	**argv;;
	char	*buf;
	int		child_pid;
	t_save_fd	save;

	save_fd(&save);
	argv = (char**)malloc(sizeof(char*) * 2);
	argv[0] = s_strdup("21sh", __FILE__);
	argv[1] = NULL;
	termcaps = get_termcaps();
	if (pipe(pdes) == -1)
		return (internal_error("exec_bacquotes", "create pipe", 0));
	child_pid = fork();
	printf("good1\n");
	if (child_pid == -1)
		return (internal_error("exec_bacquotes", "fork", 0));
	if (child_pid == 0)
	{
		close(pdes[PIPE_EXIT]);
		dup2(pdes[PIPE_ENTRY], STDOUT_FILENO);
		ft_putendl_fd(elem->content, STDIN_FILENO);
		signals_reset();
		if (termcaps->istty == 1 && set_termios(&termcaps->save, &save) == -1)
			internal_error("exec_bacquotes", "set_termcaps", 1);
		execve("./21sh", argv, NULL);///
		error_name(elem->content, elem->argv[0]);
		exit(EXIT_FAILURE);
	}
	waitpid(child_pid, NULL, 0);
	printf("good3\n");
	close(pdes[PIPE_ENTRY]);
	buf = (char*)malloc(sizeof(char) * 101);
	ft_bzero(buf, 101);
	read(pdes[PIPE_EXIT], &buf, 100);///
	printf("result: %s\n", buf);
	return (1);
}

void	del_backquote_char(t_list *elem) // check si seulement `` ?
{
	int		len;
	char	*new_str;

	len = ft_strlen(elem->content);
	new_str = s_strndup(elem->content + 1, (len - 2), __FILE__);
	free(elem->content);
	elem->content = new_str;
}

void	check_bacquotes(t_list *first)
{
	while (first != NULL)
	{
		if (first->type == LEX_BQ)
		{
			del_backquote_char(first);
			exec_bacquotes(first);
		}
		first = first->next;
	}
}

/*
**	show_analyse_lex(first);
**	show_binary_tree_lr(*root);
*/

int		cmd_analysis(t_list **root, char **entry)
{
	t_list *first;

	first = NULL;
	if (lexical_analysis(*entry, &first) == -1)
		return (-1);
	if (first == NULL)
		return (internal_error("cmd_analysis", "first NULL", 0));
	if (formatting_cmd_general(&first) == 1)
	{
		show_list(first);
		check_bacquotes(first);
		return (-1);
		*root = semantic_analysis(first);
		if (*root == NULL)
			return (internal_error("cmd_analysis", "Root NULL", 0));
	}
	else
		return (-1);
	return (1);
}
