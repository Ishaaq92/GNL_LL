/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:23:46 by isahmed           #+#    #+#             */
/*   Updated: 2024/12/18 19:09:26 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static struct s_node	*start;
	char					*line;
	int						line_len;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line_len = check_for_nl(&start);
	if (line_len < 0)
		line_len = create_ll(fd, &start);
	if (!start || line_len == -1)
		return (NULL);
	line = get_line(&start, line_len);
	clean_ll(&start, start, 0);
	return (line);
}
// int main(int ac, char *av[])
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char	*line;

// 	// line = get_next_line(fd);
// 	// while (line != NULL)
// 	// {
// 	// 	printf("%s", line);
// 	// 	line = get_next_line(fd);
// 	// }
// 	line = get_next_line(fd);
// 	printf("%s", line);

// 	line = get_next_line(fd);
// 	printf("%s", line);

// 	// line = get_next_line(fd);
// 	// printf("%s", line);

// 	close(fd);
// 	return (0);
// }