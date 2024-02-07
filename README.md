# minitalk

The **minitalk** project aims to create a program (actually two programs) enabling communication between processes through the "**minitalk**" protocol. This involves sending messages between a "**client**" process and a "**server**" process via signals. The **client** transmits signals to send a message, and the **server** interprets the signals to receive the message.

# Signals

**Signals** are software interrupts used to communicate with processes. An example is **`SIGINT`**, often triggered by pressing **Ctrl+C** to interrupt a program. For the **minitalk** project, we'll only use `SIGUSR1` and `SIGUSR2` signals.

# Functions

We’ll use only four new functions. Two for handling signals and two to control flow and timing of a program.

1. **`kill()`:**
    - **Purpose**: Sends a signal to a process or a group of processes.
    - **Example**: **`kill(pid, SIGTERM)`** sends the termination signal to the process with the specified process ID (pid).
2. **`signal()`:**
    - **Purpose**: Sets a function to handle a specific signal.
    - **Example**: **`signal(SIGINT, signal_handler)`** sets the function **`signal_handler`** to be called when the program receives the interrupt signal (SIGINT).
3. **`usleep()`:**
    - **Purpose**: Delays program execution for a specified amount of time.
    - **Example**: **`usleep(500000)`** pauses the program for 500,000 microseconds (0.5 seconds). The **`sleep`** function operates similarly but uses seconds (e.g., **`sleep(2)`** pauses for 2 seconds).
4. **`pause()`:**
    - **Purpose**: Causes the program to pause its execution until a signal is received. It’s similar to `**sleep**`, but instead of using a specified time duration for pausing, it waits until the process receives a signal to resume execution.
    - **Example**: **`pause()`** suspends the program until a signal is delivered.

# server.c

```c
#include "minitalk.h"

/* pid: Process ID of the server process (get with getpid function)
deal with 'unused variable warning' with (void)argv;
deal with user inputing more than just the name of the program (server)
handle wrong input by user when starting the process with error message
starts process printing process PID and confirming that program is waiting
infite loop to continuosly listen for signals
set signal handler for SIGUSR1 (the 1 bit) and SIGUSR2 (the 0 bit)
pause execution until a signal is received for handling with the signal ft
*/
int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error: wrong format, too many parameters\n");
		ft_printf("Try: ./server\n");
		return (0);
	}
	pid = getpid();
	ft_printf("PID %d\n", pid);
	ft_printf("Waiting for a message...\n");
	while (argc == 1)
	{
		signal(SIGUSR1, ft_handler);
		signal(SIGUSR2, ft_handler);
		pause();
	}
	return (0);
}

/* Signal handler function for handling incoming signals
bit: tracks current bit position being received, because it's static, bit = 0
i: accumulator for constructing the ASCII value, because it's static i = 0
if received signal is SIGUSR1, the corresponding bit in 'i' is set
for each signal received, 'bit' is incremented
after processing 8 bits (a complete char), the char is printed and
'bit' and 'i' are reset to 0 for the next char
 */
void	ft_handler(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
		i |= (00000001 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}
```

# client.c

```c
#include "minitalk.h"

/* pid: Process ID of the server process, needs to be argv[1], the 2nd argument
i: current char in the string argv[1], initialized to 0 to start the string
check if correct number of cli arguments is provide i.e. ./client PID MSG (3)
convert string PID, the 2nd argument (argv[1]), to integer
while loop to iterate through each char of the msg (argv[2]) and send its bits
send a newline character to mark the end of the message
if an incorrect number of cli arguents is provide, print error message
in this case also return 1, i.e. error
*/
int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			ft_send_bits(pid, argv[2][i]);
			i++;
		}
		ft_send_bits(pid, '\n');
	}
	else
	{
		ft_printf("Error: wrong format\n");
		ft_printf("Try: ./client <PID> <MESSAGE>\n");
		return (1);
	}
	return (0);
}

/* Function to send individual bits of a character as signals
bit: 1 single bit from the char i (from argv[2][i]) being send as msg
for example, the char 'h' can be described as 01101000
while loop to iterate through each bit of the char
check if current bit of the char 'i' is a 0 or a 1
if current bit is 1, send (kill) the signal SIGUSR1, if it's 0, send SIGUSR2
small delay between signal transmissions preventing overlapping of signals
move to next bit repeating the process for all 8 bits of the char 'i'
*/
void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (00000001 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}
```

