/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:23:46 by isahmed           #+#    #+#             */
/*   Updated: 2024/12/17 18:15:30 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	struct node *temp;
	int			length;
	int			end;

	length = 0;
	current = *lst;
	end = ft_strchri(current->text, '\n', 0) ;
	while (end == -1 && current != NULL)
	{
		length += end;
		current = current->next;
		end = ft_strchri(current->text, '\n', 0);
	}
	if (current == NULL)
		return (end);
	return (-1);
}
int	create_ll(int fd, struct node **lst)
{
	ssize_t		num_read;
    char     	*buffer;
	int			line_len;
	int			end;

	line_len = 0;
	end = check_for_nl(lst); // Returns length of line upto the ln character
	if (end >= 0)
		return end;
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
		end = ft_strchri(buffer, '\n', 0);
		if (end >= 0) // if it does contain '\n'
		{
			line_len += (end + 1); // Instead of adding num_read bytes add index of '\n' in the buffer.
			return (line_len);
		}
		line_len += (int)num_read;
	}
}
void	clean_ll(struct node **lst)
{
	struct node *current;
	struct node	*temp;
	int			end;
	int			i;
	
	i = 0;
	current = *lst;
	while (current->next != NULL && ft_strchri(current->text, '\n', 0)  == -1)
	{
		temp = current->next;
		free(current->text);
		free(current);
		current = temp;
	}
	end = ft_strchri(current->text, '\n', 0) + 1;
	if (end >= 0)
	{
		while (end + i < ft_strlen(current->text))
		{
			current->text[i] = current->text[end + i];
			i ++;
		}
		current->text[i] = '\0';
	}
	*lst = current;
	print_ll(*lst);
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
char *get_next_line(int fd)
{
    ssize_t         num_read;
    static struct node     *start;
	char			*line;
	int				line_len;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);	// Create ll with start as head.
	line_len = create_ll(fd, &start);
	if (!start || line_len == -1)
		return(NULL);
	line = get_line(&start, line_len);
	// clean_ll(&start);
	// print_ll(start);
	// return (line);
}
int main(int ac, char *av[])
{
	// if (ac < 2)
	// {
	// 	printf("Usage: %s <filename>\n", av[0]);
	// 	return (1);
	// }
	int fd = open("test.txt", O_RDONLY);
	char	*line;

	// while ((line = get_next_line(fd)) != NULL)
	// {
	// 	printf("%s", line);
	// }
	line = get_next_line(fd);
	// printf("(%s)", line);

	line = get_next_line(fd);
	// printf("(%s)", line);
	
	// line = get_next_line(fd);
	// printf("3: %s", line);
	close(fd);
	return (0);
}