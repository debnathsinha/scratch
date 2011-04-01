#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main() {

  char buf[4096];
  int len;
  int fd;
  struct sockaddr_in si;
  char c;

  if( (fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1 ) {
    perror("foo");
  }
  si.sin_family = AF_INET;
  inet_pton(PF_INET, "127.0.0.1", &si.sin_addr);
  si.sin_port = htons(6780);
  if( (connect(fd,(struct sockaddr*)&si, sizeof si)) == -1 ) {
    perror("foo2");
  }
  // if( (write(fd, "GET / HTTP/1.0\r\n\r\n", 22)) == -1 ) {
  //   perror("foo3");
  // }
  if( (write(fd, "GET / HTTP/1.0\r\n\r\n", 22)) == -1 ) {
    perror("foo3");
  }
  printf("wrote\n");
  if( len = read(fd, buf, 4096) == -1 ) {
    perror("read error: ");
  }
  printf("read: %s\n", buf);
  while( (c = getchar()) != '\0' ) {
    if( (write(fd, "fmoo", 22)) == -1 ) {
      perror("foo3");
    } else {
      printf("wroteinloop: %c\n", c);
    }
    if( len = read(fd, buf, 4096) == -1 ) {
      perror("read error: ");
    }
    printf("read: %s\n", buf);
    getchar();
  }
  close(fd);
}
