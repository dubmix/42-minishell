
#include "minishell.h"

void    print_list(t_env *env);

void add_stack_back_tok(t_token **tok_lst, t_token *new)
{
    t_token *tail;

    if (!new)
        return;
    if (!(*tok_lst))
    {
        *tok_lst = new;
        return;
    }
    tail = *tok_lst;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = new;
}

void add_stack_back_env(t_env **env_lst, t_env *new)
{
    t_env *tail;

    if (!new)
        return;
    if (!(*env_lst))
    {
        *env_lst = new;
        return;
    }
    tail = *env_lst;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = new;
}

void new_token(t_token **tokens, char *command, int nb, enum e_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->command = command;
    new->nb = nb;
    new->type = type;
	new->next = NULL;
    if (new->type == 2)
        new->state = 1;
    else if (new->type == 1)
        new->state = 2;
    else
        new->state = 0;
    add_stack_back_tok(tokens, new);
	return ;
}

int	special_char(int c)
{
	if (c == '|' || c == 34 || c == ' ' || c == '<' || c == '>' || c == 39)
        return (1);
	else
		return (0);
}

int new_token_var_words(t_token **tokens, char *string, int i, int nb_token)
{
    int start;
    start = i;
    char *var;
    while (special_char(string[i]) == 0 && string[i] != '\0')
        i++;
    var = ft_substr(string, start, i-start);
    if (string[start] == '$')
        new_token(tokens, var, nb_token, VARIABLE);
    else
        new_token(tokens, var, nb_token, WORD);
    return (i);
}

int new_token_quote(t_token **tokens, char *string, int i, int nb_token)
{
    int start;
    char *var;
    char c = string[i];
    
    start = i;
    i++;
    while (string[i] != '\0')
    {
        if (string[i] == c)
            break;
        i++;
    }
    var = ft_substr(string, start, i+1-start);
    if (string[i] == '\0' && string[i] != c)
        return(printf("error")); // inifinite loop - to be changed, saying that there is an incorrect number of quotes
    else if (c == 39)
        new_token(tokens, var, nb_token, S_QUOTE);
    else
        new_token(tokens, var, nb_token, D_QUOTE);
    return (i+1);
}

t_token *tokenization(t_shell *shell)
{
    //int start;
    int i;
    int nb_token;

    i = 0;
    //start = 0;
    nb_token = 0;
    t_token *tok_lst;
    tok_lst = NULL;
    while (shell->line_command[i] != '\0')
    {
        if (shell->line_command[i] == '|')
            new_token(&tok_lst, "|", nb_token, PIPE);
        else if (shell->line_command[i] == 39) // single quotes
            i = new_token_quote(&tok_lst, shell->line_command, i, nb_token) - 1;
        else if (shell->line_command[i] == 34) // double quotes
            i = new_token_quote(&tok_lst, shell->line_command, i, nb_token) - 1;
        else if (shell->line_command[i] == '>' && shell->line_command[i+1] != '>') 
            new_token(&tok_lst, ">", nb_token, REDIRECT_IN);
        else if (shell->line_command[i] == '<' && shell->line_command[i+1] != '<') 
            new_token(&tok_lst, "<", nb_token, REDIRECT_OUT);
        else if (shell->line_command[i] == '>' && shell->line_command[i+1] == '>') 
        {
            new_token(&tok_lst, ">>", nb_token, REDIR_IN_DOUBLE);
            i++;
        }
        else if (shell->line_command[i] == '<' && shell->line_command[i+1] == '<') 
        {
            new_token(&tok_lst, "<<", nb_token, REDIR_OUT_DOUBLE);
            i++;
        }    
        else if (shell->line_command[i] == ' ') //space
            new_token(&tok_lst, " ", nb_token, SPA);
        else if (shell->line_command[i] == '$')
            i = new_token_var_words(&tok_lst, shell->line_command, i, nb_token) - 1;
        else
            i = new_token_var_words(&tok_lst, shell->line_command, i, nb_token) - 1;
        i++;
        nb_token++;
    }
//    print_list(tok_lst);
    return (tok_lst);
}

void    print_list(t_env *env)
{
    t_env *tmp = env;
    while (tmp != NULL)
    {
//        printf("node #%d, cmd is %s, type is %d, state is %d\n", tmp->nb, tmp->command, tmp->type, tmp->state);
            printf("node is %s and value is %s\n", tmp->name, tmp->value);
            tmp = tmp->next;
    }
}


void new_node_env(t_env **env_list, char **string)
{
    t_env	*new;

    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return ;
    new->name = ft_strdup(string[0]);
    new->value = ft_strdup(string[1]);
    new->next = NULL;
    add_stack_back_env(env_list,new);
}

t_env *init_envp(char **envp)
{
    int i;
    int j;
    char **string;
    i = 0;
    t_env *envir;
    envir = NULL;
    while (envp[i] != NULL)
    {
        string = ft_split(envp[i], '=');
        new_node_env(&envir, string);
        j = 0;
        while(string[j] != NULL)
        {
            free(string[j]);
            j++;
        }
        i++;
    }
    return (envir);
}

void look_into_envir(t_shell *cmd, t_token *var)
{
    t_shell *tmp = cmd;
    char **string;
    int j = 0;
    string = ft_split(var->command, '$');
    while (tmp->envir != NULL)
    {
        if (ft_strncmp(string[0], tmp->envir->name, ft_strlen(var->command)) == 0)
        {
            free(var->command);
            var->command = ft_strdup(tmp->envir->value);
            break;
        }
        tmp->envir = tmp->envir->next;
    }
    while(string[j] != NULL)
    {
        free(string[j]);
        j++;
    }
    return ;
}


void expand_var(t_shell *cmd)
{
//    t_shell *tmp = cmd;
    while (cmd->tokens != NULL)
    {
        if (cmd->tokens->type == 4)
        {
//            printf("IN EXPAND VAR %s\n", tmp->tokens->command);
            look_into_envir(cmd, cmd->tokens);
        }
        cmd->tokens = cmd->tokens->next;
    }
}


void    print_list_tok(t_token *tok)
{
    t_token *tmp = tok;
    write(1,"NNN", 3);
    while (tmp != NULL)
    {
        printf("node is %s\n", tmp->command);
        tmp = tmp->next;
    }
}

int minishell_start(char **envp)
{
    (void)envp;
    t_shell *cmd;
    cmd = malloc(sizeof(t_shell));
    cmd->envir = init_envp(envp);
//    print_list(cmd->envir);
    while (1)
    {
        cmd->line_command = readline(">");
        cmd->tokens=tokenization(cmd);
        printf("IN MINISHELL START %s %d\n", cmd->tokens->command, cmd->tokens->type);
        expand_var(cmd);
//        printf("%s", cmd->tokens->command);
        print_list_tok(cmd->tokens);
    }
}

int main(int argc, char  **argv, char **envp)
{
    printf("%s",argv[0]);
    if (argc != 1)
        printf("Error, this program should not take any arguments");
    else
        minishell_start(envp);
    return (0);
}
