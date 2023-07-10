 #pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <assert.h>
#include <string.h>

namespace tao
{
	
	class string
	{
 	  public:
		  typedef char* iterator;//��ͨ������
		  typedef  const char* const_iterator; //const������

		  //�޲ι���---������û�����ݣ�����һ��\0�ģ���û�д�С,��Ϊ\0�������С������
		 /* string()
		  {
			  _size = _capacity = 0;
			  _str = new char[1];
			  _str[0] = '\0';
		  }*/
		  string(const char* str="")//�������޲ι���һ���á�ȫȱʡ//�����ַ�������Ĭ����\0
		  {
			  _size = strlen(str);
			  _capacity = _size;
			  //_str=str
			  //����ֱ�ӽ�str����_str����Ϊstr��const���εģ�����涨�ģ������Ա��޸ģ���_str����const���͵�
			  //����Ҫ����һ���strһ����Ŀռ䣬Ȼ�󿽱���_str
			  _str = new char[_capacity + 1];
			  memcpy(_str, str,_size+1);
	       }
		  string (const string& s)//���
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
		  //Ҫʵ�ֱ��������������С
		 size_t size() const //һ��ֻ���������޸�
		 {
			 return _size;
		 }
		 char& operator[](int pos)//�������÷��أ���Ϊ���˺���ֵ����
		 {
			 assert(pos < _size);
			 return _str[pos];
		 }
		 //�������������ͣ�һ�����������һ����const���εĶ���ֻ���������޸ĵ�
		 const char& operator[](int pos) const
		 {
			 assert(pos < _size);
			 return _str[pos];
		 }
		 //ͨ�����������б�������������һ�����ͣ���string�����һ�����ͣ��������ڲ��࣬Ҳ�������Զ���ġ�
		 //�����������Զ���һ��iterator��
		 iterator begin()//begin���ص���ָ��ͷλ�õĵ�����
		 {
			 return _str;
		 }
		 iterator end()//end���ص���ָ�����һ���ַ�����һ��λ��
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
//��
		 void push_back(char ch)//β�����㰴��Ҫ�����Ƿ���Ҫ����--->���������reserve������
		 {
			 if (_size >= _capacity)
			 {
				 //����ֱ������2������Ҫע��һ���������Ϊ�մ�ʱ
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
				 //���������ֱ��2�����ݣ���Ϊ����2�����ݺ������������
				 //������Ҫ���ݵ�_size+len��С
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
			 //��һ�����pos�ĺϷ���
			 assert(pos <= _size);
			 //����Ƿ���Ҫ����---��ֱ����reserve����
			 if (_size+n > _capacity)
			 {
				 reserve(_size + n);
			 }
			 //������Ų������
			 size_t end = _size;
			 //������һ���ӣ���posλ��Ϊ0ʱ��Ҳ����ͷ��ʱ������⣬��Ϊwhileѭ���ĵ�����end>=pos
			 //Ҳ����end��ҪС��0ʱ�ſ���ͣ��������end=0ʱ������ѭ���end--���󲻻���-1����Ϊend��size_t�����ɺܴ�����
			 //���������⣬����������ټ���һ���������Ǿ���end>=pos&&end��=nposʱ����������������ʱ
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
			 //��һ�����pos�ĺϷ���
			 assert(pos <= _size);
			 //����Ƿ���Ҫ����---��ֱ����reserve����
			 size_t len = strlen(str);
			 if (_size + len > _capacity)
			 {
				 reserve(_size + len);
			 }
			 //Ų������
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

//ɾ
		 void erase(size_t pos, size_t len=npos)
		 {
			 assert(pos <= _size);
			 if (len == npos || pos + len > _size)//ɾ����
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
//��/��
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
			 const char* tmp = strstr(_str+pos, str);//���ص���ָ��strλ�õ�ָ��
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
				 reserve(n);//����n�Ƿ����capacity���������ݵ�n����
				 for (size_t i = _size; i < n; i++)
				 {
					 _str[i] = ch;
				 }
				 _size = n;
				 _str[_size] = '\0';
			 }
		 }
//�Ƚϴ�С
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
		//ÿ�ν�������ȡ֮ǰ��Ҫ��֮ǰ�Ļ����������
		s.clear();
		char ch;
		ch = in.get();//in����ȡ���������ո�ͻ���
		//�����������鷳����Ҫ���ϵ����ݣ���С������
		// 
		//��Ҫ�����ַ�֮ǰ�Ŀո�ͻ���
		while (ch == ' ' || ch == '\n')
		{
			ch = in.get();
		}
		//�����ֲ�ȡһ�ַ�������ch��ȡ���ַ��ظ���һ����������
		//�������ݾͲ���Ƶ�������ݣ�һ��һ�ε����ݣ��ۼ�һ�����ٷŽ�ȥ
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


//c���ַ�������\0Ϊ��ֹ����
//string����\0,��sizeΪ��ֹ����