#pragma once

#include <cstdint>
#include <type_traits>



// template <class T, int _Enabled = 0>
// void Swap(T& left, T& right) {
// 	if (left == right) 
//         return;

// 	T tmp = left;
// 	left = right;
// 	right = tmp;
// }

// utility 헤더의 swap 함수 참고
#if _HAS_CXX17
template <class T, std::enable_if_t<std::is_move_constructible_v<T> && std::is_move_assignable_v<T>, int> = 0>
#else // ^^^ _HAS_CXX17 / !_HAS_CXX17 vvv
template <class T, int _Enabled = 0>
#endif // _HAS_CXX17
void Swap(T& left, T& right) noexcept(std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>) {
	if (left == right) 
        return;

	T tmp = std::move(left);
	left = std::move(right);
	right = std::move(tmp);
}

// <xstddef> 헤더에 정의된 구조체를 적당히 긁어옴
template <class T = void>
struct Ascend {
    _NODISCARD constexpr bool operator()(const T& left, const T& right) const {
        return left < right;
    }
};
template <class T = void>
struct Descend {
    _NODISCARD constexpr bool operator()(const T& left, const T& right) const {
        return left > right;
    }
};
// attribute 참고 : http://egloos.zum.com/sweeper/v/3201377
template <>     // template specifier
struct Ascend<void> {
    template <class _Ty1, class _Ty2>
    [[nodiscard]] // 리턴 값을 절대 버리지 않는다. 버리면 경고 출력
    constexpr auto operator()(_Ty1&& _Left, _Ty2&& _Right) const
        noexcept(noexcept(static_cast<_Ty1&&>(_Left) < static_cast<_Ty2&&>(_Right))) // strengthened
        -> decltype(static_cast<_Ty1&&>(_Left) < static_cast<_Ty2&&>(_Right)) {
        return static_cast<_Ty1&&>(_Left) < static_cast<_Ty2&&>(_Right);
    }

    using is_transparent = int;
};
template <>
struct Descend<void> {
    template <class _Ty1, class _Ty2>
    [[nodiscard]] 
    constexpr auto operator()(_Ty1&& _Left, _Ty2&& _Right) const
        noexcept(noexcept(static_cast<_Ty1&&>(_Left) > static_cast<_Ty2&&>(_Right))) // strengthened
        -> decltype(static_cast<_Ty1&&>(_Left) > static_cast<_Ty2&&>(_Right)) {
        return static_cast<_Ty1&&>(_Left) > static_cast<_Ty2&&>(_Right);
    }

    using is_transparent = int;
};


// 정렬된 배열에서 value의 위치를 찾아낸다.
// arr[begin, end] (end < length)
template <typename T, class Func>
uint32_t BinarySearch(T* arr, const T& value, int begin, int end, Func cmp, uint32_t* counter = nullptr) {
	uint32_t count = 0;
    int middle;
    // binary search
    while (begin <= end) {
        ++count;
        middle = (begin + end) / 2;
        if (arr[middle] == value) {
            if (counter)
                *counter += count;
            return middle;
        }
        if (cmp(arr[middle], value))
            begin = middle + 1;
        else 
            end = middle - 1;
        ++count;
    }

    if (counter)
		*counter += count;
	return -1;
}