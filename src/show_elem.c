/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbreart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 04:34:22 by tbreart           #+#    #+#             */
/*   Updated: 2016/10/11 04:36:31 by tbreart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	affiche les informations d'un maillon
*/

void	show_elem(t_list *elem)
{
	fprintf(stderr, "------ func show_elem -------\n");
	fprintf(stderr, "elem->content: %s\n", elem->content);
	fprintf(stderr, "elem->fulllcontent: %s\n", elem->fullcontent);
	ft_print_tab(elem->argv); ///
	fprintf(stderr, "elem->type: %d\n", elem->type);
	fprintf(stderr, "elem->aggr_fd: %d\n", elem->aggr_fd);
	fprintf(stderr, "elem->parent (pointeur): %p\n", elem->parent);
	fprintf(stderr, "elem->prev (pointeur): %p\n", elem->prev);
	fprintf(stderr, "elem->next (pointeur): %p\n", elem->next);
	fprintf(stderr, "elem->left (pointeur): %p\n", elem->left);
	fprintf(stderr, "elem->right (pointeur): %p\n", elem->right);
	fprintf(stderr, "-----------------------------\n");
}
