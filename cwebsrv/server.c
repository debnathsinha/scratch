#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/proc_info.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char buf[4096];

void
read_request( int cfd ) {
  char c;
}

int main() {

  int cfd, fd;
  struct sockaddr_in si;
  int addrlen = sizeof(si);
  int rlen;
  
  if( (fd = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1 ) {
    perror("foo2");
  }
  si.sin_family = AF_INET;
  inet_pton(PF_INET, "127.0.0.1", &si.sin_addr);
  si.sin_port = htons(6780);
  if( (bind(fd, (struct sockaddr *)&si, sizeof si)) == -1 )
    perror("foo1.5");
  if( listen(fd, 5) == -1 )
    perror("foo1");
  printf("Received a connection\n");
  //while((cfd = accept(fd, (struct sockaddr*)&si, &addrlen)) != -1) {
  while((cfd = accept(fd, NULL, NULL)) != -1) {
    printf("Got something to read\n");
    if ((rlen = read(cfd, buf, 100)) != -1) {
      printf("Read %d bytes as %s ", rlen, buf);
    }
    if( write(cfd,"200 OK HTTP/1.0\r\n\r\n" "That's it", 9+23) == -1 )
      perror("Write failed coz");
    shutdown(cfd, SHUT_RDWR);
    close(cfd);
  }
  close(fd);
  perror("foo");
}
