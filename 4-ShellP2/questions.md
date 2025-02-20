1. Can you think of why we use `fork/execvp` instead of just calling `execvp` directly? What value do you think the `fork` provides?

    > **Answer**:  If we just used execvp this would rewrite the code that is running and replace it with the command that we call in execvp. That is why fork is so valuable because it creates a copy of the program task then runs execvp so there is now two tasks running

2. What happens if the fork() system call fails? How does your implementation handle this scenario?

    > **Answer**:  If the fork() system call fails, it returns -1 and does not creat a child process. If the fork() system call fails I handle it by printing an error asking that "fork failed"

3. How does execvp() find the command to execute? What system environment variable plays a role in this process?

    > **Answer**:  execvp uses the users PATH environment variable to find were all the commands are stored. The PATH variable points to directories that hold the executable for the command we want to run. 

4. What is the purpose of calling wait() in the parent process after forking? What would happen if we didn’t call it?

    > **Answer**:  Since fork created two independent process this means that both can be running at the same time. But if we want the child to execute and see what it has returned we use wait. If we did not use wait then we would not see want the child returned.

5. In the referenced demo code we used WEXITSTATUS(). What information does this provide, and why is it important?

    > **Answer**:  WEXITSTATUS() gets the exit status of the child after it is done running. This means we can see if the child ran successfully without any errrors or if the exited with an error code. 

6. Describe how your implementation of build_cmd_buff() handles quoted arguments. Why is this necessary?

    > **Answer**:  It handles quote by using a bool called in_quote_mode. This is neccessary because when that boolean is true the program does not remove the extra white space that are inside teh quotes. 

7. What changes did you make to your parsing logic compared to the previous assignment? Were there any unexpected challenges in refactoring your old code?

    > **Answer**:  One  challenge that I faces was the change in the data type that we were using to store the command in. This caused me to change my build_cmd_list() into a build_cmd_buff(). Another challenge was to store all the things in the string into a the args. 

8. For this quesiton, you need to do some research on Linux signals. You can use [this google search](https://www.google.com/search?q=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&oq=Linux+signals+overview+site%3Aman7.org+OR+site%3Alinux.die.net+OR+site%3Atldp.org&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBBzc2MGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8) to get started.

- What is the purpose of signals in a Linux system, and how do they differ from other forms of interprocess communication (IPC)?

    > **Answer**:  A signal is a “(soft)-interrupt” to the program so it can communicate to the process. The main differ with signals is that it can interupt the flow of the program. 

- Find and describe three commonly used signals (e.g., SIGKILL, SIGTERM, SIGINT). What are their typical use cases?

    > **Answer**:   SIGKILL -- is used to kill a process immediately. It cannot be ignored. 
                    SIGTERM -- is used to request to terminate a program. This is used so it can perform clean up opertations. 
                    SIGINT -- "this is control c" this is used to get out of a program.  It can be ignored.

- What happens when a process receives SIGSTOP? Can it be caught or ignored like SIGINT? Why or why not?

    > **Answer**:  What happens is that the process is paused until it receives a different signal to unpause the process. This can not be ignored or caught because this is because it is crucial for process control. 
