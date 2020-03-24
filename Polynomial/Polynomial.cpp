#include<iostream>
#include<fstream>
using namespace std;
class Node{
public:
	int n;
	float a;
	Node *next;
	Node(float a0,int n0){a=a0;n=n0;next=NULL;};
	~Node(){};
};
class List{
public:
	Node *head;
	Node *tail;
	List();
	
	void Insert(float a0,int n0);
	void Remove(float a0,int n0);
	void Print();
	void Printf();
	void Add(List l2);
	void Sub(List l2);
	List Diff();
	List Mul(List l2);
	void Div(List &l2,List &l,List &ly);
	List operator =(List l);
	~List(){};
};
List::List(){
	head=tail=NULL;
}
void List::Insert(float a0,int n0){
	Node *temp=new Node(a0,n0);
	if(head==NULL){
		head=tail=temp;
		return;
	}
	else{
		if(n0<=head->n){
			temp->next=head;
			head=temp;
			return;
		}
		if(n0>=tail->n){
			tail->next=temp;
			tail=temp;
			return;
		}
		Node *curr=head;
		while(curr->next!=NULL){
			if((n0>=curr->n)&&(n0<=curr->next->n)){
				temp->next=curr->next;
				curr->next=temp;
				return;
			}
			curr=curr->next;
		}
	}
	
}
void List::Remove(float a0,int n0){
	if(head->n==n0){
			head=head->next;
			return;
		}
	Node*curr=head;
	while(curr!=NULL){
		if(curr->next->n==n0){
			if(curr->next->n==tail->n){
				tail=curr;
				curr->next=NULL;
				return;
			}
			else{
				curr->next=curr->next->next;
				return;
			}
		}
		curr=curr->next;
	}
}
void List::Print(){
	ofstream outfile("outputfile.txt");
	if(head==NULL)
		outfile<<"the list is empty!"<<endl;
    Node *curr=head;
if(curr->n<0)
		curr=curr->next;
	if(curr->n==0){
		outfile<<curr->a;
		curr=curr->next;
		if(curr->a>0){
			outfile<<"+"<<curr->a<<"X"<<curr->n;
			curr=curr->next;
		}
		else{
			outfile<<curr->a<<"X"<<curr->n;
			curr=curr->next;		
		}
	}
	if(curr->a==0)
	{
		curr=curr->next;
		
			outfile<<curr->a<<"X"<<curr->n;
			curr=curr->next;		
		
	}
	
	while(curr!=tail){
		if(curr->n==0){
			outfile<<curr->a;
			curr=curr->next;
		}
		if(curr->a==0||curr->n<0)
		{
			curr=curr->next;
			continue;
		}
		if(curr->a>0){
			outfile<<"+"<<curr->a<<"X"<<curr->n;
			curr=curr->next;
			continue;
		}
		else if(curr->a<0){
			outfile<<curr->a<<"X"<<curr->n;
			curr=curr->next;
			continue;
		}
		else
		{
			curr=curr->next;
			continue;
		}
	}
	if(curr==tail){
	if(curr->a>0){
			outfile<<"+"<<curr->a<<"X"<<curr->n;
		}
		else if(curr->a<0){
			outfile<<curr->a<<"X"<<curr->n;
		}
	}
}
void List::Printf(){
	ofstream outfile("outputfile.txt",ios::app);
	if(head==NULL)
		outfile<<"the list is empty!"<<endl;
	outfile<<'\n';
	outfile<<"the remainder list is:     ";
	Node *curr=head;
	outfile << '\n';
	if(curr->n<0)
		curr=curr->next;
	if(curr->n==0){
		outfile<<curr->a;
		curr=curr->next;
		if(curr->a>0){
			outfile<<"+"<<curr->a<<"X"<<curr->n;
			curr=curr->next;
		}
		else{
			outfile<<curr->a<<"X"<<curr->n;
			curr=curr->next;		
		}
	}
	if(curr->a==0)
	{
		curr=curr->next;
		
			outfile<<curr->a<<"X"<<curr->n;
			curr=curr->next;		
		
	}
	
	while(curr!=tail){
		if(curr->n==0){
			outfile<<curr->a;
			curr=curr->next;
		}
		if(curr->a==0||curr->n<0)
		{
			curr=curr->next;
			continue;
		}
		if(curr->a>0){
			outfile<<"+"<<curr->a<<"X"<<curr->n;
			curr=curr->next;
			continue;
		}
		else if(curr->a<0){
			outfile<<curr->a<<"X"<<curr->n;
			curr=curr->next;
			continue;
		}
		else
		{
			curr=curr->next;
			continue;
		}
	}
	if(curr==tail){
	if(curr->a>0){
			outfile<<"+"<<curr->a<<"X"<<curr->n;
		}
		else if(curr->a<0){
			outfile<<curr->a<<"X"<<curr->n;
		}
	}
}
void  List::Add(List l2){
	Node *curr2=l2.head;
	Node *curr1=head;
	while (curr2!=NULL){
		if((curr2->n<head->n)||(curr2->n>tail->n)){
			this->Insert(curr2->a,curr2->n);
			l2.Remove(curr2->a,curr2->n);
            curr2=l2.head;
			continue;
			}
		
		while(curr1!=NULL){
			if(curr2->n==curr1->n){
				
				curr1->a+=curr2->a;
				if(curr1->a==0){
				    this->Remove(curr1->a,curr1->n);
					curr1=head;
					l2.Remove(curr2->a,curr2->n);
					curr2=l2.head;
					break;
				}
				else {
				    l2.Remove(curr2->a,curr2->n);
					curr2=l2.head;
					break;
				}
			}
			 if((curr2->n > curr1->n)&&(curr2->n<curr1->next->n)){
				this->Insert(curr2->a,curr2->n);
				l2.Remove(curr2->a,curr2->n);
				 curr2=l2.head;
				break;
			}
			 curr1=curr1->next;
		}
	}
	return;
}
void  List::Sub(List l2){
	Node *curr2=l2.head;
	Node *curr1=head;
	while (curr2!=NULL){
		if((curr2->n<head->n)||(curr2->n>tail->n)){
			this->Insert(-curr2->a,curr2->n);
			l2.Remove(curr2->a,curr2->n);
            curr2=l2.head;
			continue;
			}
		while(curr1!=NULL){
			if(curr2->n==curr1->n){
				
				curr1->a-=curr2->a;
				if(curr1->a==0){
				    this->Remove(curr1->a,curr1->n);
					curr1=head;
					l2.Remove(curr2->a,curr2->n);
					curr2=l2.head;
					break;
				}
				else {
				    l2.Remove(curr2->a,curr2->n);
					curr2=l2.head;
					break;
				}
			}
			 if((curr2->n > curr1->n)&&(curr2->n<curr1->next->n)){
				this->Insert(-curr2->a,curr2->n);
				l2.Remove(curr2->a,curr2->n);
				 curr2=l2.head;
				break;
			}
			 curr1=curr1->next;
		}
	}
	return;
}
List List::Diff(){
	Node *curr=head;
	while(curr!=NULL){
		curr->a=curr->a*curr->n;
		curr->n--;
		curr=curr->next;
	}
	return *this;
}
List List::Mul(List l2){
	List l3,l4;
	Node *curr1=head;
	Node *curr2=l2.head;
	while(curr2!=NULL){
		l3.Insert(curr1->a*curr2->a,curr1->n+curr2->n);
		curr2=curr2->next;
	}
	curr1=curr1->next;
	while(curr1!=NULL){
		curr2=l2.head;
		while(curr2!=NULL){
			l4.Insert(curr1->a*curr2->a,curr1->n+curr2->n);
			curr2=curr2->next;
		}
		l3.Add(l4);
		
		curr1=curr1->next;
	}
	return l3;
}
List List::operator=(List l){
	Node *curr=l.head;
	while(curr!=NULL){
		this->Insert(curr->a,curr->n);
			curr=curr->next;
	}
	return *this;
}
void List::Div(List &l2,List &l,List &ly){
	    List m;	
	    float s;
		int z;
		if(tail->n < l2.tail->n){
			ly=*this;
			return;
	     } 
		if(tail->n == l2.tail->n)
		{
			s=tail->a/l2.tail->a;
	        z = 0;
			l.Insert(s, z);
			this->Sub(l2.Mul(l));
			return;
		}		
		s=tail->a/l2.tail->a;
	    z=tail->n-l2.tail->n;
		m.Insert(s,z);
	    l.Insert(s,z);
	    this->Sub(l2.Mul(m));
		m.Remove(s,z);	
        this->Div(l2,l,ly);

}
void main(){
     ifstream infile("inputfile.txt");
	 ofstream outfile("outputfile.txt");
	 int n1,n2;
	 float a1,a2;
	 char ch,ch1,ch2,ch3;
	 List l1,l2,l,ly;
	 do{
	     infile>>ch>>a1>>ch>>n1>>ch;
	     l1.Insert(a1,n1);
		}while(!((a1==0)&&(n1==0)));
	do{
		 infile>>ch>>a2>>ch>>n2>>ch;
		 l2.Insert(a2,n2);
		 }while(!((a2==0)&&(n2==0)));
	infile>>ch1>>ch2>>ch3;
	 switch(ch1){
	 case'A':
		 l1.Add(l2);
		 l1.Print();
		 break;
	 case'S':
		 l1.Sub(l2);
		 l1.Print();
		 break;
	 case'D':{
		 switch(ch3){
		 case 'V':
			l1.Div(l2,l,ly);
			l.Print();
			ly.Printf();
			 break;
		 case'F':
			 l1.Diff();
		     l1.Print();
			 break;
		 }
			 }
		 break;
	 case'M':
		 l1.Mul(l2).Print();
		 break;
	 }
}