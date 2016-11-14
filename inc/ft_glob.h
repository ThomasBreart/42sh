#ifndef FT_GLOB_H
# define FT_GLOB_H
# include "../lib/libft/includes/libft.h"
# include <ft_21sh.h>
//# include <structs.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <unistd.h>

# define DEBUG
# define GLOB_CASE 1
# define GLOB_HIDE 2

typedef struct		s_globinfo
{
	char			*local;
	char			*name;
	char			*path;
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
t_list	*ft_lstnew(void const *content, size_t content_size);
t_list	*ft_lstnew_noalloc(const void *cnt, size_t cnt_size);
void	ft_lstadd_end(t_list **addr, t_list *lst);
int		ft_strcasecmp(const char *s1, const char *s2);
int		ft_lstcpt(t_list *lst);
int		ft_isgraph(int c);
int		ft_islower(int c);
int		ft_ispunct(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
int		ft_isxdigit(int c);
int		ft_isprint(int c);
int		ft_isblank(int c);
int		ft_iscntrl(int c);

/*
**	Process
*/
int		glob__open_directory(t_globinfo g, char *pattern, t_list **results);
int		glob__match(t_globinfo *g, char *filename, char *pattern, t_list **results);
int		get_patterns(t_list **patterns, char *pattern);
int		glob_brace(t_list *first);

/*
**	User
*/
int		builtin_glob(char **argv);
char	**glob__create_tab(t_list *results);
int		ft_glob(const char *pattern, t_glob *g);
#endif