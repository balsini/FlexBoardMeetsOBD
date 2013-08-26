#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_USB "/dev/ttyUSB0"

#define REQUEST 0
#define RESPONSE 1
#define DATA    2

#define HELLO        0x01
#define CONNECT_TO   0x11
#define GET_BITMASK  0x22
#define STOP         0x31

#define SPEED        0
#define RPM          1
#define TEMP         2


char cmd[4];

unsigned char* data_names[] = { "SPEED", "RPM" };
unsigned char buffer_out[20];
unsigned char buffer_in[20];
int i;
struct termios attribs;
fd_set select_set;
int tty_fd = -1;
char a;



int init() {
  memset(&attribs, 0, sizeof(attribs));
  cfsetispeed(&attribs, B38400);
  cfsetospeed(&attribs, B38400);

  attribs.c_cflag |= CS8;
  attribs.c_cc[VMIN]  = 1;
  attribs.c_cc[VTIME] = 8;

  tty_fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC);
  tcsetattr(tty_fd, TCSANOW, &attribs);
  tcflush(tty_fd, TCIFLUSH);

  FD_ZERO(&select_set);
  FD_SET(tty_fd, &select_set);
  return tty_fd;
}

int readS(void* buffer, unsigned int nbytes) {
  if(nbytes <= 0)
    return 0;
  select(tty_fd+1, &select_set, NULL, NULL, NULL);
  FD_SET(tty_fd, &select_set);
  return read(tty_fd, buffer, nbytes);
}

int writeC(unsigned char c) {
  return write(tty_fd, &c, 1);
}

int writeS(unsigned char * str, unsigned int nbytes) {
  return write(tty_fd, str, nbytes);
}

unsigned char readC()
{
    static char c;
    select(tty_fd+1, &select_set, NULL, NULL, NULL);
    FD_SET(tty_fd, &select_set);
    read(tty_fd, &c, 1);
    return c;
}


int main()
{
  printf("Send/Receive data through serial_usb port\n");
  init();
  if(tty_fd == -1) {
    printf("Errore nell'apertura dello stream\n");
    exit(-1);
  }

  for(;;){
    readS(cmd,3);
    if(cmd[0] == REQUEST) {
      printf("Richiesta: ");
      switch(cmd[1]){
      case HELLO:
        printf(" HELLO\n");
        break;
      case CONNECT_TO:
        printf(" CONNECT_TO\n");
        break;
      case GET_BITMASK:
        printf(" GET_BITMASK\n");
        buffer_out[0] = (unsigned char)RESPONSE;
        buffer_out[1] = (unsigned char)GET_BITMASK;
        buffer_out[2] = (unsigned char)2;
        buffer_out[3] = (unsigned char) 0xc0;
        buffer_out[4] = (unsigned char) 0x00;
        writeS(buffer_out, 5);
        break;
      }
    }else if (cmd[0] == DATA) {
      printf("Data: %s\n====", data_names[cmd[1]]);
      readS(&buffer_in, cmd[2]);
      for(i=0; i<cmd[2]; i++) {
        printf("%d-", (int)buffer_in[i]);
      }
      printf("\n");
      buffer_out[0] = (unsigned char)RESPONSE;
      buffer_out[1] = (unsigned char)cmd[1];
      buffer_out[2] = (unsigned char) 1;
      buffer_out[3] = (unsigned char) 0;
      writeS(buffer_out, 4);
    }
    fflush(stdout);
  }
  printf("   .... Fatto\n");
}
