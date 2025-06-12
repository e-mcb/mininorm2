/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:29:32 by mzutter           #+#    #+#             */
/*   Updated: 2025/06/12 23:47:30 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lexer.h"

char	*handle_heredoc(t_token *token, int rank)
{
	char	*finale;
	char	*tmp;
	char	*line;

	finale = NULL;
	tmp = NULL;
	line = NULL;
	while (1)
	{
		write(1,  ">", 1);
		if (tmp)
			free (tmp);
		line = get_next_line(0);
		if ((token->value == "" && line[0] == '\n')
			|| ft_strncmp(line, token->value, ft_strlen(token->value) == 0))
		{
			free (line);
			break;
		}
		finale = ft_strjoin(line, finale);
		free (line);
		tmp = finale;
	}
	create_heredoc(rank, finale);
}

void	create_heredoc(int rank, char *str)
{
	char	*nbr;
	char	*filename;
	int		fd;
	
	nbr = ft_itoa(rank);
	filename = ft_strjoin("heredoc", nbr);
	if (!filename)
		return (NULL);
	free (nbr);
	fd = open(filename, O_CREAT, O_TRUNC);
	free (filename);
	ft_putstr_fd(str, fd);
	close (fd);
}

typedef struct s_redir
{
	char			*in;
	char			*out;
	t_token_type	type;
	bool			is_amb_redir;
	int				fd;
	bool			quoted_lim;
} t_redir;
