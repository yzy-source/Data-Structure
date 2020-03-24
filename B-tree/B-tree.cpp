#include<iostream>
using namespace std;
enum ResultCode{NotPresent,Success,Overflow,Duplicate};
static int order;
class B_node{
public :
	int count;
	int *data;
	B_node **branch;
	B_node(){
		count=0;
		data=new int[order-1];
		branch=new B_node *[order];
	}
};
class B_tree{
public:
	B_node *root;
	B_tree(){root=NULL;}
	B_node* getroot(){return root;}
	ResultCode search_tree(int &target);
	ResultCode recursive_search_tree(B_node *current,int &target);
	ResultCode search_node(B_node *current,const int &target,int &position);
	ResultCode insert(const int &new_enty);
	ResultCode push_down(B_node *current,const int &new_entry,int &median,B_node *&right_branch);
	void push_in(B_node *current,const int &entry,B_node *right_branch,int position);
	void split_node(B_node *current,const int &extra_entry,B_node *extra_branch,int position,B_node *&right_half,int &median);
	ResultCode remove(const int &target);
	ResultCode recursive_remove(B_node *current,const int &target);
	void remove_data(B_node *current,int position);
	void copy(B_node *current,int position);
	void restore(B_node *current,int position);
	void move_left(B_node *current,int position);
	void move_right(B_node *current,int position);
	void combine(B_node *current,int position);
	void print(B_node *root);
};
ResultCode B_tree::search_tree(int &target){
	return recursive_search_tree(root,target);
}
ResultCode B_tree::recursive_search_tree(B_node *current,int &target){
	ResultCode result=NotPresent;
	int position;
	if(current!=NULL){
		result=search_node(current,target,position);
		if(result==NotPresent)
			result=recursive_search_tree(current->branch[position],target);
		else
			target=current->data[position];
	}
	return result;
}
ResultCode B_tree::search_node(B_node *current,const int &target,int &position){
	position=0;
	while(position<current->count&&target>current->data[position])
		position++;
	if(position<current->count&&target==current->data[position])
		return Success;
	else
		return NotPresent;
}
ResultCode B_tree::insert(const int &new_entry){
	int median;
	B_node *right_branch,*new_root;
	ResultCode result=push_down(root,new_entry,median,right_branch);
	if(result==Overflow){
		new_root=new B_node();
		new_root->count=1;
		new_root->data[0]=median;
		new_root->branch[0]=root;
		new_root->branch[1]=right_branch;
		root=new_root;
		result=Success;
	}
	return result;
}
ResultCode B_tree::push_down(B_node *current,const int &new_entry,int &median,B_node *&right_branch){
	ResultCode result;
	int position;
	if(current==NULL){
		median=new_entry;
		right_branch=NULL;
		result=Overflow;
	}
	else{
		if(search_node(current,new_entry,position)==Success)
			result=Duplicate;
		else{
			int extra_entry;
			B_node *extra_branch;
			result=push_down(current->branch[position],new_entry,extra_entry,extra_branch);
			if(result==Overflow){
				if(current->count<order-1){
					result=Success;
					push_in(current,extra_entry,extra_branch,position);
				}
				else split_node(current,extra_entry,extra_branch,position,right_branch,median);
			}
		}
	}
	return result;
}
void B_tree::push_in(B_node *current,const int &entry,B_node *right_branch,int position){
	for(int i=current->count;i>position;i--){
		current->data[i]=current->data[i-1];
		current->branch[i+1]=current->branch[i];
	}
	current->data[position]=entry;
	current->branch[position+1]=right_branch;
	current->count++;
}
void B_tree::split_node(B_node *current,const int &extra_entry,B_node *extra_branch,int position,B_node *&right_half,int &median){
	right_half=new B_node();
	int mid=order/2;
	if(position<=mid){
		for(int i=mid;i<order-1;i++){
			right_half->data[i-mid]=current->data[i];
			right_half->branch[i+1-mid]=current->branch[i+1];
		}
		current->count=mid;
		right_half->count=order-1-mid;
		push_in(current,extra_entry,extra_branch,position);
	}
	else{
		mid++;
		for(int i=mid;i<order-1;i++){
			right_half->data[i-mid]=current->data[i];
			right_half->branch[i+1-mid]=current->branch[i+1];
		}
		current->count=mid;
		right_half->count=order-1-mid;
		push_in(right_half,extra_entry,extra_branch,position-mid);
	}
	median=current->data[current->count-1];
	right_half->branch[0]=current->branch[current->count];
	current->count--;
}
ResultCode B_tree::remove(const int &target){
	ResultCode result;
	result=recursive_remove(root,target);
	if(root!=NULL&&root->count==0){
		B_node *old_root=root;
		root=root->branch[0];
		delete old_root;
	}
	return result;
}
ResultCode B_tree::recursive_remove(B_node *current,const int &target){
	ResultCode result;
	int position;
	if(current==NULL)
		result=NotPresent;
	else{
		if(search_node(current,target,position)==Success){
			result=Success;
			if(current->branch[position]!=NULL){
				copy(current,position);
				recursive_remove(current->branch[position],current->data[position]);
			}
			else
				remove_data(current,position);
		}
		else
			result=recursive_remove(current->branch[position],target);
		if(current->branch[position]!=NULL)
			if(current->branch[position]->count<(order-1)/2)
				restore(current,position);
	}
	return result;
}
void B_tree::remove_data(B_node *current,int position){
	for(int i=position;i<current->count-1;i++)
		current->data[i]=current->data[i+1];
	current->count--;
}
void B_tree::copy(B_node *current,int position){
	B_node *leaf=current->branch[position];
	while(leaf->branch[leaf->count]!=NULL)
		leaf=leaf->branch[leaf->count];
	current->data[position]=leaf->data[leaf->count-1];

}
void B_tree::restore(B_node *current,int position){
	if(position==current->count)
		if(current->branch[position-1]->count>(order-1)/2)
			move_right(current,position-1);
		else
			combine(current,position);
	else if(position==0)
		if(current->branch[1]->count>(order-1)/2)
			move_left(current,1);
		else
			combine(current,1);
	else
		if(current->branch[position-1]->count>(order-1)/2)
			move_right(current,position-1);
		else if(current->branch[position+1]->count>(order-1)/2)
			move_left(current,position+1);
		else
			combine(current,position);
}
void B_tree::move_left(B_node *current,int position){
	B_node *left_branch=current->branch[position-1],
		*right_branch=current->branch[position];
	left_branch->data[left_branch->count]=current->data[position-1];
	left_branch->branch[++left_branch->count]=right_branch->branch[0];
	current->data[position-1]=right_branch->data[0];
	right_branch->count--;
	for(int i=0;i<right_branch->count;i++){
		right_branch->data[i]=right_branch->data[i+1];
		right_branch->branch[i]=right_branch->branch[i+1];
	}
	right_branch->branch[right_branch->count]=right_branch->branch[right_branch->count+1];
}
void B_tree::move_right(B_node *current,int position){
	B_node *right_branch=current->branch[position+1],
		*left_branch=current->branch[position];
	right_branch->branch[right_branch->count+1]=right_branch->branch[right_branch->count];
	for(int i=right_branch->count;i>0;i--){
		right_branch->data[i]=right_branch->data[i-1];
		right_branch->branch[i]=right_branch->branch[i-1];
	}
	right_branch->count++;
	right_branch->data[0]=current->data[position];
	right_branch->branch[0]=left_branch->branch[left_branch->count--];
	current->data[position]=left_branch->data[left_branch->count];
}
void B_tree::combine(B_node *current,int position){
	int i;
	B_node *left_branch=current->branch[position-1],
		*right_branch=current->branch[position];
	left_branch->data[left_branch->count]=current->data[position-1];
	left_branch->branch[++left_branch->count]=right_branch->branch[0];
	for(i=0;i<right_branch->count;i++){
		left_branch->data[left_branch->count]=right_branch->data[i];
		left_branch->branch[++left_branch->count]=right_branch->branch[i+1];
	}
	current->count--;
	for(i=position-1;i<current->count;i++){
		current->data[i]=current->data[i+1];
		current->branch[i+1]=current->branch[i+2];
	}
	delete right_branch;

}
void B_tree::print(B_node *root){
	if(root==NULL)
		return;
	else{
		int n=root->count;
		for(int k=0;k<n;k++)
			cout<<root->data[k]<<" ";
		cout<<endl;
		for(int i=0;i<=n;i++){
			print(root->branch[i]);
		}
	}
}
void main(){
	B_tree l;
	int num[100];
	int n;
	cout<<"please input the number of the key and the way of B_tree"<<endl;
	cout<<"please use the space to devide the keys"<<endl;
	cin>>n>>order;
	cout<<"please input the keys"<<endl;
	for(int i=0;i<n;i++){
		cin>>num[i];
		l.insert(num[i]);
	}
	l.print(l.getroot());
	char fun[100];
	int key[100];
	int s;
	cout<<"please input the steps you want to run and the function and the key"<<endl;
	cout<<"example:2 I 31,D 23"<<endl;
	cin>>s;
	for(int i=0;i<s;i++){
		cin>>fun[i]>>key[i];
		if(fun[i]=='I'){
			cout<<"after insert:"<<endl;
			l.insert(key[i]);
			l.print(l.getroot());
		}
		if(fun[i]=='D'){
			cout<<"after delete:"<<endl;
			l.remove(key[i]);
			l.print(l.getroot());
		}
	}		  
}
