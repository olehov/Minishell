/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:18:18 by ogrativ           #+#    #+#             */
/*   Updated: 2025/04/18 01:02:59 by ogrativ          ###   ########.fr       */
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

char	*append_part(char *accum, char *part)
{
	char	*tmp;
	char	*joined;

	tmp = NULL;
	joined = NULL;
	if (accum)
	{
		tmp = ft_strdup(accum);
		free(accum);
		accum = NULL;
		joined = ft_strjoin(tmp, part);
		free(tmp);
	}
	else
		joined = ft_strdup(part);
	return (joined);
}

void	handle_quote(char *input, t_tokenizer_ctx *ctx, t_minish *msh)
{
	int		start;
	char	*part;
	char	quote;

	(void)msh;
	quote = input[ctx->i];
	ctx->quote_char = quote;
	ctx->in_quotes = 1;
	ctx->i++;
	start = ctx->i;
	while (input[ctx->i])
	{
		if (input[ctx->i] == quote)
			break ;
		ctx->i++;
	}
	part = ft_substr(input, start, ctx->i - start);
	ctx->accum = append_part(ctx->accum, part);
	free(part);
	if (input[ctx->i] == quote)
		ctx->i++;
}


// void	handle_quote(char *input, t_tokenizer_ctx *ctx, t_minish *msh)
// {
// 	int		start;
// 	char	*part;
// 	char	quote;

// 	(void)msh;
// 	quote = input[ctx->i];
// 	ctx->quote_char = quote;
// 	ctx->in_quotes = 1;
// 	start = ctx->i;
// 	ctx->i++;
// 	while (input[ctx->i] && input[ctx->i] != quote)
// 		ctx->i++;
// 	if (input[ctx->i] == quote)
// 		ctx->i++;
// 	part = ft_substr(input, start, ctx->i - start);
// 	ctx->accum = append_part(ctx->accum, part);
// 	free(part);
// }


// void	handle_quote(char *input, t_tokenizer_ctx *ctx, t_minish *msh)
// {
// 	int		start;
// 	char	*part;
// 	char	quote;

// 	(void)msh;
// 	start = ctx->i;
// 	quote = input[ctx->i++];
// 	ctx->quote_char = quote;
// 	ctx->in_quotes = 1;
// 	while (input[ctx->i] && input[ctx->i] != quote)
// 		ctx->i++;
// 	part = ft_substr(input, start, ctx->i - start);
// 	ctx->accum = append_part(ctx->accum, part);
// 	free(part);
// 	if (input[ctx->i] == quote)
// 		ctx->i++;
// }

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
	ctx->skip_next_token_quote_handling = 1;
	return (1);
}
