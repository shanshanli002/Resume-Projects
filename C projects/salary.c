#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	extern char *optarg;
	extern int optind;
	int c, err = 0; 
	int bflag  = 0, vflag = 0, rflag = 0, tflag = 0;
	int tnum;
	int base;
	int rnum;
	static char usage[] = "usage: %s [-bv] [-r rnum] -t tnum base\n";

	while ((c = getopt(argc, argv, "bvr:t:")) != -1)
		switch (c)
        {
		    case 'b':
			bflag = 1;
			break;
            
            case 'v':
			vflag = 1;
			break;
		    
            case'r':
			rflag = 1;
			rnum = atoi(optarg);
			break;	
		    
            case 't':
			tflag = 1;
            tnum = atoi(optarg);
            break;
		    
            case '?':
			err = 1;
			break;
		}

	/*check if any errors are present */
	if (tflag == 0) 
	{
		fprintf(stderr, "%s: Missing taxes\n", argv[0]);
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
       
	if ((tnum < 5 ) || (tnum > 30 )) 
	{
		/*checks if tax is within these bounds, if not print error and stop rest of execution of program*/
		fprintf(stderr, "%s: tax needs to be between 5 and 30\n", argv[0]);
        exit(1);
	} 

	if ((rflag != 0) && ((rnum < 2) || (rnum > 10))) 
	{
        /*if rflag exists and is not within these bounds, error is thrown*/
        fprintf(stderr, "%s: r needs to be between 2 and 10 inclusive\n", argv[0]);
        exit(1);
	}
       	
	if (err) 
	{
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}

	if ((tnum) && (atoi(argv[optind]) >= 20000) && (atoi(argv[optind]) <= 90000)) 
	{
		/*check if tax value exists and input not linked to tags is within these bounds. Value is set to base if passes.*/
		base = atoi(argv[optind]);
	} 
	else 
	{	
		fprintf(stderr, "%s: missing base\n", argv[0]);
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}
        
	/*if tags are present, will alter base accordingly*/
	if (vflag != 0) 
	{
		/*v flag is applied first*/
		base = base + 6000.00;
	}	

	if (rflag != 0 && (rnum >2 && rnum <10)) 
	{
        /*rflag is applied after v if exists*/
		base = base + (base*(rnum/100.00));
	}

    if (bflag != 0)
	{
        /*if b flag exists, then 5000 is added to base after r*/
		base = base + 5000;
	}

	/*tax is applied last after all additions to base are applied if flags are present */
    /*result will be printed with only 2 decimal places */
    printf("result: %.2lf\n", base-(base*(tnum/100.00)));

	exit(0);
}
