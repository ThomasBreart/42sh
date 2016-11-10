/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_search_hist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 09:59:29 by tbreart           #+#    #+#             */
/*   Updated: 2016/07/27 18:18:19 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char		***get_tab_hist(void)
{
	static char	**tab_hist = NULL;

	return (&tab_hist);
}

static char	**add_to_tab_hist(char **tab_hist, t_list *head)
{
	char	**new_tab;
	char	**tmp;

	new_tab = tab_hist;
	if (tab_hist == NULL)
		new_tab = s_realloc_tab_end(tab_hist,
								s_strdup(head->content, __FILE__), __FILE__);
	else
	{
		tmp = tab_hist;
		while (*tmp != NULL)
		{
			if (ft_strcmp(*tmp, head->content) == 0)
				break ;
			tmp++;
		}
		if (*tmp == NULL)
			new_tab = s_realloc_tab_end(tab_hist,
								s_strdup(head->content, __FILE__), __FILE__);
	}
	return (new_tab);
}

static void	show_tab_hist(t_historic *termcaps, char **tab_tmp)
{
	int		i;

	i = 0;
	ft_putchar('\n');
	while (*tab_tmp != NULL)
	{
		ft_putchar('[');
		ft_putnbr(i);
		ft_putstr("] - ");
		ft_putendl(*tab_tmp);
		tab_tmp++;
		i++;
	}
	ft_putstr(termcaps->prompt_current);
}

int			ft_key_search_hist(t_historic *termcaps, char **entry)
{
	t_list	*tmp;
	char	***tab_hist;

	if ((tmp = termcaps->head) == NULL)
		return (-1);
	if (termcaps->select_mode == 1)
		return (1);
	if ((tab_hist = get_tab_hist()) != NULL)
		free_double_tab(*tab_hist);
	*tab_hist = NULL;
	while (tmp != NULL)
	{
		if (ft_strstr(tmp->content, "goto") == NULL)
			*tab_hist = add_to_tab_hist(*tab_hist, tmp);
		tmp = tmp->next;
	}
	show_tab_hist(termcaps, *tab_hist);
	return (1);
	(void)entry;
}
