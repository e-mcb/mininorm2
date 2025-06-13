#include "headers/lexer.h"
#include "libft/libft.h"

bool is_redir(t_token_type type)
{
    return (type == IN || type == OUT || type == APPEND || type == HDOC);
}

void print_redir_error(int type)
{
    if (type == IN)
        ft_putstr_fd("syntax error near unexpected token '<'\n", 2);
    else if (type == OUT)
        ft_putstr_fd("syntax error near unexpected token '>'\n", 2);
    else if (type == APPEND)
        ft_putstr_fd("syntax error near unexpected token '>>'\n", 2);
}


 void is_logic_valid(t_shell *shell)
 {
 	t_token	*tmp;

 	tmp = shell->token;
	if (tmp->type == PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token |", 2);
		//ft_exit
	}
 	while (tmp)
 	{
 		if (is_redir(tmp->type && tmp->next == NULL) || is_redir(tmp->type)
			&& is_redir(tmp->next->type))
		{
			print_redir_error(tmp->next->type);
			//ft_exit(NULL, shell);
		}
		if (((is_redir(tmp->type) && tmp->next->type == PIPE))
			|| (tmp->type == PIPE && tmp->next->type == PIPE))
		{
			ft_putstr_fd("syntax error near unexpected token |", 2);
			//ft_exit
		}
 		tmp = tmp->next;
 	}
 }

void	ft_parsing(char *input, t_shell *shell)
{
	int	i;

	i = 0;
	whitespace_to_space(&input);
	shell->splitted = ft_split2(input, ' ');
	if (shell->splitted == NULL)
		ft_exit(NULL, shell);
	free (input);
	while (shell->splitted[i])
	{
		tokenizer(shell, i);
		i++;
	}
	ft_free_str_array(shell->splitted);
	refine_token_type(shell->token);
	expand(shell);
	printf("test");
	second_refine_token_type(shell->token);
	shell->splitted = NULL;
}

t_shell	*init_shell(t_shell *shell, char **envp)
{
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
		ft_exit(NULL, NULL);
	shell->env = NULL;
	shell->splitted = NULL;
	shell->token = NULL;
	shell->env = ft_strdup_array(envp);
	shell->exit_status = 0;
	if (shell->env == NULL)
		ft_exit(NULL, shell);
	return (shell);
}

int main(int argc, char **argv, char **envp)
{
	char *input;
	t_shell *shell;
	t_token	*tmp;

	(void)argc;
	(void)argv;
	shell = NULL;
	shell = init_shell(shell, envp);
	while (1)
	{
		input = prompt(shell);
		if (input == NULL)
			continue;
		ft_parsing(input, shell);
		tmp = shell->token;
		while (tmp)
		{
			printf("Token: %s   token type: %d\n", tmp->value, tmp->type);
			tmp = tmp->next;
		}
		free_list(&(shell->token));
	return (0);
	}
}

