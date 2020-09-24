/*
 * Name: Davis Carmichael
 * Student ID: 2328047
 * Email: carmichael@chapman.edu
 * Course: CPSC380-operating systems
 * Assignment: hw1
*/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>


/* method taking two arguments that are file names. source and destination respectively
 * exits on error opening and specifies which file has an error.
 * proceeds and checks 2048 bytes at a time waiting for the return value to signify reaching
 * eof.
 *
 * param:
 *    const char * src: file pathname to be copied
 *    const char * des: file pathname to be written to
 * return:
 *    bool: true on success, false on failure
 */
bool write_to_file(const char * src, const char * des)
{
    int open_src = open(src, O_RDONLY);
    if (open_src==-1)
    {
        printf("error opening src, (%s)... %d\n", src, errno);
        return false;
    }

    int open_des = open(des, O_WRONLY|O_EXCL|O_CREAT);
    if (open_des==-1)
    {
        printf("error opening des, (%s)... %d\n",des, errno);
        close(open_src);
        return false;
    }


    char *buf = malloc(2048);

    int bytes_read;
    bytes_read = read(open_src, buf, 2048);

    //read 2048 bytes while the reading has not reached write_to_file
    while (bytes_read > 0)
    {
        write(open_des, buf, bytes_read);
        bytes_read = read(open_src, buf, 2048);
    }
    
    close(open_des);
    close(open_src);
    free(buf);

    return true;
}

/* program that copies cntents of file to another, based on the source and destination
 * pathnames specified in argv. no ouput on success, 1 is error code for incorrect parameters
 * given through the cli.
 */
int main(int argc, char** argv)
{
    if (argc==3)
    {
        write_to_file(argv[1],argv[2]);
    }
    else //there are not enough args to continue
    {
        return 1;
    }
}
