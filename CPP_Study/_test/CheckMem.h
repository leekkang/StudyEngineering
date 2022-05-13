#include <iostream>

//#define __FILENAME__ (strrchr(__FILE__,'\\')+1)	// change full path to file name

// 기본 new 연산자 오버로딩
inline void* operator new (size_t size) /*throw(std::bad_alloc)*/ {
	if (size == 0)
		++size;
		
	if (void* ptr = std::malloc(size)) {
		printf_s("%p : new %d byte\n", ptr, (int)size);
		return ptr;
	}
	throw std::bad_alloc{};
}
inline void* operator new[] (size_t size) /*throw(std::bad_alloc)*/ {
	if (size == 0)
		++size;
		
	if (void* ptr = std::malloc(size)) {
		printf_s("%p : new %d byte\n", ptr, (int)size);
		return ptr;
	}
	throw std::bad_alloc{};
}

// 사용자 정의 new 연산자 오버로딩
inline void* operator new (size_t size, const char* file, const int line) /*throw(std::bad_alloc)*/ {
	if (size == 0)
		++size;
		
	if (void* ptr = std::malloc(size)) {
		const char* filename = strrchr(__FILE__, '\\') + 1;
		printf_s("%p : new %d byte, line %d, filename %s\n", ptr, (int)size, line, filename);
		return ptr;
	}
	throw std::bad_alloc{};
}
inline void* operator new[] (size_t size, const char* file, const int line) /*throw(std::bad_alloc)*/ {
	if (size == 0)
		++size;
		
	if (void* ptr = std::malloc(size)) {
		const char* filename = strrchr(__FILE__, '\\') + 1;
		printf_s("%p : new %d byte, line %d, filename %s\n", ptr, (int)size, line, filename);
		return ptr;
	}
	throw std::bad_alloc{};
}
inline void operator delete(void* ptr) noexcept {
	printf_s("%p : delete %d byte\n", ptr, (int)_msize(ptr));
	//std::cout << ptr << " : delete " << _msize(ptr) << " byte" << std::endl;
	std::free(ptr);
}
inline void operator delete[](void* ptr) noexcept {
	printf_s("%p : delete %d byte\n", ptr, (int)_msize(ptr));
	//std::cout << ptr << " : delete " << _msize(ptr) << " byte" << std::endl;
	std::free(ptr);
}
#undef user_new
#define user_new new(__FILE__, __LINE__)
#undef new
#define new user_new