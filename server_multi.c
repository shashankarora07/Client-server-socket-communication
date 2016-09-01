/* Run this server code on pc machine and upto 10 clients could be connected */ 
#include"header.h"

struct sockaddr_in address,new_address;	
pthread_t thread[10];                  // Can change the value according to your processor efficency.
//pthread_attr_t *attr;
int new_sockfd[10];                    // Can change the value as per your need.
pthread_attr_t attr;
void *thread_function(void *);
int i = 0;

int main()
{
	int sockfd, len, bind_ret, lis_ret, len_client, thfd, th_init, th_detach;
	address.sin_family = AF_INET;
	address.sin_port = htons(5038);
	address.sin_addr.s_addr = INADDR_ANY;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd < 0)
	{
		perror("socket");
		goto OUT;
	}
	printf("%s : sockfd = %d\n",__FILE__,sockfd);
	len = sizeof(struct sockaddr_in);
	len_client = sizeof(struct sockaddr_in);
	
	bind_ret = bind(sockfd, (struct sockaddr *)&address,len);
	if (bind_ret == -1)
	{
		perror("bind");
		goto OUT;
	}
	
	lis_ret = listen(sockfd,10);
	if (lis_ret == -1)
	{
		perror("listen");
		goto OUT;
	}
	
	th_init = pthread_attr_init(&attr);
	if (th_init == -1)
	{
		perror("pthread_attr_init");
		goto OUT;
	}

	th_detach = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	if (th_detach == -1)
	{
		perror("pthread_attr_setdetachstate");
		goto OUT;
	}
	
	//for(i = 0; i < 10; i++)
	while(1)
	{
		new_sockfd[i] = accept(sockfd,(struct sockaddr *)&new_address,(socklen_t *)&len_client);
		if (new_sockfd[i] == -1)
		{
			perror("accept");
			goto OUT;
		}
		printf("%s : new_sockfd %d = %d\n",__FILE__,i,new_sockfd[i]);
	
		thfd = pthread_create(&thread[i],&attr,thread_function,&new_sockfd[i]);
		i++;
	}

	close(sockfd);
	return 0;
OUT: 	return -1;	
}	
	
void *thread_function(void *argu)
{	
	int new_fd; 
	new_fd = *(int *) argu;
	char buff[BUFSIZ];
	int count, k;
	
	while(1)
	{
		memset(buff,'\0',sizeof(buff));
		//fgets(buff,strlen(buff),stdin);	
		count = read(new_fd,buff,BUFSIZ);
		printf("Server read %d bytes\n",count);
		printf("you wrote: %s\n",buff);
		for (k = 0; k <= i; k++)
		{
			if (new_fd == new_sockfd[k])
				{
				continue;
				}
			else
				{
				write(new_sockfd[k],buff,BUFSIZ);
				}
		}		
	}	
}	


