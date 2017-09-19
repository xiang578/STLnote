#include <stdio.h>
#include <iostream>
using namespace std;
//定义一个简单的iterator
template <class T>
struct MyIter{
    typedef T value_type; // 内嵌型别声明
    T* ptr;
    MyIter(T* p =0):ptr(p){}
    T& operator*() const {return *ptr;}
};

template <class I>
typename I::value_type // func返回值型别
func(I iter){
    return *iter;
}

int main(){
    MyIter<int> iter(new int(8));
    cout<<func(iter)<<endl;
}
