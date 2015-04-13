//
//  client-serverSocketP.c
//  csC
//
//  Created by Aygerim on 4/13/15.
//  Copyright (c) 2015 Aygerim. All rights reserved.
//

#include "client-serverSocketP.h"

int main(void){
    
    int s; //socket descriptor
    int len; //length of the string to be echoed
    char buffer[256]; // data buffer
    struct sockaddr_in serverAdd; //Server socket address
    struct sockaddr_in clientAdd; //Client address
    int clientAddLen;
    
    
    // LOCAL SOCKET ADDRESS
    memset(&serverAdd, 0,sizeof(serverAdd)); //memory allocation
    serverAdd.sin_family= AF_INET; //family field
    serverAdd.sin_port = htons(SERVER_PORT); //PORT NUMBER
    serverAdd.sin_addr.s_addr = htonl(INADDR_ANY); // IP ADDRESS
    
    //CREATE SOCKET
    
    if((s= socket(PF_INET, SOCK_DGRAM, 0)<0))
    {
        perror("Error:socket failed");
        exit(1);
    }
    
    //binding socket to local address and port
    
    if(bind(s,(struct sockaddr*)&serverAdd, sizeof(serverAdd))<0)
    {
        perror("Error:bind failed");
        exit(1);
        
    }
    
    for(;;) // server side is finite, so running forever
    
    {
        //recerive a string
        len = (int)recvfrom(s, buffer, sizeof(buffer), 0,(struct sockaddr*)&clientAdd, &clientAddLen);
        
        // send string
        sendto(s, buffer, len, 0, (struct sockaddr*)&clientAdd, sizeof(clientAdd));
        
        // receive string
    }
    
    
    
}