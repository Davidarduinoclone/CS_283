1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

The remote client determines when a command's output is fully received from the server by sending the EOF character at the end of the command. This techiques can be used to handle partial reads to ensure complete message transmission because it adds the partial read to a buffer until it reads the EOF character. 

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

One method that can be markers to tell when one message end and another beginings that is what I have done in this assignment. I use the EOF character to tell when a command ends. Another method would be to use a send messages with the length so that you know when you get the full command. The challenges that can arise if this is not handled correctly is lead to command fragmentation. This is when a command is split amoung different packets and not reassembled correctly leading to fragmented commands. 

3. Describe the general differences between stateful and stateless protocols.
A statefull protocols maintians the state of the converation. This means it will sends a request to a client and then wait until it get a response confirming that it 
has gotten the message. If it does not send a respone it will resend the request. In stateless protocal it will just send the information and it does to care if the client has gotten the information. 


4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

We use UDP because it is very fast because it is a stateless protocal so it just sends information and does not check if the client has recieved the data. Unlike TCP which is a statefull protocal which means it is a little slow becasue it sends the information to the client then it waits to confirm the client has recieved the data. 

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

The operating system provides a socket interface/abstraction to enable applications to use network 
communications. Sockets allow applications to create network connections. This allows applications to send and
recieve data over the network. 