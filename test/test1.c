void quicksort(int T[10000], int L, int R) {
    int i = L;
    int j = R;    
    int mid;    
    mid = T[(L + R) / 2];
    int tmp;
    while(i <= j) {
        while (T[i] < mid) { 
            i = i + 1;
        }
        while (T[j] > mid) {
            j = j - 1;
        }
        if (i <= j) {
            tmp = T[i];
            T[i] = T[j];
            T[j] = tmp;
            i = i + 1;
            j = j - 1;
        }
    }
    if (L < j) {
        quicksort(T, L, j);
    }
    if (i < R) {
        quicksort(T, i, R);
    } 
    return;
}
int main(){
    int N;
    printf("haha");
    scanf("%d",&N);
    int index = 0;
    int ARRAY[10000];
    while(index < N){
        scanf("%d",&ARRAY[index]);
        index = index + 1;
    }
    int L = 0;
    int R = N - 1;
    quicksort(ARRAY,L,R);
    index = 0;
    while(index < N){
        printf("%d\n",ARRAY[index]);
        index = index + 1;
    }    
}   