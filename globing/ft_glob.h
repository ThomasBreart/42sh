#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define DEBUG

typedef struct		s_glob
{
	char			*local;
	char			*name;
	char			*path;
	t_list			*results;
}					t_glob;

t_list	*ft_lstnew_noalloc(const void *cnt, size_t cnt_size);
int		ft_strcasecmp(const char *s1, const char *s2);
int		ft_isblank(int c);
int		ft_iscntrl(int c);
void	ft_lstadd_end(t_list **addr, t_list *lst);

void	glob__open_first_directory(t_glob g, char *pattern, t_list **results);
void	glob__open_directory(t_glob g, char *pattern, t_list **results);
int		glob__match(t_glob *g, char *s, char *format, t_list **results);
int		ft_glob(char **addr, char *format, t_list **results);
