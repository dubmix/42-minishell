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

extern int g_exit_code;

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
    char *full_string;
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
    char **heredoc_arr;
    char *heredoc_string; // is not in the single_cmd struc because it is not depending on the pipes
    int nb_of_heredocs;
    int nb_of_pipes;
    int nb_of_tokens;
    int *words_per_pipe;
    int	*pid;
    int exit_flag;
    char *oldpwd;
} t_shell;


/* main.c */
int minishell_start(char **envp);
void	init_shell(t_shell *cmd);

/////////////////////////////////// LEXER //////////////////////////////////

/*lexer_init.c*/
t_env *init_envp(char **envp, t_shell *cmd);
void add_stack_back_env(t_env **env_lst, t_env *new);
void new_node_env(t_env **env_list, char **string, char *full_string);

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
void    delete_node_tok(t_token **head, t_token *nodeToDelete);
void	adjust_number(t_shell *cmd);
void	print_list_commands(t_single_cmd *cmd, t_shell *shell);

/////////////////////////////////// EXECUTOR //////////////////////////////////

/*single_command.c*/
int   single_command(t_shell *cmd);
char	**get_path(char **envp);
char	*check_access(char **envp, char **cmd); //, int *fds);
void exec_single_command(t_shell *cmd);
int pre_executor(t_shell *cmd);
int exec_piped_command(t_shell *cmd);
int ft_fork(t_shell *cmd, int pipefd[2], int fd, int i);
void dup_cmd(t_shell *cmd, int pipefd[2], int fd);
int exec_command(t_shell *cmd);
int check_redirections(t_shell *cmd);
int exec_infile(char *file);
int exec_outfile(t_shell *cmd);
int pipe_wait(int *pid, int nb_of_pipes);
int exec_heredoc(t_shell *cmd);

/*heredoc.c*/
void	grab_heredoc(t_shell *cmd);
char	**string_variables_heredoc(t_shell *cmd, char *string);
char *double_quote_env_heredoc(t_shell *cmd, char *string);

/////////////////////////////////// BUILTINS //////////////////////////////////

/*cd*/
int     cd(t_shell *cmd);
int	    go_to_path(t_shell *cmd, char *str);
char    *get_path_cd(t_shell *cmd, char *str);
void    add_path_to_env(t_shell *cmd);
/*exit*/
int	    exxit(t_shell *cmd);
void    get_exit_code(void);
int     is_only_digits(char *str);
/*echo*/
void    echo(char **args);
/*env*/
int     env(t_shell *cmd);
/*pwd*/
int     pwd(void);
/*export*/
int	export(t_shell *cmd);
int	export_error(char *str);
int check_valid_id(char c);
int	check_param(char *str);
int	ft_findchar(char *str, char c);
int var_exists(t_env *env, char *str);
int	ft_lstsize_test(t_env *lst);
/*unset*/
int unset(t_shell *cmd);
void	delete_node_env(t_env **head, t_env *nodeToDelete);

/////////////////////////////////// OTHERS //////////////////////////////////

/*errors.c*/
void    free_arr(char **arr); // free any arrays
void	free_all(t_shell *cmd, int type);
void	free_tok_lst(t_token **tok_lst);
void	delete_node_cmd(t_single_cmd **head, t_single_cmd *nodeToDelete);
void	free_cmd_lst(t_single_cmd **cmd_lst);
void	free_env_lst(t_env **env_lst);
void free_shell(t_shell *cmd);
//void	free_arr_int(int *arr);

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
*/

#endif
