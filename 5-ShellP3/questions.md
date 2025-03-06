1. Your shell forks multiple child processes when executing piped commands. How does your implementation ensure that all child processes complete before the shell continues accepting user input? What would happen if you forgot to call waitpid() on all child processes?

My implementation ensure that all child processes complete before the shell continues accepting user inputs by using the waitpid() for each child process. waitpid() is used to tell the parent process to wait until the child process is finished and it can return the exit status of the child process. If i did not use waitpid() then the parent would not wait for the child process to finish before doing something. This could create zombie process 

2. The dup2() function is used to redirect input and output file descriptors. Explain why it is necessary to close unused pipe ends after calling dup2(). What could go wrong if you leave pipes open?

We need to close unused pipe ends after calling dup2() becuase it prevents leaks and make sure of proper communication between processes. If we left pipes opened then is would lead to child process waiting of the EOF forever, this would consume system resources. 

3. Your shell recognizes built-in commands (cd, exit, dragon). Unlike external commands, built-in commands do not require execvp(). Why is cd implemented as a built-in rather than an external command? What challenges would arise if cd were implemented as an external process?

The reason that cd is a bulit in command is because then it would be the child process that change directories and not the shell. If you implemented it as an external process then the external process would change directories and not the parent process. 

4. Currently, your shell supports a fixed number of piped commands (CMD_MAX). How would you modify your implementation to allow an arbitrary number of piped commands while still handling memory allocation efficiently? What trade-offs would you need to consider?

I would modify my implementation to allow for an arbitrary number of piped commands while still handling memory allocation efficiently by using a linked list. The trade offs would be that I can could go to a specific index any more. Also it will be hard to travel a linked list then it is a regular array. 
