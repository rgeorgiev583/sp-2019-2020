#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
//Global variables that show the index where our files start and the delimiter we use
//and if the -s option is being used
static int listedFilesStartingIndex = 1;
static char delimiter[BUFSIZ];
static int printWholeFile = 0;

//This method will skip the lines we already went through since ever time we
//open the file the read pointer will reset to the beginning of the file.
static void skipLines(FILE * fp,int linesToSkip){
    int linesSkiped = 0;
    char c;
    while(linesSkiped<linesToSkip && c  != EOF){
        c = getc(fp);
        if(c == '\n'){
            linesSkiped +=1;
        }
    }
}

//Returns the number of lines for the given file
static int lineCounter(FILE * fp){
    int count = 0;
    int originalPoss = ftell(fp);
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n') count += 1;
    }
    //Restorings file original pointer position
    fseek(fp,originalPoss,SEEK_SET);
    return count;
}
//By the given file names as argument returns the index of the file
//with the least number of lines
static int leastLinesInFile(int argc,char** argv){
    int minLines = -1,lines;
    FILE * fp;
    for(int i = listedFilesStartingIndex;i<argc;++i){
        fp = fopen(argv[i],"r");
        if (fp == NULL) {
            perror("Failed: ");
            exit(EXIT_FAILURE);
        }
        lines = lineCounter(fp);
        if(lines<minLines || minLines == -1){
            minLines = lines;
        }
        if(ferror(fp)!=0){
            fprintf(stderr,"Write error for file %s \n",argv[i]);
            exit(EXIT_FAILURE);
        }
        if(fclose(fp)){
            perror("fclose error: ");
        }
    }
    return minLines;
}

//Reads a line from a given file and writes it to the stdout or
//reads all file lines and outputs them to stdout with delimiter between each of them.
static void readLine(FILE * fp,int printWholeFile,int is_last_file){
    char symbol;
    int lines = lineCounter(fp);
    int currLine = 0;
    for (symbol = getc(fp); symbol != EOF; symbol = getc(fp)){
        if (symbol == '\n'){
	    currLine++;
	    //We do this check up when we have the -s argument in order not to add delimiter at the end of the stdout line.
	    if((currLine == lines) && printWholeFile == 1) break;
            //If it is the last file we do not want to print delimiter at the end of line
            if (is_last_file == 0) fputs(delimiter,stdout);
            //If we do not have the -s option we want to break when we get a line printed to stdout from a file.
            if (printWholeFile == 0) return;
            continue;
        }
        putc(symbol,stdout);
    }
    //This is needed to output a new line whenever we have the -s option used.
    putc('\n',stdout);
}

static void cat(){
    char c;
    while(1){
    c = getc(stdin);
    putc(c,stdout);
    }
}


int main(int argc, char **argv)
{
    //Cat implementation if we do not have arguments for the command
    if(argc == 1){
        cat();
        return 0;
    }
    strcpy(delimiter,"\t");
    if (strstr(argv[1],"-d")!=NULL){
        //If we have a custom delimiter we copy it to the delimiter variable
        strncpy(delimiter,argv[1]+2,strlen(argv[1]));
        listedFilesStartingIndex = 2;
        //Error if we have optional arguments but no files
        if (listedFilesStartingIndex>=argc){
            fprintf(stderr, "%s: error: command does not have input files\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        if(strcmp(argv[2],"-s")==0){
            //If we have the -s argument our input files start from index 3 and we
            //want to print the whole files with delimiters in between lines.
            listedFilesStartingIndex = 3;
            printWholeFile = 1;
            //Error if we have optional arguments but no files
            if (listedFilesStartingIndex>=argc){
                fprintf(stderr, "%s: error: command does not have input files\n", argv[0]);
                exit(EXIT_FAILURE);
        }
            }
    }
    //Same as above but this is the situation when -s is passed before -d argument.
    else if(strstr(argv[1],"-s")!=NULL){
            listedFilesStartingIndex = 2;
            printWholeFile = 1;
            //Error if we have optional arguments but no files
            if (listedFilesStartingIndex>=argc){
                fprintf(stderr, "%s: error: command does not have input files\n", argv[0]);
                exit(EXIT_FAILURE);
            }
	    if (strstr(argv[2],"-d")!=NULL){
        	//If we have a custom delimiter we copy it to the delimiter variable
        	strncpy(delimiter,argv[2]+2,strlen(argv[2]));
        	listedFilesStartingIndex = 3;
        	//Error if we have optional arguments but no files
        	if (listedFilesStartingIndex>=argc){
            	fprintf(stderr, "%s: error: command does not have input files\n", argv[0]);
            	exit(EXIT_FAILURE);
           }
	}
    }

    FILE * file;
    //If we have the -s option we need the outer loop to be executed only once(so we don't have repetition)
    int linesToPrint = (printWholeFile == 0)? leastLinesInFile(argc,argv):1;
    //j variable will represent the lines from the start of the file we need to skip in each iteration
    for(int j = 0;j<linesToPrint;++j){
        for(int i = listedFilesStartingIndex;i<argc;++i){
            file = fopen(argv[i],"r");
            if (file == NULL) {
                perror("Failed: ");
                exit(EXIT_FAILURE);
            }
            skipLines(file,j);
            //In order not to have the delimiter at the end of line when we do not have the -s option.
            (i == (argc -1) && printWholeFile == 0)? readLine(file,printWholeFile,1):readLine(file,printWholeFile,0);
            if(ferror(file)!=0){
                fprintf(stderr,"Write error for file %s \n",argv[i]);
                exit(EXIT_FAILURE);
            }
            if(fclose(file)){
                perror("fclose error: ");
            }
	}
        if (printWholeFile==0) putc('\n',stdout);
    }
    return 0;
}
