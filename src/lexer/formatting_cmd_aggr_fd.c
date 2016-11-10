/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_cmd_aggr_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 22:50:40 by tbreart           #+#    #+#             */
/*   Updated: 2016/06/23 20:04:08 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	str_full_digit(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && ft_isdigit(s[i]))
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

/*
**	S'il y a un '&', le retire pour preparer la future redirection
**	Check s'il s'agira d'une redirection sur un fichier ou un fd
*/

static int	rebuild_aggreagator_fd(t_list *elem)
{
	char	*tmp;
	char	*tmp2;
	int		ret;

	tmp = elem->argv[0];
	if (tmp[1] == '\0' && elem->argv[1] == NULL)
		return (-1);
	if (elem->prev->type == LEX_LL_R || elem->prev->type == LEX_RR_R)
		return (-1);
	else if (tmp[1] == '\0')
		elem->argv = del_index_tab(elem->argv, 0);
	else
	{
		tmp++;
		tmp2 = s_strdup(tmp, __FILE__);
		free(elem->argv[0]);
		elem->argv[0] = tmp2;
	}
	free(elem->content);
	elem->content = s_strdup(elem->argv[0], __FILE__);
	if (elem->argv[0][0] == '-' && elem->argv[0][1] == '\0')
		elem->aggr_fd = 1;
	if ((ret = str_full_digit(elem->argv[0])) == 1)
		elem->aggr_fd = 1;
	return (ret);
}

int			find_aggregator_fd(t_list *elem)
{
	int		ret;

	ret = 0;
	while (elem != NULL)
	{
		if (elem->type == LEX_WORD && elem->prev != NULL)
			if (is_a_redir(elem->prev->type) && elem->argv[0][0] == '&')
				if ((ret = rebuild_aggreagator_fd(elem)) == -1)
					break ;
		elem = elem->next;
	}
	if (ret == -1)
		ft_putendl_fd("Syntax error: this redirection don't accept fd",
																STDERR_FILENO);
	return (ret);
}
