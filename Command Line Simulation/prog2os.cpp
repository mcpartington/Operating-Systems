//=================================================================                                  
  // Authors: Maxwell Partington & Mary Wakefield                           
  // Date:        3/3/14                                                    
  // Course/ Assignement Number: CS 433 Operating Systems Progrmming HW 2
  // Functionality: This function essentially mimics the command line. It takes in user-entered instru//    ctions and determines whether these instructions are correc format. If they are, the instruction//     s are performed. This program will continue to take user commands until "exit" is called. This
//     will kill the program. Other featueres such as history of commands are including.  
  //=============================================================
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include<string>
#include <stdlib.h>
#include <sstream>
#include <vector>
using namespace std;
# define MAX_LINE 80

int commandCounter=0;// tracks the number of cammands entered by user
int argsCounter=0;// tracks the number of arguments per command 
vector<string> history;// vector to holds the user entered commands

//-----------------------------------------------------
// This function prints the last 10 commands entered by the user. 
//----------------------------------------------------
void printHistory()
{
  if( history.size() >= 10)// if there are more than 10, only print the last 10
    {
      int i=history.size() -10;
      for( i ; i < history.size() ; i++)
	cout<<i << " "<< history[i]<<endl;
    }
  else// if there are less than 10, only print what is in history
    {
      for( int j=0; j < history.size(); j++)
	cout<< j << " " << history[j]<<endl;
    }
}
//--------------------------------------------------------
//This function gets the user entered commands and performs error checking for exit, history, !!, and !n. It also updated the history vector with the current command entered by the user. 
//Parameters: token initally stores the user entered text
//            args contains all the arguments entered. each slot contains a full "word"
//            existAnd uses reference to check if & has been encountered
//            should_run uses reference to check if user wants to end the program
//----------------------------------------------------------- 
void setup( char token[], char *args[], int *existAnd, int *should_run) 
{

  int length;//num characters in the command line
  int start;
 
  fflush( stdout);  // clear out any backwash
  cin.getline(token, MAX_LINE);// get the user entered commands
  fflush( stdout); // clear out any backwash

  history.push_back(token);// enter the full token into history of commands vector

  char*  token1 = strtok(token, " ");// break token input by spaces
  while( token1 != NULL)// while there is still some string 
    {
      if((string) token1 == "exit" )// if user enters "exit", stop the program by changing shouldrun to 0
	{
	  *should_run =0;
	  exit(1);
	}
      if( (string) token1 == "history" )// if user enters history, print all 
	printHistory();
      if( (string) token1 == "!!" )// if user enteres !!, then call the last command
	{// this gets it from the history location
	  token1 = (char*)history[history.size() -2].c_str();// -2 because we have already stored this task into history
	  // cout<< "token1 " << token1 <<endl;
	}
      string stringToken = (string)token1;
	
      char *position;
      position= strchr(token1, '&');// returns NUll if not found

      if( position !=NULL)// & was found in the input
	*existAnd =1;
      char *pch;
      pch= strchr( token1, '!');
      if(pch!=NULL )// ! was found in the input
	{
	  //int num =pch;
	  //token1 = (char*)history[num].c_str(); 
	}

      args[argsCounter] = token1;
      token1 = strtok( NULL, " ");
      argsCounter++;// increment current location in args
    }

  args[argsCounter] = '\0';
}


//-----------------------------------------------------
//This is the main function where the other smaller functions are called. This is where the continuous while loop resides- which only stops when the user enteres "exit".
// this function calls the setup function to store and perform error checking on the user entered commands.
//Then, it forks a child processes, ensures it was done accurately, then either performs the child and parent concurently or the parent waits. The parent waits if there was no & in the command line. 
//-----------------------------------------------------
int main ()
{
  char * args[MAX_LINE /2 +1] = {};
  int should_run =1;
  int i=0;
  int argsSize=0;
  char token[MAX_LINE];
  int existAnd;//0 if no &, 1 if there is an &
  pid_t pid;

  while( should_run )
    {
      existAnd=0;
      cout<< "osh> "<< flush;
      fflush(stdout);

      setup( token,args, &existAnd, &should_run);// send info to get stored into the args array and look for exit, !!, or !N commands
      commandCounter++;

      //(1) fork a child process using fork()
      pid= fork();//for a child

      if( pid < 0)// error checking
	{ 
	  cout<<"fork failed"<<endl;
	  exit(1);
	}
      else if( pid ==0 )//child process
	{
	  if ( execvp( args[0], args) == -1)// parameters is the command and the array of args
	    cout<<"Error executing command"<<endl;
	}
      else
	{//if there is no &, parent will wait
	  if ( existAnd == 0)
	    wait(NULL);
	}
      //clear args and tokens array to ensure that there are not left over arguments from previous calls.       
      for( int m=0; m < argsCounter; m++)
	{
	  args[m]=NULL;
	}
      argsCounter=0;
      
    }
  for( int n=0; n < MAX_LINE; n ++)
    token[n] = NULL;
}
