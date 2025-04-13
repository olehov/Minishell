/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_with_quote_info.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:16:31 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/13 13:45:48 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_single_redirect(char *input,
	t_token *tokens, t_tokenizer_ctx *ctx)
{
	t_tokenizer_ctx	tmp;

	if (ctx->accum)
	{
		set_token(&tokens[ctx->j++], ctx);
		reset_quote_state(ctx);
	}
	tmp.accum = ft_substr(input, ctx->i, 1);
	tmp.in_quotes = 0;
	tmp.quote_char = 0;
	set_token(&tokens[ctx->j++], &tmp);
	ft_safe_free(tmp.accum);
	ctx->i++;
	return (1);
}

static int	handle_word(char *input, int *i, char **accum)
{
	int		start;
	char	*part;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '<'
		&& input[*i] != '>' && input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	part = ft_substr(input, start, *i - start);
	*accum = append_part(*accum, part);
	free(part);
	return (1);
}

static void	handle_next_token_literal(char *input, t_tokenizer_ctx *ctx)
{
	char	*part;
	size_t	start;
	char	quote;

	start = ctx->i;
	if (input[ctx->i] == '\'' || input[ctx->i] == '"')
	{
		quote = input[ctx->i++];
		while (input[ctx->i] && input[ctx->i] != quote)
			ctx->i++;
		if (input[ctx->i] == quote)
			ctx->i++;
	}
	else
	{
		while (input[ctx->i] && !ft_isspace(input[ctx->i])
			&& input[ctx->i] != '<' && input[ctx->i] != '>'
			&& input[ctx->i] != '|' && input[ctx->i] != '&'
			&& input[ctx->i] != ';')
			ctx->i++;
	}
	part = ft_substr(input, start, ctx->i - start);
	ctx->accum = append_part(ctx->accum, part);
	free(part);
}

static void	process_tokenization_loop(char *input,
	t_token *tokens, t_tokenizer_ctx *ctx)
{
	while (input[ctx->i])
	{
		while (input[ctx->i] && ft_isspace(input[ctx->i]))
			ctx->i++;
		if (!input[ctx->i])
			break ;
		if (ctx->skip_next_token_quote_handling)
		{
			while (input[ctx->i] && ft_isspace(input[ctx->i]))
				ctx->i++;
			handle_next_token_literal(input, ctx);
			ctx->skip_next_token_quote_handling = 0;
		}
		else if (input[ctx->i] == '\'' || input[ctx->i] == '"')
			handle_quote(input, ctx);
		else if ((input[ctx->i] == '<' || input[ctx->i] == '>')
			&& input[ctx->i + 1] == input[ctx->i])
			handle_double_redirect(input, tokens, ctx);
		else if (input[ctx->i] == '<' || input[ctx->i] == '>')
			handle_single_redirect(input, tokens, ctx);
		else
			handle_word(input, &ctx->i, &ctx->accum);
		if (!input[ctx->i] || ft_isspace(input[ctx->i])
			|| input[ctx->i] == '<' || input[ctx->i] == '>')
		{
			if (ctx->accum)
			{
				set_token(&tokens[ctx->j++], ctx);
				reset_quote_state(ctx);
			}
		}
	}
	if (ctx->accum)
		set_token(&tokens[ctx->j++], ctx);
}

t_token	*tokenize_with_quote_info(char *input)
{
	t_token			*tokens;
	t_tokenizer_ctx	ctx;

	ft_bzero(&ctx, sizeof(t_tokenizer_ctx));
	tokens = ft_calloc(sizeof(t_token), (ft_strlen(input) + 2));
	if (!tokens)
		return (NULL);
	// ctx.i = 0;
	// ctx.j = 0;
	// ctx.accum = NULL;
	// ctx.in_quotes = 0;
	// ctx.quote_char = 0;
	process_tokenization_loop(input, tokens, &ctx);
	tokens[ctx.j].value = NULL;
	return (tokens);
}
