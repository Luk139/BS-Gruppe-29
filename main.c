//Echo Server Programm - sendet eingegebene Nachricht zurück
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define LOOP 1
#define BUFSIZE 1024 // Größe vom buffer
//Port zum verbinden mit Docker Container über Telnet mit telnet 127.0.0.1 5688 (oder welcher Port hier definiert wird)
#define PORT_NUMBER 5691

int put(char* key, char* value){

}
int get(char* key, char* res){

}
int del(char* key){

}


int main() {
    //File-Descriptor Rendezvous und Connect
    int rndvz_fd;
    int cnnct_fd;
    //  Struct für die Verbindung zwischen client und server
    struct sockaddr_in client;
    //Länge der Client-Data
    socklen_t client_len;
    // Counter für die gesendeten Bytes vom Client
    int read_bytes;
    // Char-Array für Nachrichten vom Client zum Server
    char in[BUFSIZE];
    rndvz_fd = socket(AF_INET, SOCK_STREAM, 0);
    //  Return value von rndzvs_fd ist negative bei error und 0 when erfolgreich. Falls nicht erfolgreich - Terminiert sich das Programm
    if (rndvz_fd < 0) {
        perror("Error while socket()");
        return EXIT_FAILURE;
    }
    // Set Option for the Socket for rapid iterative binding to address
    int option = 1;
    setsockopt(rndvz_fd, SOL_SOCKET, SO_REUSEADDR, (const void *) &option, sizeof(int));
    //  Struct for the connection between client and server
    struct sockaddr_in server;
    //  Define to use ipv4
    server.sin_family = AF_INET;
    //  Define from which ip-address clients want to connect to server, any address is allowed
    server.sin_addr.s_addr = INADDR_ANY;
    //  Define port number on which the client wants to connect
    server.sin_port = htons(PORT_NUMBER);
    int bnd_result = bind(rndvz_fd, (struct sockaddr *) &server, sizeof(server));
    // Ask for return value of the function to check for error while binding => terminate program if error
    if (bnd_result < 0) {
        perror("Error while bind()");
        return EXIT_FAILURE;
    }
    //  Max. capacity for clients communicating with the server
    const int max_clients = 5;
    int lstn_result = listen(rndvz_fd, max_clients);
    // Check return value for error
    if (lstn_result < 0) {
        perror("Error while listen()");
        return EXIT_FAILURE;
    }
    while (LOOP) {
        cnnct_fd = accept(rndvz_fd, (struct sockaddr *) &client, &client_len);
        if (cnnct_fd < 0) {
            perror("Error while accept()");
            return EXIT_FAILURE;
        }
        // read the bytes from the client
        read_bytes = read(cnnct_fd, in, BUFSIZE);
        if (read_bytes < 0) {
            perror("Error while read()");
            return EXIT_FAILURE;
        }
        //Das while sendet solange etwas zurück, wie der client was schreibt
        while (read_bytes > 0) {
            //Clion console ausgabe, client terminal sieht hiervon nichts
            printf("sending back the %d bytes I received...\n", read_bytes);

            write(cnnct_fd, in, read_bytes);

            read_bytes = read(cnnct_fd, in, BUFSIZE);
            if (strncmp("exit", in,4) == 0) {
                printf("Server Exit...\n");
                break;
            }
            //FUnktioniert NICHT
            if(strncmp("put",in,BUFSIZE)==0){
                write(cnnct_fd,"okey test funktioniert",read_bytes);
            }
        }
        close(cnnct_fd);
    }
    close(read_bytes);
}