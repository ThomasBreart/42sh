/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analysis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:08:05 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/08 22:03:12 by tbreart          ###   ########.fr       */
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
/*
t_list		*add_list(t_list *elem, t_list *new_list)
{
	new_list->prev = elem->prev;
	if (elem->prev != NULL)
		elem->prev->next = new_list;
	while (new_list->next != NULL)
		new_list = new_list->next;
	new_list->next = elem->next;
	if (elem->next != NULL)
		elem->next->prev = new_list;
	while (new_list->prev != NULL)
		new_list = new_list->prev;
	return (new_list);
}

t_list		*lexer(char **entry)
{
	t_list *first;

	first = NULL;
	if (lexical_analysis(*entry, &first) == -1)
		return (NULL);
	if (first == NULL)
	{
		internal_error("cmd_analysis", "first NULL", 0);
		return (NULL);
	}
	if (formatting_cmd_general(&first) == 1)
	{
		;
	//	show_list(first);
	//	check_bacquotes(first);
	}
	else
		return (NULL); ///
	return (first);
}
*/

char	*format_cmd(int fd_pipe_exit)
{
	char	*buf;
	char	*tmp;
	char	*new_entry;

	new_entry = NULL;
	while (get_next_line(fd_pipe_exit, &buf) > 0)
	{
		tmp = new_entry;
		if (new_entry == NULL)
			new_entry = s_strdup(buf, __FILE__);
		else
		{
			new_entry = s_strjoin(new_entry, " ", __FILE__);
			ft_strdel(&tmp);
			tmp = new_entry;
			new_entry = s_strjoin(new_entry, buf, __FILE__);
		}
		ft_strdel(&tmp);
		ft_strdel(&buf);
	}
	return (new_entry);
}

void	change_elem_in_word(t_list *elem, char *new_entry)
{
	free(elem->content);
	elem->type = LEX_WORD;
	elem->fullcontent = s_strdup(new_entry, __FILE__);
	elem->argv = s_strsplit_with_quote(new_entry, ' ', __FILE__);
	elem->content = s_strdup(elem->argv[0], __FILE__);
}

char	**s_tabjoin(char **tab1, char **tab2, const char *filename)
{
	char	**new_tab;
	int		tab1_len;
	int		tab2_len;
	int		i;
	int		j;

	tab1_len = ft_tablen(tab1);
	tab2_len = ft_tablen(tab2);
	new_tab = (char**)s_memalloc(sizeof(char*) * (tab1_len + tab2_len + 1), filename);
	i = 0;
	while (i < tab1_len)
	{
		new_tab[i] = s_strdup(tab1[i], filename);
		++i;
	}
	j = 0;
	while (j < tab2_len)
	{
		new_tab[i + j] = s_strdup(tab2[j], filename);
		++j;
	}
	return (new_tab);
}

void	del_tlist(t_list *elem)
{
	ft_strdel(&elem->content);
	ft_strdel(&elem->fullcontent);
	free_double_tab(elem->argv);
	free(elem);
}

t_list	*merge_elems(t_list *elem_prev, t_list *elem)
{
	t_list		*new_elem;
	char		*tmp;

	new_elem = s_lstnew(NULL, __FILE__);
	new_elem->type = LEX_WORD;
	new_elem->content = s_strdup(elem_prev->content, __FILE__);
	tmp = s_strjoin(elem_prev->content, " ", __FILE__);
	new_elem->fullcontent = s_strjoin(tmp, elem->fullcontent, __FILE__);
	free(tmp);
	new_elem->argv = s_tabjoin(elem_prev->argv, elem->argv, __FILE__);
	new_elem->prev = elem_prev->prev;
	if (elem_prev->prev != NULL)
		elem_prev->prev->next = new_elem;
	new_elem->next = elem->next;
	if (elem->next != NULL)
		elem->next->prev = new_elem;
	del_tlist(elem_prev);
	del_tlist(elem);
	return (new_elem);
}

void	show_elem(t_list *elem)
{
	printf("------ func show_elem -------\n");
	printf("elem->content: %s\n", elem->content);
	printf("elem->fulllcontent: %s\n", elem->fullcontent);
	ft_print_tab(elem->argv);
	printf("elem->type: %d\n", elem->type);
	printf("elem->aggr_fd: %d\n", elem->aggr_fd);
	printf("elem->parent (pointeur): %p\n", elem->parent);
	printf("elem->prev (pointeur): %p\n", elem->prev);
	printf("elem->next (pointeur): %p\n", elem->next);
	printf("elem->left (pointeur): %p\n", elem->left);
	printf("elem->right (pointeur): %p\n", elem->right);
	printf("-----------------------------\n");
}

int		exec_bacquotes(t_list **elem, t_list **first)
{
	t_historic		*termcaps;
	int		pdes[2];
	int		child_pid;
//	t_save_fd	save;
	t_list *root;
	char	*new_entry;

//	save_fd(&save);
	termcaps = get_termcaps();
	if (pipe(pdes) == -1)
		return (internal_error("exec_bacquotes", "create pipe", 0));
	child_pid = fork();
	if (child_pid == -1)
		return (internal_error("exec_bacquotes", "fork", 0));
	if (child_pid == 0)
	{
	//	printf("in child\n");
		close(pdes[PIPE_EXIT]);
		dup2(pdes[PIPE_ENTRY], STDOUT_FILENO);
		char *save = s_strdup((*elem)->content, __FILE__);
		root = cmd_analysis(/*root, */&save);
		free(save);
		exec_cmd(root->left, get_env());
//		printf("end child\n");
		exit(1);
	}
	else
	{
		waitpid(child_pid, NULL, 0);
//		printf("father continue\n");
		close(pdes[PIPE_ENTRY]);
		new_entry = format_cmd(pdes[PIPE_EXIT]);
//		printf("new_entry: %s\n", new_entry);
//		new_list = lexer(&new_entry);
//		first = add_list(elem, new_list);
		change_elem_in_word(*elem, new_entry);
		if ((*elem)->prev != NULL && (*elem)->prev->type == LEX_WORD)
			*elem = merge_elems((*elem)->prev, *elem);
		ft_strdel(&new_entry);
	//	show_elem(*elem);
		if ((*elem)->prev == NULL)
			*first = *elem;
	}
//	return (first);
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

void	check_bacquotes(t_list **first)
{
	t_list		*elem;

	elem = *first;
	while (elem != NULL)
	{
		if (elem->type == LEX_BQ)
		{
	//		printf("bq find: %s\n", elem->content);
			del_backquote_char(elem);
			exec_bacquotes(&elem, first);
			break ;
		}
		elem = elem->next;
	}
//	printf("plop\n");
//	printf("first: %s\n", first->fullcontent);
	//ft_putendl_fd((*first)->fullcontent, STDERR_FILENO);
//	return (first);
}

/*
**	show_analyse_lex(first);
**	show_binary_tree_lr(*root);
*/

t_list		*cmd_analysis(char **entry)
{
	t_list *first;
	t_list	*root;

	first = NULL;
	if (lexical_analysis(*entry, &first) == -1)
		return (NULL);
	if (first == NULL)
	{
		internal_error("cmd_analysis", "first NULL", 0);
		return (NULL);
	}
	if (formatting_cmd_general(&first) == 1)
	{
	//	show_list(first);
		check_bacquotes(&first);
//		return (-1);
//		printf("here1\n");
//		show_list(first);
//		printf("here2\n");
		root = semantic_analysis(first);
		if (root == NULL)
		{
			internal_error("cmd_analysis", "Root NULL", 0);
			return (NULL);
		}
	}
	else
		return (NULL);
	return (root);
}
