/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 05:09:25 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/03 07:38:02 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	supprime les backquotes de la sous-commande en cours (donc le premier et le
**	dernier charactere)
*/

void	del_subcmd_indicator(char **str)
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

void	find_subcmd(char **cur_argv)
{
	char	*tmp;
	int		start_subcmd;
	int		start_analysis;
	char		*sub_cmd;

	start_analysis = 0;
	sub_cmd = NULL;
	while (extract_subcmd(cur_argv, start_analysis, &start_subcmd, &sub_cmd) == 1)
	{
		del_subcmd_indicator(&sub_cmd);///
	//	printf("sub_cmd: %s\n", sub_cmd);
	//	printf("cur_argv: %s\n", *cur_argv);
		if (sub_cmd != NULL)
		{
			remove_onelvl_escape_backslash(&sub_cmd);///
//	fprintf(stderr, "subcmd3: %s\n", sub_cmd);
			if (ft_strlen(sub_cmd) != 0)// pas lieu d intervenir
				exec_backquotes(&sub_cmd);
//	fprintf(stderr, "subcmd4: %s\n", sub_cmd);
			tmp = add_str_in_str(*cur_argv, sub_cmd, start_subcmd);
//	fprintf(stderr, "tmp: %s\n", tmp);
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

void	check_backquotes(t_list **first)
{
	t_list		*elem;
	int			i;

	elem = *first;
	while (elem != NULL)
	{
		if (elem->type == LEX_WORD)
		{
			i = 0;
			while (elem->argv[i] != NULL)
			{
				find_subcmd(&elem->argv[i]);
				++i;
			}
			update_elem(elem, 1);
		//	show_elem(elem);
		}
		elem = elem->next;
	}
}
