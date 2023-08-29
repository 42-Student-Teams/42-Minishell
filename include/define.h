/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:59:58 by bverdeci          #+#    #+#             */
/*   Updated: 2023/08/29 19:17:07 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define MININT	-2147483648
# define MAXINT	2147483647

# define SUCCESS 0
# define ERROR 1

# define DEFAULT_PATH "/usr/bin:/bin"

/*
	E_END,			\n or #
	E_PIPE,			|
	E_INFILE,		<
	E_OUTFILE,		>
	E_HEREDOC,		<<
	E_APPEND,		>>
 */
enum e_token_type
{
	E_END,
	E_PIPE,
	E_INFILE,
	E_OUTFILE,
	E_HEREDOC,
	E_APPEND,
	E_WORD,
};

#endif