//
//  client_udp.c
//  csC
//
//  Created by Aygerim on 4/13/15.
//  Copyright (c) 2015 Aygerim. All rights reserved.
//

#include "client-serverSocketP.h"
int main(int argc, char* argv[]){
    int s;
    int len;
    char* serverName;
    int serverPort;
    char* string;
    char buffer[256+1];
    struct sockaddr_in serverAdd;
    
    if(argc != 3){
        printf("error: three arguments are needed");
        exit(1);
    }
    serverName = argv[1];
    serverPort = atoi(argv[2]);
    
    string = argv[3];
    
    //building server socket address
    
    memset(&serverAdd, 0, sizeof(serverAdd));
    serverAdd.sin_family= AF_INET;
    inet_pton(AF_INET, serverName,&serverAdd.sin_addr);
    serverAdd.sin_port = htons(serverPort);
    
    //create a socket
    if ((s= socket(PF_INET, SOCK_DGRAM,0)<0)){
        perror("Error:socket failed");
        exit(1);
        
    }
    
    //sending string
    
    len = (int)sendto(s, string, strlen(string), 0, (struct sockaddr*)&serverAdd, sizeof(serverAdd));
    
    // receive string
    recvfrom(s, buffer, len, 0, NULL, NULL);
    
    // print the string
    buffer[len] = '/0';
    printf("Echo string received:");
    fputs(buffer, stdout);
    
    close(s);
    exit(0);
    
}
