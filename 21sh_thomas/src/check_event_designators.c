/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_event_designators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:07:40 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/19 15:37:05 by tbreart          ###   ########.fr       */
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
				tmp = goto_next_char((*str + i), ' ');
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

int		event_previous_command(char **new_str)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	if (termcaps->end == NULL || termcaps->end->content == NULL)
		return (-1);
	*new_str = s_strdup(termcaps->end->prev->content, __FILE__);// pas passer par prev -> del elem avant
	return (1);
}

int		exec_event(char **sub_cmd)
{
	char	*new_str;
	int		ret;

	ret = -1;
	new_str = NULL;
	if (is_previous_command(*sub_cmd))
		ret = event_previous_command(&new_str);
/*	else if (is_positif_number(*sub_cmd))
		;
	else if (is_negatif_number(*sub_cmd))
		;
	else if (is_string_anywhere(*sub_cmd))
		;
	else if (is_string_substitution(*sub_cmd))
		;
	else if (is_sharp(*sub_cmd))
		;
	else
		event_string();*/
	ft_strdel(sub_cmd);
	*sub_cmd = new_str;
	return (ret);
}

void	modif_last_elem_history(t_list *first)
{
	char	*new_cmd_in_history;
	int		len;
	char	**tabtmp;
	t_list	*tmp;
	t_historic	*termcaps;

	termcaps = get_termcaps();
	len = 0;
	tmp = first;
	while (first != NULL)
	{
		if (first->type == LEX_WORD)
		{
			tabtmp = first->argv;
			while (*tabtmp != NULL)
			{
				len += ft_strlen(*tabtmp) + 1; // + 1 pour l'espace
				tabtmp++;
			}
		}
		else
		{
			len += ft_strlen(first->content) + 1;
		}
		first = first->next;
	}
	--len;
	new_cmd_in_history = s_strnew(len, __FILE__);
	while (tmp != NULL)
	{
		if (tmp->type == LEX_WORD)
		{
			tabtmp = tmp->argv;
			while (*tabtmp != NULL)
			{
				ft_strcat(new_cmd_in_history, *tabtmp);
				ft_strcat(new_cmd_in_history, " ");
				tabtmp++;
			}
		}
		else
		{
			ft_strcat(new_cmd_in_history, tmp->content);
			ft_strcat(new_cmd_in_history, " ");
		}
		tmp = tmp->next;
	}
	printf("new_cmd_in_history: -%s-\n", new_cmd_in_history);
	new_cmd_in_history[len] = '\0';
	printf("new_cmd_in_history: -%s-\n", new_cmd_in_history);
	ft_strdel(&termcaps->end->content);
	termcaps->end->content = new_cmd_in_history;
}

int		check_event_designators(t_list **first)
{
	t_list		*elem;
	int			i;
	char		*sub_cmd;
	int			start_subcmd;
	int			start_analysis;
	char	*tmp;
	int		flag_show_new_cmd = 0;

	elem = *first;
	while (elem != NULL)
	{
		if (elem->type == LEX_WORD)
		{
			i = 0;
			while (elem->argv[i] != NULL)
			{
				start_analysis = 0;
				start_subcmd = -1;
				sub_cmd = NULL;
				while (extract_subcmd2(&elem->argv[i], start_analysis, &start_subcmd, &sub_cmd) == 1)
				{
	fprintf(stderr, "start_subcmd1: %d\n", start_subcmd);
	fprintf(stderr, "subcmd1: %s\n", sub_cmd);
					if (exec_event(&sub_cmd) == -1)
						return (-1);
	fprintf(stderr, "subcmd2: %s\n", sub_cmd);
	fprintf(stderr, "subcmd4: %s\n", sub_cmd);
					tmp = add_str_in_str(elem->argv[i], sub_cmd, start_subcmd);
	fprintf(stderr, "tmp: %s\n", tmp);
					ft_strdel(&elem->argv[i]);
					elem->argv[i] = tmp;
					start_analysis = start_subcmd + ft_strlen(sub_cmd);
					ft_strdel(&sub_cmd);

					flag_show_new_cmd = 1;
				}
				++i;
			}
			//show_elem(elem);
		}
		elem = elem->next;
	}
	modif_last_elem_history(*first);
	//while ()
	//update_elem(elem, 1);
///	if (flag_show_new_cmd == 1)
///		show_new_cmd();
	return (1);
}
