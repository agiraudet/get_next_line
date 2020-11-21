/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:18:36 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/21 18:38:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_check_errors(int fd, char **line)
{
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (0);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*content = 0;
	char		*new;
	int			rd;
	int			keepgoing;
	char		buffer[BUFFER_SIZE + 1];

	if (!ft_check_errors(fd, line))
		return (-1);
	rd = 0;
	if (!ft_strnl(content))
	{
		while ((rd = read(fd, buffer, BUFFER_SIZE)) > 0)
		{
			buffer[rd] = '\0';
			new = ft_strcat(content, buffer);
			if (content)
				free(content);
			content = new;
			if (ft_strnl(buffer))
				break ;
		}
		if (rd == -1)
			return (-1);
	}
	keepgoing = 0;
	*line = ft_firstline(&content, &keepgoing);
	if (!rd && !keepgoing)
		return (0);
	return (1);
}
