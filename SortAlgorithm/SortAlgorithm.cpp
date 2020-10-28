#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T> // template<class T> 와 동일
void Swap(T& left, T& right) {

}

template<typename T> // template<class T> 와 동일
void SortBubble(T* arr) {
}

int main() {
	vector<string> msg{"Hello", "C++"};

	cout << msg[0] << msg[1] << endl;
	auto it = msg.begin();
	vector<string> msg2(10);
	vector<string> msg3{10};
	cout << msg.capacity() << endl;
	cout << msg2.capacity() << endl;
	cout << msg3.capacity() << endl;
	
	string* data = msg.data();
	string tmp = data[0];
	data[0] = data[1];
	data[1] = tmp;
	cout << msg[0] << msg[1] << endl;
	cout << *it << endl;

	for (const string& word : msg) {
		cout << word << " ";
	}
}