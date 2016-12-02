/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_globbing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:30:34 by fjacquem          #+#    #+#             */
/*   Updated: 2016/12/02 17:30:36 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_glob.h>

static int				need_globbing(char *arg)
{
	int		quote;

	quote = 0;
	while (*arg)
	{
		if (*arg == '\\')
			arg++;
		else if (*arg == '*' || *arg == '{' || *arg == '[' ||
				*arg == '?')
			return (1);
		else if (*arg == '\'' || *arg == '"')
		{
			quote = *arg;
			arg++;
			while (*arg != quote)
				arg++;
		}
		arg += !!*arg;
	}
	return (0);
}

void					do_globbing(char ***elem)
{
	char	**argv;
	int		index;
	t_glob	g;
	int		n;

	index = 0;
	g.flags = builtin_glob(NULL);
	g.results = NULL;
	argv = *elem;
	while (argv[index])
	{
		n = need_globbing(argv[index]);
		if (!n || ft_glob(argv[index], &g) != 1)
		{
			ft_lstadd_end(&g.results,
				ft_lstnew(argv[index], ft_strlen(argv[index]) + 1));
			ft_glob(NULL, &g);
		}
		free(argv[index]);
		index++;
	}
	ft_glob(NULL, NULL);
	free(*elem);
	*elem = glob__create_tab(g.results);
}
