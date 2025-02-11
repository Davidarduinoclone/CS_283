1. In this assignment I suggested you use `fgets()` to get user input in the main while loop. Why is `fgets()` a good choice for this application?

    > **Answer**: The reason is because 'fgets()' reads the STDIN. This means that what every the user types in to the prompt the program will see it. 

2. You needed to use `malloc()` to allocte memory for `cmd_buff` in `dsh_cli.c`. Can you explain why you needed to do that, instead of allocating a fixed-size array?

    > **Answer**:  the reason we use malloc for cmd_buff because not all inputs are the same size. If we used a fixed size we may run put of space if it is to big or waste space if the input is to small. 


3. In `dshlib.c`, the function `build_cmd_list(`)` must trim leading and trailing spaces from each command before storing it. Why is this necessary? If we didn't trim spaces, what kind of issues might arise when executing commands in our shell?

    > **Answer**:  if we do not trim the white space then the white space would be stored with the command. This would waste space. Also, it helps commands be recognized by the program. For example " exit " is not recognized but "exit" is. 

4. For this question you need to do some research on STDIN, STDOUT, and STDERR in Linux. We've learned this week that shells are "robust brokers of input and output". Google _"linux shell stdin stdout stderr explained"_ to get started.

- One topic you should have found information on is "redirection". Please provide at least 3 redirection examples that we should implement in our custom shell, and explain what challenges we might have implementing them.

    > **Answer**:  The three examples are 
    Output Redirection (>): it redirects the output of a command to a file ex ls > capture.txt
    Input Redirection (<): it redirects the input of a file into a command ex sort < input.txt 
    Appending Output (>>): it adds the output to the end of the file instead of overwriting it ls >> capture.txt

    the challenges we might have are checking opening files and writing to them without loosing data and reading from files and outputing it to a command instead of  stdin 

- You should have also learned about "pipes". Redirection and piping both involve controlling input and output in the shell, but they serve different purposes. Explain the key differences between redirection and piping.

    > **Answer**:  redirection is about taking output of a command and saving it to a file or the reverse But pipes are about taking the output of a command and sending it to another command. 

- STDERR is often used for error messages, while STDOUT is for regular output. Why is it important to keep these separate in a shell?

    > **Answer**:  so that we can tell the differences between the two. they both write to the same place but the contains of their messages have different meanings.  

- How should our custom shell handle errors from commands that fail? Consider cases where a command outputs both STDOUT and STDERR. Should we provide a way to merge them, and if so, how?

    > **Answer**:  we should merge both of them using this "2>&1", 2 is the stderr and 1 is the stdout and the >& comdines the two so the user can see both. 