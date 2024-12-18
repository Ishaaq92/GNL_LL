#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
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
char	*get_next_line(int fd);
void	print_ll(struct node *start);
void	append_node(struct node **lst, char *buffer);
int	    check_for_nl(struct node **lst);
int	    check_for_no_nl(struct node **lst);
int	    create_ll(int fd, struct node **lst);
void	clean_ll(struct node **lst);
char	*get_line(struct node **lst, int line_len);


#endif