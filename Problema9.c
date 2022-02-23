#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int citiren(int n)
{
    FILE* f=fopen("date.in","r");
    fscanf(f,"%d",&n);
    fclose(f);
    return n;
}

void alocare(int ***m,int nl,int nc)
{
    int i;
    (*m)=(int**)malloc(nl*sizeof(int*));
    for(i=0;i<nl;i++)
        (*m)[i]=(int*)calloc(nc,sizeof(int));
}

void afisare(int **m,int nl,int nc)
{
    FILE* f=fopen("date.out","w+");
    int i,j;
    for(i=0;i<nl;i++)
    {
        for(j=0;j<nc;j++)
            fprintf(f,"%d ",m[i][j]);
        fprintf(f,"\n");
    }
    fclose(f);
}

void matrice(int n,int lmax,int cmax,int **m,int i,int j,int tot,int ok)
{
    if(n==0)
       {if(tot==1)
            {m[i][j]=1;
            return;}
        else {if(ok==1)
                m[i][j]=1;
            return;}}

    if(tot==1)
    {
        matrice(n-1,lmax-pow(2,n-1),cmax,m,i,(j+cmax)/2+1,1,0);//dreapta sus
        matrice(n-1,lmax-pow(2,n-1),cmax-pow(2,n-1),m,i,j,1,0);//stanga sus
        matrice(n-1,lmax,cmax-pow(2,n-1),m,(i+lmax)/2+1,j,1,0);//stanga jos
        matrice(n-1,lmax,cmax,m,(i+lmax)/2+1,(j+cmax)/2+1,1,0);//dreapta jos
    }
    else{
        matrice(n-1,lmax-pow(2,n-1),cmax,m,i,(j+cmax)/2+1,1,0);//dreapta sus
        matrice(n-1,lmax-pow(2,n-1),cmax-pow(2,n-1),m,i,j,0,0);//stanga sus
        matrice(n-1,lmax,cmax-pow(2,n-1),m,(i+lmax)/2+1,j,0,0);//stanga jos
        matrice(n-1,lmax,cmax,m,(i+lmax)/2+1,(j+cmax)/2+1,0,0); //dreapta jos
    }

}
int main()
{
    int nc,nl,i,n;
    int **m;
    n=citiren(n);
    nl=pow(2,n);
    nc=nl;
    if(n>=0)
    {alocare(&m,nl,nc);
    matrice(n,nl-1,nc-1,m,0,0,0,1);
    afisare(m,nl,nc);
    for(i=0;i<nl;i++)
        free(m[i]);
    free(m);}
    else printf("Matricea nu se poate forma");
    return 0;
}
