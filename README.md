<p align="center">
  <img src="img/minishell.png" width="70%"/>
</p>

## 🚀 SYNOPSIS

The `minishell` project at 42 school immerses students in the dynamic world of UNIX shell development within the C language. This comprehensive undertaking requires a deep understanding of system calls, process management, and parsing techniques.

Students are tasked with crafting a minimalistic shell that mimics the fundamental functionalities of a UNIX command-line interface.

Beyond basic command execution, minishell delves into advanced features such as environment variable handling, signal management, and piping. Leveraging knowledge in lexical analysis and parsing, students navigate the intricacies of command interpretation and user interaction.

This project, interwoven with the philosophy of simplicity and efficiency, not only sharpens skills in system-level programming but also imparts a practical understanding of the core components that constitute a fully functional shell.

## 🛠️ PROGRAM SPECIFICITIES AND CONSIDERATIONS

Start by clonning the repo :

```bash
git clone git@github.com:maitreverge/minishell.git && cd minishell
```

> [!IMPORTANT]
> The program must replicate the behavior of a shell in interactive and non-interactive modes, following the project’s strict guidelines.

> [!WARNING]
> Undefined behavior, such as unclosed quotes or incorrect handling of special characters, should be avoided.

The program should:

- Display a prompt when waiting for user input.

- Execute commands found in the `PATH` or using absolute/relative paths.

- Handle errors gracefully and display appropriate messages.

- Implement built-in commands as specified in the subject.

## ⚙️ USAGE

The primary program is called minishell, and it will be compiled using:

```bash
make
```

The program can be executed as follows:

```bash
./minishell
```

Upon execution, it should display a prompt and allow the user to enter commands. For example:

```text
minishell$ ls -l
```

Output:
```bash
total 8
-rw-r--r-- 1 user user 1024 Jan 15 2025 file1.txt
-rw-r--r-- 1 user user 2048 Jan 15 2025 file2.txt
```

## 🔧 CORE FEATURES

The program implements the following core functionalities:

### Command Execution

- Search and execute commands based on the PATH environment variable or absolute/relative paths.

### Built-in Commands

The following built-in commands must be implemented:

- `echo`: Prints text to the terminal. Supports the `-n` option to suppress the newline.

- `cd`: Changes the current directory.

- `pwd`: Prints the current working directory.

- `export`: Sets or updates environment variables.

- `unset`: Unsets environment variables.

- `env`: Displays the current environment variables.

- `exit`: Exits the shell.

### Redirections

- `<`: Redirect input from a file.

- `>`: Redirect output to a file.

- `<<`: Implement heredoc functionality.

- `>>`: Append output to a file.

### Pipes

- Handle pipelines `|`, chaining multiple commands together so the output of one becomes the input of the next.

### Signal Handling

- `Ctrl+C`: Interrupts the current command and displays a new prompt.

- `Ctrl+D`: Exits the shell.

- `Ctrl+\`: Does nothing, mimicking bash behavior.

### Environment Variables

- Handle `$` expansion to substitute environment variables.

- Handle `$?` to display the exit status of the last executed command.

## 💻 EXAMPLE

Here’s an example session:
```bash
minishell$ echo "Hello, World!"
Hello, World!
minishell$ pwd
/home/user/minishell
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42
minishell$ ls | grep minishell
minishell
minishell$ exit
```

## 🤝 CONTRIBUTION
Contributions are open, open a Github Issue or submit a PR 🚀
