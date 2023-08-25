/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaba-qu <leonel.sabaquezada@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:51:54 by lsaba-qu          #+#    #+#             */
/*   Updated: 2023/08/25 11:30:06 by lsaba-qu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_matching_quotes(char *str, char quote)
{
	char *start = str;
	char *end = str + strlen(str) - 1;	
	while (*start == quote && *end == quote) {
	    start++;
	    end--;
	}
	size_t len = end - start + 1;
	char *trimmed = malloc(len + 1);
	ft_strncpy(trimmed, start, len);
	trimmed[len] = '\0';	
	return trimmed;
}


#include <stdio.h>
#include <string.h>

void trim_first_quote(char *command) {
    char *start = command;

    // Find the first quote or double quote
    while (*start && *start != '\'' && *start != '\"') {
        start++;
    }

    // If a quote is found, adjust the string
    if (*start == '\'' || *start == '\"') {
        char *end = start;

        // Find the matching quote or double quote
        while (*end && *end != *start) {
            end++;
        }

        // If a matching quote or double quote is found, adjust the string
        if (*end == *start) {
            while (*end) {
                *end = *(end + 1);
                end++;
            }
        }
    }
}