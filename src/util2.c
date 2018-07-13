#include "../include/ft_ls.h"

size_t	malloc_str(va_list *args, size_t delimiter_size, char **whereto)
{
	char		*str;
	size_t		whole_size;
	size_t		i;

	i = 0;
	whole_size = 0;
	while ((str = va_arg(*args, char *)))
	{
		whole_size += ft_strlen(str);
		i++;
	}
	whole_size += delimiter_size * (i - 1);
	*whereto = ft_strnew(whole_size + 1);
	va_end(*args);
	return (whole_size + 1);
}

char	*strings_join(char *delimiter, ...)
{
	va_list		args;
	va_list		copy;
	size_t		size;
	char		*joined;
	char		*str;

	va_start(args, delimiter);
	va_copy(copy, args);
	size = malloc_str(&copy, ft_strlen(delimiter), &joined);
	while ((str = va_arg(args, char *)))
	{
		if (ft_strlen(str) == 0)
			continue ;
		ft_strlcat(joined, str, size);
		if (ft_strlcat(joined, delimiter, size) > size)
			break ;
	}
	va_end(args);
	return (joined);
}
