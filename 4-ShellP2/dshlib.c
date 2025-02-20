#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "dshlib.h"


int build_cmd_list(char *cmd_line, cmd_buff_t *cmd_buff)
{
    char *token;
    char *cmd = malloc(SH_CMD_MAX);
    char *md = malloc(SH_CMD_MAX);
    int number = 0;
    token = cmd_line;
    //remove white space 
    // remove leading white space 
    while (isspace((unsigned char)*token)) {
        token++;
    }
    // remove tailing white space 
    cmd = token + strlen(token) - 1;
    while (cmd > token && isspace((unsigned char)*cmd)) {
        cmd--;
    }
    cmd[1] = '\0';
    
    bool in_quote_mode = false;
    bool in_black_mode = false; 
    int index = 0; 
    for (size_t i =0; i < strlen(token); i++ ){
        if (in_quote_mode){
            if(token[i] == '"'){
                in_quote_mode = !in_quote_mode;
                md[index] = token[i];
                index += 1;
                in_black_mode = false; 

            }else{
                md[index] = token[i];
                index += 1;
            }
            
        }else{
            if(token[i] == '"'){
                in_quote_mode = !in_quote_mode;
                md[index] = token[i];
                index += 1; 
            }else {
                if (token[i] == SPACE_CHAR){
                    if (!in_black_mode){
                        in_black_mode = true; 
                        md[index] = ' ';
                        index += 1; 
                    }           
                }else{
                    in_black_mode = false;
                    md[index] = token[i];
                    index += 1; 
                }
            }
        }
    }
   
    //printf("%s\n", md);

    cmd_buff->_cmd_buffer = malloc(SH_CMD_MAX);
    strcpy(cmd_buff->_cmd_buffer, md);

    int start = 0;
    in_quote_mode = false;
    in_black_mode = false;
    bool just_exit = false;
    cmd_buff->argc = 0;
    
    for (size_t i = 0; i < strlen(md); i++){
        if (in_quote_mode){
            if(md[i] == '"'){
                in_quote_mode = !in_quote_mode;
                cmd_buff->argv[cmd_buff->argc] = malloc(SH_CMD_MAX);
                strncpy(cmd_buff->argv[cmd_buff->argc], md+start+1, i-start-1);
                //cmd_buff->argv[cmd_buff->argc][i-start] = '\0';
                start = i + 1;
                cmd_buff->argc += 1;
                in_black_mode = false;
                just_exit = true;

            }else{
              
            }
            
        }else{
            if(md[i] == '"'){
                in_quote_mode = !in_quote_mode;
               
            }else {
                if (md[i] == SPACE_CHAR){
                    in_black_mode = true;
                    if (!just_exit){

                        
                        cmd_buff->argv[cmd_buff->argc] = malloc(SH_CMD_MAX);
                        strncpy(cmd_buff->argv[cmd_buff->argc], md+start, i-start);
                        cmd_buff->argv[cmd_buff->argc][i-start] = '\0';
                        start = i + 1;
                        cmd_buff->argc += 1;
                        
                    }
                    start = i + 1;
                             
                }
            }
        }
    }
    if (in_black_mode || cmd_buff->argc == 0){
        cmd_buff->argv[cmd_buff->argc] = malloc(SH_CMD_MAX);
        strncpy(cmd_buff->argv[cmd_buff->argc], md+start, strlen(md)-start);
        cmd_buff->argv[cmd_buff->argc][ strlen(md)-start] = '\0';
        cmd_buff->argc += 1; 
    
    }
    cmd_buff->argv[cmd_buff->argc] = NULL; 
    
    
    return OK;
    //return 1; 
}

/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
 * 
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 * 
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 * 
 *   Also, use the constants in the dshlib.h in this code.  
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */
int exec_local_cmd_loop()
{
    char *cmd_buff = malloc(SH_CMD_MAX);
    int rc = 0;
    cmd_buff_t cmd;

    // TODO IMPLEMENT MAIN LOOP

    while(1){
        //cmd_buff_t cmd;
        int return_code;
        printf("%s", SH_PROMPT);
        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
            printf("\n");
            break;
        }
        //remove the trailing \n from cmd_buff
        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
    
        //IMPLEMENT THE REST OF THE REQUIREMENTS
        if(*cmd_buff == 0){
            printf(CMD_WARN_NO_CMD);
        }else{
            
            return_code = build_cmd_list(cmd_buff, &cmd);


            if (return_code == -2 ){
                printf( CMD_ERR_PIPE_LIMIT , CMD_MAX);
            }else if (return_code == 0){
                // exit 
                if (strcmp(cmd.argv[0], EXIT_CMD) == 0 ) {
                    free(cmd_buff); 
                    exit(0);
                }
                //dragon
                else if (strcmp(cmd.argv[0], "dragon") == 0 ) {
                    print_dragon();

                }
                else if (strcmp(cmd.argv[0], "cd") == 0){
                    //printf("%d\n", cmd.argc);
                    //printf("%s\n", cmd.argv[0]);
                    
                    if (cmd.argc == 2){
                        
                       
                        chdir(cmd.argv[1]);
                        //printf("%s\n", cmd.argv[0]);

                    }
                    
                }else{
                    pid_t pid = fork();
                    if (pid == 0) {
                        
                        
                        execvp(cmd.argv[0], cmd.argv);
                      
                        exit(EXIT_FAILURE);
                    } else if (pid > 0) {
                        wait(NULL);
                    } else {
                        perror("fork failed");
                    }
                    
                   
                }
            }else if (return_code == 1){
                printf("%s\n", cmd._cmd_buffer);

                for (int i =0; i < cmd.argc ; i++){
                    printf("%s\n", cmd.argv[i]);
                }
                if (cmd.argv[cmd.argc]== NULL){
                    printf("the last is NULL\n");
                }
                printf("%d",strcmp(cmd.argv[0], "dragon"));

            }

        



        }

                
        
        
    }

    // TODO IMPLEMENT parsing input to cmd_buff_t *cmd_buff

    // TODO IMPLEMENT if built-in command, execute builtin logic for exit, cd (extra credit: dragon)
    // the cd command should chdir to the provided directory; if no directory is provided, do nothing

    // TODO IMPLEMENT if not built-in command, fork/exec as an external command
    // for example, if the user input is "ls -l", you would fork/exec the command "ls" with the arg "-l"

    return OK;
}
