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

static int exit_code;

enum e_type
{
	WORD,		//0   any word inside quotes as well
	S_QUOTE,	//1
	D_QUOTE,	//2
	SPA,	// Space
	VARIABLE,		//4 $USER
	PIPE,		//5   |
	REDIRECT_OUTPUT,//6  >
	REDIRECT_INPUT,//7 <
    APPEND, // 8  >>
    HEREDOC, // 9  <<
};

typedef struct s_token
{
    char *command;
    int index;
    int state; // 0 if nowhere, 1 if in double quote, 2 if in single quote
    enum e_type type;
    struct s_token *next;
}   t_token;

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
}   t_env;

typedef struct s_single_cmd
{
    char **command;
    int redir_in;
    char *redir_in_str;
    int redir_out;
    char *redir_out_str;
    int append;
    char *append_str;
    int index; // is the index of the pipe basically
    struct s_single_cmd *next;
} t_single_cmd;

typedef struct s_shell
{
    char *line;
    t_token *tok_lst;
    t_env   *env_lst;
    t_single_cmd *cmd_lst;
    char **envp_copy; // export function recre2er la char ** // do we really need something else than the path
    int size_arr_var;
    char **heredoc_arr; // is not in the single_cmd struc because it is not depending on the pipes
    int nb_of_heredocs;
    int nb_of_pipes;
    int nb_of_tokens;
    int *words_per_pipe;
    int	*pid;
} t_shell;


/* main.c */
int minishell_start(char **envp);
void	init_shell(t_shell *cmd);

/////////////////////////////////// LEXER //////////////////////////////////

/*lexer_init.c*/
t_env *init_envp(char **envp, t_shell *cmd);
void add_stack_back_env(t_env **env_lst, t_env *new);
void new_node_env(t_env **env_list, char **string);

/* lexer_expand_var.c */
void expand_var(t_shell *cmd);
void	look_into_envir(t_shell *cmd, t_token *var);
char	**string_variables(t_shell *cmd, t_token *var);
void	double_quote_env(t_shell *cmd, t_token *var);
char	*look_into_envir_quote(t_shell *cmd, char *string);

/* lexer_utils.c */
void    print_list(t_env *env); // print the envp
void    print_list_tok(t_token *tok); // print the token list
int         special_char(int c);
int         length_arr_var(char **arr_var, t_shell *cmd);
int         length_string_without_var(char *string);

/* lexer_token.c */
void add_stack_back_tok(t_token **tok_lst, t_token *new);
void new_token(t_token **tokens, char *command, int nb, enum e_type type);
int new_token_var_words(t_token **tokens, char *string, int i, int nb_token);
int new_token_quote(t_token **tokens, char *string, int i, int nb_token);
t_token *tokenization(t_shell *shell);

/////////////////////////////////// PARSER //////////////////////////////////

/*parser_main.c*/
void    parser(t_shell *cmd);
void	number_words_per_pipe(t_shell *cmd);

/*parser_triage.c*/
void    triage_space(t_shell *cmd);
void	triage_quotes(t_shell *cmd);

/*parser_cmd_lst.c*/
t_single_cmd    *triage_cmd_redir(t_shell *cmd);
void init_node_cmd(t_single_cmd **new, t_shell *cmd, int index);
t_token	*new_node_cmd(t_single_cmd **cmd_lst, int index, t_token *temp, t_shell *cmd);
void	add_stack_back_cmd(t_single_cmd **cmd_lst, t_single_cmd *new);

/*parser_redir.c*/
void	handle_redir_in(t_single_cmd *new, t_token *temp);
void	handle_redir_in_out(t_single_cmd *new, t_token *temp);

/*parser_utils.c*/
void    delete_node(t_token **head, t_token *nodeToDelete);
void	adjust_number(t_shell *cmd);
void	print_list_commands(t_single_cmd *cmd, t_shell *shell);

/////////////////////////////////// EXECUTOR //////////////////////////////////

/*single_command.c*/
int   single_command(t_shell *cmd);
char	**get_path(char **envp);
char	*check_access(char **envp, char **cmd); //, int *fds);
void exec_single_command(t_shell *cmd);
int pre_executor(t_shell *cmd);

/////////////////////////////////// BUILTINS //////////////////////////////////

/*builtin*/
void    echo(char **args);
int     env(t_shell *cmd);
int     pwd(void);

/////////////////////////////////// OTHERS //////////////////////////////////

/*errors.c*/
void    free_arr(char **arr); // free any arrays

/* libft */
int	countsubstr(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*checksub(void);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);

/* TO DO 
error handling, usually I put error in the printf statement 
free all the struct for each new prompt
handle ?* in the expander
handle history
*/

#endif
