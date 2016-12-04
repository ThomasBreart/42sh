/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 05:09:25 by tbreart           #+#    #+#             */
/*   Updated: 2016/12/04 17:20:06 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	supprime les backquotes de la sous-commande en cours (donc le premier et le
**	dernier charactere)
*/

static void	del_subcmd_indicator(char **str)
{
	int		len;
	char	*new_str;

	new_str = NULL;
	len = ft_strlen(*str);
	if (len > 2)
		new_str = s_strndup(*str + 1, (len - 2), __FILE__);
	ft_strdel(str);
	*str = new_str;
}

static void	find_subcmd(char **cur_argv)
{
	char	*tmp;
	int		start_subcmd;
	int		start_analysis;
	char	*sub_cmd;

	start_analysis = 0;
	sub_cmd = NULL;
	while (extract_subcmd(cur_argv, start_analysis, &start_subcmd, &sub_cmd)
																		== 1)
	{
		del_subcmd_indicator(&sub_cmd);
		if (sub_cmd != NULL)
		{
			remove_onelvl_escape_backslash(&sub_cmd);
			if (ft_strlen(sub_cmd) != 0)
				exec_backquotes(&sub_cmd);
			if (sub_cmd == NULL)
				sub_cmd = s_strdup("", __FILE__);
			tmp = add_str_in_str(*cur_argv, sub_cmd, start_subcmd);
			ft_strdel(cur_argv);
			*cur_argv = tmp;
			start_analysis = start_subcmd + ft_strlen(sub_cmd);
			ft_strdel(&sub_cmd);
		}
	}
}

/*
**	cherche et execute les sous-commandes entre backquotes
*/

void		check_backquotes(t_list **first)
{
	t_list	*elem;
	int		i;

	elem = *first;
	while (elem != NULL)
	{
		if (elem->type == LEX_WORD && is_token_llr(elem->prev) == 0)
		{
			i = 0;
			while (elem->argv[i] != NULL)
			{
				find_subcmd(&elem->argv[i]);
				ft_strlen(elem->argv[i]);
				++i;
			}
			update_elem(elem, 1);
		}
		elem = elem->next;
	}
}
