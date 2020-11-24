/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:20:41 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/25 00:14:52 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		check_error(int fd, char **line)
{
	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (0);
	return (1);
}

int		lst_create_front(t_line **lst, int fd)
{
	t_line *new;

	new = (t_line*)malloc(sizeof(t_line));
	if (!new)
		return (0);
	new->content = 0;
	new->fnb = fd;
	new->next = *lst;
	*lst = new;
	return (1);
}

int		lst_del_srch(t_line **lst, int fd)
{
	t_line	*pop;
	t_line	*prev;

	if (!*lst)
		return (0);
	pop = *lst;
	prev = 0;
	while (pop->fnb != fd)
	{
		if (!pop->next)
			break ;
		prev = pop;
		pop = pop->next;
	}
	if (prev)
		prev->next = pop->next;
	else
		*lst = pop->next;
	if (pop->content)
		free(pop->content);
	free(pop);
	return (0);
}

t_line		*lst_elem_srch(t_line **lst, int fd)
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
		if (!(lst_create_front(lst, fd)))
			return (0);
		return (*lst);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_line	*lst_file = 0;
	t_line			*wip;
	char			buffer[BUFFER_SIZE + 1];
	int				rd;
	int				keepgoing;

	rd = 1;
	if (!(wip = lst_elem_srch(&lst_file, fd)) || !check_error(fd, line))
		return (-1);
	while (getnl(wip->content) == -1 && (rd = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rd] = '\0';
		rd = clean_join(&(wip->content), buffer) ? 1 : -1;
	}
	if (rd == -1)
		return (-1);
	if (!(wip->content))
	{
		keepgoing = 0;
		*line = ft_strdup("");
	}
	else if ((keepgoing = get_first_line(line, &(wip->content))) == -1)
		return (-1);
	return (!rd && !keepgoing) ? lst_del_srch(&lst_file, fd) : 1;
}
