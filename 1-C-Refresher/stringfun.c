#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int);
//add additional prototypes here
int  reverse_string(char *, int);
int  word_print(char *, int);
int  word_replace(char *, int, int, int, char **);

int setup_buff(char *buff, char *user_str, int len){
    //TODO: #4:  Implement the setup buff as per the directions
    int blank = 0;
    int user_str_len = 0;
    int user_str_buff = 0; 
    while(user_str[user_str_buff] != 0){
        if (user_str_len > len){
            return -1;
        }
        // checks to space or tab and handles double spaces 
        if (user_str[user_str_buff] == 9 || user_str[user_str_buff] == 32){
            if (blank){
                // inserts blank space 
                blank = 0;
                buff[user_str_len] = 32;
                user_str_len++;
            }
        }else {
            // inserts string
            blank = 1; 
            buff[user_str_len] = user_str[user_str_buff];
            user_str_len++;
        }
        user_str_buff++;
    }
    // get ride of trailing blank space 
    if (buff[user_str_len -1] == 32){
        user_str_len = user_str_len -1;
    }
    // adds '.' to the end of string 
    memset(buff + user_str_len, '.', (len - user_str_len)*sizeof(char));
    return user_str_len;
    
}
void print_buff(char *buff, int len){
    printf("Buffer:  [");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar(']');
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}
// counts the number of words that are in the buffer string 
int count_words(char *buff,  int str_len){
    int blank = 1;
    int count = 0;
    for(int i = 0; i < str_len; i++){
        // looks for a blank space to count how many words 
        if(buff[i] != 32){
            if(blank){
                blank = 0;
                count++;
            }
        }else{
            blank = 1;
        }
    }
    return count;
}
 
//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

// this reverse the string in the buffer 
int reverse_string(char *buff, int str_len){
    char *temp = malloc(str_len);
    if (temp ==NULL){
        return -1;
    }
    // copies the user string from the buffer 
    memcpy(temp, buff, str_len);
    // reverse the string 
    for (int i =0; i < str_len; i++){
        buff[i] = temp[str_len -i -1];
    }
   
    free(temp);
    return 0;
}

// this prints the number of words and then the length of each word 
// if there are no words then it returns No Words!
int  word_print(char *buff, int str_len){
    int count = 0;
    int blank = 1;
    int word_count = 0;
    if (str_len > 0){
        printf("Word Print\n");
        printf("----------\n");
        for(int i = 0; i < str_len; i++){
            if(buff[i] != 32){
                if(blank){
                    blank = 0;
                    count++;
                    // prints the number of words
                    printf("%d. ", count );
                }
                // prints the string 
                printf("%c", buff[i]);
                word_count++;

            }else{
                if (blank == 0){
                    // the length fo the word 
                    printf("(%d)\n", word_count);
                    word_count =0; 
                }
                blank = 1;
            }
        }
        printf("(%d)\n\n", word_count);
        printf("Number of words returned: %d\n", count);
        
    }else{
        printf("No Words!\n");
    }
    return 0;
}


// this replaces the word in a buffer with a another word given by the user 
int  word_replace(char *buff, int str_len, int len, int argc, char *argv[]){
    
    if (argc != 5){
        return -1;
    }
    char *search = argv[3];
    char *replace = argv[4];
    int start = 0; 
    int end =-1; 
    int search_len = 0;
    int replace_len = 0; 
    // get the length of search string 
    while (search[search_len] != '\0'){
        search_len++;
    }
    // get the length of replace string 
    while (replace[replace_len] != '\0'){
        replace_len++;
    }
    
    for (int i = 0; i < str_len - search_len +1; i++){
        if(buff[i] == search[0]){
            int match = 1; 
            // finds the index of the start of the search string 
            start = i;
            for (int j = 0; j < search_len; j++){
                if(buff[i+j] != search[j]){
                    match = 0;
                }
            }
            // finds the index of the end of the search string 
            if(match){
                end = i + search_len - 1; 
                break;
            }

        }

    }
    
    if (end == -1){
        
        return -1;
    }
    // copies the string that comes after the search string in temp 
    int temp_size = str_len - (end +1);
    char *temp = malloc(temp_size);
   
    memcpy(temp, buff + end +1, temp_size);


    // replace the search string with the replace string 
    for (int i = 0; i < replace_len; i++) {
        buff[start +i ] = replace[i];
    }
    // puts the temp at the of the replacement string 
    memset(buff + start+ replace_len, '.', (len - (start+ replace_len))*sizeof(char));
    for (int i = 0; i < temp_size; i++) {
        if (len >= start+ replace_len +i){
            buff[start+ replace_len +i ] = temp[i];
        }
        
    }

    free(temp);
   
    return 0;


}


int main(int argc, char *argv[]){

    char *buff ;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    /* 
    The reason for this code is to make sure the user uses the program correctly 
    If arv[1] does not exist meaning that the user did pass in any arguments, then the program exit because argc < 2
    also it checks if the arv[1] is not '-' meaning the user is not using the program correctly then the program exits 
    */
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    // if the user does not give the proper input to the function then it displays the options then exits the program
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3
    buff = malloc(BUFFER_SZ);
    if (buff == NULL) { 
        exit(99);
    }



    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d\n", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d \n", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        case 'w':
            rc = word_print(buff, user_str_len);  
            if (rc < 0){
                printf("Error word print, rc = %d \n", rc);
                exit(2);
            }
       
            break;
        case 'r':
            rc = reverse_string(buff, user_str_len);  
            if (rc < 0){
                printf("Error  reverse string, rc = %d \n", rc);
                exit(2);
            }
          
            break;

        case 'x':
            rc = word_replace(buff, user_str_len, BUFFER_SZ, argc, argv);  
            
            if (rc < 0){
                printf("Error  reverse_string, rc = %d \n", rc);
                exit(2);
            }
          
            break;

        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          PLACE YOUR ANSWER HERE
/* 
The reason that you would provide the pointer, string length, and buffer length is good pratice 
is because for many reasons 
One reason is that we may not have to go througth the full buffer just good throught the length of the string.
A second reason is that we want to increase the buffer size and if we pass in the varible 
then we just need to change the value of that variable.
A third reason is if the string is empty then the string length is zero so we do not need to do anything. (handle edge cases)
*/