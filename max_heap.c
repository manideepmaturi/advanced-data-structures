#include <stdio.h>
#include<stdbool.h>
int main()
{
    int n,pos,par;
    scanf("%d",&n);
    int a[n+1];
    int size=1;
    while(true){
        if(size>n){
            printf("heap is full\n");
            break;
        }
        printf("enter element");
        scanf("%d",&a[size]);
        pos = size;
        par = pos/2;
        while(pos>1 && a[pos]>a[par]){
            int temp =a[pos];
            a[pos]=a[par];
            a[par]=temp;
            pos = par;
            par = pos/2;
        }
        size++;
    }
    for(int i=1;i<=n;i++){
        printf("%d\n",a[i]);
    }
    return 0;
}
