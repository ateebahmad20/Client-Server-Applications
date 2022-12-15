// C Code of Server Side:

#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

#include<unistd.h>

// Defining Macros for Port Number and Buffer Size:

#define PORT 5000
#define BUFFER_SIZE 20

// Function for sending File:

void send_video(int socket)
{

   char buffer[BUFFER_SIZE];
   
   // Opening and Reading the Contents of the Video file:
   
   FILE* file = fopen("server_video.mp4", "r");
   
   if(file == NULL)
   printf("No File Found\n");
     
   else
   {
       printf(">> Sending Video...\n");
       
      //Until EOF is Reached, sends Data in CHUNKS of 20 BYTES Each:
      
      while(fread(buffer, BUFFER_SIZE, 1, file) != 0)
        send(socket, buffer, BUFFER_SIZE, 0);
   }
   
   printf(">> Video Sent Successfully!\n");
   fclose(file);
}

int main()
{
  // Creating a TCP Socket for the Server: 
  
  int server = socket(AF_INET, SOCK_STREAM, 0);
  
  // IP Address and Port for the Socket:
  
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = INADDR_ANY;
  
  // Binding to the IP and Port:
  
  int status = bind(server, (struct sockaddr*) &address, sizeof(address));
  
  if(status == -1)
  printf("Binding Error\n");
  
  else
  {
    printf(">> Binding Successfull\n");
  
    // Listening to upto max 3 Connections:
  
    int status2 = listen(server, 3);
  
    if(status2 == -1)
    printf("Error in Listening\n");
  
    else
    printf(">> Listening for Connection...\n");
  
    // Sending Video to the Client Socket:
  
    int client_socket = accept(server, NULL, NULL); 
    send_video(client_socket);
  }
 
  // Closing Connection:
  
  close(server);
  printf(">> Connection Closed!\n");
  
  return 0;
}
