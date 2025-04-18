/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:18 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 04:52:14 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"

void	set_token(t_token *token, t_tokenizer_ctx *ctx)
{
	if (token->value != NULL)
		free(token->value);
	token->value = ft_strdup(ctx->accum);
	token->in_quotes = ctx->in_quotes;
	token->quote_char = ctx->quote_char;
}

void	reset_quote_state(t_tokenizer_ctx *ctx)
{
	if (ctx->accum != NULL)
		free(ctx->accum);
	ctx->accum = NULL;
	ctx->in_quotes = 0;
	ctx->quote_char = 0;
}

char	*append_part(char *accum, char *part, t_minish *msh)
{
	char	*tmp;
	char	*joined;
	char	*processed;
	char	*cleaned;
	bool	is_removed;

	is_removed = 0;
	tmp = NULL;
	joined = NULL;
	processed = NULL;
	if (part[0] == '\'')
	{
		is_removed = 1;
		// processed = process_env(part, msh->env, msh, '\'');
		// processed = remove_quotes(part);
		processed = remove_outer_quotes(part);
	}
	else
		processed = process_env(part, msh->env, msh, 0);
	if (processed && !is_removed)
	{
		cleaned = remove_quotes(processed);
		free(processed);
		processed = cleaned;
	}
	if (accum)
	{
		tmp = ft_strdup(accum);
		free(accum);
		accum = NULL;
		joined = ft_strjoin(tmp, processed);
		free(tmp);
	}
	else
		joined = ft_strdup(processed);
	free(processed);
	return (joined);
}


// char	*append_part(char *accum, char *part)
// {
// 	char	*tmp;
// 	char	*joined;

// 	tmp = NULL;
// 	joined = NULL;
// 	if (accum)
// 	{
// 		tmp = ft_strdup(accum);
// 		free(accum);
// 		accum = NULL;
// 		joined = ft_strjoin(tmp, part);
// 		free(tmp);
// 	}
// 	else
// 		joined = ft_strdup(part);
// 	return (joined);
// }

void	handle_quote(char *input, t_tokenizer_ctx *ctx, t_minish *msh)
{
	int		start;
	char	*part;
	char	quote;

	quote = input[ctx->i];
	ctx->quote_char = quote;
	ctx->in_quotes = 1;
	start = ctx->i;
	ctx->i++;
	while (input[ctx->i])
	{
		if (input[ctx->i] == quote)
			break ;
		ctx->i++;
	}
	if (input[ctx->i] == quote)
		ctx->i++;
	part = ft_substr(input, start, ctx->i - start);
	ctx->accum = append_part(ctx->accum, part, msh);
	free(part);
}

int	handle_double_redirect(char *input, t_token *tokens, t_tokenizer_ctx *ctx)
{
	t_tokenizer_ctx	tmp;

	if (ctx->accum)
	{
		set_token(&tokens[ctx->j++], ctx);
		reset_quote_state(ctx);
	}
	tmp.accum = ft_substr(input, ctx->i, 2);
	tmp.in_quotes = 0;
	tmp.quote_char = 0;
	set_token(&tokens[ctx->j++], &tmp);
	if (tmp.accum != NULL)
		free(tmp.accum);
	ctx->i += 2;
	return (1);
}
