#ifndef __MY_VECTOR_H
#define __MY_VECTOR_H

#include <iostream>
#include <assert.h>
#include <iterator>

template <typename T>
class my_vector{
    // 这段是什么区域？(private)
public:
    typedef T* iterator;
    typedef const T* const_iterator;

private:
    iterator _start{nullptr};
    iterator _finish{nullptr};          // 指向最后一个元素的后一个地址
    iterator _end_of_storage{nullptr};  // 最后一块限定内存的后一个地址

public:
    // 构造函数
    my_vector(){

    }

    iterator begin(){
        return _start;
    }
    iterator end(){
        return _finish;
    }

    // 定义const声明的成员函数，使const对象也能够调用相应的成员函数
    const_iterator begin()const{
        return _start;
    }
    const_iterator end()const{
        return _finish;
    }

    std::size_t size(){
        // 在 C++ 中，当两个类型相同的指针相减时，编译器返回的结果是两个指针之间元素的个数
        return (std::size_t)(_finish-_start);
    }
    std::size_t capacity(){
        return (std::size_t)(_end_of_storage-_start);
    }

    // 增加容器的容量（capacity），使其能够容纳至少 n 个元素
    void reserve(std::size_t n){
        if(capacity() < n){
            std::size_t old_size = size();
            T* temp{new T[n]};
            // memcpy(temp, _start, size());
            for(std::size_t i=0; i<old_size; i++){
                temp[i] = _start[i];
            }

            delete[] _start;
            _start = temp;
            _finish = _start + old_size;
            _end_of_storage = _start + n;
        }
    }

    // 改变容器的大小（size），使其包含 n 个元素，多出来的设置为x，size>n时删除末尾几个
    void resize(std::size_t n, const T& x = T()){   // T()是临时对象，是参数x的默认值
        if(size() < n){
            reserve(n);
            // memset(_start[size()], x, n-size());
            for(std::size_t i=size(); i<n; i++){
                _start[i] = x;
            }
            _finish = _start + n;
        }
        else if(size() > n){
            _finish = _start + n;
        }
    }

    void push_back(const T& x){
        if(_finish == _end_of_storage){
            std::size_t new_capacity = capacity()==0?2:capacity()*2;
            reserve(new_capacity);
        }
        *_finish = x;
        _finish++;
    }

    void pop_back(){
        _finish--;
    }

    iterator insert(iterator pos, const T& x){

        assert(pos >= _start && pos < _finish);

        // 扩容
        if(_finish == _end_of_storage){
            std::size_t site = pos - _start;
            std::size_t new_capacity = (capacity()==0)?2:2*capacity();
            reserve(new_capacity);
            pos = _start + site;
        }

        // 后移
        iterator temp = _finish-1;
        while(temp != pos){
            *(temp+1) = *temp;
            temp--;
        }

        // 插值
        *pos = x;
        _finish++;
        return pos;
    }

    iterator erase(iterator pos){
        assert(pos >= _start && pos < _finish);
        assert(size() > 0);

        iterator temp = pos+1;
        while(temp < _finish){
            *(temp-1) = *temp;
            temp++;
        }
        _finish--;
        return pos;
    }

    // 重载[]（因为该自定义类本身不能使用[]）
    T& operator[](std::size_t i){
        assert(i < size());
        return _start[i];
    }
    const T& operator[](std::size_t i) const{
        assert(i < size());
        return _start[i];
    }

    // 重载=
    my_vector<T>& operator=(my_vector<T>& v){
        std::swap(_start, v._start);        // 按值传递
        std::swap(_finish, v._finish);
        std::swap(_end_of_storage, v._end_of_storage);
        return *this;
    }

    // 构造函数
    my_vector(std::size_t n, const T& x = T()){     // 注意要const常量引用，否则右值传不进来
        resize(n, x);
    }

    // template <typename input_iterator>      // 允许输入其他类型迭代器，只是要按该vector类型来存放
    // my_vector(input_iterator first, input_iterator last){
    //     while(first != last){
    //         push_back(*first);
    //         first++;
    //     }
    // }

    // 拷贝构造函数
    my_vector(const my_vector<T>& v){
        reserve(v.capacity());
        for(const auto& e:v){   // 从v.begin()到v.end()取出元素
            push_back(e);
        }
    }

    // 析构函数
    ~my_vector(){
        delete[] _start;
        _start = nullptr, _finish = nullptr, _end_of_storage = nullptr;
    }

};

#endif