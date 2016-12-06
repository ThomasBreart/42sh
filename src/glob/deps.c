/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 10:54:57 by fjacquem          #+#    #+#             */
/*   Updated: 2016/12/06 15:33:15 by jmaccion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_glob.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*element;

	/* element = (t_list*)malloc(sizeof(t_list)); */
	element = (t_list *)s_memalloc(sizeof(t_list), __FILE__);
	if (element == NULL)
		return (NULL);
	if (content == NULL)
	{
		element->content = NULL;
		element->content_size = 0;
	}
	else
	{
		/* element->content = (char*)malloc(content_size); */
		element->content = (char *)s_memalloc(content_size, __FILE__);
		if (element->content == NULL)
			return (NULL);
		ft_memcpy(element->content, content, content_size);
		element->content_size = content_size;
	}
	element->next = NULL;
	return (element);
}

t_list		*ft_lstnew_noalloc(const void *cnt, size_t cnt_size)
{
	t_list	*new;

	new = ft_memalloc(sizeof(t_list));
	new->content = (void*)cnt;
	new->content_size = cnt_size;
	return (new);
}

void		ft_lstadd_end(t_list **addr, t_list *lst)
{
	t_list	*tmp;

	tmp = *addr;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lst;
	}
	else
		*addr = lst;
}

int			ft_lstcpt(t_list *lst)
{
	int		len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

int			ft_strcasecmp(const char *s1, const char *s2)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = (char*)s1;
	tmp2 = (char*)s2;
	while (!ft_isalnum(*s1) && !ft_isalnum(*s2) && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 && *s2)
	{
		while (ft_tolower(*s1) == ft_tolower(*s2) && *s1 && *s2)
		{
			s1++;
			s2++;
		}
		return (ft_tolower(*s1) - ft_tolower(*s2));
	}
	while (!ft_isalnum(*tmp1) && !ft_isalnum(*tmp2) && *tmp1 == *tmp2 && *tmp1)
	{
		tmp1++;
		tmp2++;
	}
	return (*tmp1 - *tmp2);
}
