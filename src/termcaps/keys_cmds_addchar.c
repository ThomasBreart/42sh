/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_cmds_addchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <tbreart@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/21 08:19:48 by tbreart           #+#    #+#             */
/*   Updated: 2016/11/10 11:15:31 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char	*buffnull(char newchar)
{
	char	*new;

	new = s_strnew(1, __FILE__);
	new[0] = newchar;
	return (new);
}

char		*concat_entry(char *buffread, char newchar, int j)
{
	char	*new;
	int		i;
	int		h;

	if (buffread == NULL)
		return (buffnull(newchar));
	i = 0;
	new = s_strnew(ft_strlen(buffread) + 1, __FILE__);
	while (i < j)
	{
		new[i] = buffread[i];
		i++;
	}
	h = i;
	new[h] = newchar;
	h++;
	while (buffread[i] != '\0')
	{
		new[h] = buffread[i];
		h++;
		i++;
	}
	free(buffread);
	return (new);
}

static int	accepted_char(long int c)
{
	if (c < 32 || c > 126)
		return (-1);
	return (1);
}

int			cmd_add_char(t_historic *tcaps, char **entry)
{
	if (accepted_char(tcaps->buff) == -1)
		return (-1);
	*entry = concat_entry(*entry, (char)tcaps->buff, tcaps->cur_x);
	tcaps->cur_x++;
	show_entry(tcaps, *entry);
	if (tcaps->cur_x == (int)ft_strlen(*entry) &&
				(tcaps->cur_x + tcaps->len_prompt) % tcaps->ws.ws_col == 0)
		tputs(tgoto(tgetstr("do", NULL), 0, 0), 1, ft_outc);
	if (tcaps->hist == 0)
		tcaps->cmd_inprogress = s_strdup(*entry, __FILE__);
	else if (tcaps->hist == 1)
	{
		ft_strdel(&tcaps->cur->content);
		tcaps->cur->content = s_strdup(*entry, __FILE__);
		tcaps->cur->content_modified = 1;
	}
	return (1);
}
