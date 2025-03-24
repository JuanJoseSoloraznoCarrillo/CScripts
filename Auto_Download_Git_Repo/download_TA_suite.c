/**
 * Author: Solorzano, Juan Jose (ID)
 * Date: 01/07/2025
 * Description: This C file is used to create a executable file that allows the <name> suite user
 * dowload it without Git knowledge.
 * compile: gcc download_TA_suite.c suite.o -o get_<name>_suite
 */
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <windows.h>
// Constants
#define REPO_NAME_1 "<repo_link_1>"
#define REPO_NAME_2 "<repo_link_2>"
#define GITCOMMAND "git clone %s"
#define GITSUBMODULES "%s --recursive -j8"
#define SUITENAME "FOLDER_NAME"

/**
 * Description: converts to upper case the string given.
 */
void upper(char *string){
    while(*string){
        *string = toupper((unsigned char)*string);
        *string++;
    }
}
/**
 * Description: Based on the suite name given, it will download the github repository.
 * [!] IMPORTANT: The implementation is not completed. 
 */
int getSuiteLink(char *suiteName){
    upper(suiteName);
    char commandBuffer[MAX_PATH];
    char fcommand[MAX_PATH];
    if(strcmp(suiteName,"FC1")==0){
        sprintf(commandBuffer,GITCOMMAND,REPO_NAME_1);
        sprintf(fcommand,GITSUBMODULES,commandBuffer);
        printf("%s\n",fcommand);
        system("pause");
    }
    return 0;
}
/**
 * Description: download the FC1 suite only, and starts the Auto-cnf .exe file. 
 */
int downloadSuite(){
    char commandBuffer[MAX_PATH];
    char fcommand[MAX_PATH];
    sprintf(commandBuffer,GITCOMMAND,REPO_NAME_1);
    sprintf(fcommand,GITSUBMODULES,commandBuffer);
    printf("%s\n",fcommand);
    system(fcommand);
    _chdir(SUITENAME); //change current work directory to the suite root path.
    char *startAutoCnf = "start ./set_TA_env.exe"; // NOTE: this is an .exe file that is used to start auto-suite configuration, it might not be the same for you.
    system(startAutoCnf);
    return 0;
}
// Main Flow Code
int main(int argc,char *argv[]){
    if(argc>1){ // if the .exe is used on a console with parameters. NOTE: is not implemented yet.
        char *usrArg = argv[1];
        getSuiteLink(usrArg);
        printf("downloading: %s\n",usrArg);
        return 0;
    }
    downloadSuite(); // start the main process.
    return 0;
}