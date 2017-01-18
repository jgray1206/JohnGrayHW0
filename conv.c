/*
**	Name: John Gray
**	Assignment: 1
**	Description: This program is a base converter.
**	It uses command line arguments to convert from
**	an inputted decimal number to an certain inputted
**	base. Bases that are powers of 2 are converted
**	using a mask/shift algorithm, while all other supported
**	bases are converted using mod/divison. 
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/"; //ascii conversion string	
char buffer[32]; 	//buffer that holds converted number
int counter = 30; 	//counter that keeps track of converted number length 

int main(int argc, char **argv)
{	
	// Program will only work if there are exactly 2 arguments (decimal, base).
	if(argc!=3)
	{
		printf("Usage: conv <decimal> <base>\n");
	}
	
	else
	{
		int decimal = atoi(argv[1]); 	//converts inputted decimal char
		int base = atoi(argv[2]); 	//converts inputted base char
		
		if(decimal==0||decimal<0)
		{
			printf("INVALID NUMBER\n");
			return 0;
		}
		//Checks if the inputted base is in the propper range
		if(base>16&&base!=64||base<2)
		{
			printf("INVALID BASE\n");
			return 0;
		}
	
		//This fancy algorithm checks if the given base is a power of 2 using 2s complement
		else if((base != 0)&&((base & (~base+1))==base))
		{	
			//continue looping until number is converted or buffers runs out of room
			while(decimal!=0&&counter>=0)
			{
				buffer[counter] = ascii[decimal&(base-1)]; 	//masks number, converts to ascii, stores it in buffer
				counter--; 					//since we put in a number, we must decrement the counter
				decimal = decimal >> (int)(log(base)/log(2)); 	//updates decimal number via shifting off masked part of binary
			}	
		}	
		
		else
		{	
			//very similar to above code, but for non 2 power bases. Uses simple mod/division algorithm.
			while(decimal!=0&&counter>=0)
			{
				buffer[counter] = ascii[decimal%base];
				counter--;
				decimal/=base;
			}
		}

		if(counter==-1||decimal!=0)
		{
			printf("NUMBER TOO LARGE\n");
		}else{
		printf("%s\n",&buffer[counter+1]); 	//outputs converted number in buffer. Uses counter to get right location.
		}
	}
	
	return 0;
}
