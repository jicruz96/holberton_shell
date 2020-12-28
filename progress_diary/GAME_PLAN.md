| Function                 | Assigned To | Status                      | Notes                                                                                                     |
| ------------------------ | ----------- | --------------------------- | --------------------------------------------------------------------------------------------------------- |
| `int main()`             |             | Waiting                     |
| `execute_hshrc()`        |             | Complete                    |
| `execute_arg()`          |             | Complete                    |
| `execute_file()`         |             | Waiting                     |
| `get_env()`              | J.I.        | Complete                    |
| `get_prompt()`           |             | Incomplete - Low Priority   | Return: prompt (str)                                                                                      |
| `get_history()`          | J.I.        | Incomplete - Low Priority   | Return: history array (char \*\*)                                                                         |
| `sigint_handler()`       | J.I.        | Incomplete - High Priority  | Handles SIGINT                                                                                            |
| `tokenize(line)`         | J.I.        | Incomplete - High Priority  | Input: Line from getline<br>Output: Tokens                                                                |
| `make_commands()`        | Gabriel     | Incomplete - High Priority  | Input: Tokens Output: :Linked list of commands                                                            |
| `get_program_path()`     | Gabriel     | Incomplete - High Priority  | Input program name<br>Output: Program path                                                                |
| `command_node_init()`    |             | Waiting                     | Input: program name, program path<br> Output: command node<br>Used by make_commands to make command nodes |
| `get_executor()`         | Gabriel     | Incomplete - High Priority  | Input: command node<br> Returns: executor (int func(command_t \*))                                        |
| `fork_and_exec()`        | J.I.        | Incomplete - High Priority  | Input: command node<br>Return: status                                                                     |
| `builtin_cd()`           | Gabriel     | Incomplete - High Priority  | Input: command node<br>Return: status                                                                     |
| `builtin_env()`          | J.I.        | Incomplete - High Priority  | Input: command node<br>Return: status                                                                     |
| `builtin_setenv()`       | Gabriel     | Incomplete - High Priority  | Input: command node<br>Return: status                                                                     |
| `builtin_unsetenv()`     | Gabriel     | Incomplete - High Priority  | Input: command node<br>Return: status                                                                     |
| `builtin_alias()`        | Not Now     | Incomplete - Low Priority   | Input: command node<br>Return: status                                                                     |
| `builtin_history()`      | J.I.        | Incomplete - Low Priority   | Input: command node<br>Return: status                                                                     |
| `builtin_help()`         | Not Now     | Incomplete - Low Priority   | Input: command node<br>Return: status                                                                     |
| `save_line_to_history()` | J.I.        | Incomplete - Low Priority   | Input: line, history array                                                                                |
| `clean_and_exit()`       | Not Now     | Incomplete - High Priority` |
| `free_command_chain()`   | Gabriel     | Incomplete - High Priority  | Free linked list of command structs                                                                       |
