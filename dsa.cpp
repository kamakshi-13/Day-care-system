#include <iostream>

int vertarr[20][20];
int count=0;
void display(int v){
	int i,j;
	for(i=0;i<v;i++){
		for(j=0;j<v;j++){
			cout<<vertarr[i][j];
		}
	}
	
}
void add(int u,int v){
	vertarr[u][v]=1;
	vertarr[v][u]=1;
}
int main(){
	int v=3;
	add(2,5);
	add(3,6);
	add(7,9);
	
	display(v);
	
	return 0;
}
