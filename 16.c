#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#define LEN_ANSWER 1

int main()
 {
    char ch;
    int fd;
     struct termios tty, savtty;

     fd = open("/dev/tty", O_RDONLY);
     tcgetattr(fd, &tty);
     if (isatty(fileno(stdout)) == 0) {
         fprintf(stderr, "stdout not terminal\n");
         exit(1);

    }
     savtty = tty;
     tty.c_lflag &= ~(ISIG | ICANON);
     tty.c_cc[VMIN] = 1; /* MIN */
     tcsetattr(fd, TCSAFLUSH, &tty);
     setbuf(stdout, (char*)NULL);
     printf("Are you gouing to sleep ?  ");

     read(fd, &ch, LEN_ANSWER);



     tcsetattr(fd, TCSAFLUSH, &savtty);
     printf("Your ansver is:  %c\n", ch);
 }