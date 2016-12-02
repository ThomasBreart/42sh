/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:53:16 by fjacquem          #+#    #+#             */
/*   Updated: 2016/11/14 10:53:18 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_glob.h>

char					**glob__create_tab(t_list *results)
{
	t_list	*tmp;
	char	**ret;
	int		len;

	len = ft_lstcpt(results);
	tmp = results;
	ret = (char**)ft_memalloc(sizeof(char*) * (len + 1));
	len = 0;
	while (results)
	{
		tmp = results->next;
		ret[len] = results->content;
		free(results);
		len++;
		results = tmp;
	}
	ret[len] = NULL;
	return (ret);
}

static int				ft_glob2(char *pattern, t_globinfo gi, t_list **res)
{
	t_list		*ps;
	t_list		*next;

	ps = ft_lstnew(pattern, ft_strlen(pattern) + 2);
	if (glob_brace(ps) != -1)
	{
		while (ps)
		{
			next = ps->next;
			if (!ft_strchr(ps->content, '{'))
				glob__open_directory(gi, ps->content, res);
			free(ps->content);
			free(ps);
			ps = next;
		}
		return (0);
	}
	free(ps->content);
	free(ps);
	return (-1);
}

static int				ft_glob0(const char *pattern, t_glob *gl)
{
	static int	cmpt = -1;

	if (!gl)
		cmpt = -1;
	if (!pattern)
		cmpt += (cmpt != -1);
	return (cmpt);
}

int						ft_glob(const char *pattern, t_glob *gl)
{
	t_globinfo	g;
	int			ret;
	int			tmp;
	int			cmpt;

	cmpt = ft_glob0(pattern, gl);
	if (!pattern || !gl)
		return (0);
	if (cmpt == -1)
		cmpt = ft_lstcpt(gl->results);
	g.local = NULL;
	g.path = NULL;
	g.name = NULL;
	g.flags = gl->flags;
	ret = ft_glob2((char*)pattern, g, &gl->results);
	if (ret != -1)
	{
		tmp = ft_lstcpt(gl->results);
		ret = (cmpt != tmp);
		cmpt = tmp;
	}
	return (ret);
}
