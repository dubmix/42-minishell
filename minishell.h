#ifndef MINISHELL_H
    #define MINISHELL_H

# include <stdlib.h>
# include <signal.h>
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
# include <sys/ioctl.h>
//# include <linux/limits.h> to put again
# include <termios.h>

# define READLINE_MSG "\033[1;32m\U0001F308 minishell> \033[0m"
# define EXIT_MSG "\033[1;35mexit \U0001F496\033[0m\n"
# define HEREDOC_MSG "\033[1;36m\U0001F984 heredoc> \033[0m"

extern int g_xcode;

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
    int     index;
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
    int index;
    struct s_single_cmd *next;
} t_single_cmd;

typedef struct s_shell
{
    char *line;
    t_token *tok_lst;
    t_env   *env_lst;
    t_single_cmd *cmd_lst;
    char **envp_copy;
    int     size_arr_var;
    char **heredoc_arr;
    char *heredoc_string;
    int     nb_of_heredocs;
    int     nb_of_pipes;
    int     nb_of_tokens;
    int     *words_per_pipe;
    int	    *pid;
    char *oldpwd;
    int     tok_alloc;
    int     cmd_alloc;
    int     env_alloc;
    int     words_per_pipe_alloc;
    int     pid_alloc;
} t_shell;


/*debugging*/
void print_chararr(char **envp);

/* minishell.c */
void	init_shell(t_shell *cmd);
int     minishell_start_null(t_shell *cmd);
int     minishell_start(t_shell *cmd);
t_shell	*main_bis(t_shell *cmd);

/* minishell_utils.c */
void	clear_line_space(t_shell *cmd);

/////////////////////////////////// LEXER //////////////////////////////////

/*lexer_init.c*/
t_env *init_envp(char **envp, t_shell *cmd);
void add_stack_back_env(t_env **env_lst, t_env *new);
void	new_node_env(t_shell *cmd, t_env **env_list, char **string, char *full_string);

/* lexer_expand_var_utils.c */
void expand_var(t_shell *cmd);
void	look_into_envir(t_shell *cmd, t_token *var);
char	*look_into_envir_quote(t_shell *cmd, char *string);
char *look_into_envir_quote_sub(char *string);

/* lexer_expand_var.c */
char	**string_variables(t_shell *cmd, t_token *var);
char	**string_variables_bis(t_shell *cmd, char *command,
		char **arr_string, int i);
void	double_quote_env(t_shell *cmd, t_token *var);
char	*double_quote_env_bis(char *command, char *new_string, 
		char **arr_var, int i);
int	double_quote_env_bis_sub(char *command, int i);
void	look_into_envir_sub(char **string, t_token *var, t_env *tmp);
int		string_variables_tri(char *command, int i);
int	string_variables_bis_bis(t_shell *cmd, char *command, int i, char **arr_string);

/* lexer_utils.c */
void    print_list(t_env *env);
void    print_list_tok(t_token *tok);
int         special_char(int c);
int         length_arr_var(char **arr_var, t_shell *cmd);
int         length_string_without_var(char *string);

/* lexer_token.c */
int new_token_var_words(t_token **tokens, char *string, int i, int nb_token);
int new_token_quote(t_token **tokens, char *string, int i, int nb_token);
t_token	*tokenization_bis(t_shell *cmd, int *i, t_token *tok_lst, int nb_token);
t_token	*tokenization_simple_char(t_shell *cmd, int i, t_token *tok_lst, int nb_token);
t_token	*tokenization_special_char(t_shell *cmd, int *i, t_token *tok_lst, int nb_token);
t_token *token_loop(t_shell *cmd, int i, int nb_token, t_token *tok_lst);


/* lexer_token_utils.c */
t_token	*tokenization(t_shell *cmd);
int	tokenization_sub(t_shell *cmd, int i, t_token *tok_lst, int nb_token);
void add_stack_back_tok(t_token **tok_lst, t_token *new);
void new_token(t_token **tokens, char *command, int nb, enum e_type type);

/////////////////////////////////// PARSER //////////////////////////////////

/*parser_main.c*/
int    parser(t_shell *cmd);
int	error_syntax(t_shell *cmd);
int	test_tok_lst(t_shell *cmd);
void	space_commands(t_shell *cmd);

/*parser_main_utilsc*/
void	number_heredocs(t_shell *cmd);
void init_words_per_pipe(t_shell *cmd);
void	number_words_per_pipe(t_shell *cmd);

/*parser_triage.c*/
void	triage_space_bis(t_shell *cmd, t_token **temp, 
		t_token *node_to_delete, int state);
void    triage_space(t_shell *cmd);
void	triage_space_redir_pipe(t_shell *cmd);
void	triage_quotes(t_shell *cmd);
void	triage_quotes_bis(t_token **temp, char **cmd_splitted);

/*parser_cmd_lst.c*/
t_single_cmd    *triage_cmd_redir(t_shell *cmd);
void init_node_cmd(t_single_cmd **new, t_shell *cmd, int index);
t_token	*new_node_cmd(t_single_cmd **cmd_lst, int index, t_token *temp, t_shell *cmd);
void	new_node_cmd_sub(t_single_cmd *new, int i, int index);
void	add_stack_back_cmd(t_single_cmd **cmd_lst, t_single_cmd *new);
int new_node_word(t_token *temp, t_single_cmd *new, int i);

/*parser_redir.c*/
int     handle_redir_in(int fd, t_single_cmd *new, t_token *temp);
void	handle_redir_in_out(t_single_cmd *new, t_token *temp);
int     handle_redir_in_out_sub(t_single_cmd *new, t_token *temp, int fd);

