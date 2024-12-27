/**
 * Author: Solorzano, Juan Jose
 * Date: 12/27/2024
 * File description: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define SEPARATOR "-----------------------------------------------------------------------------------------\n"

int readFile(const char *fileName){
    FILE *file; // file pointer
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // console manage
    char ch; 
    file = fopen(fileName,"r");
    if(file == NULL){
        perror("[!] >> Error opening the file");
        return EXIT_FAILURE;
    }
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    printf(SEPARATOR);
    printf("\tFile Name: %s\n",fileName);
    printf(SEPARATOR);
    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
    while((ch = fgetc(file)) != EOF){
        putchar(ch);
    }
    SetConsoleTextAttribute(console, FOREGROUND_BLUE);
    printf("\n:EOF\n");
    SetConsoleTextAttribute(console, FOREGROUND_RED);
    printf(SEPARATOR);
    fclose(file);
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return 0;
}

/**
 * Main Function 
 */
int main(int argc, char *argv[]){
    if(argc < 2){
        printf("[?] >> Usage:\n\t $> cat.exe <file>\n");
        return EXIT_FAILURE;
    }
    readFile(argv[1]);
}
