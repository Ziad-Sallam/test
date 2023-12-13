#include <stdio.h>

int main()
{
    int n;
    int power;
    scanf("%i", &power);
    scanf("%i", &n);

    int a[n][n];
    int b[n][n];
    int c[n][n];
    
   for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < n;j++)
        {
            scanf("%i", &a[i][j]);
            a[i][j] = b[i][j];
        }
    }
    for (int q = 0; q < power; q++)
    for (int i = 0; i < n; i++) {
        
        for (int j = 0; j < n; j++) {
        
        c[i][j] = 0;
        
        for (int k = 0; k < n-1; k++) {
            
            c[i][j] |= a[i][k] & b[k][j];
        }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) 
        {
            a[i][j] = c[i][j]; 
        }
    }

        
    for (int i =0; i < n; i++)
    {
        for(int j = 0; j< n; j++)
        {
            printf("%i ", c[i][j]);
        }
        printf("\n");
    }

}
