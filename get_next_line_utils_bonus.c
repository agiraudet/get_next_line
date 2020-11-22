/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:20:29 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/21 21:23:35 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_strnl(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (*str++ == '\n')
			return (1);
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*ret;
	size_t	i;

	ret = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ret)
		return (0);
	i = 0;
	while (*s)
		ret[i++] = *s++;
	ret[i] = '\0';
	return (ret);
}

void	ft_strcat(char **s1, char *s2)
{
	char	*ret;
	size_t	i;

	ret = (char*)malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (!ret)
	{
		if (*s1)
			free(*s1);
		return ;
	}
	i = 0;
	while (*s1 && (*s1)[i])
	{
		ret[i] = (*s1)[i];
		i++;
	}
	while (*s2)
		ret[i++] = *s2++;
	ret[i] = '\0';
	if (*s1)
		free(*s1);
	*s1 = ret;
}

char	*ft_firstline(char **str, int *keepgoing)
{
	char	*line;
	char	*newdata;
	size_t	i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if (!(line = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
	{
		line[i] = (*str)[i];
		i++;
	}
	line[i] = '\0';
	if ((*str)[i] == '\n')
	{
		i++;
		*keepgoing = 1;
	}
	newdata = ft_strdup(*str + i);
	free(*str);
	*str = newdata;
	return (line);
}
