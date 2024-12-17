#include "get_next_line.h"

struct node *new_node(char *text)
{
    struct node *new_node;

    new_node = (struct node *)malloc(sizeof(struct node));
    if (!new_node) 
        return (NULL);
    new_node->text = ft_strdup(text); 
    new_node->next = NULL; 
    return (new_node);
}

void	print_text(struct node *start)
{
	struct node *current;

	current = start;
	while(current != NULL)
	{
		printf("%s", current->text);
		current = current->next;
	}
}

char	*extract(struct node **start)
{
	struct node	*current;
	struct node	*temp;
	char		*line;
	char		*temp_line;

	current = *start;
    line = ft_strdup("");  // Initialize line to an empty string
    if (!line)
        return (NULL);
		// && ft_strchri(current->text, '\n', 0) == -1
	while (current->next != NULL)
	{
		printf("(%s)", current->text);
		temp_line = line;  // Store the old line
		line = ft_strjoin(line, current->text);
		free(temp_line);  // Free the old line
		temp = current->next;
		if (!temp)
			current = NULL;
		free(current->text);
		free(current);
		current = temp->next;
	}
	// if (ft_strchri(current->text, '\n', 0) >= 0)
	// {
	// 	line = ft_strjoin(line, ft_substr(current->text, 0, ft_strchri(current->text, '\n', 0)));
	// 	temp = current->next;
	// 	free(current->text);
	// 	free(current);
	// 	current = temp->next;
	// 	if (current)
	// 		current->text = ft_truncate(current->text, ft_strchri(current->text, '\n', 0));
	// }
	*start = current;
	return (line);
}
char	*free_list(struct node *start)
{
    struct node *temp;

    while (start)
    {
        temp = start->next;
        free(start->text);
        free(start);
        start = temp;
    }
	return(NULL);
}
char *get_next_line(int fd)
{
    ssize_t         num_read;
    static char     buffer[BUFFER_SIZE + 1];
    static struct node     *start = NULL;   // Initialize to NULL
    struct node     *current = NULL;
    struct node     *temp;
	int				linelen;

    if (!start)
    {
		num_read = read(fd, buffer, BUFFER_SIZE);
   		if (num_read < 0)
    		return (NULL);
   		buffer[num_read] = '\0';
        start = new_node(buffer);
        current = start;
    }
    while (num_read > 0 && ft_strchri(buffer, '\n', 0))
    {
        num_read = read(fd, buffer, BUFFER_SIZE);
        if (num_read <= 0)
            break;
        buffer[num_read] = '\0';
        temp = new_node(buffer);
        if (!temp)  // Handle malloc failure
            return (free_list(start));
        current->next = temp;  // Link the new node to the list
        current = temp;        // Move current to the new node
    }
	return (extract(&start));
	//print_text(start);
    
	return (NULL);
}
int main(int ac, char *av[])
{
	if (ac < 2)
	{
		printf("Usage: %s <filename>\n", av[0]);
		return (1);
	}
	int fd = open(av[1], O_RDONLY);
	get_next_line(fd);
	// printf("(%s)", get_next_line(fd));
	close(fd);
	return (0);
}