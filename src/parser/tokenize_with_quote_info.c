/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_with_quote_info.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:16:31 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/16 12:13:26 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
#include "../../include/ft_parser.h"

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

static void	skip_space(char	*input, t_tokenizer_ctx *ctx)
{
	while (input[ctx->i] && ft_isspace(input[ctx->i]))
		ctx->i++;
}

static void	reset_quote_state_set_token(t_token *tokens,
	t_tokenizer_ctx *ctx)
{
	if (ctx->accum)
	{
		set_token(&tokens[ctx->j++], ctx);
		reset_quote_state(ctx);
	}
}

static void	process_tokenization_loop(char *input,
	t_token *tokens, t_tokenizer_ctx *ctx, t_minish *msh)
{
	while (input[ctx->i])
	{
		skip_space(input, ctx);
		if (!input[ctx->i])
			break ;
		if (ctx->skip_next_token_quote_handling)
		{
			skip_space(input, ctx);
			handle_next_token_literal(input, ctx);
			ctx->skip_next_token_quote_handling = 0;
		}
		else if ((input[ctx->i] == '\'' || input[ctx->i] == '"'))
			handle_quote(input, ctx, msh);
		else if ((input[ctx->i] == '<' || input[ctx->i] == '>')
			&& input[ctx->i + 1] == input[ctx->i])
			handle_double_redirect(input, tokens, ctx);
		else if (input[ctx->i] == '<' || input[ctx->i] == '>')
			handle_single_redirect(input, tokens, ctx);
		else
			handle_word(input, &ctx->i, &ctx->accum, msh);
		if (!input[ctx->i] || ft_isspace(input[ctx->i])
			|| input[ctx->i] == '<' || input[ctx->i] == '>')
			reset_quote_state_set_token(tokens, ctx);
	}
}

t_token	*tokenize_with_quote_info(char *input, t_minish *msh)
{
	t_token			*tokens;
	t_tokenizer_ctx	ctx;

	ft_bzero(&ctx, sizeof(t_tokenizer_ctx));
	tokens = ft_calloc(sizeof(t_token), (ft_strlen(input) + 2));
	if (!tokens)
		return (NULL);
	process_tokenization_loop(input, tokens, &ctx, msh);
	if (ctx.accum)
		set_token(&tokens[ctx.j++], &ctx);
	tokens[ctx.j].value = NULL;
	return (tokens);
}
