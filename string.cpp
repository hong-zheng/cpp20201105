#include <string>
#include <iostream>
using namespace std;

class String
{
public:

	//迭代器：一种访问容器元素的机制， 体现封装的特性，
	//不需要关注容器的实现细节，就可以直接访问(可读可写)元素
	//使用方式： 类似于指针的操作
	//     1. 解引用--> 获取指向位置的内容
	//     2. 位置移动 --> 执向其他位置

	//string 迭代器： 通过指针实现
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin()
	{
		//第一个元素的位置
		return _str;
	}

	iterator end()
	{
		//最后一个元素的下一个位置
		return _str + _size;
	}

	const_iterator begin() const
	{
		//第一个元素的位置
		return _str;
	}

	const_iterator end() const
	{
		//最后一个元素的下一个位置
		return _str + _size;
	}


	String()
		:_str(new char[16])
		, _size(0)
		, _capacity(0)
	{
		_str[_size] = '\0';
		_capacity = 15;
	}

	String(const char* str)
	{
		_size = strlen(str);
		_str = new char[_size + 1];
		strcpy(_str, str);
		_capacity = _size;
	}

	//String(const String& str)
	//	:_str(new char[str._capacity + 1])
	//	, _size(str._size)
	//	, _capacity(str._capacity)
	//{
	//	//深拷贝：资源拷贝
	//	strcpy(_str, str._str);
	//	cout << "String(const String&)" << endl;
	//}

	//拷贝构造：现代写法, 代码复用
	String(const String& str)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		//调用构造函数
		String tmp(str._str);
		Swap(tmp);
	}

	void Swap(String& str)
	{
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}

	//深拷贝交换： 效率低
	//void Swap(String& str)
	//{
	//	//拷贝构造
	//	String tmp = str;
	//	//赋值运算符
	//	str = *this;
	//	//赋值运算符
	//	*this = tmp;
	//}

	//String& operator=(const String& str)
	//{
	//	if (this != &str)
	//	{
	//		//开空间
	//		char* tmp = new char[str._capacity + 1];

	//		//内容拷贝
	//		strcpy(tmp, str._str);

	//		//释放原有空间
	//		delete[] _str;

	//		_str = tmp;
	//		_size = str._size;
	//		_capacity = str._capacity;
	//	}
	//	return *this;
	//}
	//赋值运算符： 现代写法， 代码复用： 拷贝构造(传参进行拷贝构造)
	String& operator=(String str)
	{
		Swap(str);
		return *this;
	}

	const char* c_str() const
	{
		return _str;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_size = _capacity = 0;
			_str = nullptr;
		}
		cout << "~String" << endl;
	}

	void pushBack(const char& ch)
	{
		//检查容量
		//if (_size == _capacity)
		//{
		//	size_t newC = _capacity == 0 ? 1 : 2 * _capacity;
		//	reserve(newC);
		//}
		////尾插
		//_str[_size] = ch;
		////更新size
		//++_size;
		//_str[_size] = '\0';
		insert(_size, ch);
	}

	void reserve(size_t n)
	{
		if (n > _capacity)
		{
			//开空间:+1--->存放\0
			char* tmp = new char[n + 1];
			//拷贝
			strcpy(tmp, _str);
			//释放原有空间
			delete[] _str;

			_str = tmp;
			//更新容量
			_capacity = n;
		}
	}

	char& operator[](size_t pos)
	{
		if (pos < _size)
			return _str[pos];
	}

	const char& operator[](size_t pos) const
	{
		if (pos < _size)
			return _str[pos];
	}

	size_t size() const
	{
		return _size;
	}

	void Append(const char* str)
	{
		//int len = strlen(str);
		////检查容量
		//if (_size + len > _capacity)
		//{
		//	reserve(_size + len);
		//}
		////尾插
		//strcpy(_str + _size, str);

		////修改size
		//_size += len;
		insert(_size, str);
	}

	String& operator+=(const char& ch)
	{
		pushBack(ch);
		return *this;
	}

	String& operator+=(const char* str)
	{
		Append(str);
		return *this;
	}

	void insert(size_t pos, const char& ch)
	{
		if (pos > _size)
			return;

		//检查容量
		if (_size == _capacity)
		{
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}
		//移动元素[pos, _size]： 从后向前移动,首先移动最右端的字符，防止覆盖
		size_t end = _size + 1;
		//end >= pos: 当pos = 0时， 死循环，访问越界
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}
		//插入
		_str[pos] = ch;

		++_size;
	}

	void insert(size_t pos, const char* str)
	{
		if (pos > _size)
			return;
		int len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len);
		}
		//移动元素[pos, _size]
		size_t end = _size + len;
		//size --> size + len,  pos ---> pos + len
		while (end > pos + len - 1)
		{
			_str[end] = _str[end - len];
			--end;
		}
		//插入
		for (int i = 0; i < len; ++i)
		{
			_str[i + pos] = str[i];
		}

		_size += len;
	}

	void resize(size_t n, const char& ch = '\0')
	{
		if (n > _capacity)
		{
			reserve(n);
		}
		if (n > _size)
		{
			memset(_str + _size, ch, n - _size);
		}
		_size = n;
		_str[_size] = '\0';
	}

	void popBack()
	{
		erase(_size - 1, 1);
	}

	void erase(size_t pos, size_t len)
	{
		if (pos < _size)
		{
			//判断删除的长度是否大于从pos位置开始的剩余字符串的长度
			if (pos + len >= _size)
			{
				_size = pos;
				_str[_size] = '\0';
			}
			else
			{
				//移动元素[pos + len, size]  ---> [pos, size - len]: 从前向后移动
				for (int i = pos + len; i <= _size; ++i)
				{
					_str[pos++] = _str[i];
				}
				_size -= len;
			}
		}
	}

	size_t find(const char* str)
	{
		char* ptr = strstr(_str, str);
		if (ptr)
			return ptr - _str;
		else
			return npos;
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;
public:
	static const size_t npos;
};

