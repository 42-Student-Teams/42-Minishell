# Minishell
Minishell is a project developed as part of the curriculum at School 42. It involves creating a simplified version of a command-line shell, commonly known as a shell. This implementation adheres to the requirements and specifications outlined below, providing a comprehensive and user-friendly shell experience.

## Project Requirements
The 42-Minishell project encompasses the following key features:

- **Prompt**: The shell displays a prompt, waiting for user input to enter a new command.

- **Functional History**: The shell maintains a functional command history, allowing users to recall and execute previous commands.

- **Executable Lookup**: The shell searches for and launches the correct executable by leveraging the PATH environment variable or using relative or absolute paths.

- **Minimal Use of Global Variables**: The shell implements the solution with no more than one global variable, ensuring a concise and well-structured codebase.

- **Limited Interpretation of Quotes and Special Characters**: The shell does not interpret unclosed quotes or special characters not explicitly requested in the project specifications, such as backslashes () or semicolons (;).

- **Handling of Single Quotes**: The shell correctly handles single quotes ('), preventing the interpretation of metacharacters within the quoted sequence.

- **Handling of Double Quotes**: The shell properly handles double quotes ("), preventing the interpretation of metacharacters within the quoted sequence, except for the dollar sign ($).

- **Redirection Implementation**: The shell supports various types of redirection:
    - **<** redirects input.
    - **>** redirects output.
    - **<<** receives a delimiter and reads input until a line containing the delimiter is encountered (the history does not need to be updated).
    - **>>** redirects output in append mode.
- **Pipeline Implementation**: The shell implements pipes (|). The output of each command in the pipeline is connected to the input of the subsequent command through a pipe.

- **Handling of Environment Variables**: The shell properly handles environment variables (denoted by a $ followed by a sequence of characters) and substitutes them with their corresponding values.

- **Handling of $?**: The shell replaces $? with the exit status of the last executed foreground pipeline.

- **Handling of ctrl-C, ctrl-D, and ctrl-\\**: The shell properly handles the following keyboard shortcuts, akin to bash:
    - ctrl-C displays a new prompt on a new line.
    - ctrl-D exits the shell.
    - ctrl-\ does nothing.
- **Interactive Mode**: In interactive mode, the shell implements the following built-ins:
    - **´echo´** with the -n option.
    - **´cd´** with only relative or absolute paths.
    - **´pwd´** without any options.
    - **´export´** without any options.
    - **´unset´** without any options.
    - **´env´** without any options or arguments.
    - **´exit´** without any options.

- **Handling of Memory Leaks**: While the readline() function may cause memory leaks, they do not need to be managed in this project. However, it is crucial to ensure that your own code does not have any memory leaks.


Please note that while the readline() function used within the project may cause memory leaks, managing them is not a requirement. However, it is important to ensure that your own code does not have any memory leaks.

Minishell provides a comprehensive implementation of a command-line shell, incorporating essential functionalities and features. It serves as an opportunity to enhance understanding of Unix-like systems and improve programming skills while delivering a user-friendly shell experience.
