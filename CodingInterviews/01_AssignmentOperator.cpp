#include<cstring>
#include<cstdio>
#define HIGH

class CMyString
{
public:
	CMyString(char* pData = nullptr);
	CMyString(const CMyString& str);
	~CMyString(void);

	CMyString& operator = (const CMyString& str);

	void Print();

private:
	char* m_pData;
};

CMyString::CMyString(char* pData)
{
	if (pData == nullptr)
	{
		m_pData = new char[1];
		m_pData[0] = '\0';
	}
	else
	{
		int length = strlen(pData);
		m_pData = new char[length + 1];
		strcpy(m_pData, pData);
	}
}

CMyString::CMyString(const CMyString& str)
{
	int length = strlen(str.m_pData);
	m_pData = new char[length + 1];
	strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString()
{
	delete[] m_pData;
}

void CMyString::Print()
{
	printf("%s", m_pData);
}

CMyString& CMyString::operator = (const CMyString& str)
{
#ifndef HIGH
	if (this != &str)
	{
		delete[] m_pData;
		m_pData = nullptr;
		m_pData = new char[strlen(str.m_pData) + 1];	//内存分配失败时返回空指针
		strcpy(m_pData, str.m_pData);
	}

#else
	if (this != &str)
	{
		CMyString strTemp(str);			//内存分配失败时不会修改实例
		char* pTemp = strTemp.m_pData;
		strTemp.m_pData = m_pData;		//自动析构
		m_pData = pTemp;
	}

#endif // !HIGH
	return *this;
}