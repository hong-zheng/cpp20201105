#include <string>
#include <iostream>
using namespace std;

class String
{
public:

	//��������һ�ַ�������Ԫ�صĻ��ƣ� ���ַ�װ�����ԣ�
	//����Ҫ��ע������ʵ��ϸ�ڣ��Ϳ���ֱ�ӷ���(�ɶ���д)Ԫ��
	//ʹ�÷�ʽ�� ������ָ��Ĳ���
	//     1. ������--> ��ȡָ��λ�õ�����
	//     2. λ���ƶ� --> ִ������λ��

	//string �������� ͨ��ָ��ʵ��
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin()
	{
		//��һ��Ԫ�ص�λ��
		return _str;
	}

	iterator end()
	{
		//���һ��Ԫ�ص���һ��λ��
		return _str + _size;
	}

	const_iterator begin() const
	{
		//��һ��Ԫ�ص�λ��
		return _str;
	}

	const_iterator end() const
	{
		//���һ��Ԫ�ص���һ��λ��
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
	//	//�������Դ����
	//	strcpy(_str, str._str);
	//	cout << "String(const String&)" << endl;
	//}

	//�������죺�ִ�д��, ���븴��
	String(const String& str)
		:_str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		//���ù��캯��
		String tmp(str._str);
		Swap(tmp);
	}

	void Swap(String& str)
	{
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}

	//��������� Ч�ʵ�
	//void Swap(String& str)
	//{
	//	//��������
	//	String tmp = str;
	//	//��ֵ�����
	//	str = *this;
	//	//��ֵ�����
	//	*this = tmp;
	//}

	//String& operator=(const String& str)
	//{
	//	if (this != &str)
	//	{
	//		//���ռ�
	//		char* tmp = new char[str._capacity + 1];

	//		//���ݿ���
	//		strcpy(tmp, str._str);

	//		//�ͷ�ԭ�пռ�
	//		delete[] _str;

	//		_str = tmp;
	//		_size = str._size;
	//		_capacity = str._capacity;
	//	}
	//	return *this;
	//}
	//��ֵ������� �ִ�д���� ���븴�ã� ��������(���ν��п�������)
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
		//�������
		//if (_size == _capacity)
		//{
		//	size_t newC = _capacity == 0 ? 1 : 2 * _capacity;
		//	reserve(newC);
		//}
		////β��
		//_str[_size] = ch;
		////����size
		//++_size;
		//_str[_size] = '\0';
		insert(_size, ch);
	}

	void reserve(size_t n)
	{
		if (n > _capacity)
		{
			//���ռ�:+1--->���\0
			char* tmp = new char[n + 1];
			//����
			strcpy(tmp, _str);
			//�ͷ�ԭ�пռ�
			delete[] _str;

			_str = tmp;
			//��������
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
		////�������
		//if (_size + len > _capacity)
		//{
		//	reserve(_size + len);
		//}
		////β��
		//strcpy(_str + _size, str);

		////�޸�size
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

		//�������
		if (_size == _capacity)
		{
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}
		//�ƶ�Ԫ��[pos, _size]�� �Ӻ���ǰ�ƶ�,�����ƶ����Ҷ˵��ַ�����ֹ����
		size_t end = _size + 1;
		//end >= pos: ��pos = 0ʱ�� ��ѭ��������Խ��
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}
		//����
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
		//�ƶ�Ԫ��[pos, _size]
		size_t end = _size + len;
		//size --> size + len,  pos ---> pos + len
		while (end > pos + len - 1)
		{
			_str[end] = _str[end - len];
			--end;
		}
		//����
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
			//�ж�ɾ���ĳ����Ƿ���ڴ�posλ�ÿ�ʼ��ʣ���ַ����ĳ���
			if (pos + len >= _size)
			{
				_size = pos;
				_str[_size] = '\0';
			}
			else
			{
				//�ƶ�Ԫ��[pos + len, size]  ---> [pos, size - len]: ��ǰ����ƶ�
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
	//��Ҫ������ַ�����Ϊsize�� ��������\0�ͽ������
	//cout << str.c_str();
	//1. ��Χfor
	for (const auto& ch : str)
		cout << ch;

	//operator[]
	//for (int i = 0; i < str.size(); ++i)
	//	cout << str[i];

	////������
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
	//����������
	String::const_iterator it = str.begin();
	while (it != str.end())
	{
		cout << *it << " ";
		//ֻ����������֧��д����
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
	cout << s << "����" << endl;

	string s1("0123");
	cout << s1 << endl;
	s1.resize(10);
	cout << s1 << "����" << endl;
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