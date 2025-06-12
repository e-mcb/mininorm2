/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzutter <mzutter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:32:53 by mzutter           #+#    #+#             */
/*   Updated: 2025/06/13 00:13:13 by mzutter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

t_token	*new_token_append(t_token *head, char *str, t_token_type type)
{
	t_token	*new_node;
	t_token	*last;

	new_node = create_token(str);
	if (!new_node)
		return (NULL);
	new_node->type = type;
	if (!head)
		return (new_node);
	last = head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (head);
}

void amb_redir(char *str)
{
	char	*msg;

	msg = ft_strjoin(AMB_REDIR, str);
	ft_putstr_fd(msg, 2);
	free(msg);
}

static void init_vars(int *i, t_token **last, t_token **first)
{
	*i = 0;
	*last = NULL;
	*first = NULL;
}

t_token	*insert_new_nodes(t_shell *shell, t_token *prev, t_token *current,
	char **splitted)
{
	int		i;
	t_token	*new_node;
	t_token	*last;
	t_token	*first;

	init_vars(&i, &last, &first);
	while (splitted[i])
	{
		new_node = new_token_append(first, splitted[i], current->type);
		if (!new_node)
			return (free_list(&first), NULL);
		if (!first)
			first = new_node;
		else
			last->next = new_node;
		last = new_node;
		i++;
	}
	if (first)
		first->next = current->next;
	if (prev)
		prev->next = first;
	else
		shell->token = first;
	return (free(current->value), free(current), last);
}

void	ft_print_array(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	return ;
}

void	cleanup_token(char **expanded, char ***splitted)
{
	if (*splitted)
	{
		ft_free_str_array(*splitted);
		*splitted = NULL;
	}
	if (*expanded)
	{
		free(*expanded);
		*expanded = NULL;
	}
}


int	process_token(t_shell *shell, t_token **tmp, t_token **prev,
			char **expanded, char ***splitted)
{
	if (!ft_strchr((*tmp)->value, '$'))
		return 0;
	*expanded = join_chars(split_and_expand((*tmp)->value));
	if (*expanded && (*expanded)[0] != 0)
	{
		*splitted = split_keep_separators(*expanded, is_whitespace);
		ft_print_array(*splitted);
		if ((*tmp)->type == FILEN && count_strings(*splitted) > 1)
		{
			amb_redir(*expanded);
			return (free(*expanded), ft_free_str_array(*splitted), 1);
		}
		*tmp = insert_new_nodes(shell, *prev, *tmp, *splitted);
		if (ft_strchr((*tmp)->value, '$'))
		{
			*prev = *tmp;
			*tmp = (*tmp)->next;
		}
	}
	else
		(*tmp)->value[0] = 0;
	return (cleanup_token(expanded, splitted), 1);
}


void	expand(t_shell *shell)
{
	t_token *tmp;
	t_token *prev;
	char *expanded;
	char **splitted;
	int skip;

	// CHECK A FAIRE ICI J'AI FAIT DE LA :ERDE

	tmp = shell->token;
	prev = NULL;
	expanded = NULL;
	splitted = NULL;
	skip = 0;

	while (tmp)
	{
		skip = process_token(shell, &tmp, &prev, &expanded, &splitted);
		if (skip)
			continue;
		prev = tmp;
		tmp = tmp->next;
	}
}


// void *ft_realloc_array(void *ptr, size_t old_count, size_t new_count, size_t elem_size)
// {
//     void *new_ptr = malloc(new_count * elem_size);
//     if (!new_ptr)
//         return (NULL);
//     if (ptr)
//     {
//         ft_memcpy(new_ptr, ptr, old_count * elem_size);
//         free(ptr);
//     }
//     return (new_ptr);
// }


// char **split_keep_separators(const char *s, bool (*is_sep)(char))
// {
//     char    **res;
//     size_t  i;
//     size_t  start;
//     size_t  count;
//     size_t  capacity;
//     char    *chunk;

// 	i = 0;
// 	start = 0;
// 	count = 0;
// 	capacity = 4;
//     res = malloc(sizeof(char *) * capacity);
//     if (!res)
//         return (NULL);
//     while (s[i])
//     {
//         while (s[i] && is_sep(s[i]))
//             i++;
//         while (s[i] && !is_sep(s[i]))
//             i++;
//         while (s[i] && is_sep(s[i]))
//             i++;
//         chunk = ft_substr(s, start, i - start);
//         if (!chunk)
//             return (NULL);
//         if (count + 1 >= capacity)
//         {
//             capacity *= 2;
//             char **new_res = malloc(sizeof(char *) * capacity);
//             if (!new_res)
//                 return NULL;
//             ft_memcpy(new_res, res, sizeof(char *) * count);
//             free(res);
//             res = new_res;
//         }
//         res[count++] = chunk;
//         start = i;
//     }
//     if (res)
//         res[count] = NULL;
//     return (res);
// }


