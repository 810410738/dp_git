/*
ĳ�����ݼƻ����ţ��⽫n̨��ͬ���豸�����m�����䣬�������������豸��
����Ϊ�����ṩӯ��Ci j(į�豸�ṩ��j�ų��佫�õ�������1��i��n��1��j��m) ��
����η��䣬��ʹ���ҵõ�����ӯ����
*/
/*
����5̨�豸�����3�����䣬c����Ϊ[
	1 2 1 
	2 4 3
	4 5 4 
	5 6 8
	8 7 9 
] 
*/
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int count = 0;
long long Max = 0;
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
int cal(int **c, int *temp, int n, int m){
	int sum= 0; 
	int i,j;
	for(j=1;j<=m;j++){
		sum += c[temp[j]][j];
	}
	return sum;
}
void violence1(int**c,int * temp,int n, int m,int j,int * Result){
	int i , result;
	if(j>=m){
		temp[j] = n;
		for(int k=1;k<m;k++){
			temp[j] -= temp[k]; 
		}
		if(temp[j]<0){
			return ;
		}
		//print
//		for(int k=1;k<=m;k++){
//			cout<<temp[k]<<" ";
//		}
//		cout<<endl;
		result = cal(c,temp,n,m);
		if(result > Max){
			for(int k=1;k<=m;k++){
				Result[k] = temp[k];
		}
			Max = result;
		}
		//������������һ 
		count++;
		return ;
	}
	for(i=0;i<=n;i++){
		//�ŵĸ�����0����n����j��1��ʼ 
		temp[j] = i; 
		violence1(c,temp,n,m,j+1,Result);
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
//		result = max(result, c[i][j]+dp(c,n,m,i+1));
		int temp ;
		temp = c[i][j]+dp(c,n,m,i+1);
		if(temp>result){
			result = temp;
		}	 
	}
	return result;
} 
int dp_bottom_up(int**c,int n, int m){
	int i,j,k,temp;
	//new f
	int **f = new int*[n+1];
	for(i=0;i<=n;i++){
		f[i] = new int[m+1];
	}
	//init f = 0
	for(i=0;i<=n;i++){
		for(j=0;j<=m;j++){
			f[i][j] = 0; 
		}
	}
	for(j=1;j<=m;j++){//������ 
		for(i=1;i<=n;i++){//�豸��
				for(k=0;k<=i;k++)
				{	
					temp = f[k][j-1] + c[i-k][j];
					if(f[i][j] < temp ){
						f[i][j] = temp;
					}
				} 	
		}
	}
	 
	return f[n][m];
}
int main()
{
	int result;
	float time;
	time_t c_start,c_end;
	int i,j;
	int n,m;
	cin>>n>>m;
	int **c = new int*[n+1];
	for(i=0;i<=n;i++){
		c[i] = new int[m+1];
	}
	//input c array
	//��ʼ��ʱ
		c_start = clock();
		for(i=0;i<=n;i++){ 
		for(j=0;j<=m;j++){
			if(i == 0){
				c[i][j] = 0;
			}
			else if(i == 1){
				c[i][j] = rand();	
			}
			else{
			    c[i][j] = c[i-1][j] + rand();	
			}
			if(j == 0){
				c[i][j] = 0;
			}
//			cout<<c[i][j]<<" ";
		}
//		cout<<endl;
	}
	cout<<endl;
		c_end = clock();
		//������ʱ
		time = difftime(c_end, c_start);
	cout << "�����������ʱ��"<<time << "ms "<<endl;
	//new a temp array
	int *temp = new int[m+1];
	int * Result = new int[m+1];
	for(i=0;i<=m;i++){
		temp[i] = 0;
		Result[i] = 0;
	} 
	cout<<"***********************************************************"<<endl;
	cout<<"dp�Ե����ϣ�"<<endl;
	//��ʼ��ʱ
		c_start = clock();
		result = dp_bottom_up(c,n,m);
		c_end = clock();
		//������ʱ
		time = difftime(c_end, c_start);
	cout << "dp�Ե����Ϻ�ʱ��"<<time << "ms "<<endl;
	cout<<"dp�Ե���������ֵΪ:"<<result<<endl;
	  
	cout<<"***********************************************************"<<endl;
	/*
	cout<<"��������"<<endl;
		//��ʼ��ʱ
		c_start = clock();
		violence1(c,temp,n,m,1,Result);	
		c_end = clock();
		//������ʱ
		time = difftime(c_end, c_start);
	cout << "��������ʱ��"<<time << "ms "<<endl;
	cout<<"����ֵ����Ϊ��"<<endl; 
	for(i=1;i<=m;i++){
		cout<<Result[i]<<" ";
	} 
	cout<<endl;
	cout<<"����ֵΪ��"<<Max<<endl;
	cout<<"����������"<<count<<endl;
	cout<<"***********************************************************"<<endl;
	
	count = 0;
	cout<<"dp�ݹ�ʵ�֣�"<<endl;
		//��ʼ��ʱ
		c_start = clock();
		result = dp(c,n,m,0);
		c_end = clock();
		//������ʱ
		time = difftime(c_end, c_start);
	cout << "dp�ݹ��ʱ��"<<time << "ms "<<endl;
	cout<<"dp����ֵΪ:"<<result<<endl;
	cout<<"����������"<<count<<endl;
	*/ 
	for(i=0;i<n;i++){
		delete [] c[i];
	} 
	delete [] c;
	return 0;
}
