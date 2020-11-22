/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:57:22 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/21 22:17:44 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_line
{
	int				fnb;
	char			*content;
	struct s_line	*next;
}					t_line;

int					get_next_line(int fd, char **line);
void				ft_strcat(char **s1, char *s2);
char				*ft_firstline(char **str, int *keepgoing);
int					ft_strnl(char *str);

#endif
