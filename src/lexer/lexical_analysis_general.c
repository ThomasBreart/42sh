/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis_general.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 10:06:04 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/17 05:39:42 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	edite le lexeme trouve
*/

static int	edit_lexeme(t_list *current, char **s, int len_lexeme, int type)
{
	current->type = type;
	current->aggr_fd = 0;
	current->content = s_strsub(*s, 0, len_lexeme, __FILE__);
	*s = *s + len_lexeme;
	current->fullcontent = s_strdup(current->content, __FILE__);
	if (type == LEX_WORD)
	{
		current->argv = s_strsplit_with_quote(current->content, ' ', __FILE__);
		ft_strdel(&current->content);
		if (current->argv[0] == NULL)
		{
			del_tlist(current);
			return (0);
		}
		current->content = s_strdup(current->argv[0], __FILE__);
	}
	return (1);
}

static int	check_lexeme(int *len_lexeme, char *currentchar)
{
	if ((*len_lexeme = is_ope_coma(currentchar)) > 0)
		return (LEX_COMA);
	else if ((*len_lexeme = is_ope_and(currentchar)) > 0)
		return (LEX_AND);
	else if ((*len_lexeme = is_ope_or(currentchar)) > 0)
		return (LEX_OR);
	else if ((*len_lexeme = is_ope_pipe(currentchar)) > 0)
		return (LEX_PIPE);
	else if ((*len_lexeme = is_ope_leftleft_redir(currentchar)) > 0)
		return (LEX_LL_R);
	else if ((*len_lexeme = is_ope_left_redir(currentchar)) > 0)
		return (LEX_L_R);
	else if ((*len_lexeme = is_ope_rightright_redir(currentchar)) > 0)
		return (LEX_RR_R);
	else if ((*len_lexeme = is_ope_right_redir(currentchar)) > 0)
		return (LEX_R_R);
	else if ((*len_lexeme = is_ope_subshell(currentchar)) > 0)
		return (LEX_SUBSH);
	else if ((*len_lexeme = is_a_word(currentchar)) > 0)
		return (LEX_WORD);
	return (-1);
}

static void	remove_spaces(char **cmd)
{
	while (**cmd == ' ')
		(*cmd)++;
}

/*
**	cree une liste chainee contenant tout les lexemes crees par rapport a la
**	cmd passee
*/

int			lexical_analysis(char *cmd, t_list **first)
{
	t_list	*current;
	t_list	*prev;
	int		len_lexeme;
	int		type_lex;

	prev = NULL;
	if (ft_strlen(cmd) == 0)
		return (-1);
	while (*cmd != '\0')
	{
		remove_spaces(&cmd);
		if (*cmd == '\0')
			break ;
		current = s_lstnew(NULL, __FILE__);
		if ((type_lex = check_lexeme(&len_lexeme, cmd)) == -1)
			return (internal_error("lexical_analysis", "lexeme inconnu", 0));
		if (edit_lexeme(current, &cmd, len_lexeme, type_lex) == 1)
		{
			ft_lst_add_end(prev, current);
			prev = current;
			if (*first == NULL)
				*first = current;
		}
	}
	return (1);
}
