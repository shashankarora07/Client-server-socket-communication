#include"header.h"

struct sockaddr_in addr_client;
int main()
{	
	int sockfd, con_ret, len_client,count;
	char buff[BUFSIZ];
	addr_client.sin_family = AF_INET;	
	addr_client.sin_port = htons(5026);
	addr_client.sin_addr.s_addr = inet_addr("127.0.0.1");	
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd < 0)
        {
                perror("socket");
                goto OUT;
        }
	printf("%s : sockfd = %d\n",__FILE__,sockfd);
	len_client = sizeof(struct sockaddr_in);

	con_ret = connect(sockfd,(struct sockaddr *)&addr_client,(size_t)len_client);
	if (con_ret == -1)
	{
                perror("connect");
                goto OUT;
	}
	else
	{
		printf("socket connected\n");
	}
	
	printf("Enter anything which is in your mind\n");
	while(1)
	{
		memset(buff,'\0',sizeof(buff));
		
		fgets(buff,BUFSIZ,stdin);
		count = write(sockfd,buff,strlen(buff));
		printf("client wrote %d bytes\n",(count));
		//fputs(buff,stdout);
		
	}		
	close(sockfd);

	return 0;
OUT:	return -1;
}

