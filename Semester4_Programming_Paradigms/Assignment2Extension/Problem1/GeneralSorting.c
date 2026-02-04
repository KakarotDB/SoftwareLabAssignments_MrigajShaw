#include <iostream> 
using std::cout, std::cin, std::endl;

namespace GeneralSorting {
	template <typename T>
		void GenericInsertionSort(T *a, const int n) {
   	 		if (a == NULL)
    	    	return;
			T key;
    		int i, j;
    		for (i = 1; i < n; i++) {
        		key = a[i];
        		j = i - 1;
        		while (j >= 0 && a[j] > key) {
            		a[j + 1] = a[j];
            		j--;
        		}
        	a[j + 1] = key;
    		}
		}
	template <typename T>
		void printArray(const T *a, int n) {
			for(int i = 0; i < n; i++) cout << a[i] << " ";
			cout << endl;
		}
}

struct example {
	int a; 
	int b;
};
int main() {
	using namespace GeneralSorting;
	int n = 0;
	cout << "Enter the value of n : ";
	cin >> n;
	int *intArray = new int[n];
	short *shortArray = new short[n];
	float *floatArray = new float[n];
	double *doubleArray = new double[n];
	char *charArray = new char[n];
	example *structArray = new example[n];

	cout << "Enter n integers : ";
	for(int i = 0; i < n; i++) cin >> intArray[i];
	
	cout << "Enter n short integers: ";
	for(int i = 0; i < n; i++) cin >> shortArray[i];

	cout << "Enter n float values: ";
	for(int i = 0; i < n; i++) cin >> floatArray[i];

	cout << "Enter n double values: ";
	for(int i = 0; i < n; i++) cin >> doubleArray[i];

	cout << "Enter n char values: ";
	for(int i = 0; i < n; i++) cin >> charArray[i];

//	cout << "Enter two integers for each struct in the struct array : ";
//	for(int i = 0; i < n; i++) cin >> structArray[i].a >> structArray[i].b;
//	This doesn't work as structure has no compare function with "<" or ">"
//	Thus it gives a compilation error (Trying to sort the structure)

	cout << endl;
	cout << "Arrays before Sorting : " << endl;
	cout << "IntArray = "; printArray(intArray, n);
	cout << "FloatArray = "; printArray(floatArray, n);
	cout << "DoubleArray = "; printArray(doubleArray, n);
	cout << "CharArray = "; printArray(charArray, n);

	GenericInsertionSort(intArray, n);
	GenericInsertionSort(floatArray, n);
	GenericInsertionSort(doubleArray, n);
	GenericInsertionSort(charArray, n);

	cout << "Arrays after Sorting : " << endl;
	cout << "IntArray = "; printArray(intArray, n);
	cout << "FloatArray = "; printArray(floatArray, n);
	cout << "DoubleArray = "; printArray(doubleArray, n);
	cout << "CharArray = "; printArray(charArray, n);

	return 0;
}

