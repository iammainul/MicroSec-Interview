#include<stdio.h>
#include<string.h>  
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>    
 
int main(int argc , char *argv[])
{
    FILE *in;
    char buff[256];
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
     
    
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 2999 );
     
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
      
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
   
    listen(socket_desc , 3);
     
 
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0){
        perror("accept failed");
        return 1;
    }
    else{
        puts("Connection accepted");
        //system(wget -r $url | grep $word >> word.txt);
        if(!(in = popen("wget -r www.usec.io | grep Ninja >> word.txt", "r")))
            return 0;
    pclose(in);

    }
     
    return 0;
}