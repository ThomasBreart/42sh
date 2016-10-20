/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_event_designators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:07:40 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/20 18:57:12 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
		else if ((*str)[i] == '^')
		{
				*start_subcmd = i;
				tmp = goto_next_char(*str + i + 1, '^');
				if (*tmp == '^')
					tmp = goto_next_char(tmp + 1, '^');
				len_subcmd = tmp + 1 - (*str + i);
				printf("len_subcmd: %d\n", len_subcmd);
				*sub_cmd = s_strsub(*str, i, len_subcmd, __FILE__);
				new_str = s_strnew(ft_strlen(*str) - len_subcmd, __FILE__);
				ft_strncat(new_str, *str, *start_subcmd);
				ft_strcat(new_str, *str + (*start_subcmd + len_subcmd));
				ft_strdel(str);
				*str = new_str;
				printf("str: %s\n", *str);
				return (1);
		}
		if ((*str)[i] != '\0')
			++i;
	}
	return (0);
}

int		error_event_not_found(char *str, int error)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (error == E_NOT_FOUND)
		ft_putendl_fd("event not found", STDERR_FILENO);
	else if (error == E_NO_PREVSUB)
		ft_putendl_fd("no previous substitution", STDERR_FILENO);
	return (-1);
}

int		exec_event(char **sub_cmd, char *entry, int *start_subcmd)
{
	char	*new_str;
	int		ret;

	ret = 0;
	new_str = NULL;
	if (is_event_string_substitution(*sub_cmd))
		ret = event_string_substitution(*sub_cmd, &new_str);
	else if (is_event_previous_command(*sub_cmd))
		ret = event_previous_command(&new_str);
	else if (is_event_positif_number(*sub_cmd))
		ret = event_positif_number(*sub_cmd, &new_str);
	else if (is_event_negatif_number(*sub_cmd))
		ret = event_negatif_number(*sub_cmd, &new_str);
	else if (is_event_sharp(*sub_cmd))
		ret = event_sharp(*sub_cmd, entry, *start_subcmd, &new_str);
	else if (is_event_string_anywhere(*sub_cmd))
		ret = event_string_anywhere(*sub_cmd, &new_str);
	else
		ret = event_string(*sub_cmd, &new_str);
	ft_strdel(sub_cmd);
	if (ret != 1)
		return (error_event_not_found(*sub_cmd, ret));
	*sub_cmd = new_str;
	return (1);
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
	int			event = 0;
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
					event = 1;
				}
	if (event == 1)
	{
	modif_last_elem_history(*entry);
	ft_putendl(*entry);
	}
	return (1);
}
