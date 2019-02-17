#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
struct HTNode
{
	int weight,parent,lchild,rchild;
};
typedef char **HuffmanCode;
int main()
{
	fstream tree;
	
	tree.open("F:\\各种作业\\数据结构\\第五次\\1725111037 元雨暄\\hfmTree.txt");
	int i=0,count=0,index=0,group=0;
	int n=27;
	char c;
	char *ch=new char[n];
	int *p=new int[n];
	string s;
//	int shuru;
	HTNode *HT=new HTNode[2*n-1]; 
	while(!tree.eof())
	{	
	/*	for(int j=0;j<n+1;j++)    //前面n行是有code的,除去第一行的文字描述n+1行 
		{
			if(j<6)continue;
			if(j%6==1)
			{
				tree>>s;
			   // istringstream is();
			//	tree>>ch[i];
				cout<<s;
				//ch[i]=c;
				//i++;
			}
			if(j%6==2)
			{
				tree>>s;
				cout<<s;
				i++;
			}
			//cout<<"1\t";
		}
		cout<<"n";*/
		
		tree>>s;
		cout<<s;
		group++;   //如果group=1（index） 2（word，放入ch） 3(weight) 4(lchild) 5(rchild) 6(code,放入HC[]); 
		count++;
	/*	if(index>=(n+1) && count==6)
		{
			index++;
			count=0;
			cout<<endl;
		}
		if(count==7)
		{
			index++;
			count=0;
			cout<<endl;
		}*/
	}
	tree.close();
	return 0; 
	
	
 } 

