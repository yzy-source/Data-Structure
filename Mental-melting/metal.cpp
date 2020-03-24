#include<iostream>
using namespace std;
class metal{
public:
	char **row;
	int n;
	int time;
	metal(int num){
		n=num;
		 row=new char*[n+2];
		for(int i=0;i<n+2;i++){
			*(row+i)=new char[n+2];
		}
		for(int i=0;i<n+2;i++)
			row[i][0]=row[i][n+1]='#';
		for(int j=1;j<n+1;j++)
			row[0][j]=row[n+1][j]='#';
		time=0;
	}
	bool ismetal(int i,int j);
	bool isempty(int i,int j);
	bool isliquid(int i,int j);
	bool ismelt(int i,int j);
	void change(int i,int j);
	void onetime();
	bool isdone();
};
//�ж��ǲ��ǽ���
bool metal::ismetal(int i,int j){
	if(row[i][j]=='#')
		return true;
	else 
		return false;
}
//�ж��ǲ����п�
bool metal::isempty(int i,int j){
	if(ismetal(i,j))
		return false;
	else{
	int left,right,up,down;
	left=right=up=down=0;
	for(int m=1;m<j;m++){
		if(ismetal(i,m))
			left=1;
	}
	if(j==1)
		left=1;
	for(int m=j+1;m<n+1;m++){
		if(ismetal(i,m))
			right=1;
	}
	if(j==n)
		right=1;
	for(int l=1;l<i;l++){
		if(ismetal(l,j))
			up=1;
	}
	if(i==1)
		up=1;
	for(int l=i+1;l<n+1;l++){
		if(ismetal(l,j))
			down=1;
	}
	if(i==n)
		down=1;
	if(left==1&&right==1&&up==1&&down==1){
		row[i][j]='/';                                  //�п���ʱ��/����-����ֹ��Һ�����
		return true;
	}
	else 
		return false;
	}
}
//�ж��ǲ���Һ��
bool metal::isliquid(int i,int j){
	if((row[i][j]=='-')&&(!isempty(i,j)))
		return true;
	else 
		return false;
}
//�жϽ����ǲ��Ƿ����ڻ�����
bool metal::ismelt(int i,int j){
	if(ismetal(i,j)){
	  int side=0;
	  if(isliquid(i-1,j))
		  side++;
	  if(isliquid(i+1,j))
		  side++;
	  if(isliquid(i,j-1))
		  side++;
	  if(isliquid(i,j+1))
		  side++;
	  if(side>=2)
		  return true;
	  else 
		  return false; 
	}
	else 
		return false;
}
//�п�ת��ΪҺ��
void metal::change(int i,int j){
	if(row[i][j]!='/')
		return ;
	else{
			row[i][j]='-';
			change(i-1,j);
			change(i+1,j);
			change(i,j-1);
			change(i,j+1);
	}
}
//�ж��Ƿ����еĽ������ڻ���
bool metal::isdone(){
	for(int i=1;i<n+1;i++){
		for(int j=1;j<n+1;j++){
			if(ismetal(i,j))
				return false;
			else 
				continue;
		}
	}
	return true;
}
void metal::onetime(){
	for(int i=1;i<n+1;i++){
		for(int j=1;j<n+1;j++){ 
			if(ismelt(i,j))
				row[i][j]='$';        //������ʱ��$�������Ӱ������ڻ��ж�
		}
	}
	time++;
	for(int i=1;i<n+1;i++){
		for(int j=1;j<n+1;j++){
			if(row[i][j]=='$'){
				row[i][j]='-';
			}
		}
	}
	for(int i=1;i<n+1;i++)
		for(int j=1;j<n+1;j++){
			if(row[i][j]=='/')
				if(isliquid(i-1,j)||isliquid(i+1,j)||isliquid(i,j-1)||isliquid(i,j+1)){
					change(i,j);
				}
		}
}
void main(){
	int size;
	cout<<"please input the size "<<endl;
	cin>>size;
	metal l(size);
	cout<<"please input the matal(using'-'replace liquid and empty ,using'#'replace metal)"<<endl;
	for(int i=1;i<size+1;i++)
		for(int j=1;j<size+1;j++)
			cin>>l.row[i][j];
	while(!l.isdone()){
		l.onetime();
	}
	cout<<"to melt the metal,the tatal time is t="<<l.time<<endl;	
}


