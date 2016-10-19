/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_event_designators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:07:40 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/19 22:17:24 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*goto_next_char(char *str, char c)
{
	while (*str != '\0' && *str != c)
		++str;
	return (str);
}

int		extract_subcmd2(char **str, int start_analysis, int *start_subcmd, char **sub_cmd)
{
	int		i;
	int		len_subcmd;
	char	*new_str;
	char	*tmp;

	i = 0;
	*start_subcmd = -1;
	while ((*str)[i] != '\0' && i < start_analysis)
		++i;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\\')
			++i;
		else if ((*str)[i] == '\'')
		{
			tmp = goto_next_quote(*str + i);
			i = tmp - *str;
		}
		else if ((*str)[i] == '!')
		{
			if ((*str)[i + 1] != ' ' && (*str)[i + 1] != 9 && (*str)[i + 1] != '=')//man dit qui yen a dautre mais ca se verifie po sur le bash
			{
				*start_subcmd = i;
				if ((*str)[i + 1] == '?')
				{
					tmp = goto_next_char((*str + i + 2), '?');
					if (*tmp == '\0')
						tmp = goto_next_char((*str + i + 2), ' ');
					else
						++tmp;
				}
				else
					tmp = goto_next_char((*str + i), ' ');
				printf("tmp: %s\n", tmp);
				len_subcmd = tmp - (*str + i);
				*sub_cmd = s_strsub(*str, i, len_subcmd, __FILE__);
				new_str = s_strnew(ft_strlen(*str) - len_subcmd, __FILE__);
				ft_strncat(new_str, *str, *start_subcmd);
				ft_strcat(new_str, *str + (*start_subcmd + len_subcmd));
				ft_strdel(str);
				*str = new_str;
				return (1);
			}
		}
		if ((*str)[i] != '\0')
			++i;
	}
	return (0);
}

int		is_positif_number(char *str)
{
	++str;
	while (*str != '\0' && *str >= '0' && *str <= '9')
		++str;
	if (*str == '\0')
		return (1);
	return (0);
}

int		is_negatif_number(char *str)
{
	++str;
	if (*str == '-')
		++str;
	else
		return (0);
	if (is_positif_number(str) == 1)
		return (1);
	return (0);
}

int		is_previous_command(char *str)
{
	++str;
	if (*str == '!')
		return (1);
	return (0);
}

int		is_sharp(char *str)
{
	++str;
	if (*str == '#')
		return (1);
	return (0);
}

int		event_previous_command(char **new_str)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (termcaps->end == NULL || termcaps->end->prev == NULL || termcaps->end->prev->content == NULL)
		return (-1);
	*new_str = s_strdup(termcaps->end->prev->content, __FILE__);
	return (1);
}

int		event_positif_number(char *sub_cmd, char **new_str)
{
	t_historic	*termcaps;
	int		cmd_number;
	int		i;
	t_list	*cmd_histo;

	termcaps = get_termcaps();
	cmd_number = ft_atoi(sub_cmd + 1);
	i = 1;
	cmd_histo = termcaps->head;
	while (i < cmd_number)
	{
		if (cmd_histo == termcaps->end)
			break ;
		cmd_histo = cmd_histo->next;
		++i;
	}
	if (i < cmd_number)
		return (-1);
	*new_str = s_strdup(cmd_histo->content, __FILE__);
	return (1);
}

int		event_negatif_number(char *sub_cmd, char **new_str)
{
	t_historic	*termcaps;
	int		cmd_number;
	t_list	*cmd_histo;

	termcaps = get_termcaps();
	cmd_number = ft_atoi(sub_cmd + 1);
	cmd_histo = termcaps->end;
	printf("cmd_number: %d\n", cmd_number);
	while (cmd_number < 0)
	{
		if (cmd_histo == termcaps->head)
			break ;
		cmd_histo = cmd_histo->prev;
		++cmd_number;
	}
	if (cmd_number < 0)
		return (-1);
	*new_str = s_strdup(cmd_histo->content, __FILE__);
	return (1);
}

void	error_event_not_found(char *str)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": event not found", STDERR_FILENO);
}

int		event_sharp(char *sub_cmd, char *entry, int start_subcmd, char **new_str)
{
	char *tmp;

	if (start_subcmd == 0)
		return (-2);
	*new_str = s_strndup(entry, start_subcmd, __FILE__);
	if (sub_cmd[2] != '\0')
	{
		tmp = s_strjoin(*new_str, sub_cmd + 2, __FILE__);
		ft_strdel(new_str);
		*new_str = tmp;
	}
	return (1);
}

