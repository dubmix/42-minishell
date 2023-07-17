#ifndef MINISHELL_H
    #define MINISHELL_H

    # include <stdlib.h>
    # include <stdio.h>
    # include <readline/readline.h>
    # include <readline/history.h>
    # include "libft/libft.h"
    # include <string.h>
    # include <unistd.h>


enum e_type
{
	WORD,		//0   any word inside quotes as well
	S_QUOTE,	//1
	D_QUOTE,	//2
	SPA,	// Space
	VARIABLE,		//4 $USER
	PIPE,		//5   |
	REDIRECT_IN,//6  >
	REDIRECT_OUT,//7 <
    REDIR_IN_DOUBLE, // 8  >>
    REDIR_OUT_DOUBLE, // 9  <<
};

typedef struct s_token
{
    char *command;
    int nb;
    enum e_type type;
    struct s_token *next;
    int state; // 0 if nowhere, 1 if in double quote, 2 if in single quote
}   t_token;

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
}   t_env;

typedef struct s_shell
{
    char *line_command;
    int d_quote;
    int s_quote;
    t_token *tokens;
    t_env   *envir;
} t_shell;


/* main.c */
int minishell_start(char **envp);

/* lexer_utils.c */
void    print_list(t_env *env); // print the envp
void    print_list_tok(t_token **tok); // print the token list

/* lexer_token.c */
void add_stack_back_tok(t_token **tok_lst, t_token *new);
void new_token(t_token **tokens, char *command, int nb, enum e_type type);
int	special_char(int c);
int new_token_var_words(t_token **tokens, char *string, int i, int nb_token);
int new_token_quote(t_token **tokens, char *string, int i, int nb_token);
t_token *tokenization(t_shell *shell);

/* lexer_envp.c */
void add_stack_back_env(t_env **env_lst, t_env *new);
void new_node_env(t_env **env_list, char **string);
t_env *init_envp(char **envp);
void look_into_envir(t_shell *cmd, t_token *var);
void expand_var(t_shell *cmd);
char *look_into_envir_quote(t_shell *cmd, char *variable);



/* TO DO 
error handling, usually I put error in the printf statement 
free all the struct

*/

#endif