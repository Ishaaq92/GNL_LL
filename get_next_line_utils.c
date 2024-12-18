#include "get_next_line.h"

void	print_ll(struct node *start)
{
	struct node	*current;

	current = start;
	while (current != NULL)
	{
		printf("%s", current->text);
		current = current->next;
	}
}
void	append_node(struct node **lst, char *buffer)
{
    struct node *new_node;
	struct node *current;

    new_node = (struct node *)malloc(sizeof(struct node));
    if (!new_node) 
        return;
    new_node->text = buffer; 
    new_node->next = NULL; 
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

int	check_for_nl(struct node **lst)
{
    struct node *current;
    int         length;
    int         i;

    if (lst == NULL || *lst == NULL) // Ensure the list is not NULL
        return (-1);
    length = 0;
    current = *lst;
    while (current != NULL)
    {
        i = 0;
        while (current->text[i] != '\0')
        {
            length++;
            if (current->text[i] == '\n') // Stop if a newline is found
                return (length);
            i++;
        }
        current = current->next; // Move to the next node
    }
    return (-1);
}
int	check_for_no_nl(struct node **lst)
{
	struct node *current;
    int         length;
    int         i;

    if (lst == NULL || *lst == NULL) // Ensure the list is not NULL
        return (0);
    length = 0;
    current = *lst;
    while (current != NULL)
    {
        i = 0;
        while (current->text[i] != '\0')
        {
            length++;
            i++;
        }
        current = current->next; // Move to the next node
    }
    return (length);
}
int	create_ll(int fd, struct node **lst)
{
	ssize_t		num_read;
    char     	*buffer;
	int			line_len;
	int			nl_pos;

	nl_pos = check_for_nl(lst);
	if (nl_pos >= 0) // Check if there is already a line to return.
		return nl_pos;
	line_len = check_for_no_nl(lst);
	while (1)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (-1);
		num_read = read(fd, buffer, BUFFER_SIZE);
		if (num_read <= 0)
		{
			free(buffer);
			return (line_len);	
		}
		buffer[num_read] = '\0';
		append_node(lst, buffer);
		nl_pos = ft_strchri(buffer, '\n', 0);
		if (nl_pos >= 0) // if it does contain '\n'
		{
			line_len += (nl_pos + 1); // Instead of adding num_read bytes add index of '\n' in the buffer.
			return (line_len);
		}
		line_len += (int)num_read;
	}
}
void	clean_ll(struct node **lst)
{
	struct node *current;
	struct node	*temp;
	int			nl_pos;
	int			i;
	
	current = *lst;
	//print_ll(current);
	while (current != NULL)
	{
		nl_pos = ft_strchri(current->text, '\n', 0);
		if (nl_pos >= 0)
			break;
		temp = current->next;
		free(current->text);
		free(current);
		current = temp;
	}
	if (nl_pos == -1)
		return;
	i = 0; 
	nl_pos ++; // Don't include new line
	while (current->text[nl_pos + i] != '\0')
	{
		current->text[i] = current->text[nl_pos + i];
		i ++;
	}
	current->text[i] = '\0';
	*lst = current;
	//print_ll(*lst);
}
char	*get_line(struct node **lst, int line_len)
{
	struct node *current;
	char		*line;
	int			i;
	int			j;

	i = 0;
	current = *lst;
	line = malloc(sizeof(char) * (line_len + 1));
	while (current != NULL)
	{
		j = 0;
		while (current->text[j] != '\n' && current->text[j] != '\0')
		{
			line[i ++] = current->text[j ++];
		}
		if (current->text[j] == '\n')
			line[i] = '\n';
		current = current->next;
	}
	line[line_len] = '\0'; // ENSURE LINE_LEN IS THE ACTUAL LENGTH OF THE LINE
	return (line);
}
int	ft_strchri(const char *s, int c, int start)
{
	int		i;

	i = start;
	while (s[i] != 0)
	{
		if (s[i] == c)
			return (i);
		i ++;
	}
	if (c == 0)
		return (-1);
	return (-1);
}