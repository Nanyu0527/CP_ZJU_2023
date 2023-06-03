int A[625],B[625],C[625];
int main(){ 
    int MA,NA,MB,NB,i=0,j=0,k=0;
    scanf("%d %d\n",&MA,&NA);
    while(i<MA){
        j=0;
        while(j<NA){
            scanf("%d",&A[i*NA+j]);
            j=j+1;
        }
        i=i+1;
    }
    i=0;
    j=0;
    scanf("%d %d",&MB,&NB);

    while(i<MB){
        j=0;
        while(j<NB){
            scanf("%d",&B[i*NB+j]);
            j=j+1;
        }
        i=i+1;
    }
    if(NA!=MB){
        printf("Incompatible Dimensions\n");
        return 0;
    }
    i=0;
    j=0;
    while(i<MA){
        j=0;
        while(j<NB){
            C[i*NB+j] = 0;
            k=0;
            while(k<NA){
                C[i*NB+j] = C[i*NB+j]+A[i*NA+k]*B[k*NB+j];
                k=k+1;
            }
            j=j+1;
        }
        i=i+1;
    }
    i=0;
    j=0;
    while(i<MA){
        j=0;
        while(j<NB){
            printf("%10d",C[i*NB+j]);
            j=j+1;
        }
        printf("\n");
        i=i+1;
    }
    return 0;
}