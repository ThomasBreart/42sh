/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_event_designators.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:07:40 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/05 21:06:23 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int		error_event_not_found(char *str, int error)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (error == E_NOT_FOUND)
		ft_putendl_fd(" event not found", STDERR_FILENO);
	else if (error == E_NO_PREVSUB)
		ft_putendl_fd(" no previous substitution", STDERR_FILENO);
	ft_strdel(&str);
	return (-1);
}

static int		exec_event(char **sub_cmd, char *entry, int *start_subcmd,
														int *is_substitution)
{
	char	*new_str;
	int		ret;

	ret = 0;
	new_str = NULL;
	if (is_event_string_substitution(*sub_cmd))
	{
		ret = event_string_substitution(*sub_cmd, &new_str);
		if (ret == 1)
			*is_substitution = 1;
	}
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
	if (ret != 1)
		return (error_event_not_found(*sub_cmd, ret));
	ft_strdel(sub_cmd);
	*sub_cmd = new_str;
	return (1);
}

static void		modif_last_elem_history(char *str)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	ft_strdel(&termcaps->end->content);
	termcaps->end->content = s_strdup(str, __FILE__);
}

static void		del_last_elem_histo()
{
	t_historic		*termcaps;
	t_list			*tmp;

	termcaps = get_termcaps();
	if (termcaps->end->prev == NULL)
	{
		del_elem_list(termcaps->end);
		termcaps->end = NULL;
		termcaps->cur = NULL;
		termcaps->head = NULL;
		return ;
	}
	tmp = termcaps->end;
	termcaps->cur = termcaps->end->prev;
	termcaps->end = termcaps->end->prev;
	del_elem_list(tmp);
}

int				check_event_designators(char **entry)
{
	char	*sub_cmd;
	int		start_event;
	int		start_analysis;
	char	*tmp;
	int		is_substitution;

	start_analysis = 0;
	sub_cmd = NULL;
	while (extract_event(entry, start_analysis, &start_event, &sub_cmd) == 1)
	{
		is_substitution = 0;
		if (exec_event(&sub_cmd, *entry, &start_event, &is_substitution) == -1)
		{
			del_last_elem_histo();
			return (-1);
		}
		tmp = add_str_in_str(*entry, sub_cmd, start_event);
		ft_strdel(entry);
		*entry = tmp;
		start_analysis = start_event + ft_strlen(sub_cmd);
		ft_strdel(&sub_cmd);
		if (is_substitution == 1)
			break ;
	}
	if (start_analysis != 0)
	{
		modif_last_elem_history(*entry);
		ft_putendl(*entry);
	}
	return (1);
}
