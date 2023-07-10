 #pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <assert.h>
#include <string.h>

namespace tao
{
	
	class string
	{
 	  public:
		  typedef char* iterator;//普通迭代器
		  typedef  const char* const_iterator; //const迭代器

		  //无参构造---不代表没有数据，是有一个\0的，但没有大小,因为\0不计入大小计算中
		 /* string()
		  {
			  _size = _capacity = 0;
			  _str = new char[1];
			  _str[0] = '\0';
		  }*/
		  string(const char* str="")//可以与无参构造一起复用。全缺省//常量字符串后面默认有\0
		  {
			  _size = strlen(str);
			  _capacity = _size;
			  //_str=str
			  //不能直接将str赋给_str，因为str是const修饰的，库里规定的，不可以被修改，而_str不是const类型的
			  //而需要开辟一块跟str一样大的空间，然后拷贝给_str
			  _str = new char[_capacity + 1];
			  memcpy(_str, str,_size+1);
	       }
		  string (const string& s)//深拷贝
		  {
			  _str = new char[s._capacity+1];
			  memcpy(_str, s._str,s.size()+1);
			  _size = s._size;
			  _capacity = s._capacity;
		  }
		  //s1=s3
		  string& operator=(const string& s)
		  {
			  if (*this != s)
			  {
				  char* tmp = new char[s._capacity + 1];
				  memcpy(tmp, s.c_str(), s._size);
				  delete[] _str;
				  _str = tmp;
				  _size = s.size();
				  _capacity = s._capacity;
				
			  }
			  return *this;
		  }
		  ~string()
		  {
			  delete[] _str;
			  _str = nullptr;
			  _size = _capacity = 0;
		  }
		 const char* c_str() const
	      {
			  return _str;
		  }
		  //要实现遍历，首先需向大小
		 size_t size() const //一般只读，不给修改
		 {
			 return _size;
		 }
		 char& operator[](int pos)//可以引用返回，因为出了函数值还在
		 {
			 assert(pos < _size);
			 return _str[pos];
		 }
		 //有两种重载类型，一种是上面的另一种是const修饰的对象，只读，不给修改的
		 const char& operator[](int pos) const
		 {
			 assert(pos < _size);
			 return _str[pos];
		 }
		 //通过迭代器进行遍历，迭代器是一种类型，是string类里的一种类型，可以是内部类，也可以是自定义的。
		 //我们在这里自定义一个iterator。
		 iterator begin()//begin返回的是指向开头位置的迭代器
		 {
			 return _str;
		 }
		 iterator end()//end返回的是指向最后一个字符的下一个位置
		 {
			 return _str + _size;
		 }
		 const_iterator begin()const
		 {
			 return _str;
		 }
		 const_iterator end()const
		 {
			 return _str + _size;
		 }

		 void reserve(size_t n)
		 {
			 if (n > _capacity)
			 {
				 char* temp = new char[n + 1];
				 memcpy(temp, _str,_size+1);
				 delete[] _str;
				_str = temp;
				_capacity = n;
			 }
		 }
//增
		 void push_back(char ch)//尾插首秀按需要考虑是否需要扩容--->扩容最好用reserve来扩容
		 {
			 if (_size >= _capacity)
			 {
				 //可以直接扩容2倍，但要注意一种情况，当为空串时
				 reserve(_capacity == 0 ? 4 : 2 * _capacity);
				
			 }
			 _str[_size++] = ch;
			 _str[_size] = '\0';
		 }
		 void append(const char * str)
		 {
			 size_t len = strlen(str);
			 if (_size + len > _capacity)
			 {
				 //这个不可以直接2倍扩容，因为可能2倍扩容后的容量还不够
				 //至少需要扩容到_size+len大小
				 reserve(_size + len);
				 memcpy(_str + _size, str,len+1);
				 _size += len;
			 }
		 }
		 string& operator+=(char ch)
		 {
			 push_back(ch);
			 return *this;
		 }
		 string& operator+=(const char* str)
		 {
			 append(str);
			 return *this;
		 }
		 void insert(size_t pos, size_t n, char ch)
		 {
			 //第一步检查pos的合法性
			 assert(pos <= _size);
			 //检查是否需要扩容---》直接用reserve扩容
			 if (_size+n > _capacity)
			 {
				 reserve(_size + n);
			 }
			 //第三步挪动数据
			 size_t end = _size;
			 //这里有一个坑，当pos位置为0时，也就是头插时会出问题，因为while循环的调试是end>=pos
			 //也就是end需要小于0时才可以停下来，当end=0时，进入循环里，end--，后不会变成-1，因为end是size_t，会变成很大是数
			 //所以有问题，解决方法是再加上一个条件，那就是end>=pos&&end！=npos时当满足这两个条件时
			 while (end >= pos&&end!=npos)
			 {
				 _str[end + n] = _str[end];
				 end--;
			 }
			 for (int i = 0; i < n; i++)
			 {
				 _str[pos + i] = ch;
			 }
			  _size += n;

		 }

