#include<stdio.h>
int graph[40][40],n,count=0;
void creategraph(){
printf("Number of vertices>>");
 scanf("%d",&n);
printf("Enter adjacency matrix:\n");
for(int i=0;i<n;i++){
for(int j=0;j<n;j++){
scanf("%d",&graph[i][j]);
}
}
}
void main(){
creategraph();
int temp;
for(int k=0;k<n;k++){
for(int i=0;i<n;i++){
temp=graph[i][k];
for(int j=0;j<n;j++){
 if(graph[i][j]>temp){
count++;
if(temp+graph[k][j]<graph[i][j])
graph[i][j]=temp+graph[k][j];
}
}
}
}
printf("Applying Floyd's algorithm\n");
printf("all pair shortest path matrix:\n");
for(int i=0;i<n;i++){
for(int j=0;j<n;j++){
printf("%d ",graph[i][j]);
}
printf("\n");
}
printf("operation count:%d\n",count);
}

