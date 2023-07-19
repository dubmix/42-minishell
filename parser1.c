#include "minishell.h"

void    adjust_number(t_shell *cmd)
{
    t_token **temp = &(cmd->tok_lst);
    int i = 0;

    while (*temp != NULL)
    {
        (*temp)->index = i;
    temp = &((*temp)->next);
        i++;
    }
    cmd->number_token = i;
}

void   triage_quotes(t_shell *cmd)
{
    t_token **temp = &(cmd->tok_lst);
    char **cmd_splitted;

    while (*temp != NULL)
    {
        if ((*temp)->state == 1)
        {
            cmd_splitted = ft_split((*temp)->command, '\"');
            free((*temp)->command);
            (*temp)->command = ft_strdup(cmd_splitted[0]);
            free_arr(cmd_splitted);
        }
        else if ((*temp)->state == 2)
        {
            cmd_splitted = ft_split((*temp)->command, '\'');
            free((*temp)->command);
            (*temp)->command = ft_strdup(cmd_splitted[0]);
            free_arr(cmd_splitted);
        }
        temp = &((*temp)->next);
    }
}

void    parser(t_shell *cmd)
{
    triage_quotes(cmd);
    triage_space(cmd);
    adjust_number(cmd);
    triage_cmd_redir(cmd);
    // if (cmd->pipe_number != 0)
    //     printf("IL Y A DES PIPES, ON FERA CA PLUS TARD");
    // else
    //     single_command(cmd);
    printf("\nPRINTING TOKENS \n");
    print_list_tok(cmd->tok_lst);
    printf("\nEND TOKENS \n");

    // if (cmd->redir_in != 0)
    //     printf("IN : NB REDIR %d\n ARR 1 %s\n ARR 2 %s \n", cmd->redir_in, cmd->redir_in_arr[0], cmd->redir_in_arr[1]);
    // if (cmd->redir_out != 0)
    //     printf("OUT : NB REDIR %d\n ARR 1 %s\n ARR 2 %s \n", cmd->redir_out, cmd->redir_out_arr[0], cmd->redir_out_arr[1]);
    // if (cmd->heredoc != 0)
    //     printf("NB HEREDOC %d\n ARR 1 %s\n ARR 2 %s \n", cmd->heredoc, cmd->heredoc_arr[0], cmd->heredoc_arr[1]);
    // if (cmd->append != 0)
    //     printf("NB APPEND %d\n ARR 1 %s\n ARR 2 %s \n", cmd->append, cmd->append_arr[0], cmd->append_arr[1]);
    
    /*
    part 1 : check if there is a pipe
    part 2 : form the command in a new list 
    part 3 : put all the redirections in a separate struct
    part 4 : handle two cases : pipes or single command
    part 5 : differentiate if the command are builtin or not
    */
}

void    triage_space(t_shell *cmd)
{
    t_token **temp = &(cmd->tok_lst);
    t_token *nodeToDelete;

    nodeToDelete = NULL;
    int state = 0;
    while (*temp != NULL)
    {
        if ((*temp)->type == 0)
        {
            state = 0;
            temp = &((*temp)->next);
        }
        else if ((*temp)->type == 3 && (state == 1 || state == 2))
        {
            nodeToDelete = *temp;
            deleteNode(&(cmd->tok_lst), nodeToDelete);
            state = 2;
        }
        else
        {
            state = 1;
            temp = &((*temp)->next);
        }
    }
}

char *copy_redir(t_shell *cmd, int nb_node)
{
    int i;
    i = 0;
    t_token *temp = cmd->tok_lst;
    while (temp != NULL)
    {
        while (i < nb_node)
        {
            temp = temp->next;
            i++;
        }
        if (temp->type == 0)
            break;
        temp = temp->next;
    }
    return (temp->command);
}

void    triage_cmd_redir(t_shell *cmd)
{
    t_token *temp = cmd->tok_lst;
    int redir_in = 0;
    int redir_out = 0;
    int heredoc = 0;
    int append = 0;
    // should I malloc only in the number are different from 0 ? then different function for it, could put the end with 0 also in it with a different status kinda
    cmd->redir_in_arr = (char **)malloc(sizeof(char *) * cmd->redir_in + 1);
    cmd->redir_out_arr = (char **)malloc(sizeof(char *) * cmd->redir_out + 1);
    cmd->heredoc_arr = (char **)malloc(sizeof(char *) * cmd->heredoc + 1);
    cmd->append_arr = (char **)malloc(sizeof(char *) * cmd->append + 1);
    if (!cmd->redir_in_arr || !cmd->redir_out_arr || !cmd->heredoc_arr || !cmd->append_arr)
        return ;
    while (temp != NULL)
    {
        if (temp->type == REDIRECT_IN)
        {
            cmd->redir_in_arr[redir_in] = ft_strdup(copy_redir(cmd, temp->index));
            redir_in++;
        }
        else if (temp->type == REDIRECT_OUT)
        {
            cmd->redir_out_arr[redir_out] = ft_strdup(copy_redir(cmd, temp->index));
            redir_out++;
        }
        else if (temp->type == REDIR_IN_DOUBLE)
        {
            cmd->heredoc_arr[heredoc] = ft_strdup(copy_redir(cmd, temp->index));
            heredoc++;
        }
        else if (temp->type == REDIR_OUT_DOUBLE)
        {
            cmd->append_arr[append] = ft_strdup(copy_redir(cmd, temp->index));
            append++;
        }
        temp = temp->next;
    }
    cmd->redir_in_arr[redir_in] = 0;
    cmd->redir_out_arr[redir_out] = 0;
    cmd->heredoc_arr[heredoc] = 0;
    cmd->append_arr[append] = 0;
}

void    deleteNode(t_token **head, t_token *nodeToDelete) 
{
    t_token *prevNode;

    prevNode = NULL;
    if (*head == NULL || nodeToDelete == NULL)
        return ;
    if (*head == nodeToDelete) 
        *head = nodeToDelete->next;
    else 
    {
        prevNode = *head;
        while (prevNode->next != NULL && prevNode->next != nodeToDelete) 
            prevNode = prevNode->next;
        if (prevNode->next == nodeToDelete) 
            prevNode->next = nodeToDelete->next;
        else
            return ;
    }
    free(nodeToDelete->command);
    free(nodeToDelete);
    return ;
}