/*parser_utils.c*/
void    delete_node_tok(t_token **head, t_token *nodeToDelete);
void	adjust_number(t_shell *cmd);
void	print_list_commands(t_single_cmd *cmd, t_shell *shell);

/////////////////////////////////// EXECUTOR //////////////////////////////////

/* executor.c */
int pre_executor(t_shell *cmd);
int exec_single_command(t_shell *cmd);
int    exec_single_command_sub(t_shell *cmd);
int	exec_single_command_sub_sub(t_shell *cmd);
int exec_command(t_shell *cmd);

/* single_command.c */
char	**get_path(char **envp);
char	*check_access(char **envp, char **command);
char *check_acc_sub(char **path_arr, char **cmd, char *path_cmd, char *tmp);

/* single_command_utils.c */
int	is_builtins(char *string);
int   single_command(t_shell *cmd);
void	single_command_sub(t_shell *cmd, char *path, t_single_cmd *temp);
void	single_command_sub_sub(t_shell *cmd, char *path, t_single_cmd *temp);
void	single_command_error(char *str, t_single_cmd *temp);

/* redirections.c */
int	redir_error(char *str);
int	check_redirections(t_shell *cmd);
int exec_heredoc(t_shell *cmd);
int exec_outfile(t_shell *cmd);
int exec_infile(char *file);

/* piped_command.c */
int exec_piped_command(t_shell *cmd);
int   exec_piped_command_sub(t_shell *cmd, int pipefd[], int fd, int i);
int ft_fork(t_shell *cmd, int pipefd[2], int fd, int i);
void dup_cmd(t_shell *cmd, int pipefd[2], int fd);
int pipe_wait(t_shell *cmd);

/* heredoc.c */
void	grab_heredoc(t_shell *cmd);
char	*grab_hd_sub(char *l_ipt, char *fir_l, char *fin_l, t_shell *c);
void	grab_hd_sub_sub(char *l_ipt, char *fir_l, char *temp);
char	**string_variables_heredoc(t_shell *cmd, char *string);
char **string_var_hd_sub(t_shell *c, char *str, char **arr_str, int start);
int	grab_heredoc_tri(int i, char *l_ipt);

/* heredoc_utils.c */
char *double_quote_env_heredoc(t_shell *cmd, char *string);

/////////////////////////////////// BUILTINS //////////////////////////////////

/* cd */
void	find_old_pwd(t_shell *cmd);
int     cd(t_shell *cmd);
int	cd_tilde_folder(t_shell *cmd, char *string);
char    *get_path_cd(t_shell *cmd, char *str);
int	    go_to_path(t_shell *cmd, char *str);

/* cd_utils */
void   add_path_to_env(t_shell *cmd);
int	add_path_to_env_sub(t_env *tmp, int check);
int	add_oldpath_to_env_sub(t_shell *cmd, t_env *tmp, int check);

/* exit */
int	    exxit(t_shell *cmd);
void    get_exit_code(char **command);
int     is_only_digits(char *str);

/* echo */
void    echo(char **args, t_shell *cmd);
int	echo_sub(char **cmd, int i, int check);
int find_new_line(char **cmd, int i);

/* env */
int     env(t_shell *cmd);

/* pwd */
int     pwd(void);

/* export.c */
int	export_variable(t_shell *cmd);
void	export_variable_bis(t_shell *cmd, char **command, int i, t_shell **tmp);
int	export(t_shell *cmd, char **command);
void	export_bis(char **command, t_shell **tmp, int i, t_shell *cmd);
void	unset_if_export(t_shell *cmd, char *command);

/* export_utils.c */
int	export_error(char *str);
int	ft_lstsize_env(t_env *lst);
int check_valid_id(char c);
char	**new_line(char *line);
char	**var_arr(t_shell *cmd, char *command);

/* export_utils_ext.c */
char	*look_into_envir_export(t_shell *cmd, char *string);
void	update_envp_copy(t_shell *cmd);
int var_exists(t_env *env, char *str);
int	check_param(char *str);
int	ft_findchar(char *str, char c);

/* export_env.c */
int     print_sorted_env(t_env **env_lst);
void	sort_env(t_env **env_lst);
void	assign_back_to_zero(t_env **env_lst);
void	assign_index(t_env **env_lst, char *string, int i);
char *find_biggest(t_env **env_lst);

/* unset */
int unset(t_shell *cmd, char **command);
int	unset_error(char **command);
void	unset_message_error(char *command);
void unset_sub(t_shell *cmd, char **command);
void	delete_node_env(t_env **head, t_env *node_to_delete);

/////////////////////////////////// OTHERS //////////////////////////////////

/*signals*/
void init_signals();
void	sigint_heredoc(int sig);
void sigint_child(int sig);
void sigint_handler(int sig);
void sigquit_handler(int sig);

/* errors.c */
void    free_arr(char **arr);
void	free_all_inside_loop(t_shell *cmd);
void	free_all_exit(t_shell *cmd);
void	ft_error(t_shell *cmd, char *string, int exit_code);
void	free_tok_lst(t_token **tok_lst);

/* errors_utils.c */
void	free_cmd_lst(t_single_cmd **cmd_lst);
void	free_env_lst(t_env **env_lst);
void	delete_node_cmd(t_single_cmd **head, t_single_cmd *node_to_delete);
int cd_error(char *str);

/* libft */
int	countsubstr(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*checksub(void);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);

#endif
