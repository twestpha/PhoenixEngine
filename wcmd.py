from msvcrt import getch
from subprocess import check_output
from sys import stdout
from os import system

system("cls")

while True:
    stdout.write("CMD: ")
    command = ""

    # Capture keystrokes until enter pressed
    while True:
        key = ord(getch())
        # print(key)

        # Keystroke commands
        if(key == 13): # Newline character enters command
            break
        elif(key == 3): # Ctrl + C escape character exits
            exit(0)
        elif(key == 9): # TODO Tab completes
            pass
        else:
            stdout.write(chr(key))
            command += chr(key)

    stdout.write("\n")

    print(command)

    # Run Commands
    if(command == "exit"):
        exit(0)
    elif(command == "cls" or command == "clear"):
        system("cls")
    else:
        # make this progressive somehow...?
        out = ""
        try:
            out = check_output(command.split(" "))
        except Exception as e:
            print(e)

        stdout.write(out)

        stdout.write("\n")

# import sys

# while(True):
    # print(sys.stdin.read(1))

    # command = raw_input("$ ")
    #
    # if(command == "exit"):
    #     exit(0)
    # elif(command == "cls" or command == "clear"):
    #     system(command)
    # else:
    #     out = ""
    #     try:
    #         out = check_output(command.split(" "))
    #     except Exception as e:
    #         print(e)
    #
    #     print(out)
