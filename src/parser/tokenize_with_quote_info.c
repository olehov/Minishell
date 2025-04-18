/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_with_quote_info.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:16:31 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 03:28:44 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_parser.h"

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
		if ((input[ctx->i] == '\'' || input[ctx->i] == '"'))
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
		reset_quote_state_set_token(&tokens[ctx.j++], &ctx);
	tokens[ctx.j].value = NULL;
	return (tokens);
}
