#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

uint64_t calculateFactorial(uint64_t n)
{
    uint64_t factorial = 1;

    for (uint64_t i = 1; i <= n; ++i)
    {
        factorial *= i;
    }

    return factorial;
}

void *threadFunction(void *arguments)
{
    int clientFD = *((int *)arguments);
    char buffer_To_Receive_Numbers_From_Client[1024];

    while (1)
    {
        int bytesReceived;
        if ((bytesReceived = recv(clientFD, buffer_To_Receive_Numbers_From_Client, sizeof(buffer_To_Receive_Numbers_From_Client), 0)) > 0)
        {
            uint64_t num = atoi(buffer_To_Receive_Numbers_From_Client);
            uint64_t factorial = num <= 20 ? calculateFactorial(num) : calculateFactorial(20);

            //printf("Number Sent by Client is: %ld and it's Factorial is: %ld\n", num, factorial);

            if (send(clientFD, &factorial, sizeof(factorial), 0) == -1)
            {
                printf("Failed to Send Data to Client\n");
                exit(1);
            }

            bzero(buffer_To_Receive_Numbers_From_Client, sizeof(buffer_To_Receive_Numbers_From_Client));
        }

        else if (bytesReceived == 0)
        {
            close(clientFD);
        }
    }

    free(arguments);
    pthread_exit(NULL);
}

int main()
{
    int socketFD;
    struct sockaddr_in serverAddress;

    if ((socketFD = socket(AF_INET, SOCK_STREAM, 0)) != -1)
    {
        printf("\n\nTCP Socket is Created\n");

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(8081);
        serverAddress.sin_addr.s_addr = inet_addr("11.0.2.9");

        if (bind(socketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != -1)
        {
            printf("\nSocket is Binded to Port no.8081\n");

            if (listen(socketFD, 100) != -1)
            {
                printf("\n\nListening....\n\n");

                int *clientFD;
                struct sockaddr_in clientAddress;
                socklen_t clientAddressLength = sizeof(clientAddress);

                while (1)
                {
                    clientFD = (int *)malloc(sizeof(int));

                    if ((*clientFD = accept(socketFD, (struct sockaddr *)&clientAddress, &clientAddressLength)) != -1)
                    {
                        //printf("\nConnection Accepted from Client with IP Address: %s and Port no.: %d\n\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

                        pthread_t thread;
                        if (pthread_create(&thread, NULL, threadFunction, clientFD) != 0)
                        {
                            printf("Failed to create thread for client");
                            exit(1);
                        }
                    }

                    else
                    {
                        printf("Failed to Accept Client Socket\n");
                        exit(1);
                    }
                }

                free(clientFD);
            }

            else
            {
                printf("Failed to Listen\n");
                exit(1);
            }
        }

        else
        {
            printf("Failed to Bind\n");
            exit(1);
        }
    }

    else
    {
        printf("Failed to Create Socket\n");
        exit(1);
    }

    close(socketFD);

    return 0;
}
