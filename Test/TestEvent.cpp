#include <list>
#include <unordered_map>
#include <functional>
#include <iostream>

// typedef void (*FuncP0)();
using FuncP0 = std::function<void()>;
enum struct EventType { Hello, Bye };

class EventP0
{
	std::list<FuncP0*> _pFuncs;

public:
	EventP0& operator+=(FuncP0* pFunc)
	{
		_pFuncs.emplace_back(pFunc);
		return *this;
	}

	EventP0& operator-=(FuncP0* pFunc)
	{
		_pFuncs.remove(pFunc);
		return *this;
	}

	void operator()()
	{
		for (auto& pf : _pFuncs)
			(*pf)();
	}

	EventP0() = default;

	~EventP0() = default;
};

class EventMgr
{
	std::unordered_map<EventType, EventP0> _eventMap;

public:
	EventMgr() = default;

	~EventMgr() = default;

	void AddListener(EventType type, FuncP0* pFunc)
	{
		if (_eventMap.find(type) == _eventMap.end())
			_eventMap.emplace(type, EventP0());
		_eventMap[type] += pFunc;
	}

	void RmvListener(EventType type, FuncP0* pFunc)
	{
		if (_eventMap.find(type) != _eventMap.end())
			_eventMap[type] -= pFunc;
	}

	void Invoke(EventType type)
	{
		_eventMap[type]();
	}
};

class Test
{
public:
	Test() = default;

	~Test() = default;

	void Hello()
	{
		std::cout << "Hello, world!\n";
	}

	void Bye()
	{
		std::cout << "Bye, bye!\n";
	}
};


int main(int argc, char const* argv[])
{
	EventMgr mgr;
	Test test;
	FuncP0 func = std::bind(&Test::Hello, test);
	mgr.AddListener(EventType::Hello, &func);
	mgr.Invoke(EventType::Hello);
	mgr.RmvListener(EventType::Hello, &func);
	mgr.Invoke(EventType::Hello);
	return 0;
}
