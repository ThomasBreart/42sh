/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2016/11/14 10:53:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_glob.h>

int			builtin_glob(char **argv)
{
	static int	flag = 0;
	int			i;
	int			j;

	i = 1;
	if (!argv)
		return (flag);
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j])
			{
				if (argv[i][j] == 'c')
					flag |= GLOB_CASE;
				else if (argv[i][j] == 'h')
					flag |= GLOB_HIDE;
				else if (argv[i][j] == 'r')
					flag = 0;
				else
					return (0);
				j++;
			}
		}
		i++;
	}
	return (flag);
}

int			can_continue(int flags, char *name, char *pattern)
{
	return ((flags & GLOB_HIDE) || (*name != '.' ||
	*pattern == '.'));
}

static void	correct_string(char *s, char *pattern)
{
	char	*tmp;

	if ((*pattern == '*' || *pattern == '?' || *pattern == '[')
		&& !ft_strcmp("./", s))
	{
		tmp = s + 2;
		while (*tmp)
		{
			*s = *tmp;
			s++; 
			tmp++;
		}
		*s = 0;
		*(s + 1) = 0;
	}
}

void		glob__list_adding(t_list **lst, char *s, int (*cmp)(),
										char *pattern)
{
	t_list				*tmp;
	t_list				*add;
	t_list				*last;

	add = NULL;
	last = NULL;
	tmp = *lst;
	correct_string(s, pattern);
	if (tmp)
	{
		while (tmp && !((*cmp)(s, tmp->content) <= 0))
		{
			last = tmp;
			tmp = tmp->next;
		}
		add = ft_lstnew_noalloc(s, ft_strlen(s) + 1);
		add->next = tmp;
		if (last)
			last->next = add;
		else
			*lst = add;
	}
	else
		*lst = ft_lstnew_noalloc(s, ft_strlen(s) + 1);
}

