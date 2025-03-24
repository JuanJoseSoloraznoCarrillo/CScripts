/**
 * Author: Solorzano, Juan Jose.
 * Date: 2020-07-07.
 * Description: This program searches for a file in the current directory and its subdirectories.
 * The program receives the name of the file to search as an argument. The program will print the 
 * full path of the file.
 */
// Importing libraries
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

/**
 * This function searches for a file in the current directory and its subdirectories.
 * @param path: The path to search for the file.
 * @param fileName: The name of the file to search.
 * @param buffer: The buffer to store the full path of the file.
 * @param buffer_size: The size of the buffer.
 * @param verbose: If 1, the function will print the search progress.
 */
int findFile(const char *path, const char *fileName, char *buffer, size_t buffer_size, int verbose){
    DIR *dir = opendir(path);
    if (dir == NULL) {return 1;} // Return non-zero to indicate not found or an error
    struct dirent *dirInfo;
    if(verbose){printf("Searching for '%s'\n",fileName);}
    int counter = 0;
    while((dirInfo = readdir(dir)) != NULL) {
        if(verbose){printf("Directory counter: %d\r",counter++);}
        int isDotDir,isDoubleDotDir;
        isDotDir = (strcmp(dirInfo->d_name,".") == 0);
        isDoubleDotDir = (strcmp(dirInfo->d_name,"..") == 0);
        if (isDotDir || isDoubleDotDir){continue;}// Skip '.' and '..'
        // Construct the full path of this entry
        char fullpath[4096];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, dirInfo->d_name);
        struct stat stdDirInfo; // folder information structure.
        int stdDirInfoExists = (stat(fullpath, &stdDirInfo) == -1);
        if(stdDirInfoExists){continue;}
        if (S_ISDIR(stdDirInfo.st_mode)){// It's a directory, so recurse into it
            int fileFound = (findFile(fullpath, fileName, buffer, buffer_size,0) == 0);
            if (fileFound){
                closedir(dir);
                return 0;
            }
        } else if (S_ISREG(stdDirInfo.st_mode)){// It's a file. Check if it's the one we are looking for.
            int samefileName = (strcmp(dirInfo->d_name, fileName) == 0);
            if(samefileName){// Found the file
                snprintf(buffer, buffer_size, "%s", fullpath);
                closedir(dir);
                if(verbose){printf("\n");}
                return 0;
            }
        }
    }
    closedir(dir); // close directory.
    return 1; // file name not found.
}
/**
 * Description: Main function of the program.
 * @param argc: The number of arguments.
 * @param args: The arguments.
 */
int main(int argc,char *args[]){
    clock_t start,end;
    double cpuTimeUsed;
    start = clock();
    char *fileToFind = args[1];
    char buffer[256];
    findFile(".",fileToFind,buffer,sizeof(buffer),0);
    end = clock();
    cpuTimeUsed = ((double)(end-start))/CLOCKS_PER_SEC;
    printf("file was found at: %s\n",buffer);
    printf("Execution time: %f\n",cpuTimeUsed);
}