const size_t String::npos = -1;

String operator+(const String& s, const String& str)
{
	String ret(s);
	ret += str.c_str();
	return ret;
}
String operator+(const String& s, const char* str)
{
	String ret(s);
	ret += str;
	return ret;
}
String operator+(const String& s, const char& ch)
{
	String ret(s);
	ret += ch;
	return ret;
}

ostream& operator<<(ostream& cout, const String& str)
{
	//需要输出的字符个数为size， 不能遇到\0就结束输出
	//cout << str.c_str();
	//1. 范围for
	for (const auto& ch : str)
		cout << ch;

	//operator[]
	//for (int i = 0; i < str.size(); ++i)
	//	cout << str[i];

	////迭代器
	//String::const_iterator it = str.begin();
	//while (it != str.end())
	//{
	//	cout << *it;
	//	++it;
	//}

	return cout;
}

void printString(const String& str)
{
	//迭代器遍历
	String::const_iterator it = str.begin();
	while (it != str.end())
	{
		cout << *it << " ";
		//只读迭代器不支持写操作
		//*it = '0';
		++it;
	}
	cout << endl;
}

void test()
{
	String s("01234");
	printString(s);
	s.resize(3, 'a');
	printString(s);
	s.resize(6, 'a');
	printString(s);
}

void test2()
{
	String s("0123456789");
	printString(s);
	s.erase(3, 4);// 012789
	printString(s);
	s.erase(4, 2); // 0127
	printString(s);
	s.erase(2, 100);  //01
	printString(s);
}

void test3()
{
	String s("0123456789");
	size_t pos = s.find("789");
	pos = s.find("0123489");
	if (pos == String::npos)
	{
		cout << "not find" << endl;
	}
}

void test4()
{
	String s("0123");
	cout << s << endl;
	s.resize(10);
	cout << s << "结束" << endl;

	string s1("0123");
	cout << s1 << endl;
	s1.resize(10);
	cout << s1 << "结束" << endl;
}

void test5()
{
	String s("0123");
	String s2("456");
	String s3 = s + s2;
	String s4 = s + "789";
	String s5 = s + 'a';
}

//int main()
//{
//	//test();
//	//test2();
//	//test3();
//	//test4();
//	test5();
//	return 0;
//}