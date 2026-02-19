#include "stack_and_queue.h"

using namespace stack_and_queue;

/**
 * 【232. 用栈实现队列】
 */
MyQueue::MyQueue(){

}
void MyQueue::push(int x){
    in_stack.push(x);
}
int MyQueue::pop(){
    if(!out_stack.empty()){
        int out = out_stack.top();
        out_stack.pop();
        return out;        
    }

    while(!in_stack.empty()){
        out_stack.push(in_stack.top());     // top输出顶部的数值
        in_stack.pop();     // pop不提供输出
    }
    int out = out_stack.top();
    out_stack.pop();
    return out;
}
int MyQueue::peek(){
    if(!out_stack.empty()){
        return out_stack.top();
    }

    while(!in_stack.empty()){
        out_stack.push(in_stack.top());     // top输出顶部的数值
        in_stack.pop();     // pop不提供输出
    }
    return out_stack.top();
}
bool MyQueue::empty(){
    if(in_stack.empty() && out_stack.empty()){
        return true;
    }
    return false;
}

/**
 * 【225. 用队列实现栈】
 */
MyStack::MyStack(){

}
void MyStack::push(int x){
    queue.push(x);
}
int MyStack::pop(){
    int size = queue.size();
    size--;
    while(size--){
        // 将头部的元素重新添加到尾部
        queue.push(queue.front());
        queue.pop();
    }
    int out = queue.front();
    queue.pop();
    return out;
}
int MyStack::top(){
    int size = queue.size();
    size--;
    while(size--){
        // 将头部的元素重新添加到尾部
        queue.push(queue.front());
        queue.pop();
    }
    int out = queue.front();
    queue.push(queue.front());
    queue.pop();
    return out;
}
bool MyStack::empty(){
    if(!queue.empty()){
        return false;
    }
    return true;
}

/**
 * 【20. 有效的括号】
 */
bool Solution::isValid(std::string s){
    std::stack<char> left_stack;        // 左括号栈
    for(int i=0; i<s.size(); i++){
        if(s[i]=='(' || s[i]=='{' || s[i]=='['){
            left_stack.push(s[i]);
        }
        else if(s[i]==')'){
            // 无元素时执行pop操作会导致报错

            if(left_stack.empty() || left_stack.top() != '('){
                return false;
            }
            left_stack.pop();
        }
        else if(s[i]=='}'){
            if(left_stack.empty() || left_stack.top() != '{'){
                return false;
            }
            left_stack.pop();
        }
        else if(s[i]==']'){
            if(left_stack.empty() || left_stack.top() != '['){
                return false;
            }
            left_stack.pop();
        }
    }
    if(left_stack.empty()){
        return true;
    }
    return false;
}

/**
 * 【1047. 删除字符串中的所有相邻重复项】
 */
std::string removeDuplicates(std::string s){
    std::stack<char> the_stack;

    the_stack.push(s[0]);
    for(int i=1; i<s.size(); i++){
        if(!the_stack.empty() && the_stack.top() == s[i]){
            the_stack.pop();
        }
        else{
            the_stack.push(s[i]);
        }
    }

    // 输出成字符串
    std::string res(the_stack.size(), ' ');     // 先数量后赋值
    for(int i=0; i<res.size(); i++){
        res[res.size()-1-i] = the_stack.top();
        the_stack.pop();
    }
    return res;
}

/**
 * 【150. 逆波兰表达式求值】
 */
int string_to_num(std::string s){
    if(s[0] == '-'){
        long res = s[1]-'0';
        for(int i=2; i<s.size(); i++){
            res = res*10+(s[i]-'0');
        }
        return -1*res;
    }
    else{
        int res = s[0]-'0';
        for(int i=1; i<s.size(); i++){
            res = res*10+(s[i]-'0');
        }
        return res;
    }
}

#if 0
std::string num_to_string(long num){
    std::string s = "";
    int flag = 0;
    if(num < 0){
        flag = 1;
        num *= -1;
    }
    else if(num == 0){
        return "0";
    }

    while(num != 0){
        int n = num%10;
        char c = '0'+n;
        s.push_back(c);     // 像字符串末尾插入字符
        num /= 10;
    }

    if(flag){
        s.push_back('-');
    }
    
    // 翻转
    int left_p = 0, right_p = s.size()-1;
    while(left_p < right_p){
        char temp = s[left_p];
        s[left_p] = s[right_p];
        s[right_p] = temp;
        left_p++;
        right_p--;
    }
    return s;
}
#endif

int Solution::evalRPN(std::vector<std::string>& tokens){
    // 原版自己写的较为耗时，因为没必要字符串和数值转来转去，栈的定义直接数值即可

    // 使用栈，每遇见符号就pop
    std::stack<long long> st;
    for(int i=0; i<tokens.size(); i++){
        if(tokens[i]=="+" || tokens[i]=="-" || tokens[i]=="*" || tokens[i]=="/"){
            long long num1 = st.top();
            st.pop();
            long long num2 = st.top();
            st.pop();
            long long num3 = 0;
            if(tokens[i]=="+"){
                num3 = num2+num1;
            }
            else if(tokens[i]=="-"){
                num3 = num2-num1;
            }
            else if(tokens[i]=="*"){
                num3 = num2*num1;
            }
            else if(tokens[i]=="/"){
                num3 = num2/num1;
            }
            st.push(num3);
        }
        else{
            st.push(string_to_num(tokens[i]));  // 有现成的std::stoll，字符串转换为 long long 类型
        }
    }
    return st.top();
}

/**
 * 【239. 滑动窗口最大值】（力扣上困难的就先暂时放下吧）
 */
std::vector<int> Solution::maxSlidingWindow(std::vector<int>& nums, int k){
    std::queue<int> queue;
    std::vector<int> max_vector(nums.size()-k+1, 0);
    int max_num = 0;

    for(int i=0; i<k; i++){
        queue.push(nums[i]);
    }

    for(int i=0; i<max_vector.size(); i++){
        // 找最大

        queue.pop();
        queue.push(nums[k+i]);
    }
}

/**
 * 【347. 前 K 个高频元素】
 */

