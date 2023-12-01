/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pretoken.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolkova <tbolkova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:11:56 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/12 17:22:09 by tbolkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* function() allocates memory for input string
checks if there is an invalid char inside the input string -> lexer_utils
checks for quotes:
		if '$something -> set flag_no_expand to true(1) : SUBJECT requirement 
else copies the input string into the allocated array pretoken.
pretoken = allocated logical part of input string
quote_pretoken = part of input string inside squotes and dquotes
if a quote_pretoken was created and isn't empty -> ft_join_pretoken()
and return it as pretoken */
int	ft_c_pretoken(t_data *data, char *s, int i, int x)
{
	char	*quote_pretoken;
	char	*pretoken;
	bool	flag_no_expand;

	quote_pretoken = NULL;
	pretoken = ft_calloc(ft_strlen(s) + 1, 1);
	while (1)
	{
		if (ft_invalid_char(s, i))
			break ;
		else if (s[i] == '\"' || s[i] == '\'')
		{
			flag_no_expand = ft_check_sqdollar(s, i);
			quote_pretoken = quoted_pretoken(s, i);
			i += ft_qpretoken_len(quote_pretoken);
			if (quote_pretoken != NULL)
				pretoken = ft_join_pretoken(&pretoken, &quote_pretoken);
			x = ft_strlen(pretoken) - 1;
		}
		else
			pretoken[x] = s[i];
		increase_counters(&i, &x);
	}
	ft_create_pretoken_node(data, x, pretoken, flag_no_expand);
	return (i - 1);
}

int	ft_create_pretoken(t_data *data, char *str, int i)
{
	int	x;

	x = 0;
	return (ft_c_pretoken(data, str, i, x));
}

/* initializes a "quoted pretoken" -> part of a string inside quotes
error check: returns (NULL) if immidiately followed
by a quote -> (empty string)
or if quote_len() returned an error.
formerly "quote_chunk2" */
char	*quoted_pretoken(char *input, int i)
{
	char	quote;
	int		quote_ptlen;

	quote = input[i];
	quote_ptlen = quote_len(input, i + 1, quote);
	if (input[i + 1] == quote || quote_ptlen == -1)
		return (NULL);
	return (init_string(input, i, quote_ptlen));
}

/* joins the content of the quoted pretoken with
the remainder of the pretoken string
and dcreates a copy of it
frees the old pretoken, the tmp variable and quoted pretoken,
returns the copy of the joined string */
char	*ft_join_pretoken(char **pretoken, char **quote_pretoken)
{
	char	*tmp;

	tmp = ft_strjoin(*pretoken, *quote_pretoken);
	free(*pretoken);
	*pretoken = ft_strdup(tmp);
	free(tmp);
	free(*quote_pretoken);
	tmp = NULL;
	quote_pretoken = NULL;
	return (*pretoken);
}

/*
add new lexer node pretoken.
A chunk of a string which will need to get identified in the parser. 
If this pretoken is in squotes it gets the type NO_EXPAND assigned,
since meta chars will not get expanded in squotes.
*/
void	ft_create_pretoken_node(t_data *data, int x, char *pretoken, \
		bool flag_no_expand)
{
	t_lexer	*tmp;

	if (x > 0)
	{
		pretoken[x] = '\0';
		ft_add_lexer_node(data, pretoken);
		if (flag_no_expand == true)
		{
			tmp = ft_lstlast_lexer(data->tok_list);
			tmp->type = NO_EXPAND;
		}
		free(pretoken);
	}
}
