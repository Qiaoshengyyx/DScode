#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	int n=27;
	char *ch=new char[n];
	int *p=new int[n];
	char out;
	int o; 
	int i=0,j=0;
	fstream myin;
	myin.open("≤‚ ‘.txt");
	while(!myin.eof())
	{
		if(i<n)
		{
			myin>>ch[i];
			cout<<ch[i]<<" ";
			i++;
		} 
		else
		{
			myin>>p[j];
			cout<<p[j]<<" ";
			j++;
		}
	}
	myin.close(); 
	return 0;
 } 
