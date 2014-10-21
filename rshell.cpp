#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<cstring>
#include<stdio.h>
#include<cstdlib>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

int main(int argc, char *argv[])
{
	while(1)
	{
		char token[128];
		char username[128];
		char hostname[128];
		getlogin_r(username,128);	
		gethostname(hostname,128);
		cout << username << "@" << hostname << "$";
		cin.getline(token, 128);

		if(strcmp(token,"exit") == 0)
		{
			exit(1);//if user typed exit, it exits the program.
		}	
		unsigned l;	
		while(token[l] != '\0')
		{
			if(token[l] == '#');
			{
				token[l] = '\0';
			}	
		    l++;
		}
		char **argument;
		argument = new char *[128];//creates array of pointers

		int i = 0;//counts when it gets to end of line using strtok;
						
		char *cmptoken = strtok(token, " ");
	
		while( cmptoken != NULL)
		{
			argument[i] = cmptoken;
			for(;i< 128;i++);
			cmptoken = strtok(NULL," ");
		}
		argument[i] = NULL;//ends the strtok with a null to make sure its finished
			
		
		int forkvar = fork();//uses pid to identify processes
		
		if(forkvar)//parent process which runs 
		{
			wait(0);
		}
			
		 else if(forkvar == 0)//child process which lets us run exec
		{	wait(0);
			if(execvp(argument[0], argument) == -1)//takes in the argument from array.
			{
				perror("execvp did not run");
			}
			exit(1);//exits when fails
			
		}
		else
		{
			perror("Fork failed");//error flag when forking fails
			return 0;
		}
		delete []argument;	
	}
	return 0;

}

