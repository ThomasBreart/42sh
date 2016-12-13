#include "libft/libft.h"

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

int			ft_iscntrl(int c)
{
	return (c >= 0 && c <= 31);
}

int			ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
}

int			ft_strcasecmp(const char *s1, const char *s2)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = (char*)s1;
	tmp2 = (char*)s2;
	while (!ft_isalnum(*s1) && !ft_isalnum(*s2))
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
	while (!ft_isalnum(*tmp1) && !ft_isalnum(*tmp2) && *tmp1 == *tmp2)
	{
		tmp1++;
		tmp2++;
	}
	return (*tmp1 - *tmp2);
}
