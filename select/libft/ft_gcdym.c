/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcdym.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 21:22:51 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/01 21:22:54 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static void	gcaddend(t_mem *next, t_mem *new)
{
	while (next->next)
		next = next->next;
	next->next = new;
}

void		*ft_gcdym(void *addr, size_t len, int mask)
{
	t_mem	*new;
	t_mem	**gc;
	t_mem	*next;
	void	*pointer;

	if (len > 0 && (gc = ft_gc()))
	{
		pointer = malloc(len);
		ft_memcpy(pointer, addr, len);
		next = *gc;
		if (*gc)
		{
			new = ft_gcnew(pointer, len, next->index + 1,\
				IS_DUMP | mask);
			gcaddend(next, new);
		}
		else
		{
			*gc = ft_gcnew(pointer, len, 0, IS_DUMP | mask);
			new = (*gc);
		}
		return ((void*)new->pointer);
	}
	else
		return (NULL);
}
