#include <stdio.h>

/* this function takes an int argument and converts that argument into a double using a double constant variable */
double MlToOz (int value)
{
    const double OZ_IN_ONEML = 0.0338;
    double ml                = value; 
    /*multiplying int with double constant will result in double */
    double oz                = ml * OZ_IN_ONEML; 
     
    return oz;
}

int main (void) 
{
    char mainTitle[] = "Convert Mililiters";	
    char mlTitle[]   = "Mililiters";
    char ozTitle[]   = "Ounces";
    int ml1          = 10;
    int ml2          = 18;
    int ml3          = 30;
    int ml4          = 58;
    
    printf ("%25s\n", mainTitle);
    /*Each column below main title will occupy 15 spaces */
    printf ("%15s %15s\n", mlTitle, ozTitle);
    printf ("%15d %15.4lf\n", ml1, MlToOz(ml1));
    printf ("%15d %15.4lf\n", ml2, MlToOz(ml2));
    printf ("%15d %15.4lf\n", ml3, MlToOz(ml3));
    printf ("%15d %15.4lf\n", ml4, MlToOz(ml4));
}

