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
	
	tree.open("F:\\������ҵ\\���ݽṹ\\�����\\1725111037 Ԫ����\\hfmTree.txt");
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
	/*	for(int j=0;j<n+1;j++)    //ǰ��n������code��,��ȥ��һ�е���������n+1�� 
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
		group++;   //���group=1��index�� 2��word������ch�� 3(weight) 4(lchild) 5(rchild) 6(code,����HC[]); 
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

