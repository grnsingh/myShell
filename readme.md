Features:

Command Execution:

The shell supports the execution of external programs using execvp.
Users can run multiple commands sequentially.
Input Parsing:

The shell parses user input to separate commands, arguments, and other tokens.
It handles whitespace and special characters correctly.
Background Processes:

Users can run processes in the background by appending & at the end of the command.
The shell can manage multiple background processes simultaneously.
Path Resolution:

The shell resolves command paths using the PATH environment variable.
If a command is not found in the current directory, the shell searches for it in the directories specified in PATH.
Exit Command:

Users can exit the shell by typing the command quit.
Implementation:

The shell uses fork() and execvp() functions to create new processes and execute commands.
User input is parsed, and commands along with their arguments are stored in an array.
Background processes are managed using a structure that stores their pid and status.
The shell continuously prompts the user for input, executes the commands, and waits for the processes to finish (unless they are background processes).
The shell handles errors related to input, command execution, and process management.
Limitations and Future Improvements:

Pipes: The shell currently does not support pipes for communication between processes.
Limited Built-in Commands: The shell does not support built-in commands like cd or shell scripting.
Error Handling: More detailed error messages and error codes can be implemented for better user feedback.
Customization: Future versions could include features like customizable prompts or configurable environment variables.
