/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:53:24 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/22 20:43:02 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_lstcreate_front(t_line **lst, int fd)
{
	t_line	*new;

	new = (t_line*)malloc(sizeof(t_line));
	if (!new)
		return (0);
	new->content = 0;
	new->fnb = fd;
	new->next = *lst;
	*lst = new;
	return (1);
}

int		ft_emptystr(char **str)
{
	*str = (char*)malloc(sizeof(char));
	*str[0] = '\0';
	return (-1);
}

int		ft_dellst(t_line **lst)
{
	t_line	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = 0;
	return (0);
}

t_line	*ft_find_fd(int fd, t_line **lst)
{
	t_line	*cursor;

	cursor = *lst;
	while (cursor)
	{
		if (fd == cursor->fnb)
			return (cursor);
		cursor = cursor->next;
	}
	if (!cursor)
	{
		if (!(ft_lstcreate_front(lst, fd)))
			return (0);
		return (*lst);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_line	*lst_lines = 0;
	t_line			*wip_line;
	char			buffer[BUFFER_SIZE + 1];
	int				rd;
	int				keepgoing;

	rd = 0;
	if ((wip_line = ft_find_fd(fd, &lst_lines)) == 0 ||
			fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!ft_strnl(wip_line->content))
	{
		while ((rd = read(fd, buffer, BUFFER_SIZE)) > 0)
		{
			buffer[rd] = '\0';
			ft_strcat(&(wip_line->content), buffer);
			if (ft_strnl(buffer))
				break ;
		}
		if (rd == -1 || (!(wip_line->content) && rd == 0))
			return (ft_emptystr(line));
	}
	keepgoing = 0;
	*line = ft_firstline(&(wip_line->content), &keepgoing);
	return (!rd && !keepgoing) ? ft_dellst(&lst_lines) : 1;
}
