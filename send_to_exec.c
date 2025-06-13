#include "headers/lexer.h"

typedef struct s_exec
{
	char **args;
	int fd_in;
	int fd_out;
	t_exec *next;
} t_exec;

t_exec *init_exec(t_exec *exec)
{
	exec = malloc(sizeof(t_exec));
	if (exec == NULL)
		return NULL;
	exec->args = NULL;
	exec->fd_in = -1;
	exec->fd_out = -1;
	exec->next = NULL;
	return (exec);
}

void free_exec(t_exec *exec)
{
	if (exec == NULL)
		return;
	if (exec->env != NULL)
		ft_free_str_array(exec->env);
	if (exec->args != NULL)
		ft_free_str_array(exec->args);
	free(exec);
}

void fill_struct(t_shell *shell, t_exec *exec)
{
	t_token	*tmp;
	int		capacity;
	int		count;

	capacity = 4;
	exec->args = malloc(sizeof(char *) * capacity);
	if (shell == NULL || exec == NULL)
		return ; //IDK
	tmp = shell->token;
	while (tmp)
	{
		if (is_redir(tmp->type))
		{
			if(tmp->type == IN)
				exec->fd_in = open(tmp->next->value, O_RDONLY);
			else if (tmp->type == OUT)
				exec->fd_out = open(tmp->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (tmp->type == APPEND)
				exec->fd_out = open(tmp->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (tmp->type == HDOC)
			{
				//revu le fonctionement des heredocs, à update en consequence	
																								  //A revoir en utilisant une structure exec avec un tableau pour chaque commande
			}
			else if (tmp->type == CMD || tmp->type == ARG)
			{
				if (count >= capacity)
				{
					capacity *= 2;
					exec->args = ft_realloc(exec->args, sizeof(char *) * capacity, sizeof(char *) * (capacity * 2));
				}
				exec->args[count] = ft_strdup(tmp->value);
				if (exec->args[count] == NULL)
				{
					// Handle memory allocation failure
					return;
				}
				count++;
			}
		}
	}
}

