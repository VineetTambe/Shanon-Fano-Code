/**
	Author : Vineet Tambe 
	Batch : N-6
	Roll number : 32265
*/
//Shanon Fano Coding using string to store the code
#include<iostream>
#include<algorithm>
#include<string>
#include<cmath>
#include <bits/stdc++.h>
#include<limits>
using namespace std;


int check(double*,int);
double sumProb(double*,int,int);
vector<string> compute(double*,vector<string>,int,int);
double L_bar(double*,vector<string>,int);
double Entropy(double*,int);
int len(string);



template <typename T>
bool ApproximatelyEqual(const T dX, const T dY)
{
    return std::abs(dX - dY) <= std::max(std::abs(dX), std::abs(dY))
    * std::numeric_limits<T>::epsilon();
}

int main()
{
	int symboll_num=0;
	
	cout<<"Please enter the number of symbolls\n";
	cin>>symboll_num;
	
	double *prob = (double*)malloc(symboll_num*(sizeof(double)));
	vector<string>code;
	
	cout<<"Enter the probabilities of the symboll in the respective order\n";
	
	for(int i=0;i<symboll_num;i++)
	{
		cin>>prob[i];
		code.push_back("");
	}/*
	prob[0]=0.45;
	prob[1]=0.15;
	prob[2]=0.1;
	prob[3]=0.1;
	prob[4]=0.08;
	prob[5]=0.08;
	prob[6]=0.04;*/
	cout<<"Probabilities of symbolls are :\n";
	for(int i=0;i<symboll_num;i++)
	{
		cout<<"x"<<i;
		cout<<"  "<<prob[i]<<"\n";
	}
	if(ApproximatelyEqual(sumProb(prob,0,symboll_num),1.0))
	{
		sort(prob,prob+symboll_num,greater<double>());
		cout<<"sorted probability\n";
		for(int i=0;i<symboll_num;i++)
		{
			cout<<"x"<<i;
			cout<<"  "<<prob[i]<<"\n";
		}	
		code = compute(&prob[0],code,0,symboll_num);
		for(int i =0;i<symboll_num;i++)
		{
			cout<<code[i]<<"\n";
		}
		double L = L_bar(&prob[0],code,symboll_num);
		double H = Entropy(&prob[0],symboll_num);
		double efficiency = H/L*100;
		cout<<"L_bar = "<<L<<"bits/symbol"<<"\n";
		cout<<"Entropy = "<<H<<"bits/symbol"<<"\n";
		cout<<"Efficiency = "<<efficiency<<"%\n";
		
		
	}	
	else
	{
		cout<<"Please enter correct probabilities!";
	}
	free(prob);
	return 0;	
}
double sumProb(double *prob,int l1,int l2)
{
	double s=0.0;
	for(int i=l1;i<l2;i++)
	{
		s+=prob[i];
	}
	return s;
}
vector<string> compute(double *prob,vector<string> code,int l1,int l2)
{
	if(l1==(l2-1))
	{
		return code;
	}
	else
	{
		
		double prob1=0.0,prob2=0.0;
		int x=l1,y=l2;
		double n=0.0,m=0.0;
		while(x!=y)
		{
			prob1+=prob[x];			
			prob2=sumProb(prob,x+1,y); 
			if(prob1>=prob2)
			{	
				for(int i=l1;i<=x;i++)
				{
					code[i].append("0");
				}
				for(int i=x+1;i<y;i++)
				{
					code[i].append("1");
				}
				break;
			}
			else
			{
				if(x+2<y)
				{
					n=abs(prob1-prob2);
					m=abs(prob1+prob[x+1]-sumProb(prob,x+2,y));
					if(n<m)
					{
						for(int i=l1;i<=x;i++)
						{	
							code[i].append("0");
						}		
						for(int i=x+1;i<y;i++)
						{
							code[i].append("1");
						}
						break;
					}
				}
			}
			x++;
		}
		if(x!=l1)
		{
			code = compute(prob,code,l1,x+1);
			code = compute(prob,code,x+1,y);
		}
		else
		{
			code = compute(prob,code,x+1,y);
		}
		return code;
	}
}
double Entropy(double *prob,int y)
{
	double H = 0.0;
	for(int i=0;i<y;i++)
	{
		H+= -1*prob[i]*log2(prob[i]);
	}
	return H;
}
double L_bar(double *prob,vector<string> code,int y)
{
	double L=0.0;
	int l;
	for(int i=0;i<y;i++)
	{
		l=len(code[i]);
		L+= prob[i]*l; 
	}
	return	L;
}
int len(string str)
{
	int i=0;
	while(str[i]!='\0')
	{
		i++;
	}
	return i;
}


