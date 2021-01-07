#!/usr/bin/python3

from os import popen, chdir, getcwd
from sys import argv
import subprocess as sp
from time import sleep

output = """

    ❌ {}:
        SH:
        |   {}
        |   exit status: {}
        |   error msg: {}
        HSH:
        $   {}
        $   exit status: {}
        $   error msg: {}
    """


def add_commands(commands):

    if len(commands) == 0:
        print('Usage: shelltest new <command> [...]')
        return

    prompt = "Confirm new command: {}? Write anything to cancel."
    with open('test_commands.txt', 'a') as command_file:
        for command in commands:
            confirm = input(prompt.format(command))
            if confirm == '':
                command_file.write(command + '\n')
        command_file.close()
    return


def shelltest(command, shell):

    echo = 'echo "{}" | {}'.format(command, shell)
    result = sp.Popen(echo, shell=True, stderr=sp.PIPE, stdout=sp.PIPE)
    stdout, stderr = result.communicate()
    if stdout:
        stdout = stdout.decode()
    else:
        stdout = ''
    if stderr:
        stderr = stderr.decode()
    else:
        stderr = ''
    status = int(popen('echo $?').read())
    return stdout, stderr, status


# If there are args, the args the commmands, else use pre-made command list
commands = None
if len(argv) > 1:
    if argv[1] == 'new':
        add_commands(argv[2:])
        exit(0)
    else:
        commands = argv[1:]
else:
    try:
        with open('test_commands.txt', 'r') as command_file:
            commands = command_file.readlines()
            command_file.close()
    except FileNotFoundError:
        print('test_commands.txt does not exist!')
        exit(1)

# Compile file using make file
make_error = sp.Popen('make re', shell=True,
                      stderr=sp.PIPE).communicate()[1]
if make_error:
    print("Program does not compile!\n\nError: {}".format(make_error.decode()))
    exit(1)

# Get home directory in case we need to return to it
HOME = getcwd()

# Check each command
results = ''
for command in commands:
    if command[-1] == '\n':
        command = command[:-1]
    if command == '':
        continue
    hsh_out, hsh_err, hsh_code = shelltest(command, './hsh')
    sh_out, sh_err, sh_code = shelltest(command, '/bin/sh')
    hsh_err = hsh_err.replace('./hsh', '/bin/sh')
    chdir(HOME)

    if sh_out != hsh_out or sh_err != hsh_err or sh_code != hsh_code:
        print(output.format(command, sh_out, sh_code,
                            sh_err, hsh_out, hsh_code, hsh_err))
        print('------------------------------------------')
        results += '❌'
    else:
        print('✅', end='')
        results += '✅'
print('\n')
print('Passed {} / {} tests'.format(results.count('✅'), len(results)))
print(results)
