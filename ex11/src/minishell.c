#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>	
#include <dirent.h>
#include <fcntl.h>	
#include "../include/linked_list.h"
#include "../include/hash.h"

#define BUILTIN_COMMANDS 5	

char PWD[1024];
char PATH[1024];	
char  *builtin[] = {"exit", "ls", "echo", "export", "env"};


node_t *exp_lst; 
hashtable_t  *exp_tbl;

int pshl_exit(char ** args)
{
        return 0;
}

int pshl_env (char ** args)
{
        node_t *tmp = exp_lst;
        while( tmp != NULL)
             {
                 printf("%s: %s\n", tmp->data, hash_get(exp_tbl, tmp->data));
	             tmp = tmp->next;
             }
}

char *checkfirstsymb(char * str) 
{
	    for (int i = 0; i <= strlen(str); i++)
		    str[i] = str[i + 1];
	    return str;
}
int pshl_ls(char **args)
{
        struct dirent *Dirent;
        DIR *Dir;
        if (args[1])
         {
             Dir = opendir(args[1]);
             if (Dir == NULL)
               {
                  printf ("Cannot open directory '%s'\n", args[1]);
                  return 1;
               }
         }
        else
                Dir = opendir(".");
        while ((Dirent = readdir(Dir)) != NULL)
                printf ("%s ", Dirent->d_name);
                closedir (Dir);
                printf("\n");
        return 1;
}

int pshl_echo(char ** args)
{
	    int i = 1;
	    while (1)
         {
		        if (args[i] == NULL)
		        break;
		        if (args[i][0] == '$')
		            printf("%s ", hash_get(exp_tbl, checkfirstsymb(args[i])));
		        else printf("%s ", args[i]);
		            i++;
        }
	    printf("\n");
}

int pshl_export (char ** args)
{
        char *token;
        char s[2] = "=";
        token = strtok(args[1], s);
        if (exp_lst == NULL && exp_tbl == NULL)
         {
	        exp_lst = list_create(token);
	        exp_tbl = hash_create(18);
         }
        else list_push(exp_lst, token);
            char *tmp = token;
            token = strtok(NULL, s);
            hash_set(exp_tbl, tmp, token);
}

int (* builtin_function[]) (char **) = {
	    &pshl_exit,
	    &pshl_ls,
        &pshl_echo,
        &pshl_export,
        &pshl_env
};

char ** spliting(char * command)
{
        int position = 0;
        int no_of_tokens = 64;
        char ** tokens = malloc(sizeof(char *) * no_of_tokens);
        char delim[2] = " ";
        char * token = strtok(command, delim);
        while (token != NULL)
          {
            tokens[position] = token;
            position++;
            token = strtok(NULL, delim);
          }
        tokens[position] = NULL;
        return tokens;
}

char * readingcomand(void)
{
        int position = 0;
        int buf_size = 1024;
        char * command = (char *)malloc(sizeof(char) * 1024);
        char c;
        c = getchar();
        while (c != EOF && c != '\n')
         {
            command[position] = c;
            if (position >= buf_size)
              {    
                buf_size += 64;
                command = realloc(command, buf_size);
              }
            position++;
            c = getchar();
         }
        command[position] = '\0';
        return command;
}

int start(char ** args)
{
        pid_t pid, wpid;
        int status;
        pid = fork();
        if (pid == 0) 
          {
        if (execvp(args[0], args) == -1)
            perror("minishell");
            exit(EXIT_FAILURE);
          }
        else if (pid < 0) 
            perror("minishell");
        else  do 
            wpid = waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
        return 1;
}


int pshl_execute(char **args)
{
        if (args[0] == NULL)
            return 1;
        for (int i = 0; i < 4; i++) 
        if (strcmp(args[0], builtin[i]) == 0) 
        return (*builtin_function[i])(args);
        return start(args);
}

void signalHandler(int sign)
{
        if (sign == SIGINT)
          {
            puts("");
            write(1, "$_>", 3);
            signal(SIGINT, signalHandler);
          }
}

void pshl_loop(void)
{
        char * command_line;
        char ** arguments;
        int	status = 1;
        while (status)
         {
            printf("$_> ");
            signal(SIGINT, signalHandler);
            command_line = readingcomand();
		    if ( strcmp(command_line, "") == 0 )
		        continue;
                arguments = spliting(command_line);
                status = pshl_execute(arguments);
         }
}

    
int main(int argc, char ** argv)
{
	    pshl_loop();
        return 0;
}

