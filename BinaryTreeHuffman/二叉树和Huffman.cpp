#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
static int leafcount=0;
static int twonode=0;
bool onenode=false;
template<typename E>
class BinNode{
public:
	E data;
	BinNode* lc;
	BinNode* rc;
};
//insert节点
template<class E>
void insert( BinNode<E> *&root, E *s, int n){
	static int length = 0;
	if(n == 0){
		int i = 0;
		while(s[i] != '\0'){
			i ++;
			length ++;
		}
	}
	if(s[n] == '\0'){
		root = NULL;
		return;
	}
	if(n == 0)
		root->data = s[n];
	if((2*n+1)<=(length - 1)){
		if(s[2*n + 1] == ' ')
			root->lc = NULL;
		else{
			root->lc = new BinNode<E>();
			insert(root->lc, s, (2*n+1));
			root->lc->data = s[2*n+1];
		}
	}
	else{
		root->lc = NULL;
		return;
	}
	if((2 * n + 2) <= (length - 1)){
		if(s[2*n + 2] == ' ')
			root->rc = NULL;
		else{
			root->rc = new BinNode<E>();
			insert(root->rc, s, (2 * n + 2));
			root->rc->data = s[2*n + 2];}
	}
	else{
		root->rc = NULL;
		return;
	}
}
//遍历二叉树
template<class E>
void order(BinNode<E> *root){                         
	if(root == NULL){return ;}
	visit(root);
	order(root->lc);
	order(root->rc);
}
//计算叶节点 度为二的节点数目，判断度为一的节点是否存在
template<class E>
void visit(BinNode<E> *root){   
	if(root == NULL)return;
	if((root->lc == NULL)&&(root->rc == NULL))
		leafcount++;
	if((root->lc!=NULL)&&(root->rc!=NULL))
		twonode++;
	if(((root->lc != NULL)&&(root->rc ==NULL))||((root->lc== NULL)&&(root->rc!= NULL)))
		onenode = true;
}
//二叉树高度
template<class E>
int Height(BinNode<E> *root){                               
	int lh, rh;
	if(root == NULL){
		return 0;
	}
	else{
		lh = Height(root->lc);
		rh = Height(root ->rc);
		return(lh > rh)?(lh + 1):(rh + 1);
	}
}
class Huffnode{
public:
	Huffnode*lc;
	Huffnode*rc;
	int wgt;
	char it;
	Huffnode(){lc=NULL;rc=NULL;wgt=0;it='\0';};
	Huffnode(int fre,char val){wgt=fre;it=val;lc=NULL;rc=NULL;}
	Huffnode(int fre,Huffnode*l,Huffnode *r){wgt=fre;it='\0';lc=l;rc=r;}
	Huffnode(int fre,char val,Huffnode *l,Huffnode *r){wgt=fre;it=val;lc=l;rc=r;}
	void operator=(Huffnode *m);
	bool isleaf(){
		if(lc==NULL&&rc==NULL)
			return true;
		else 
			return false;
	}	
	void code();
	void decode();
	~Huffnode(){};
}; 
void Huffnode::operator=(Huffnode *m){
	if(this==NULL){
		*this=new Huffnode(m->wgt,m->it,m->lc,m->rc);
	}
	if(this!=NULL){
	 this->lc=m->lc;
	 this->wgt=m->wgt;
	 this->it=m->it;
	 this->rc=m->rc;}
 }
