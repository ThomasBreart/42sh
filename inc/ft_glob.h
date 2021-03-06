/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 10:23:35 by fjacquem          #+#    #+#             */
/*   Updated: 2016/12/06 14:54:13 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOB_H
# define FT_GLOB_H
# include "../libft/includes/libft.h"
# include <ft_42sh.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <unistd.h>

# define GLOB_CASE 1
# define GLOB_HIDE 2

typedef struct		s_globinfo
{
	char			*local;
	char			*name;
	char			*path;
	char			*origin_pattern;
	int				flags;
}					t_globinfo;

typedef struct		s_glob
{
	char			*pattern;
	t_list			*results;
	int				flags;
}					t_glob;

/*
**	Need to add as libft
*/
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstnew_noalloc(const void *cnt, size_t cnt_size);
void				ft_lstadd_end(t_list **addr, t_list *lst);
int					ft_strcasecmp(const char *s1, const char *s2);
int					ft_lstcpt(t_list *lst);
int					ft_isgraph(int c);
int					ft_islower(int c);
int					ft_ispunct(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
int					ft_isxdigit(int c);
int					ft_isprint(int c);
int					ft_isblank(int c);
int					ft_iscntrl(int c);

/*
**	Process
*/
int					can_continue(int flags, char *name, char *pattern);
int					glob__open_directory(t_globinfo g, char *pattern,
					t_list **results);
int					match_bracket(t_globinfo *g, char *s, char *pattern,
					t_list **results);
int					glob__match(t_globinfo *g, char *filename, char *pattern,
					t_list **results);
int					get_patterns(t_list **patterns, char *pattern);
void				glob__list_adding(t_list **lst, char *s, int (*cmp)(),
										char *pattern);
int					glob_brace(t_list *first);

/*
**	User
*/
int					builtin_glob(char **argv);
char				**glob__create_tab(t_list *results);
int					ft_glob(const char *pattern, t_glob *g);
#endif
