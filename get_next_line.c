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
char *get_next_line(int fd)
{
    ssize_t         num_read;
    static char     buffer[BUFFER_SIZE + 1];
    struct node     *start = NULL;   // Initialize to NULL
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
        temp = new_node(buffer)