static int wei[56];
static char let[56];
Huffnode *Root[56];
class Hufftree{
public:
    Huffnode*root;
	Hufftree(){};
	Hufftree(Huffnode*l,Huffnode*r){root->wgt=l->wgt+r->wgt;root->lc=l;root->rc=r;}
	void read();
	void sort();
	void huffsort();	
	void build();
	void print();
	void decode();
};
//读文件建立node,用两个数组分别保存权值和字符；
void  Hufftree::read(){
	for(int i=0;i<56;i++){
		wei[i]=0;
		let[i]='\0';
	} 
	char ch;
	ifstream fin("inputfile1.txt");
	fin.get(ch);
	while(!fin.eof()){
		if(ch==' '){
			wei[52]++;	
		}
		 else if(ch=='.'){
			wei[53]++;
		}
		 else if(ch==','){
			wei[54]++;
		}
		 else if(ch=='!'){
			 wei[55]++;		 
		 }
		else if((ch>='a')&&(ch<='y')){
			wei[ch-'a']++;
		}
		else if((ch>='A')&&(ch<='Y')){
			wei[ch-'A'+26]++;
		}
		fin.get(ch);
	}
	fin.close();
	for(int i=0;i<26;i++){
		let[i]=(char)'a'+i;
	}	
	for(int i=26;i<52;i++){
		let[i]=(char)'A'+(i-26);
	}
	for(int i=52;i<56;i++){
		if(i==52){
			let[i]=' ';
			continue;
		}
		if(i==53){
			let[i]='.';
			continue;
		}
		if(i==54){
			let[i]=',';
			continue;
		}
		if(i==55){
			let[i]='!';
			continue;
		}
	}
}
 void Hufftree::sort(){
	int temp;
	Huffnode *curr;
	for(int i=0;i<56;i++){
		Root[i]=new Huffnode(wei[i],let[i]);
	}
	for(int i=0;i<55;i++){
		if(Root[i]->wgt!=0){
		temp=i;
		for(int j=i+1;j<56;j++){
			if(Root[temp]->wgt>Root[j]->wgt)
				temp=j;	
		}
		if(i!=temp){
			curr=Root[temp];
			Root[temp]=Root[i];
			Root[i]=curr;
		}
	}
		else continue;
	}
}
 void Hufftree::huffsort(){
	 int temp;
	 Huffnode *curr;
	 for(int i=0;i<55;i++){
		if(Root[i]->wgt!=0){
		temp=i;
		for(int j=i+1;j<56;j++){
			if(Root[temp]->wgt>Root[j]->wgt)
				temp=j;	
		}
		if(i!=temp){
			curr=Root[temp];
			Root[temp]=Root[i];
			Root[i]=curr;
		}
	}
		else continue;
	}
 }
 //建立Huffman树
void Hufftree::build(){
	for(int i=0;i<55;i++){
		if(Root[i]->wgt!=0){
			Huffnode *root1=new Huffnode();;
			Huffnode *root2=new Huffnode();
			*root1=Root[i];
			*root2=Root[i+1];
			Root[i]->wgt=0;
			Root[i+1]->it='\0';
			Root[i+1]->wgt=root1->wgt+root2->wgt;
			Root[i+1]->lc=root1;
			Root[i+1]->rc=root2;
			huffsort();
		}
		else continue;
	}
	root=Root[55];
}
void Hufftree::print(){
	ofstream outfile("outputfile1.txt");
	outfile<<"字符\t"<<"次数\t"<<"编码\t"<<endl;
}
//编码
static int co[100];
int m=0;
void Huffnode::code(){
	ofstream outfile("outputfile1.txt",ios::app);
	if(this->isleaf()){
		outfile<<this->it<<"\t"<<this->wgt<<"\t";
		for(int i=0;i<m;i++)
			outfile<<co[i];
		outfile<<"\t";
		outfile<<endl;
		return;
	}
	co[m++]=0;
	this->lc->code();
	co[m-1]=1;
	this->rc->code();
	co[m--]=1;
}
//译码
void Hufftree::decode(){
	char ch;
	char dec[500];
	int i=0;
	Huffnode *curr=root;
	ifstream inread("inputfile2.txt");
	inread.get(ch);
	while(!inread.eof()){
		dec[i++]=ch;
		inread.get(ch);
	}
	inread.close();
	ofstream output("outputfile2.txt");
	int j=0;
	while(dec[j]!='\0'){
		while(curr->lc!=NULL&&curr->rc!=NULL){
			if(dec[j]=='0'){
				curr=curr->lc;
			}
			if(dec[j]=='1'){
				curr=curr->rc;
			}
			j++;
		}
		output<<curr->it;
		curr=root;
	}
}
void main(){
	int i=0;
	char node[100];
	cout<<"please input the node you want to build(there is no space):"<<endl;            
	cin>>node;
	BinNode<char> *T=new BinNode<char> ();
	insert(T, node, 0);
	order(T);
	cout<<"the number of leafnode is :"<<leafcount<<endl;
	cout<<"the number of two-node is :"<<twonode<<endl;
	if(onenode){
		cout<<"there is one-node "<<endl;
	}
	else{
		cout<<"there is no one-node"<<endl;
	}
	int h=Height(T);
	cout<<"the hight of Binnode"<<h<<endl;
	Hufftree l;
	l.read();
	l.sort();
	l.build();
	l.print();
	Huffnode *m;
	m=l.root;
	l.print();
	m->code();
	l.decode();
}

