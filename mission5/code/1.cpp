#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
using namespace std;
#define MAX_LEN 9999
struct HTNode
{
	int weight,parent,lchild,rchild;
};
typedef char **HuffmanCode;
void Initialization(HTNode HT[],HuffmanCode &HC,char *&ch,int &n)
{
	void HuffmanTree(HTNode HT[],int w[],int n);
	void CreateHuffmanCode(HTNode HT[],HuffmanCode &HC,int n);
	int *p;
	int opt; //输入的操作序号	
	cout<<"1：建立新的哈夫曼树\n2：读取文件建立哈夫曼树\n输入操作：";
	cin>>opt;
	if(opt==1)
	{
		ofstream myout("hfmTree.txt");	
		cout<<"输入元素个数：";
		cin>>n;
		ch=new char[n];
		p=new int[n];
		cout<<"输入每个元素：(空格即为加号)";
		for(int i=0;i<n;i++)	
		cin>>ch[i];
		cout<<"输入每个元素的权重：";
		for(int i=0;i<n;i++)	
		cin>>p[i];
		cout<<"输入成功！开始建立哈夫曼树\n";
		HuffmanTree(HT,p,n);  //构造哈夫曼树
		CreateHuffmanCode(HT,HC,n);  //构造哈夫曼编码 
		myout<<left;
		myout<<"index\tword\tweight\tparent\tlchild\trchild\tcode\n";
		for(int i=0;i<2*n-1;++i)
		{
			if(i<n)
			myout<<i<<"\t"<<ch[i]<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<"\t"<<HC[i]<<endl;
			else
			{
				myout<<i<<"\t"<<"0\t"<<HT[i].weight<<"\t";
				myout<<HT[i].parent<<"\t";
				myout<<HT[i].lchild<<"\t";
				myout<<HT[i].rchild<<endl;
			}	
		}
		cout<<"建树成功！哈夫曼树和哈夫曼编码保存在文件hfmTree.txt中\n";
		myout.close();
	}
	if(opt==2)
	{
		fstream myin;
		myin.open("hfm.txt");
		n=27;
		ch=new char[n];
		p=new int[n];
		int m1=0,m2=0;	
		while(!myin.eof())
		{
			if(m1<n)
			{
				myin>>ch[m1];
				m1++;
			} 
			else
			{
				myin>>p[m2];
				m2++;
			}
		}
		myin.close(); 
		ofstream myout("hfmTree.txt");
		HuffmanTree(HT,p,n);  //构造哈夫曼树
		CreateHuffmanCode(HT,HC,n);  //构造哈夫曼编码 
		myout<<left;
		myout<<"index\tword\tweight\tparent\tlchild\trchild\tcode\n";
		for(int i=0;i<2*n-1;++i)
		{
			if(i<n)
			myout<<i<<"\t"<<ch[i]<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<"\t"<<HC[i]<<endl;
			else
			{
				myout<<i<<"\t"<<"0\t"<<HT[i].weight<<"\t";
				myout<<HT[i].parent<<"\t";
				myout<<HT[i].lchild<<"\t";
				myout<<HT[i].rchild<<endl;
			}	
		}
		cout<<"建树成功！哈夫曼树和哈夫曼编码保存在文件hfmTree.txt中\n";
		myout.close();		
	}	
}
void CreateHuffmanCode(HTNode HT[],HuffmanCode &HC,int n)  //哈夫曼编码实现 
{
	int start,p,c;
	char *cd = new char[n];
	cd[n-1]='\0';
	for(int i=0;i<n;i++)
	{
		start=n-1;
		c=i;
		p=HT[i].parent;
		while(p!=-1)
		{
			--start;
			if(HT[p].lchild==c) cd[start]='0';
			else cd[start]='1';
			c=p;
			p=HT[p].parent;
		}
		HC[i]=new char[n-start];
		strcpy(HC[i],&cd[start]);
	}
	delete cd;
}
void Select(HTNode HT[],int sum,int &s1,int &s2)
{
	int i,j;
	for(i=0;i<sum;i++)
	{
		if(HT[i].parent==-1)
		{
			s1=i;     //初始化s1
			break; 
		}
	}
	for(i=0;i<sum;i++)
	{
		if(HT[i].parent==-1 && HT[s1].weight>HT[i].weight)	s1=i;
	}
	for(j=0;j<sum;j++)
	{
		if(HT[j].parent==-1 && j!=s1)
		{
			s2=j;
			break;
		}
	}
	for(j=0;j<sum;j++)
	{
		if(HT[j].parent==-1 && HT[s2].weight>HT[j].weight&& j!=s1)	s2=j;
	}
}
void HuffmanTree(HTNode HT[],int w[],int n)
{
	for(int i=0;i<2*n-1;i++)
	{
		HT[i].weight=0;
		HT[i].parent=-1;
		HT[i].lchild=-1;
		HT[i].rchild=-1;	
	}
	for(int i=0;i<n;i++)
		HT[i].weight=w[i];
	for(int j=n;j<2*n-1;j++)
	{
		int s1,s2;
		Select(HT,j,s1,s2);
		HT[s1].parent=j;
		HT[s2].parent=j;
		HT[j].lchild=s1;
		HT[j].rchild=s2;
		HT[j].weight=HT[s1].weight+HT[s2].weight;
	}
}
void encoding(HTNode HT[],HuffmanCode &HC,char *ch,int n)   
{
	char s;
	string ss="";
	char *c=new char[9999];
	int i=0; 
	ifstream ToBeTran;
	ofstream CodeFile("CodeFile.txt");
	ToBeTran.open("ToBeTran.txt");
	cout<<"读入待编码文件ToBeTran.txt并进行编码\n";
	while (!ToBeTran.eof()) 
	{
		ToBeTran>>s;
		c[i]=s; //输出 
		i++;
	}
	i=0;
	while(c[i+1]!='\0')
	{
		for(int j=0;j<n;j++)
		{
			if(c[i]==ch[j])
			{
				ss=ss+HC[j];
				i++;
				break;
			}
		}
	} 
	cout<<"编码为："<<ss;
	cout<<"\n编码成功！\n将编码结果存入文件CodeFile.txt中";
	CodeFile<<ss;
	CodeFile.close();
	cout<<"存入成功！\n";		
} 
void decoding(HTNode HT[],char *ch,char *&b,int n)   //b[] 用来记录译出的字符 
{
	cout<<"读入待译码文件CodeFile.txt进行译码\n";
	char s;
	int i=0;
	string ss="";
	ifstream CodeFile;
	char *d=new char[999];
	CodeFile.open("CodeFile.txt");
	while (!CodeFile.eof()) 
	{
		CodeFile>>s;
		d[i]=s;
		i++;
	}
	i=0;
	int p=2*n-2;  //根结点下标 
	int k=0;
	for(i=0;d[i+1]!='\0';i++)
	{
		if(d[i]=='0')p=HT[p].lchild;
		if(d[i]=='1')p=HT[p].rchild;
		if(HT[p].lchild==-1 && HT[p].rchild==-1)
		{
			b[k++]=ch[p];	
			p=2*n-2;
		}
	} 
	b[k]='\0'; //将结果存入TextFile
	k=0;
	ofstream TextFile("TextFile.txt");
	cout<<"译码为：";
	while(b[k]!='\0')
	{
		cout<<b[k];
		TextFile<<b[k];
		k++;
	}
	TextFile.close(); 
	cout<<"\n成功将译码存入文件TextFile.txt中\n"; 
}
void print() //印代码文件（Print）。将文件CodeFile以紧凑格式显示在终端上，每行50个代码。同时将此字符形式的编码文件写入文件CodePrin中。
{
	char *q=new char[MAX_LEN];
	char in;
	ifstream CodeFile;
	ofstream CodePrin("CodePrin.txt");
	CodeFile.open("CodeFile.txt");
	int i=0,count=0;
	while(!CodeFile.eof())
	{
		CodeFile>>in;
		q[i]=in;
		i++;
	}
	i=0;
	cout<<"打印CodeFile内容：\n"; 
	while(q[i+1]!='\0')
	{
		cout<<q[i];
		CodePrin<<q[i];
		count++;
		i++;
		if(count==50)
		{
			cout<<endl;
			count=0;
		}
	}
	cout<<"\n成功将编码写入文件CodePrin.txt中\n";
} 
void printhelp(HTNode HT[],int index,string ss,char *ch,ofstream &TreePrin,int n)
{
	ss+="	";
	if(HT[index].lchild==-1 && HT[index].rchild==-1)
	{
		//cout<<ss<<HT[index].weight<<endl;
		if(index>n)
		{
			cout<<ss<<"#"<<endl;
			TreePrin<<ss<<"#"<<endl;
		}
		else
		{
			cout<<ss<<ch[index]<<endl;
			TreePrin<<ss<<ch[index]<<endl;
		  }  
		return;
	}
	else
	{
		printhelp(HT,HT[index].lchild,ss,ch,TreePrin,n);
	//	cout<<ss<<HT[index].weight<<endl;
		if(index>n)
		{
			cout<<ss<<"#"<<endl;
			TreePrin<<ss<<"#"<<endl;
		}
		else 
		{
			cout<<ss<<ch[index]<<endl;
			TreePrin<<ss<<ch[index]<<endl;
		 } 
		printhelp(HT,HT[index].rchild,ss,ch,TreePrin,n);
	}
} 
void treeprinting(HTNode HT[],int n,char *ch)  //印哈夫曼树（Tree printing）。将已在内存中的哈夫曼树以直观的方式（树或凹入表形式）显示在终端上，同时将此字符形式的哈夫曼树写入文件TreePrint中
{
	ofstream TreePrin("TreePrin.txt");//
	void printhelp(HTNode HT[],int index,string ss,char *ch,ofstream &TreePrin,int n);
	string ss="";
	int index=2*n-2;  //index从最后一个结点开始 
	cout<<"打印哈夫曼树（权值）：\n";
	printhelp(HT,index,ss,ch,TreePrin,n);
} 
void menu()
{
	char g;   //g是每次输入的操作 
	int n;    //n是元素总个数 
	char *ch;  //ch是读入的字符 例如+ a b c d e f g等 
	HuffmanCode HC=new char*[MAX_LEN]; 
	HTNode *HT=new HTNode[MAX_LEN];
	char *b=new char[MAX_LEN];
	cout<<"菜单：\n";
	cout<<"I：初始化（Initialization）\nE：编码（Encoding）\nD：译码（Decoding）\nP：印代码文件（Print）\nT：印哈夫曼树（Tree printing）\nQ：退出(Quit)\n";
	while(true)
	{
		cout<<"\n请输入想要实现的操作：";
		cin>>g;
		switch(g)
		{
			case 'I':	
				Initialization(HT,HC,ch,n);
				break;
			case 'E':
				encoding(HT,HC,ch,n);
				break;
			case 'D':
				decoding(HT,ch,b,n);
				break;
			case 'P':
				print();
				break;
			case 'T':
				treeprinting(HT,n,ch);
				break;
			case 'Q':
				cout<<"退出成功！\n";
				exit(0);
		} 
	}
	return;
 } 
int main()
{
	void encoding(HTNode HT[],HuffmanCode &HC,int n);
	void menu();
	void encoding(HTNode HT[],HuffmanCode &HC,int n);
	void Initialization();
	menu(); 
	return 0;
}
