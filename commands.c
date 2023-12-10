//
// Created by dimgo on 10/12/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "commands.h"

Command** CommandList = NULL;
int CommandCount;

void ReadCommand(){
    char* commandString = malloc(sizeof(char) * 100);
    printf(">> ");
    fgets(commandString, 100, stdin);
    commandString[strlen(commandString) - 1] = '\0'; // remove newline

    //count spaces between args
    int argCount = 1;
    for (int i = 0; commandString[i] != '\0'; ++i) {
        if(commandString[i] == ' ') argCount++;
    }

    //split commandString into args
    char** args = malloc(sizeof(char*) * argCount);
    int argIndex = 0;
    int argStart = 0;
    int i = 0;
    do {
        if(commandString[i] == ' ' || commandString[i] == '\0'){
            if(i == argStart){
                argStart++;
                continue;
            }
            args[argIndex] = malloc(sizeof(char) * (i - argStart + 1));
            for (int j = 0; j < i - argStart; ++j) {
                args[argIndex][j] = commandString[argStart + j];
            }
            args[argIndex][i - argStart] = '\0';
            argIndex++;
            argStart = i + 1;
        }
    } while (commandString[i++] != '\0');

    free(commandString);
    ExecuteCommand(args, argIndex);
    for (int j = 0; j < argCount; ++j) {
        free(args[j]);
    }
    free(args);
}
void AddCommand(char* name, char* description, void (*function)(char** args, int argCount), char* argsInfo){
    Command* command = malloc(sizeof(Command));
    command->name = name;
    command->description = description;
    command->function = function;
    command->argsInfo = argsInfo;
    command->subCommandCount = 0;
    command->subCommands = NULL;
    CommandList = realloc(CommandList, sizeof(Command) * (CommandCount + 1));
    CommandList[CommandCount] = command;
    CommandCount++;
}

void AddSubCommand(char* commandPath[], int commandPathLength, char* name, char* description, void (*function)(char** args, int argCount), char* argsInfo){
    Command* command = NULL;
    for (int i = 0; i < CommandCount; ++i) {
        if(strcmp(CommandList[i]->name, commandPath[0]) == 0){
            command = CommandList[i];
            break;
        }
    }
    if(command == NULL){
        printf("Root command not found\n");
        return;
    }
    for (int i = 1; i < commandPathLength; ++i) {
        int found = 0;
        for (int j = 0; j < command->subCommandCount; ++j) {
            if(strcmp(command->subCommands[j]->name, commandPath[i]) == 0){
                command = command->subCommands[j];
                found = 1;
                break;
            }
        }
        if(!found){
            printf("Root command not found\n");
            return;
        }
    }
    Command* subCommand = malloc(sizeof(Command));
    subCommand->name = name;
    subCommand->description = description;
    subCommand->function = function;
    subCommand->argsInfo = argsInfo;
    subCommand->subCommandCount = 0;
    subCommand->subCommands = NULL;
    command->subCommands = realloc(command->subCommands, sizeof(Command) * (command->subCommandCount + 1));
    command->subCommands[command->subCommandCount] = subCommand;
    command->subCommandCount++;
}

void FreeCommands(){
    for (int i = 0; i < CommandCount; ++i) {
        free(CommandList[i]);
    }
    free(CommandList);
}

void ExecuteCommand(char** args, int argCount){
    int success = 0;
    char** commandArgs = malloc(sizeof(char*) * (argCount));
    for (int j = 0; j < argCount; ++j) {
        commandArgs[j] = args[j + 1];
    }

    for (int i = 0; i < CommandCount; ++i) {
        if(strcmp(CommandList[i]->name, args[0]) == 0){
            if(argCount > 1){
                if(strcmp(args[1], "help") == 0){
                    CommandUsage(CommandList[i]);
                    success = 1;
                    break;
                }
                if(TryExecuteSubCommand(commandArgs, argCount - 1, CommandList[i])){
                    success = 1;
                    break;
                }
            }
            if(CommandList[i]->function != NULL)
                CommandList[i]->function(commandArgs, argCount - 1);
            else
                printf("Command not found, type 'help' after a command to get a list of usages\n");
            success = 1;
            break;
        }
    }

    free(commandArgs);
    if(!success)
        printf("Command not found, type 'help' to get a list of available commands\n");
}

int TryExecuteSubCommand(char** args, int argCount, Command* command){
    int success = 0;
    char** commandArgs = malloc(sizeof(char*) * (argCount));
    for (int j = 0; j < argCount; ++j) {
        commandArgs[j] = args[j + 1];
    }

    for (int i = 0; i < command->subCommandCount; ++i) {
        if(strcmp(command->subCommands[i]->name, args[0]) == 0){
            if(argCount > 1){
                if(strcmp(args[1], "help") == 0){
                    CommandUsage(command->subCommands[i]);
                    success = 1;
                    break;
                }
                if(TryExecuteSubCommand(commandArgs, argCount - 1, command->subCommands[i])){
                    success = 1;
                    break;
                }
            }
            if(command->subCommands[i]->function != NULL){
                command->subCommands[i]->function(commandArgs, argCount - 1);
                success = 1;
            }
            break;
        }
    }

    free(commandArgs);
    return success;
}

void PrintCommands(){
    printf("Available commands:\n");
    for (int i = 0; i < CommandCount; ++i) {
        printf("\t - %s: %s\n", CommandList[i]->name, CommandList[i]->description);
    }
}

void CommandUsage(Command* command){
    printf("%s\n", command->description);

    if(command->argsInfo != NULL){
        printf("\nArgument usages:\n");
        printf("\t%s\n", command->argsInfo);
    }
    if(command->subCommandCount == 0)
        return;
    printf("\nSub commands:\n");
    for (int i = 0; i < command->subCommandCount; ++i) {
        printf("\t - %s: %s\n", command->subCommands[i]->name, command->subCommands[i]->description);
    }
}

int isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return 0;
    }
    return 1;
}

void HelpCommand(char** args, int argCount){
    PrintCommands();
}

void InitCommands(){
    AddCommand("help", "Prints all commands", HelpCommand, NULL);
}