int		event_string(char *sub_cmd, char **new_str)
{
	t_historic *termcaps;
	t_list	*tmp;
	int		len;

	termcaps = get_termcaps();
	len = ft_strlen(sub_cmd + 1);
	tmp = termcaps->end->prev;///
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, sub_cmd + 1, len) == 0)
		{
			*new_str = s_strdup(tmp->content, __FILE__);
			break ;
		}
		tmp = tmp->prev;
	}
	if (tmp == NULL)
		return (-1);
	return (1);
}

int		is_string_anywhere(char *str)
{
	++str;
	if (*str == '?')
		return (1);
	return (0);
}

int		event_string_anywhere(char *sub_cmd, char **new_str)
{
	t_historic *termcaps;
	t_list	*tmp;
	int		len;
	char	*new_subcmd;

	termcaps = get_termcaps();
	len = ft_strlen(sub_cmd);
	if (sub_cmd[len - 1] == '?')
		new_subcmd = s_strsub(sub_cmd, 2, (len - 3), __FILE__);
	else
		new_subcmd = s_strdup(sub_cmd + 2, __FILE__);
	tmp = termcaps->end->prev;///
	while (tmp != NULL)
	{
		if (ft_strstr(tmp->content, new_subcmd) != NULL)
		{
			*new_str = s_strdup(tmp->content, __FILE__);
			break ;
		}
		tmp = tmp->prev;
	}
	free(new_subcmd);
	if (tmp == NULL)
		return (-1);
	return (1);
}



int		exec_event(char **sub_cmd, char *entry, int *start_subcmd)
{
	char	*new_str;
	int		ret;

	ret = -1;
	new_str = NULL;
	if (is_previous_command(*sub_cmd))
		ret = event_previous_command(&new_str);
	else if (is_positif_number(*sub_cmd))
		ret = event_positif_number(*sub_cmd, &new_str);
	else if (is_negatif_number(*sub_cmd))
		ret = event_negatif_number(*sub_cmd, &new_str);
	else if (is_sharp(*sub_cmd))
		ret = event_sharp(*sub_cmd, entry, *start_subcmd, &new_str);
	else if (is_string_anywhere(*sub_cmd))
		ret = event_string_anywhere(*sub_cmd, &new_str);
//	else if (is_string_substitution(*sub_cmd))
//		;
	else
		ret = event_string(*sub_cmd, &new_str);
	if (ret == -1)
		error_event_not_found(*sub_cmd);
	if (ret == -2)
		ret = -1;
	ft_strdel(sub_cmd);
	*sub_cmd = new_str;
	return (ret);
}

void	modif_last_elem_history(char *str)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	ft_strdel(&termcaps->end->content);
	termcaps->end->content = s_strdup(str, __FILE__);
	printf("new_cmd_in_history: -%s-\n", str);
}

int		check_event_designators(char **entry)
{
	char		*sub_cmd;
	int			start_subcmd;
	int			start_analysis;
	char	*tmp;
	int		flag_show_new_cmd = 0;
	t_historic		*termcaps;

	termcaps = get_termcaps();
				start_analysis = 0;
				start_subcmd = -1;
				sub_cmd = NULL;
				while (extract_subcmd2(entry, start_analysis, &start_subcmd, &sub_cmd) == 1)
				{
	fprintf(stderr, "start_subcmd1: %d\n", start_subcmd);
	fprintf(stderr, "subcmd1: %s\n", sub_cmd);
					if (exec_event(&sub_cmd, *entry, &start_subcmd) == -1)
					{
				/*		termcaps->end = termcaps->end->prev;///pas safe, check si histo = 1 seul arg
						del_elem_list(termcaps->end);///*/
						return (-1);
					}
	fprintf(stderr, "subcmd2: %s\n", sub_cmd);
	fprintf(stderr, "subcmd4: %s\n", sub_cmd);
					tmp = add_str_in_str(*entry, sub_cmd, start_subcmd);
	fprintf(stderr, "tmp: %s\n", tmp);
					ft_strdel(entry);
					*entry = tmp;
					start_analysis = start_subcmd + ft_strlen(sub_cmd);
					ft_strdel(&sub_cmd);

					flag_show_new_cmd = 1;
				}
			//show_elem(elem);
	modif_last_elem_history(*entry);
	//while ()
	//update_elem(elem, 1);
///	if (flag_show_new_cmd == 1)
///		show_new_cmd();
	return (1);
}
