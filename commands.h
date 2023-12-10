//
// Created by dimgo on 10/12/2023.
//

#ifndef DAYLIST_COMMANDS_H
#define DAYLIST_COMMANDS_H

typedef struct command{
    char* name;
    char* description;
    struct command** subCommands;
    int subCommandCount;
    void (*function)(char** args, int argCount);
    char* argsInfo;
} Command;

void InitCommands();
void FreeCommands();
//Read a command from the user input
void ReadCommand();
//Add a command
void AddCommand(char* name, char* description, void (*function)(char** args, int argCount), char* argsInfo);
//Add a subcommand
void AddSubCommand(char* commandPath[], int commandPathLength, char* name, char* description, void (*function)(char** args, int argCount), char* argsInfo);
//Execute a command
void ExecuteCommand(char** args, int argCount);
//Try to execute a subcommand
int TryExecuteSubCommand(char** args, int argCount, Command* command);
//Print all the commands
void PrintCommands();
//Print the usage of a command
void CommandUsage(Command* command);

#endif //DAYLIST_COMMANDS_H