		 void insert(size_t pos, const char* str)
		 {
			 //第一步检查pos的合法性
			 assert(pos <= _size);
			 //检查是否需要扩容---》直接用reserve扩容
			 size_t len = strlen(str);
			 if (_size + len > _capacity)
			 {
				 reserve(_size + len);
			 }
			 //挪动数据
			 size_t end = _size;
			 while (end >= pos && end != npos)
			 {
				 _str[end + len] = _str[end];
				 end--;
			 }
			 for (int i = 0; i < len; i++)
			 {
				 _str[pos + i] = str[i];
			 }
			 _size += len;
		 }

//删
		 void erase(size_t pos, size_t len=npos)
		 {
			 assert(pos <= _size);
			 if (len == npos || pos + len > _size)//删除完
			 {
				 _str[pos] = '\0';
				 _size = pos;
				 _str[_size] = '\0';
			 }
			 else
			 {
				 size_t end = pos + len;
				 while (end <= _size)
				 {
					 _str[pos++] = _str[end++];
					
				 }
				 _size -= len;
			 }
			
		 }
		 void clear()
		 {
			 _str[0] = '\0';
			 _size = 0;
		 }
//查/改
		 size_t find(char ch, size_t pos = 0)
		 {
			 assert(pos <= _size);
			 for (size_t i = pos; i < _size; i++)
			 {
				 if (_str[i] == ch)
					 return i;
			 }
			 return npos;

		 }
		 size_t find(const char* str, size_t pos = 0)
		 {
			 assert(pos <= _size);
			 const char* tmp = strstr(_str+pos, str);//返回的是指向str位置的指针
			 if (tmp == nullptr)
			 {
				 return npos;
			 }
			 return tmp - _str;
		 }
		 string substr(size_t pos,size_t len=npos)
		 {
			 assert(pos <= _size);
			 size_t n = len;
			 if (len == npos || pos + len > _size)
			 {
				 n = _size - pos;
			 }
			 string tmp;
			 for (size_t i = pos; i < n + pos; i++)
			 {
				 tmp += _str[i];
			 }
			 return tmp;
		 }
		 void resize(size_t n,char ch='\0')
		 {
			 if (n < _size)
				 _size = n;
			 else
			 {
				 reserve(n);//不管n是否大于capacity都给他扩容到n即可
				 for (size_t i = _size; i < n; i++)
				 {
					 _str[i] = ch;
				 }
				 _size = n;
				 _str[_size] = '\0';
			 }
		 }
//比较大小
		 bool operator<(const string& s)
		 {
			 int i1 = 0;
			 int i2 = 0;
			 while (i1 < _size && i2 < s.size())
			 {
				 if (_str[i1] < _str[i2])
				 {
					 return true;
				 }
				 else if (_str[i1] > _str[i2])
				 {
					 return false;
				 }
				 else
				 {
					 ++i1;
					 ++i2;
				 }
			 }
			 //"tao"  "taox"
			 //taox   tao
			 //tao tao
			 if (i1 == _size && i2 != s.size())
			 {
				 return true;
			 }
			 else
			 {
				 return false;
			 }
		 }
		 bool operator==(const string& s)
		 {
			 return _size == s.size() && memcmp(_str, s.c_str(), _size);
		 }
		 bool operator<=(const string s)
		 {
			 return *this < s || *this == s;
		 }
		 bool operator>(const string& s)
		 {
			 return !(*this <= s);
		 }
		 bool operator>=(const string& s)
		 {
			 return !(*this < s);
		 }
		 bool operator!=(const string& s)
		 {
			 return !(*this == s);
		 }
	  private:
		  char* _str;
		  size_t _size;
		  size_t _capacity;
		  public:

		  size_t static npos;
	};

	size_t string::npos = -1;

	/* ostream& operator<<(ostream& out, const string& s)
	{

		for (auto ch : s)
		{
			out << ch;
		}
		return out;

	}*/
	 
	istream& operator>>(istream& in, string& s)
	{
		//每次进入流提取之前都要把之前的缓存清理掉。
		s.clear();
		char ch;
		ch = in.get();//in流提取，会跳过空格和换行
		//但是这样很麻烦，需要不断的扩容，从小扩到大。
		// 
		//还要清理字符之前的空格和换行
		while (ch == ' ' || ch == '\n')
		{
			ch = in.get();
		}
		//所有又采取一种方法，把ch提取的字符县附近一个数组里面
		//这样扩容就不会频繁的扩容，一段一段的扩容，累加一定量再放进去
		char buf[128];
		int i = 0;
		while (ch != ' ' && ch != '\n')
		{
			buf[i++] = ch;
			
			if (i == 127)
			{
				buf[i] = '\0';
				s += buf;
				i = 0;
			}
			ch = in.get();
		}
		if (i != 0)
		{
			buf[i] = '\0';
			s += buf;
		}
		return in;
	}

};


//c的字符数组以\0为终止长度
//string不看\0,以size为终止长度