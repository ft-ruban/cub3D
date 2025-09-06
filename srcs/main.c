#include <unistd.h> //write
#include "parsing.h"

int main(int argc, char *argv[])
{
    //parsing
      //if parsing fail return error with right msg
    if(parsing(argc, argv))
        write(2, "placeholder failed parsing\n", 27);
    //init structures/data
        //if fail return error with right msg + free close
    //init minilibx + I guess the controls? 
        //if fail return error with right msg + free/close
    //running part
    //write(1,"Hello, world\n", 13);
    return (0);
}