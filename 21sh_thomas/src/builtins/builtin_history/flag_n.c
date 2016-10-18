/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 18:48:41 by mfamilar          #+#    #+#             */
/*   Updated: 2016/10/18 19:15:35 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "stdio.h"

// char		**recover_historic_file(t_historic *termcaps)
// {
// 	int		fd;
// 	char	**taab;
// 	char	*entry;
// 	int		i;
//
// 	if ((fd = open(termcaps->path_historic_file, O_RDONLY)) == -1)
// 		return (NULL);
// 	taab = (char**)s_memalloc(sizeof(char *) * 501, __FILE__);
// 	i = 0;
// 	while (i < 501)
// 		taab[i++] = NULL;
// 	i = 0;
// 	while (get_next_line(fd, &entry) != 0)
// 	{
// 		if (taab[i] != NULL)
// 			free(taab[i]);
// 		taab[i++] = entry;
// 		termcaps->n_indice++;
// 		if (i == 501)
// 			break ;
// 	}
// 	ft_strdel(&entry);
// 	if (i == 501)
// 		recover_historic_file_error(&taab);
// 	close(fd);
// 	return (taab);
// }
//
// char   **get_tab(t_historic *termcaps)
// {
//   int   limit;
//   int		fd;
//   char	*entry
//
//   if ((fd = open(termcaps->path_historic_file, O_RDONLY)) == -1)
// 		return (NULL);
//   limit = 0;
//   while (get_next_line(fd, &entry) != 0)
// 	{
//     if (limit >= termcaps->n_indice)
// 		  taab[i++] = entry;
// 		if (i == 501)
//       break ;
//     limit++;
// 	}
//   ft_strdel(&entry);
// 	if (i == 501)
// 		recover_historic_file_error(&taab);
// 	close(fd);
// }

void	flag_n(void)
{
	t_historic	*termcaps;

	termcaps = get_termcaps();
  printf("termcaps->n_indice = %d\n", termcaps->n_indice);

	// char	**taab;
	// char	*entry;
	// int		i;
  //
  //
  // (taab = recover_historic_file(termcaps)) != NULL)
  //   create_historic_list(termcaps, taab);
	// while (get_next_line(fd, &entry) != 0)
	// {
	// 	if (taab[i] != NULL)
	// 		free(taab[i]);
	// 	taab[i++] = entry;
	// 	termcaps->n_indice++;
	// 	if (i == 501)
	// 		break ;
	// }
	// ft_strdel(&entry);
	// if (i == 501)
	// 	recover_historic_file_error(&taab);
	// close(fd);
	// return (taab);
}
