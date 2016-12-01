/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_c_and_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 15:38:34 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/20 16:02:32 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** Supprime tout l'historique
*/

void		flag_c(void)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
	free_historic(termcaps);
	termcaps->head = NULL;
	termcaps->cur = NULL;
	termcaps->end = NULL;
	termcaps->block_flag_a = 1;
}

/*
** Un cas particulier en fonction de si on supprime le premier ou dernier
** élément de la liste.
*/

int			del_indice_history(t_flags flags)
{
	t_list		*cpy;
	t_historic	*termcaps;
	int			i;

	i = 0;
	termcaps = get_termcaps();
	if (termcaps->head)
		cpy = termcaps->head;
	else
		return (0);
	if ((ft_lst_size(cpy)) < flags.indice)
		return (out_of_range(flags.argument));
	while (i < flags.indice - 1 && cpy->next)
	{
		cpy = cpy->next;
		i++;
	}
	check_what_element_to_delete(termcaps, cpy);
	return (0);
}

static int	parse_others_flags(char **args, t_flags *flags)
{
	while (**args)
	{
		if (**args == '-' && *(*args + 1) == '-')
			return (0);
		else if (**args == '-')
		{
			if (append_flag(args, flags))
				return (1);
		}
		*(args) += 1;
	}
	return (0);
}

int			put_flag_d(t_flags *flags, char **args)
{
	char	*cpy;

	cpy = *args;
	flags->flag_d = 1;
	return (parse_others_flags(&cpy, flags));
}

/*
** Le flag 'd' prend une valeure numérique (un indice) en paramètre et supprime
** l'indice de l'historique en question.
*/

int			flag_d(char *args, t_flags *flags)
{
	char	*cpy;
	int		index;

	index = 0;
	args++;
	while (*args == ' ')
		args++;
	if (!*args)
		return (history_usage());
	cpy = args;
	while (*args && *args != ' ')
	{
		if (!ft_isnumber(*args))
			return (out_of_range(args - index));
		index++;
		args++;
	}
	flags->indice = get_value(cpy, index);
	flags->argument = ft_itoa(flags->indice);
	return (0);
}
