/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_shifts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 02:46:14 by tbreart           #+#    #+#             */
/*   Updated: 2016/08/14 12:02:24 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	calcul(char *s, int i, int cur_x)
{
	if (s[i - 1] != ' ')
	{
		while (i > 0 && (s[i] != ' ' || i == cur_x))
			i--;
	}
	else
	{
		while (i > 0)
		{
			if (s[i] == ' ')
			{
				while (i > 0 && s[i] == ' ')
					i--;
				break ;
			}
			i--;
		}
		while (i > 0 && s[i] != ' ')
			i--;
	}
	if (i != 0)
		i++;
	return (i);
}

int			ft_key_shift_left(t_historic *tcaps, char **entry)
{
	int		i;
	char	*s;
	int		tmp;

	if (*entry == NULL || tcaps->cur_x == 0)
		return (1);
	s = *entry;
	i = calcul(s, tcaps->cur_x, tcaps->cur_x);
	tmp = tcaps->select_mode;
	tcaps->select_mode = 0;
	while (tcaps->cur_x > i)
		ft_key_left(tcaps, entry);
	if (tmp == 1)
	{
		tcaps->select_mode = 1;
		show_entry(tcaps, *entry);
	}
	return (1);
}

int			ft_key_shift_right(t_historic *tcaps, char **entry)
{
	int		i;
	int		tmp;

	if (*entry == NULL || tcaps->cur_x == (int)ft_strlen(*entry))
		return (1);
	i = tcaps->cur_x;
	while ((*entry)[i] != '\0')
	{
		if ((*entry)[i] == ' ')
		{
			while ((*entry)[i] == ' ')
				i++;
			break ;
		}
		i++;
	}
	tmp = tcaps->select_mode;
	tcaps->select_mode = 0;
	while (tcaps->cur_x < i && tcaps->cur_x < (int)ft_strlen(*entry))
		ft_key_right(tcaps, entry);
	if (tmp == 1)
		tcaps->select_mode = 1;
	if (tmp == 1)
		show_entry(tcaps, *entry);
	return (1);
}

int			ft_key_shift_up(t_historic *tcaps, char **entry)
{
	int		len_line;
	int		tmp;

	if (*entry == NULL)
		return (1);
	len_line = tcaps->ws.ws_col;
	tmp = tcaps->select_mode;
	tcaps->select_mode = 0;
	while (len_line > 0 && tcaps->cur_x > 0)
	{
		ft_key_left(tcaps, entry);
		len_line--;
	}
	if (tmp == 1)
	{
		tcaps->select_mode = 1;
		show_entry(tcaps, *entry);
	}
	return (1);
}

int			ft_key_shift_down(t_historic *tcaps, char **entry)
{
	int		i;
	int		tmp;

	if (*entry == NULL)
		return (1);
	i = tcaps->ws.ws_col;
	tmp = tcaps->select_mode;
	tcaps->select_mode = 0;
	while (i > 0 && tcaps->cur_x < (int)ft_strlen(*entry))
	{
		ft_key_right(tcaps, entry);
		i--;
	}
	if (tmp == 1)
	{
		tcaps->select_mode = 1;
		show_entry(tcaps, *entry);
	}
	return (1);
}
