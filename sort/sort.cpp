#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
using namespace std;
static int dis=10;
long long Insertcompare=0,Insertswap=0;
long Quickcompare=0,Quickswap=0;
long Heapcompare=0,Heapswap=0;
//交换 
void swap(int a[],long i,long j){
	int temp;
	temp=a[j];
	a[j]=a[i];
	a[i]=temp;
}
//比较
bool compare(int i,int j){
	if(i<j)
		return true;
	else 
		return false;
}
//插入排序
void Insertsort(int a[],long n){
	for(long i=1;i<n;i++){
		for(long j=i;(j>0)&&(compare(a[j],a[j-1]));j--){
			swap(a,j,j-1);
			Insertswap++;
			Insertcompare++;
		}
		Insertcompare++;                                 //结束循环进行一次比较
	}
}
//快速排序
int findpivot(int a[],long i,long j){
	return (i+j)/2;
}
int partition(int a[],int l,int r,int&pivot){
	do{                                
		while(compare(a[++l],pivot)){
			Quickcompare++;                             //比较
		};
		Quickcompare++;
		while((l<r)&&compare(pivot,a[--r])){
			Quickcompare++;                             //比较
		};
		Quickcompare++;
		swap(a,l,r);
		Quickswap++;                                    //交换次数++；
	}while(l<r);
	return l;
}
void Quicksort(int a[],long i,long j){
	if(j<=i)
		return;
	int pivotindex=findpivot(a,i,j);
	swap(a,pivotindex,j);
	Quickswap++;
	int k=partition(a,i-1,j,a[j]);
	swap(a,k,j);
	Quickswap++;
	Quicksort(a,i,k-1);
	Quicksort(a,k+1,j);
}
//堆排序
//返回父节点
long parent(long i){
	return (long)floor((i-1)/2);
}
//返回左孩子节点
long left(long i){
	return (2*i+1);
}
//返回右孩子节点
long right(long i){
	return (2*i+2);
}
//以某一节点为根的子树调整成为最大堆
void Heapadjust(int a[],long i,long heapsize){
	long l=left(i);
	long r=right(i);
	long largest;
	if(l<heapsize&&compare(a[i],a[l])){
		largest=l;
	}
	else{
		largest=i;
	}
	Heapcompare++;
	if(r<heapsize&&compare(a[largest],a[r])){
		largest=r;
	}
	Heapcompare++;
	if(largest!=i){
		swap(a,i,largest);
		Heapswap++;
		Heapadjust(a,largest,heapsize);
	}
}
//建立最大堆
void Buildheap(int a[],long heapsize){
	for(long i=(heapsize-2)/2;i>=0;i--){
		Heapadjust(a,i,heapsize);
	}
}
void Heapsort(int a[],long heapsize){
	Buildheap(a,heapsize);
	for(long i=heapsize-1;i>=0;i--){
		swap(a,0,i);
		Heapswap++;
		Heapadjust(a,0,i);
	}
}

//判断排序是否正确
bool adjust(int a[],long n){
	for(long i=0;i<n-1;i++){
		if(compare(a[i+1],a[i]))
			return false;
	}
	return true;
}
//统计数组的区间个数
void distribute(int a[],long size,int m){
	int *count;
	count=new int[m];
	for(int i=0;i<m;i++)
		count[i]=0;
	for(int long j=0;j<size;j++){
		for(int i=0;i<m;i++){
			if((a[j])<=((i+1)*(size/m)-1)&&(a[j]>=i*(size/m)))
				count[i]++;
		}
	}
	for(int i=0;i<m;i++){
		cout<<"["<<i*(size/m)<<","<<(i+1)*(size/m)-1<<"]: "<<count[i]<<endl;
	}

}
//打印
void print(int a[],long m){
	for(long i=0;i<m;i++){
		cout<<a[i]<<"\t";
		if((i+1)%20==0)
			cout<<endl;
	}
}
void main(){	
	long const size=10000;
	double *temp=new double[size];
	int *a=new int[size];
	int *insert=new int[size];
	int *quick=new int[size];
	int *heap=new int[size];
	srand((unsigned)time(NULL));
	for(long i=0;i<size;i++){
		int t=rand()%1000;
		double te=(t/(double)(1000));
		temp[i]=te;
		a[i]=(int)(temp[i]*size);
	}
	cout<<"rand numbers created successfully"<<endl;
	distribute(a,size,dis);
	for(long i=0;i<size;i++){
		insert[i]=a[i];
		quick[i]=a[i];
		heap[i]=a[i];
	}

	cout<<"Quicksort :"<<endl<<endl;
	Quicksort(quick,0,size-1);
	//print(quick,size);
	if(adjust(quick,size))
		cout<<"Quicksort right!"<<endl;
	else
		cout<<"Quicksort failed!"<<endl;
	cout<<"Quickcompare="<<Quickcompare<<endl;
	cout<<"Quickswap="<<Quickswap<<endl<<endl;
	cout<<"Heapsort: "<<endl<<endl;
	Heapsort(heap,size);
	//print(heap,size);
	if(adjust(heap,size))
		cout<<"Heapsort right!"<<endl;
	else
		cout<<"Heapsort failed!"<<endl;
	cout<<"Heapcompare="<<Heapcompare<<endl;
	cout<<"Heapswap="<<Heapswap<<endl;
	cout<<"Insertsort :"<<endl<<endl;
	Insertsort(insert,size);
	//print(insert,size);
	if(adjust(insert,size))
		cout<<"Insertsort right!"<<endl;
	else
		cout<<"Insertsort failed!"<<endl;
	cout<<"Insertcomapre="<<Insertcompare<<endl;
	cout<<"Insertswap="<<Insertswap<<endl<<endl;
	
}