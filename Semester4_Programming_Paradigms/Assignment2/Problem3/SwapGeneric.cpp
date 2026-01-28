#include <iostream>
using std::cout, std::cin, std::endl;

namespace SwapUtility {
	template <typename T>
    void swap(T &a, T &b) {
		T temp = a;
		a = b;
		b = temp;
	}
	struct structure {
		int x; int y;
	};
}

int main() {
	using namespace SwapUtility;

	int a = 10, b = 20;
	float x = 1.1, y = 2.2;
	structure A, B;
	A.x = a;
	A.y = b;

	B.x = x;
	B.y = y;
	
	cout << "Numbers before swapping : " << endl;
	cout << "a=" << a << " " << "b=" << b << endl;
	cout << "x=" << x << " " << "y=" << y << endl;

	cout << "Structures before swapping : " << endl;
	cout << "A.x=" << A.x << " " << "A.y=" << endl;


	swap(a, b);
	swap(x, y);

	cout << "Numbers after swapping : " << endl;
	cout << "a=" << a << " " << "b=" << b << endl;
	cout << "x=" << x << " " << "y=" << y << endl;

	return 0;
}
