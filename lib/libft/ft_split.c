/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzahir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:05:38 by aezzahir          #+#    #+#             */
/*   Updated: 2023/11/13 18:31:09 by aezzahir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_vstrlcpy(char *start, const char *end)
{
	int		len;
	char	*word;
	int		i;

	len = end - start;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = *start;
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static int	is_separator(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

static int	count_words(const char *str, char charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && is_separator(*str, charset))
			str++;
		if (*str && !is_separator(*str, charset))
		{
			count++;
			while (*str && !is_separator(*str, charset))
				str++;
		}
	}
	return (count);
}

static char	**ft_free(char ***result, int i)
{
	while (i >= 0)
	{
		free((*result)[i]);
		i--;
	}
	free(*result);
	return (NULL);
}

char	**ft_split(const char *str, char charset)
{
	char	**result;
	int		i;

	if (!str)
		return (NULL);
	result = (char **)malloc((count_words(str, charset) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (!is_separator(*str, charset))
		{
			result[i] = (char *)str;
			while (*str && !is_separator(*str, charset))
				str++;
			result[i] = ft_vstrlcpy(result[i], str);
			if (!result[i++])
				return (ft_free(&result, i - 2));
		}
		else
			str++;
	}
	result[i] = NULL;
	return (result);
}
