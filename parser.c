#include "parser.h"

//Command to trim whitespace and ASCII control characters from buffer
//[Input] char* inputbuffer - input string to trim
//[Input] size_t bufferlen - size of input and output string buffers
//[Output] char* outputbuffer - output string after trimming 
//[Return] size_t - size of output string after trimming
size_t trimstring(char* outputbuffer, const char* inputbuffer, size_t bufferlen)
{   
    memcpy(outputbuffer, inputbuffer, bufferlen*sizeof(char));

    for(size_t ii = strlen(outputbuffer)-1; ii >=0; ii--){
        if(outputbuffer[ii] < '!') //In ASCII '!' is the first printable (non-control) character
        {
            outputbuffer[ii] = 0;
        }
        else{
            break;
        }    
    }

    return strlen(outputbuffer);
}

//Command to trim the input command to just be the first word
//[Input] char* inputbuffer - input string to trim
//[Input] size_t bufferlen - size of input and output string buffers
//[Output] char* outputbuffer - output string after trimming 
//[Return] size_t - size of output string after trimming
size_t wordFinder(char* outputbuffer, const char* inputbuffer, size_t bufferlen, int wordNumber)
{   

    memcpy(outputbuffer, inputbuffer, bufferlen*sizeof(char));
    int start =-1;
    int finish = -1;
    int count =0;
    int quotesFlag = 0;
    for(int ii=0; ii<=strlen(outputbuffer); ii++){
         if (inputbuffer[ii] == '\"') {
            quotesFlag = 1 - quotesFlag; 
            continue;
        }
        if((outputbuffer[ii] == ' '|| ii == strlen(outputbuffer)) && !quotesFlag){
            count++;
            if(count == wordNumber){
                finish =ii;
                break;
            }
            
            start =ii;
        }
    }
    int write =0;
    for(int ii =start+1; ii<finish; ii++){ 
        if(inputbuffer[ii] != '"' && inputbuffer[ii] != '\'' ){
        outputbuffer[write] = inputbuffer[ii];
        write++;
        }
    }
    outputbuffer[write ] ='\0';
    return 0;
}

//Command to test that string only contains valid ascii characters (non-control and not extended)
//[Input] char* inputbuffer - input string to test
//[Input] size_t bufferlen - size of input buffer
//[Return] bool - true if no invalid ASCII characters present
bool isvalidascii(const char* inputbuffer, size_t bufferlen)
{
    //TO DO: Correct this function so that the second test string fails
    size_t testlen = bufferlen;
    size_t stringlength = strlen(inputbuffer);
    if(strlen(inputbuffer) < bufferlen){
        testlen = stringlength;
    }

    bool isValid = true;
    for(size_t ii = 0; ii < testlen; ii++)
    {
        isValid &= ((unsigned char) inputbuffer[ii] <= '~'); //In (lower) ASCII '~' is the last printable character
    }

    return isValid;
}

//Command to find location of pipe character in input string
//[Input] char* inputbuffer - input string to test
//[Input] size_t bufferlen - size of input buffer
//[Return] int - location in the string of the pipe character, or -1 pipe character not found
int findpipe(const char* inputbuffer, size_t bufferlen){
    for(int i =0; i <strlen(inputbuffer); i++){
        if(inputbuffer[i]=='|'){
            return 1;
        }
    }
    return 0;
}

//Command to test whether the input string ends with "&" and
//thus represents a command that should be run in background
//[Input] char* inputbuffer - input string to test
//[Input] size_t bufferlen - size of input buffer
//[Return] bool - true if string ends with "&"
bool runinbackground(char* inputbuffer, size_t bufferlen){
    if(inputbuffer[strlen(inputbuffer)-1]=='&'){
        inputbuffer[strlen(inputbuffer)-1]='\0';
        return true;
    }
    return false;
}
