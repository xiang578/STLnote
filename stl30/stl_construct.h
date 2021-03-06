/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

// placement new 相关
#include <new.h>

__STL_BEGIN_NAMESPACE

//调用对象的析构函数
template <class T>
inline void destroy(T* pointer) {
    pointer->~T();
}

//placement new, 在已经申请的内存上进行构造对象
template <class T1, class T2>
inline void construct(T1* p, const T2& value) {
  new (p) T1(value);
  //使用opreator new分配的内存空间无法使用construct函数构造对象，需要用placement new来构造对象
  //C++ primerP729，形式 new (place_address) type (initializers)
  //p为内存的地址，initializers 为初始值列表，用于构造新分配的对象
}

//no trivial destructor情况，调用对象的析构函数
template <class ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
  for ( ; first < last; ++first)
    destroy(&*first);
}

// 对象只有系统生成的析构函数，不做任何处理
template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator, ForwardIterator, __true_type) {}

// 利用__type_traits判断对象是否有定义析构函数，决定使用的 __destroy_aux 版本
template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
  typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
  __destroy_aux(first, last, trivial_destructor());
}

//处理一组对象的版本
template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
  __destroy(first, last, value_type(first));
}

//特化版本，specializtion
inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */

// Local Variables:
// mode:C++
// End:
