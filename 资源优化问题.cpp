/*
某厂根据计划安排，拟将n台相同的设备分配给m个车间，各车间获得这种设备后，
可以为国家提供盈利Ci j(i台设备提供给j号车间将得到的利润，1≤i≤n，1≤j≤m) 。
问如何分配，才使国家得到最大的盈利？
*/
/*
假设5台设备分配给3个车间，c数组为[
	1 2 3
	2 7 3
	4 5 1
	3 4 8
	8 4 2
] 
*/
#include<iostream>
#include<ctime>
using namespace std;
int count = 0;
int Max = 0;
int result2 = 0;
void show(int **c,int n, int m){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;	
}
int cal(int **c, int **temp, int n, int m){
	int sum= 0;
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(temp[i][j] == 1){
			 sum+=c[i][j];	
			}
		}
	}
	return sum;
}
void violence1(int**c,int ** temp,int n, int m,int i){
	int j , result;
	if(i>=n){
//		show(temp,n,m);
		result = cal(c,temp,n,m);
		if(Max < result)
		{
			Max = result;
		}
		count++;
		return ;
	}
	for(j=0;j<m;j++){
		//放
		temp[i][j] = 1; 
		violence1(c,temp,n,m,i+1);
		temp[i][j] = 0; 
	}
}

//优化后的蛮力法，不用辅助数组 
void violence2(int**c,int n, int m,int i){
	int j ;
	if(i>=n){
//		show(temp,n,m);
		if(Max < result2)
		{
			Max = result2;
		}
		count++;
		return ;
	}
	for(j=0;j<m;j++){
		//放
		result2 +=c[i][j] ; 
		violence2(c,n,m,i+1);
		result2 -=c[i][j];
	}
}
int dp(int**c,int n,int m,int i){
	if(i>=n){
		count++;
		return 0;
	}
	int j,result = 0;
	for(j=0;j<m;j++){
		//A放i
		result = max(result, c[i][j]+dp(c,n,m,i+1));	 
	}
	return result;
} 
int main()
{
	time_t c_start,c_end;
	int i,j;
	int n,m;
	cin>>n>>m;
	int **c = new int*[n];
	for(i=0;i<n;i++){
		c[i] = new int[m];
	}
	//input c array
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			cin>>c[i][j];
		}
	}
	//new a temp array
	int **temp = new int*[n];
	for(i=0;i<n;i++){
		temp[i] = new int[m];
	}
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			temp[i][j] = 0;
		}
	}
	//violence(c,temp,n,m,0);
	cout<<"蛮力法："<<endl;
		//开始计时
		c_start = clock();
		violence2(c,n,m,0);	
		c_end = clock();
		//结束计时
		float time = difftime(c_end, c_start);
	cout << "蛮力法耗时："<<time << "ms ";
	cout<<"遍历次数："<<count<<endl;
	cout<<"最大价值为："<<Max<<endl;
	cout<<"***********************************************************"<<endl;
	count = 0;
	cout<<"dp递归实现："<<endl;
	int result ;
		//开始计时
		c_start = clock();
		result = dp(c,n,m,0);
		c_end = clock();
		//结束计时
		time = difftime(c_end, c_start);
	cout << "dp递归耗时："<<time << "ms ";
	cout<<"dp:"<<result<<endl;
	cout<<"遍历次数："<<count<<endl;
	return 0;
}
