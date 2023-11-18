#include <iostream>
#include <string>

using namespace std;

namespace app {
	template <typename T> class Test {
		template <typename _T> struct Test2 {
			int i = 222;
			string str = "Test2";

			Test2() = default;

			~Test2() = default;
		};

		friend struct std::hash<Test2<T>>;

	public:
		int i = 111;
		string str = "Test1";
		Test2<T> t2;

		Test() = default;

		~Test() = default;

		size_t get_Hash();
	};

	class Test3 {
		struct Test4 {
			int i = 444;
			string str = "Test4";

			Test4() = default;

			~Test4() = default;
		};

		friend struct std::hash<Test4>;

	public:
		int i = 333;
		string str = "Test3";
		Test4 t4;

		Test3() = default;

		~Test3() = default;

		size_t get_Hash();
	};
} // namespace app

template <typename T> struct std::hash<app::Test<T>> {
	size_t operator()(const app::Test<T>& p) const {
		return std::hash<string>()(p.str) ^ std::hash<int>()(p.i);
	}
};

// template<typename T>
// struct std::hash<typename app::Test<T>::template Test2<T>> {
//     size_t operator()(const typename app::Test<T>::template Test2<T> &p)
//     const {
//         return std::hash<string>()(p.str) ^ std::hash<int>()(p.i);
//     }
// };

template <> struct std::hash<app::Test3> {
	size_t operator()(const app::Test3& p) const {
		return std::hash<string>()(p.str) ^ std::hash<int>()(p.i);
	}
};

template <> struct std::hash<app::Test3::Test4> {
	size_t operator()(const app::Test3::Test4& p) const {
		return std::hash<string>()(p.str) ^ std::hash<int>()(p.i);
	}
};

// template<typename T>
// inline size_t app::Test<T>::get_Hash() {
//     return std::hash<typename app::Test<T>::template Test2<T>>()(t2);
// }

inline size_t app::Test3::get_Hash() { return std::hash<Test3::Test4>()(t4); }

int main(int argc, char const* argv[]) {
	app::Test<int> t;
	cout << "Test:" << hash<app::Test<int>>()(t) << "\n";
	// cout << "Test2:" << t.get_Hash() << "\n";
	app::Test3 t3;
	cout << "Test3:" << hash<app::Test3>()(t3) << "\n";
	cout << "Test4:" << t3.get_Hash() << "\n";
	return 0;
}
