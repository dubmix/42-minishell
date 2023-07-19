#ifndef MINISHELL_H
    #define MINISHELL_H

    # include <stdlib.h>
    # include <stdio.h>
    # include <readline/readline.h>
    # include <readline/history.h>
    # include "libft/libft.h"
    # include <string.h>
    # include <unistd.h>
    # include <sys/types.h>
    # include <sys/wait.h>
    # include <fcntl.h>
    # include <limits.h>

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
    int index;
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
    t_token *tok_lst;
    t_env   *env_lst;
    char **envp_copy; // export function recre2er la char ** // do we really need something else than the path
    int size_arr_var;
    int redir_in;
    int redir_out;
    int heredoc;
    int append;
    char **redir_in_arr;
    char **redir_out_arr;
    char **heredoc_arr;
    char **append_arr;
    int pipe_number;
    int number_token;
} t_shell;


/* main.c */
int minishell_start(char **envp);

/* lexer_utils.c */
void    print_list(t_env *env); // print the envp
void    print_list_tok(t_token *tok); // print the token list
void    free_arr(char **arr); // free any arrays 
int	special_char(int c);

/* lexer_token.c */
void add_stack_back_tok(t_token **tok_lst, t_token *new);
void new_token(t_token **tokens, char *command, int nb, enum e_type type);
int new_token_var_words(t_token **tokens, char *string, int i, int nb_token);
int new_token_quote(t_token **tokens, char *string, int i, int nb_token);
t_token *tokenization(t_shell *shell);

/* lexer_envp.c */

char **string_variables(t_shell *cmd, t_token *var);
void double_quote_env(t_shell *cmd, t_token *var);
void expand_var(t_shell *cmd);
void look_into_envir(t_shell *cmd, t_token *var);
char *look_into_envir_quote(t_shell *cmd, char *variable);

/* lexer_envp2.c */
int length_arr_var(char **arr_var, t_shell *cmd);
int length_string_without_var(char *string);
void add_stack_back_env(t_env **env_lst, t_env *new);
void new_node_env(t_env **env_list, char **string);
t_env *init_envp(char **envp, t_shell *cmd);


/* libft */
int	countsubstr(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*checksub(void);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);

/*parser1.c*/
void    parser(t_shell *cmd);
void    triage_cmd_redir(t_shell *cmd);
void    deleteNode(t_token **head, t_token *nodeToDelete);
void    triage_space(t_shell *cmd);

/*parser_single_command.c*/
void   single_command(t_shell *cmd);

/*src/builtin*/
void    echo(char **args);
int     env(t_shell *cmd);
int     pwd(void);

/* TO DO 
error handling, usually I put error in the printf statement 
free all the struct for each new prompt
handle ?* in the expander
handle history
*/

#endif