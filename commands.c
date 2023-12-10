//
// Created by dimgo on 10/12/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "commands.h"
#include "dateTime.h"
#include "App.h"

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

t_date* getDate(char* date){
    if(strlen(date) != 10){
        printf("Invalid date format\n");
        return NULL;
    }
    if(date[2] != '/' || date[5] != '/'){
        printf("Invalid date format\n");
        return NULL;
    }

    char day[] = {date[0], date[1], '\0'};
    char month[] = {date[3], date[4], '\0'};
    char year[] = {date[6], date[7], date[8], date[9], '\0'};

    if(!isNumber(day) || !isNumber(month) || !isNumber(year)){
        printf("Invalid date format\n");
        return NULL;
    }

    int dayInt = strtof(day, NULL);
    int monthInt = strtof(month, NULL);
    int yearInt = strtof(year, NULL);

    if(dayInt < 1 || dayInt > 31){
        printf("Invalid day\n");
        return NULL;
    }

    if(monthInt < 1 || monthInt > 12){
        printf("Invalid month\n");
        return NULL;
    }

    if(yearInt < 0){
        printf("Invalid year\n");
        return NULL;
    }

    t_date* parsedDate = malloc(sizeof(t_date));
    parsedDate->day = dayInt;
    parsedDate->month = monthInt;
    parsedDate->year = yearInt;
    return parsedDate;
}

t_time* getTime(char* time){
    if(strlen(time) != 5){
        printf("Invalid time format\n");
        return NULL;
    }
    if(time[2] != ':'){
        printf("Invalid time format\n");
        return NULL;
    }

    char hour[] = {time[0], time[1], '\0'};
    char minute[] = {time[3], time[4], '\0'};

    if(!isNumber(hour) || !isNumber(minute)){
        printf("Invalid time format\n");
        return NULL;
    }

    int hourInt = strtof(hour, NULL);
    int minuteInt = strtof(minute, NULL);

    if(hourInt < 0 || hourInt > 23){
        printf("Invalid hour\n");
        return NULL;
    }

    if(minuteInt < 0 || minuteInt > 59){
        printf("Invalid minute\n");
        return NULL;
    }

    t_time* parsedTime = malloc(sizeof(t_time));
    parsedTime->hour = hourInt;
    parsedTime->minute = minuteInt;
    return parsedTime;
}

void HelpCommand(char** args, int argCount){
    PrintCommands();
    printf("Note: valid date format is dd/mm/yyyy and valid time format is hh:mm\n");
}

void ExitCommand(char** args, int argCount){
    stopApp();
}

void SaveCommand(char** args, int argCount){
    appSaveCalendar();
}

void LoadCommand(char** args, int argCount){
    appLoadCalendar();
}

void AddContactCommand(char** args, int argCount){
    if(argCount < 2){
        printf("Not enough arguments\n");
        return;
    }
    appAddContact(args[0], args[1]);
}

void SearchContactCommand(char** args, int argCount){
    if(argCount < 1){
        printf("Not enough arguments\n");
        return;
    }

    appSearchContact(args[0]);
}

void ShowContactCommand(char** args, int argCount){
    appShowContacts();
}

void AddAppointmentCommand(char** args, int argCount){
    if(argCount < 4){
        printf("Not enough arguments\n");
        return;
    }

    t_date* date = getDate(args[2]);
    if(date == NULL)
        return;
    t_time *time = getTime(args[3]);
    if(time == NULL)
        return;
    t_time *duration = getTime(args[4]);
    if(duration == NULL)
        return;
    appAddAppointment(args[5], date, time, duration, args[0], args[1]);
}

void RemoveAppointmentCommand(char** args, int argCount){
    if(argCount < 1){
        printf("Not enough arguments\n");
        return;
    }

    if(!isNumber(args[1])){
        printf("Id must be a number\n");
        return;
    }

    int id = strtof(args[1], NULL);
    appRemoveAppointment(id);
}

void ShowAppointmentCommand(char** args, int argCount){
    if(argCount < 1){
        printf("Not enough arguments\n");
        return;
    }
    appShowAppointments(args[0]);
}

void InitCommands(){
    AddCommand("help", "Prints all commands", HelpCommand, NULL);
    AddCommand("exit", "Exits the program", ExitCommand, NULL);

    AddCommand("save", "Saves the current calendar", SaveCommand, NULL);
    AddCommand("load", "Loads a calendar", LoadCommand, NULL);
    AddCommand("loaddataset", "Loads a data set of names", appLoadNameDataset, NULL);

    AddCommand("contact", "Contact management", NULL, NULL);
    AddSubCommand((char*[]){"contact"}, 1, "add", "Adds a contact", AddContactCommand, "<firstname> <lastname>");
    AddSubCommand((char*[]){"contact"}, 1, "search", "Search a contact", SearchContactCommand, "<partial_lastname>");
    AddSubCommand((char*[]){"contact"}, 1, "show", "Shows all contacts", ShowContactCommand, NULL);

    AddCommand("appointment", "Appointment management", NULL, NULL);
    AddSubCommand((char*[]){"appointment"}, 1, "add", "Adds an appointment", AddAppointmentCommand, "<contact_firstname> <contact_lastname> <date> <startTime> <duration> <description>");
    AddSubCommand((char*[]){"appointment"}, 1, "remove", "Removes an appointment", RemoveAppointmentCommand, "<contact_lastname> <id>");
    AddSubCommand((char*[]){"appointment"}, 1, "show", "Shows all appointments for a contact", ShowAppointmentCommand, "<contact_lastname>");
}