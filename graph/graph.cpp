#include<iostream>
#include<fstream>
using namespace std;
static int ver;
static int top[100];
static int y=0;
static int color[100]={0};
static bool iscircle=true;
static int *D;
enum record{UNVISITED,VISITED};
class Graph{
public:
	int numVertex,numEdge;
	int **matrix;
	int *mark;
	Graph(int numvert){Init(numvert);}
	~Graph(){
		delete[] mark;
		for(int i=0;i<numVertex;i++){
			delete[]matrix[i];
		}
		delete[]matrix;
	}
	void read();
	void print();
	void arrayprint(Graph *G);
	void Init(int n);
	int n(){return numVertex;}
	int e(){return numEdge;}
	int first(int v);
	int next(int v,int w);;
	void setEdge(int v1,int v2,int wt);
	void delEdge(int v1,int v2);
	bool isEdge(int i,int j){return matrix[i][j]!=0;};
	int weight(int v1,int v2){return matrix[v1][v2];}
	int getMark(int v){return mark[v];}
	void setMark(int v,int val){mark[v]=val;}
	bool isnondirected();
	void isdiruncircle(Graph *G,int i);
	bool connected(Graph * G);
	void DFS(Graph *G,int v);
	void traverse(Graph * G);
	void topsort(Graph *G);
	void circleDFS(Graph *G);
	int minVertex(Graph *G,int *D);
	//void Dijkstra(Graph * G,int * D,int s);
};
//读文件建立图的矩阵
void Graph::read(){
	ifstream infile("inputfile.txt");
	infile>>ver;
	numVertex=ver;
	int input;
	matrix=new int*[ver];
	for(int i=0;i<ver;i++)
		*(matrix+i)=new int[ver];
	int temp[100];
	int q=0;
	for(int i=0;i<ver*ver;i++){
		infile>>input;
		temp[q]=input;
		q++;
	}
	int l=0;
	for(int i=0;i<ver;i++)
		for(int j=0;j<ver;j++){
			matrix[i][j]=temp[l];
			l++;
		}
}
//图的初始化，申请一个矩阵的空间
void Graph::Init(int n){
	int i;
	numVertex=n;
	numEdge=0;
	mark=new int[n];
	for(i=0;i<numVertex;i++)
		mark[i]=UNVISITED;
	matrix=(int **)new int *[numVertex];
	for(i=0;i<numVertex;i++)
		matrix[i]=new int[numVertex];
	for(i=0;i<numVertex;i++)
		for(int j=0;j<numVertex;j++)
			matrix[i][j]=0;
}
//访问第一个顶点，返回第一个顶点的第一条边所对应的的顶点，否则返回顶点个数
int Graph::first(int v){
	for(int i=0;i<numVertex;i++){
		if(matrix[v][i]!=0)
			return i;
		else 
			continue;
	}
	return numVertex;
}
//顶点V1，V2作为输入，顺序返回V1的所有边里边在顶点V2之后的第一个未访问的顶点，全部访问之后返回顶点个数
int Graph::next(int v,int w){
	for(int i=w+1;i<numVertex;i++)
		if(matrix[v][i]!=0)
			return i;
	return numVertex;
}
void Graph::setEdge(int v1,int v2,int wt){
	if(wt<=0){
		cout<<"illegal weight value!"<<endl;
		return;
	}
	else{
		if(matrix[v1][v2]==0)
			numEdge++;
		matrix[v1][v2]=wt;
	}
}
void Graph::delEdge(int v1,int v2){
	if(matrix[v1][v2]!=0)
		numEdge--;
	matrix[v1][v2]=0;
}
//判断是不是无向图
bool Graph::isnondirected(){
	int bo=0;
	for(int i=0;i<ver;i++)
		for(int j=0;j<=i;j++){
			if(matrix[i][j]!=matrix[j][i])
				bo=1;
		}
	if(bo==1)
		return false;
	else 
		return true;
}
//深度优先遍历
void Graph::DFS(Graph *G,int v){
	G->setMark(v,VISITED);
	for(int w=G->first(v);w<G->n();w=G->next(v,w))
		if(G->getMark(w)==UNVISITED)
			DFS(G,w);
	top[y++]=v;
}
//拓扑排序
void Graph::topsort(Graph *G){
	int i;
	for(i=0;i<G->n();i++)
		G->setMark(i,UNVISITED);
	for(i=0;i<G->n();i++)
		if(G->getMark(i)==UNVISITED)
			DFS(G,i);	
}
//拓扑排序输出
void Graph::print(){
	for(int i=y-1;i>=0;i--)
		cout<<top[i];
}
//建立的图的矩阵的输出
void Graph::arrayprint(Graph *G){
	for(int i=0;i<G->n();i++){
		for(int j=0;j<G->n();j++){
			cout<<G->matrix[i][j];
		}
		cout<<endl;
	}

}
//判断是不是有向无环图
void Graph::isdiruncircle(Graph *G,int i){
	color[i]=-1;
	for(int j=0;j<G->n();j++){
		if(G->matrix[i][j]!=0){
			if(color[j]==-1){
				iscircle=false;
				return;
			}
			else if(color[j]==0)
				isdiruncircle(G,j);
		}
	}
	color[i]=1;
}
void Graph::circleDFS(Graph * G){
	for(int i=0;i<G->n();i++){
		if(color[i]==0)
			isdiruncircle(G,i);
	}

}
//判断图是不是连通的
bool Graph::connected(Graph *G){
	int m=0;
	if(G->isnondirected()){
		for(int i=0;i<G->n();i++)
			G->setMark(i,UNVISITED);
		G->DFS(G,0);
		for(int i=0;i<G->n();i++){
			if(getMark(i)==UNVISITED)
				m=1;
		}
		if(m==0)
			return true;
		else 
			return false;
	}
	else{
		Graph M(G->n());
		for(int i=0;i<G->n();i++)
			for(int j=0;j<G->n();j++)
				M.matrix[i][j]=G->matrix[i][j];
		for(int i=0;i<G->n();i++)
			for(int j=0;j<i;j++)
				if(M.matrix[i][j]!=0||M.matrix[j][i]!=0)
					M.matrix[i][j]=M.matrix[j][i]=1;
		if(M.isnondirected()){
			for(int i=0;i<M.n();i++)
				M.setMark(i,UNVISITED);
			M.DFS(&M,0);
			for(int i=0;i<M.n();i++)
				if(M.getMark(i)==UNVISITED)
					m=1;
		if(m==0)
			return true;
		else 
			return false;
		}
	}
}
//单源最短路径
//int Graph::minVertex(Graph * G,int *D){
//	int i,v=-1;
//	for(i=0;i<G->n();i++)
//		if(G->getMark(i)==UNVISITED){
//			v=i;
//			break;
//		}
//	for(i++;i<G->n();i++){
//		if((G->getMark(i)==UNVISITED)&&(D[i]<D[v]))
//			v=i;
//	}
//	return v;
//}
//void Graph::Dijkstra(Graph *G,int *D,int s){
//	for(int i=1;i<G->n();i++){
//			G->setMark(i,UNVISITED);
//		}
//	int minroad=0;
//	D=new int[G->n()];
//	for(int i=0;i<G->n();i++){
//		if(G->weight(0,i)!=0)
//			{D[i]=G->weight(0,i);
//	        
//		}
//		else
//			D[i]=10000;
//		cout<<i<<"--"<<D[i]<<endl;
//	}
//	int i,v,w;
//	for(i=1;i<G->n();i++){
//		v=minVertex(G,D);
//		if(D[v]==10000)
//		{return;}
//		G->setMark(v,VISITED);
//		for(w=G->first(v);w<G->n();w=G->next(v,w)){
//			if(D[w]>D[v]+G->weight(v,w))
//				D[w]=D[v]+G->weight(v,w);
//			}
//		for(int j=0;j<G->n()-1;j++){
//			if(D[j]>=D[j+1]){
//				minroad=D[j+1];
//				continue;
//			}
//			else{
//				minroad=D[j];
//				continue;
//			}
//			
//		}
//		cout<<"The vertex"<<i<<" minroad is :"<<minroad<<endl;
//
//		}	
//}

void main(){
 	Graph *m=new Graph(ver);
	m->read();
	cout<<"The Graph is built successfully!"<<endl;
	m->arrayprint(m);
	if(m->isnondirected()){
		cout<<"The Graph is nondirected!"<<endl;
		//m->Dijkstra(m,D,0);
		/*cout<<endl;*/
	}
	else{ 
		cout<<"The Graph is directed!"<<endl;
		m->circleDFS(m);
		if(iscircle)
			cout<<"The Graph is diruncircle!"<<endl;
		else
			cout<<"The Graph is dircircle!"<<endl;
	}
	m->topsort(m);
	cout<<"The result of topsort:";
	m->print();
	cout<<endl;
	if(m->connected(m))
		cout<<"The Graph is connected!"<<endl;
	else
		cout<<"The Graph is unconnected!"<<endl;
}