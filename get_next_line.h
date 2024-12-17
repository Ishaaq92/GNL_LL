#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif 

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h> 

struct node
{
    char *text;
    struct node *next;
};


int	    ft_strchri(const char *s, int c, int start);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_truncate(char *s, unsigned int start);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*subnstr(char *text, unsigned int len);
// size_t	ft_strlen(const char *s);
// char	*get_next_line(int fd);
// char	*ft_truncate(char *s, unsigned int start);

#endif