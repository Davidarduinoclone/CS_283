#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <ctype.h>

#include "dshlib.h"


/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */
int build_cmd_list(char *cmd_line, command_list_t *clist)
{
    char *token;
    char *cmd;
  
    clist->num = 0;
    if (strlen(cmd_line) >= SH_CMD_MAX) {
        return ERR_CMD_OR_ARGS_TOO_BIG;
    }

    token = strtok(cmd_line, PIPE_STRING);
    //token = strtok_r(cmd_line,PIPE_STRING, &end_str);
    while (token != NULL){
        clist->num += 1; 
        
        // remove leading white space 
        while (isspace((unsigned char)*token)) {
            token++;
        }
        // remove tailing white space 
        cmd = token + strlen(token) - 1;
        while (cmd > token && isspace((unsigned char)*cmd)) cmd--;
        cmd[1] = '\0';

        if (clist->num > CMD_MAX) {
            return ERR_TOO_MANY_COMMANDS;
        }

        char *space_pos = strchr(token, ' ');
        if (space_pos != NULL) {
            size_t exec = space_pos - token;  // Length of the first part
            strncpy(clist->commands[clist->num - 1].exe, token, exec);
            clist->commands[clist->num - 1].exe[exec] = '\0'; 
    
            // Copy the second part
            strcpy(clist->commands[clist->num - 1].args, space_pos + 1);  
        } else {
            // If there is no space, copy the entire string to the first part
            strcpy(clist->commands[clist->num - 1].exe, token);
            clist->commands[clist->num - 1].args[0] = '\0';  
        }


        
            
  
     
        token = strtok(NULL, PIPE_STRING );
        //token = strtok_r(NULL,PIPE_STRING, &end_str);

    }
    return OK;
   
}