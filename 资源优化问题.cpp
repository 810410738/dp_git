/*
ĳ�����ݼƻ����ţ��⽫n̨��ͬ���豸�����m�����䣬�������������豸��
����Ϊ�����ṩӯ��Ci j(į�豸�ṩ��j�ų��佫�õ�������1��i��n��1��j��m) ��
����η��䣬��ʹ���ҵõ�����ӯ����
*/
/*
����5̨�豸�����3�����䣬c����Ϊ[
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
		//��
		temp[i][j] = 1; 
		violence1(c,temp,n,m,i+1);
		temp[i][j] = 0; 
	}
}

//�Ż���������������ø������� 
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
		//��
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
		//A��i
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
	cout<<"��������"<<endl;
		//��ʼ��ʱ
		c_start = clock();
		violence2(c,n,m,0);	
		c_end = clock();
		//������ʱ
		float time = difftime(c_end, c_start);
	cout << "��������ʱ��"<<time << "ms ";
	cout<<"����������"<<count<<endl;
	cout<<"����ֵΪ��"<<Max<<endl;
	cout<<"***********************************************************"<<endl;
	count = 0;
	cout<<"dp�ݹ�ʵ�֣�"<<endl;
	int result ;
		//��ʼ��ʱ
		c_start = clock();
		result = dp(c,n,m,0);
		c_end = clock();
		//������ʱ
		time = difftime(c_end, c_start);
	cout << "dp�ݹ��ʱ��"<<time << "ms ";
	cout<<"dp:"<<result<<endl;
	cout<<"����������"<<count<<endl;
	return 0;
}
