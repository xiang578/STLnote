#include<stdio.h>
#include<list>
#include<iostream>
using namespace std;

int main()
{
    list<int>l;
    for(int i=1;i<=10;i++)
        l.push_back(i);
    list<int>::iterator it;
    for(it=l.begin();it!=l.end();++it)
        cout<<*it<<" ";
    cout<<endl;
    l.reverse();
    for(it=l.begin();it!=l.end();++it)
        cout<<*it<<" ";
    cout<<endl;
    return 0;
}
