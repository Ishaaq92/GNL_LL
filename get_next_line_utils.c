#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i ++;
	return (i);
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
char	*ft_strdup(const char *s)
{
	int		i;
	char	*duplicate;

	i = 0;
	duplicate = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!duplicate)
		return (NULL);
	while (s[i] != 0)
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = 0;
	return (duplicate);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	if (ft_strlen(s) <= start)
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	i = 0;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = s[start + i];
		i ++;
	}
	ptr[i] = '\0';
	return (ptr);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i ++;
	}
	i = 0;
	while (i < len2)
	{
		str[len1 + i] = s2[i];
		i ++;
	}
	str[len1 + len2] = 0;
	return (str);
}
char	*ft_truncate(char *s, unsigned int start)
{
	unsigned int	i;
	unsigned int	len;
	char			*new_str;

	i = 0;
	len = ft_strlen(s);
	if (start >= len) // If start is beyond the string, return an empty string
	{
		free(s);
		new_str = malloc(sizeof(char));
		if (!new_str)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	new_str = malloc(sizeof(char) * (len - start + 1));
	if (!new_str)
		return (NULL);
	while (s[start + i] != 0)
	{
		new_str[i] = s[start + i];
		i ++;
	}
	new_str[i] = '\0';
	free(s);
	return (new_str);
}