/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_analysis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:08:05 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/09 09:56:51 by tbreart          ###   ########.fr       */
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
	int		ret = -1;

	new_entry = NULL;
	tmp = NULL;
	while ((ret = get_next_line(fd_pipe_exit, &buf)) > 0)/// remplacer par un bon read ?
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
	if (ret == 0)
	{
	//	fprintf(stderr, "ret 0\n");
	//	fprintf(stderr, "buf: -%s-\n", buf);
		if (new_entry == NULL)
			new_entry = s_strdup(buf, __FILE__);
		else
		{
			tmp = new_entry;
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
	tmp = s_strjoin(elem_prev->fullcontent, " ", __FILE__);
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
	fprintf(stderr, "------ func show_elem -------\n");
	fprintf(stderr, "elem->content: %s\n", elem->content);
	fprintf(stderr, "elem->fulllcontent: %s\n", elem->fullcontent);
	ft_print_tab(elem->argv); ///
	fprintf(stderr, "elem->type: %d\n", elem->type);
	fprintf(stderr, "elem->aggr_fd: %d\n", elem->aggr_fd);
	fprintf(stderr, "elem->parent (pointeur): %p\n", elem->parent);
	fprintf(stderr, "elem->prev (pointeur): %p\n", elem->prev);
	fprintf(stderr, "elem->next (pointeur): %p\n", elem->next);
	fprintf(stderr, "elem->left (pointeur): %p\n", elem->left);
	fprintf(stderr, "elem->right (pointeur): %p\n", elem->right);
	fprintf(stderr, "-----------------------------\n");
}

int		exec_bacquotes(char **str)
{
	t_historic		*termcaps;
	int		pdes[2];
	int		child_pid;
	t_list *root;
	char	*new_entry;

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
		char *save = s_strdup(*str, __FILE__);
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
//		fprintf(stderr, "new_entry: -%s-\n", new_entry);
//		new_list = lexer(&new_entry);
//		first = add_list(elem, new_list);
		//change_elem_in_word(*elem, new_entry);
		//if ((*elem)->prev != NULL && (*elem)->prev->type == LEX_WORD)
		//	*elem = merge_elems((*elem)->prev, *elem);
		ft_strdel(str);
		*str = new_entry;
	//	ft_strdel(&new_entry);
		//show_elem(*elem);
	//	if ((*elem)->prev == NULL)
	//		*first = *elem;
	}
	return (1);
}

void	del_backslash(char **str)
{
	int		i;
	int		j;
	char	*tmp;
	int		flag;

	i = 0;
	j = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\\')
		{
			++j;
			++i;
		}
		if ((*str)[i] != '\0')
			++i;
	}
	if (j > 0)
	{
		tmp = s_memalloc(sizeof(char) * (ft_strlen(*str) - j + 1), __FILE__);
		i = 0;
		j = 0;
		flag = 0;
		while ((*str)[j] != '\0')
		{
			if ((*str)[j] == '\\' && flag == 0)
			{
				++j;
				flag = 1;
			}
			else
			{
				tmp[i] = (*str)[j];
				++i;
				++j;
				flag = 0;
			}
		}
		ft_strdel(str);
		*str = tmp;
	}
}

void	del_backquote_char(char **str) // check si seulement `` ?
{
	int		len;
	char	*new_str;

	len = ft_strlen(*str);
	new_str= s_strndup(*str + 1, (len - 2), __FILE__);
	ft_strdel(str);
	*str = new_str;
}

int		find_backquotes(char *fullcontent)
{
	if (ft_strchr(fullcontent, '`') != NULL)
		return (1);
	return (0);
}

char	*implode(char **taab)
{
	char	*str;
	char	**tmp;
	int		len;
	int		i;

	tmp = taab;
	len = 0;
	i = 0;
	while (*tmp != NULL)
	{
		len += ft_strlen(*tmp);
		++len;
		++tmp;
		++i;
	}
	--len;
	str = s_strnew(len, __FILE__);
	tmp = taab;
	while (*tmp != NULL)
	{
		ft_strcat(str, *tmp);
		if (i > 1)
			ft_strcat(str, " ");
		++tmp;
		--i;
	}
	return (str);
}

void	update_elem(t_list *elem)
{
	char	**tmp;

	ft_strdel(&elem->content);
	elem->content = s_strdup(elem->argv[0], __FILE__);
	ft_strdel(&elem->fullcontent);
	elem->fullcontent = implode(elem->argv);
	tmp = s_strsplit_with_quote(elem->fullcontent, ' ', __FILE__);
	free_double_tab(elem->argv);
	elem->argv = tmp;
}

void	check_bacquotes(t_list **first)
{
	t_list		*elem;
	int			i;

	elem = *first;
	while (elem != NULL)
	{
		if (elem->type == LEX_WORD/* && find_backquotes(elem->fullcontent) == 1*/)
		{
//			exit(12);
			i = 0;
			while (elem->argv[i] != NULL)
			{
				if (ft_strchr(elem->argv[i], '`') != NULL)
				{
		//	show_elem(elem);
					del_backquote_char(&elem->argv[i]);
fprintf(stderr, "new_str1: %s\n", elem->argv[i]);
					del_backslash(&elem->argv[i]);
fprintf(stderr, "new_str2: %s\n", elem->argv[i]);
					if (ft_strlen(elem->argv[i]) != 0)
						exec_bacquotes(&elem->argv[i]);
		//			exit(14);
				}
			update_elem(elem);
		//	show_elem(elem);
				++i;
			}
			//fprintf(stderr, "word find: %s\n", elem->fullcontent);
		//	fprintf(stderr, "elem modified: %s\n", elem->content);
		//	break ;
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
	if (formatting_cmd_general(&first) == 1)//check bon formatage `
	{
	//	show_list(first);
		check_bacquotes(&first);
		if (ft_strlen(first->content) == 0)
			return (NULL);
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
