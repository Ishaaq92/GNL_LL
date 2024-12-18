/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:07:32 by isahmed           #+#    #+#             */
/*   Updated: 2024/12/18 17:45:33 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// void	print_ll(struct s_node *start)
// {
// 	struct s_node	*current;
// 	int				i;

// 	i = 0;
// 	current = start;
// 	while (current != NULL)
// 	{
// 		printf("%d: %s\n", i, current->text);
// 		current = current->next;
// 		i ++;
// 	}
// }

void	append_node(struct s_node **lst, char *buffer)
{
	struct s_node	*new_node;
	struct s_node	*current;

	new_node = (struct s_node *)malloc(sizeof(struct s_node));
	if (!new_node)
		return ;
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

int	check_for_nl(struct s_node **lst)
{
	struct s_node	*current;
	int				length;
	int				i;

	if (lst == NULL || *lst == NULL)
		return (-1);
	length = 0;
	current = *lst;
	while (current != NULL && current->text != NULL)
	{
		i = 0;
		while (current->text[i] != '\0')
		{
			length++;
			if (current->text[i] == '\n')
				return (length);
			i++;
		}
		current = current->next;
	}
	return (-1);
}

int	check_for_no_nl(struct s_node **lst)
{
	struct s_node	*current;
	int				length;
	int				i;

	if (lst == NULL || *lst == NULL)
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
		current = current->next;
	}
	return (length);
}

int	create_ll(int fd, struct s_node **lst)
{
	ssize_t		num_read;
	char		*buffer;
	int			line_len;
	int			nl_pos;

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
		if (nl_pos >= 0)
			return (line_len + (nl_pos + 1));
		line_len += (int)num_read;
	}
}

void	clean_ll(struct s_node **lst, struct s_node *current, int i)
{
	struct s_node	*temp;
	int				nl_pos;

	while (current != NULL)
	{
		nl_pos = ft_strchri(current->text, '\n', 0);
		if (nl_pos >= 0)
			break ;
		temp = current->next;
		free(current->text);
		free(current);
		current = temp;
	}
	if (nl_pos++ == -1)
	{
		*lst = current;
		return ;
	}
	while (current->text[nl_pos + i] != '\0')
	{
		current->text[i] = current->text[nl_pos + i];
		i ++;
	}
	current->text[i] = '\0';
	*lst = current;
}

char	*get_line(struct s_node **lst, int line_len)
{
	struct s_node	*current;
	char			*line;
	int				i;
	int				j;

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
	line[line_len] = '\0';
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

// ft_strchi() can be removed if code is replaced in the two locations.
