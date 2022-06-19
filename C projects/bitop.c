#include <stdio.h>
#include <stdlib.h>
/*stdint allows for uint32_t ints */
#include <stdint.h>

int main()
{
    int bit;
    char sorc;
    /*unsigned int*/
    uint32_t initialVal;
    uint32_t Val;
    uint32_t res;
    
    printf("Please enter initial value between 1 and 30000\n");
    /* the entered value is stored in variable initialval*/
    scanf(" %d", &initialVal);

    /*check if the initialVal is between 1 and 30000 if not then throw error*/
    if(initialVal<1 || initialVal>30000)
    {
	fprintf(stderr, "initial value must be between 1 and 30000 inclusive\n");    
        exit(1);	    
    }
    
    /*ask user which bit to manipulate and store their answer to bit*/
    printf("Which bit would you like to manipulate? Enter 0 - 31 representing 2^0 - 2^31\n");
    scanf(" %d", &bit);

    /*Check if the bit input is between 0 and 31*/
    if(bit<0 || bit>31)
    {
        fprintf(stderr, "bit to manipulate must be between 0 and 31\n");	    
        exit(1);
    }	    
    /*ask user if they want to set or clear the bit, any other value besides s or c will exit program */
    printf("Enter s or c to set or clear this bit: ");
    scanf("  %c \n", &sorc);
    /*check if the user wants to continue setting or clearing the bits. if the sorc variable is not s or c, the while loop will break and program exits*/
  
    while(sorc == 'c' || (sorc == 's' ))
    {
        if(sorc == 'c')
	    {
	        /*this will set val to have 0s up until the bit location that the user specifies*/
	        Val = 0;
            Val = (0 << (bit-1));
            res = initialVal & Val;
            printf("result: %d \n", res);
            initialVal = res;	    
	    }
	
	    else if (sorc == 's')
	    {
	        /*val will be set to a 1 followed by trailing zeroes determined by bit-1. this will be used to do comparison in bitwise operators*/
	        Val = 1;
            Val = 1<<(bit-1);
            /*going to use inclusive or bitwise operator */
            res = initialVal | Val;
            printf("result: %d\n", res);
            /*store res as initial val now so the user can keep manipulating this val instead of the initial val*/
            initialVal = res;	    
	    }
        
        printf("Enter another bit to set or clear: \n");
        scanf("%d", bit);
	    printf("Set or Clear this bit?: \n");
        scanf("%c", sorc);	

    }	    
    
    	    
    exit(0);
}	
