// C Code of Client Side:

#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>

#include<unistd.h>

// Defining Macros for Port Number and Buffer Size:

#define PORT 5000
#define BUFFER_SIZE 20

//Function for receiving video from the Server:

void get_video(int socket)
{
   char Buffer[BUFFER_SIZE];
   int flag;
   
   //Opening a new video file:
   
   FILE* file = fopen("client_video.mp4", "w");
   
   printf(">> Receiving Video from the Server\n");
        
   while(1)
   {
     flag = recv(socket, &Buffer, BUFFER_SIZE, 0);
     
     //EOF to terminate:
     
     if(flag <= 0)
     break;
     
     // Receiving Chunks of 20 Bytes from the Server
     // Writing them in a new video file:
     
     fwrite(Buffer, BUFFER_SIZE, 1, file);
   }
   
   printf(">> Video Received Successfully!\n");
   
   //Closing File:
   fclose(file);
}

int main()
{
   // Creating a TCP client Socket:

   int client = socket(AF_INET, SOCK_STREAM, 0);
   
   // Address and Port for the Socket:
   
   struct sockaddr_in address;
   address.sin_family = AF_INET;
   address.sin_port = htons(PORT); // Connects to Port Number 5000
   address.sin_addr.s_addr = INADDR_ANY; // Any IP address
   
   // Connecting to the Server:
   
   int connection = connect(client, (struct sockaddr*) &address, sizeof(address));
   
   if (connection == -1)
   printf("Connection Failed!\n");
   
   else
   {   
     printf(">> Connection Estabilished with the Server!\n");
   
     // Getting Data from the Server:
     get_video(client);  
   }
   
   // Closing Connection:
   
   close(client);

   return 0; 
}
