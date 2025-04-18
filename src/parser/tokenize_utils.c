/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:18 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 06:16:11 by ogrativ          ###   ########.fr       */
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
