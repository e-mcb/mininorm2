/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 21:27:35 by mzutter           #+#    #+#             */
/*   Updated: 2025/05/18 14:16:37 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/lexer.h"

//gives the prompt back to 
//the user and sends the input back to the main
char	*prompt(t_shell *shell)
{
	char	*input;

	input = readline("minishell>");
	if (input == NULL)
	{
		ft_putstr_fd("Goodbye\n", 2);
		ft_exit(NULL, shell);
	}
	if (input[0] != '\0')
		add_history(input);
	if (ft_has_invalid_quotes(input))
	{
		ft_putstr_fd(OPEN_QUOTES, 2);
		free(input);
		return (NULL);
	}
	return (input);
}