# Example of interaction

To initiate the **minitalk** communication, we begin by launching the **server** process in a terminal using the command: **`./server`**. This action provides us with the **Process ID (PID)** of our server; for the sake of explanation, let's assume the **PID** is 4242. The terminal then displays the message:

```css
PID 4242
Waiting for a message...
```

Subsequently, in a separate terminal, we initiate the **client** process with the command: **`./client 4242 hi`**. The client promptly sends the message "hi" and then exits. Upon returning to the first terminal (where the **server** process is running), the message is updated to:

```css
PID 4242
Waiting for a message...
hi
```

This sequence illustrates the process of setting up the **server**, obtaining its **PID**, initiating the **client** with the s**erver's PID** and a message, and observing the received message in the **server** terminal.

## Step by step of the client process

Let's delve into the client process, specifically when sending the message "hi":

1. **1st interaction:**
    - **`char i = 'h';` ’h’**can also be represented as **‘01101000’** in binary.
    - **`bit = 0;`**
    - The `if` statement evaluates as follows:This condition is false, as the result of the "bit 0 & bit 1" operation **is** 0.
        
        ```c
        if (("01101000" & "00000001" != 0))
        ```
        
    - Consequently, the `else` statement is executed: **`kill(pid, SIGUSR2);`**
    - The **first signal** sent from the client to the server is **SIGUSR2**.
2. **2nd interaction:**
    - **`char i = 'h';`**
    - **`bit = 1;`** (incremented with "bit++")
    - The `if` statement evaluates similarly: The condition is false, resulting in **`kill(pid, SIGUSR2);`**
        
        ```c
        if (("01101000" & "00000010" != 0))
        ```
        
    - The **second signal** sent is also **SIGUSR2**. So far, we've sent **"SIGUSR2 SIGUSR2"**
3. **3rd to 8th interactions:**
    - The process repeats, with bit incremented in each iteration.
    - For each iteration, if the condition is false, **SIGUSR2** is sent; otherwise, **SIGUSR1** is sent.
    - The sequence of signals sent accumulates as "**SIGUSR2 SIGUSR2 SIGUSR2 SIGUSR1 SIGUSR2 SIGUSR1 SIGUSR1 SIGUSR2**"

After the 8th iteration, **`bit`** becomes **8**, and the `while` loop exits. Returning to the **`main()`** function, **`i++`** is executed, and the entire process is repeated for the next character in the message (**'i'** in this case). This pattern continues until the entire message is transmitted.

## Step by step of the server process

When transmitting the char **'h'** from the **client**, the corresponding signals sent to the **server** are: "**SIGUSR2 SIGUSR2 SIGUSR2 SIGUSR1 SIGUSR2 SIGUSR1 SIGUSR1 SIGUSR2**"

Let's delve into the **`ft_handler()`** function in **`server.c`** to understand how the server processes these signals:

- Before receiving any signals, the initial state is set:
    
    ```c
    bit = 0;
    i = 0;
    ```
    
- To satisfy the `if` statement, the signal being received must be **SIGUSR1**:

```c
if (signal == SIGUSR1)
```

- In the 1st, 2nd and 3rd iterations, where the signal received is **SIGUSR2**, the `if` statement is not satisfied. 1 is added to the `int bit`, nevertheless, independently of which signal is being received.
- In the 4th iterations, where the signal received is **SIGUSR1**, the `if` statement is satisfied, and the following bitwise operation occurs:
    
    ```c
    i |= (00000001 << bit);
    ```
    
    At this point the `int i` is still **0**, which can be represented as **00000000**:
    
    ```c
    i |= (00000001 << 3);
    00000000 |= (00000001 << 00001000);
    i = 00001000;
    ```
    
    After this operation, 'bit' is incremented by 1:
    
    ```c
    bit = 4;  // 5th iteration
    ```
    
- Similar operations occur in the 6th and 7th iterations, resulting in the `int i` being constructed as follows:
    
    ```c
    i = 00101000;  // 6th iteration
    i = 01101000;  // 7th iteration
    ```
    
- In the 8th iteration, where the signal received is **SIGUSR2**, the `int bit` is incremented to 8, satisfying the second `if` statement, and the character **'h'** (constructed from the `int i`) is printed. `bit` and `i` are reset to zero, and the **server** continues to receive signals.

This process repeats as the server waits for and processes signals, handling each bit to construct characters until the transmission is complete.