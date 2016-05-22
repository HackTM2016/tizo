#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

static void error(const char *msg) { perror(msg); exit(0); }

int send_http(int count, char *params[])
{
  int portno =        80;
  char *host =        "172.16.2.79";
  char *message_fmt = "GET /lights/%s/ HTTP/1.0\r\n\r\n";

  struct hostent *server;
  struct sockaddr_in serv_addr;
  int sockfd, bytes, sent, received, total;
  char message[1024],response[4096];

  if (count < 2) { puts("Parameters: <color>"); exit(0); }

  /* fill in the parameters */
  sprintf(message,message_fmt, params[1]);
  printf("Request:\n%s\n",message);

  /* create the socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) error("ERROR opening socket");

  /* lookup the ip address */
  server = gethostbyname(host);
  if (server == NULL) error("ERROR, no such host");

  /* fill in the structure */
  memset(&serv_addr,0,sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

  /* connect the socket */
  if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
    error("ERROR connecting");

  /* send the request */
  total = strlen(message);
  sent = 0;
  do {
    bytes = write(sockfd,message+sent,total-sent);
    if (bytes < 0)
      error("ERROR writing message to socket");
    if (bytes == 0)
      break;
    sent+=bytes;
  } while (sent < total);

  /* receive the response */
  memset(response,0,sizeof(response));
  total = sizeof(response)-1;
  received = 0;
  do {
    bytes = read(sockfd,response+received,total-received);
    if (bytes < 0)
      error("ERROR reading response from socket");
    if (bytes == 0)
      break;
    received+=bytes;
  } while (received < total);

  if (received == total)
    error("ERROR storing complete response from socket");

  /* close the socket */
  close(sockfd);

  /* process response */
  printf("Response:\n%s\n",response);

  return 0;
}
