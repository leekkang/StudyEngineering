#pragma once

#include <locale>

namespace StringUtility {
	constexpr auto TRIM_SPACE = " \t\n\r";
	//#define TRIM_SPACE " \t\n\r"

	//template<typename Out>
	//constexpr void Split(const std::string& s, char delim, Out result) {
	//	std::stringstream ss(s);
	//	std::string item;

	//	while (getline(ss, item, delim))
	//		*(result++) = item;
	//}
	//inline std::vector<std::string> Split(const std::string& s, const char delim) {
	//	std::vector<std::string> elems;
	//	Split(s, delim, back_inserter(elems));

	//	return elems;
	//}

#if _HAS_CXX17
	template<typename Type, std::enable_if_t<std::is_class_v<Type>, bool> = true>
#else
	template<typename Type, typename std::enable_if<std::is_class<Type>::value, bool>::type = true>
#endif // _HAS_CXX17
	inline std::string GetClassTypeName() {
		std::string name = typeid(Type).name();
		size_t spacePosition = name.find_first_of(" ");
		if (spacePosition != std::string::npos) {
			return name.substr(spacePosition + 1, name.length());
		}
		return name; // mostly primitive types
	}

	inline std::string GetFilename(const std::string& path) {
		//size_t found = path.find_last_of("/\\");
		for (int i = (int)path.length() - 1; i >= 0; --i) {
			if (path[i] == '/' || path[i] == '\\') {
				return std::string(path.begin() + i + 1, path.end());
			}
		}
		return std::string();
	}

	inline std::string GetDirectory(const std::string& path) {
		size_t found = path.find_last_of("/\\");
		if (found != std::string::npos) {
			return path.substr(0, found);
		}
		return std::string();
	}

	inline std::string Trim(std::string& s, const std::string& drop = TRIM_SPACE) {
		std::string r = s.erase(s.find_last_not_of(drop) + 1);
		return r.erase(0, r.find_first_not_of(drop));
	}
	inline std::string RTrim(std::string& s, const std::string& drop = TRIM_SPACE) {
		return s.erase(s.find_last_not_of(drop) + 1);
	}
	inline std::string LTrim(std::string& s, const std::string& drop = TRIM_SPACE) {
		return s.erase(0, s.find_first_not_of(drop));
	}

	/// <summary> convert ANSI to Unicode </summary>
	inline std::wstring LocalToWide(const std::string& s) {
		// cbMultiByte 인자가 -1인 경우, null문자를 포함한 전체 입력 문자열을 처리한다.
		// cchWideChar 인자가 0인 경우, null문자를 포함한 필요한 버퍼의 크기를 반환한다. lpWideCharStr는 사용하지 않는다.
		int len = MultiByteToWideChar(CP_ACP, 0, s.data(), -1, nullptr, 0);
		std::wstring result(len, 0);
		MultiByteToWideChar(CP_ACP, 0, s.data(), -1, &result[0], len);

		return result;
	}

	/// <summary> convert Unicode to ANSI </summary>
	inline std::string WideToLocal(const std::wstring& s) {
		// cchWideChar 인자가 -1인 경우, null문자를 포함한 전체 입력 문자열을 처리한다.
		// cbMultiByte 인자가 0인 경우, null문자를 포함한 필요한 버퍼의 크기를 반환한다. lpMultiByteStr는 사용하지 않는다.
		int len = WideCharToMultiByte(CP_ACP, 0, s.data(), -1, nullptr, 0, nullptr, nullptr);
		std::string result(len, 0);
		WideCharToMultiByte(CP_ACP, 0, s.data(), -1, &result[0], len, nullptr, nullptr);

		return result;
	}

	/// <summary> convert Unicode to UTF-8 </summary>
	inline std::string WideToUTF8(const std::wstring& s) {
		// cchWideChar 인자가 -1인 경우, null문자를 포함한 전체 입력 문자열을 처리한다.
		// cbMultiByte 인자가 0인 경우, null문자를 포함한 필요한 버퍼의 크기를 반환한다. lpMultiByteStr는 사용하지 않는다.
		int len = WideCharToMultiByte(CP_UTF8, 0, s.data(), -1, nullptr, 0, nullptr, nullptr);
		std::string result(len, 0);
		WideCharToMultiByte(CP_UTF8, 0, s.data(), -1, &result[0], len, nullptr, nullptr);

		return result;
	}

	/// <summary> convert UTF-8 to Unicode </summary>
	inline std::wstring UTF8ToWide(const std::string& s) {
		// cbMultiByte 인자가 -1인 경우, null문자를 포함한 전체 입력 문자열을 처리한다.
		// cchWideChar 인자가 0인 경우, null문자를 포함한 필요한 버퍼의 크기를 반환한다. lpWideCharStr는 사용하지 않는다.
		int len = MultiByteToWideChar(CP_UTF8, 0, s.data(), -1, nullptr, 0);
		std::wstring result(len, 0);
		MultiByteToWideChar(CP_UTF8, 0, s.data(), -1, &result[0], len);

		return result;
	}

	/// <summary> convert Multibyte(ANSI) to UTF-8 </summary>
	inline std::string LocalToUTF8(const std::string& s) {
		std::string result;

		int len = MultiByteToWideChar(CP_ACP, 0, s.data(), -1, nullptr, 0);
		if (len <= 0)
			return result;

		wchar_t* uni = new wchar_t[(size_t)len];
		// ansi ---> unicode
		MultiByteToWideChar(CP_ACP, 0, s.data(), -1, uni, len);

		len = WideCharToMultiByte(CP_UTF8, 0, uni, -1, nullptr, 0, nullptr, nullptr);
		if (len <= 0) {
			delete[] uni;
			return result;
		}

		// unicode ---> utf8
		char* utf = new char[(size_t)len];
		WideCharToMultiByte(CP_UTF8, 0, uni, -1, utf, len, nullptr, nullptr);
		result = utf;

		delete[] uni;
		delete[] utf;

		return result;
	}

	/// <summary> convert UTF-8 to Multibyte(ANSI) </summary>
	inline std::string UTF8ToLocal(const std::string& s) {
		std::string result;

		int len = MultiByteToWideChar(CP_UTF8, 0, s.data(), -1, nullptr, 0);
		if (len <= 0)
			return result;

		wchar_t* uni = new wchar_t[(size_t)len];
		// utf8 --> unicode
		MultiByteToWideChar(CP_UTF8, 0, s.data(), -1, uni, len);

		len = WideCharToMultiByte(CP_ACP, 0, uni, -1, nullptr, 0, nullptr, nullptr);
		if (len <= 0) {
			delete[] uni;
			return result;
		}

		// unicode --> ansi
		char* ansi = new char[(size_t)len];
		WideCharToMultiByte(CP_ACP, 0, uni, -1, ansi, len, nullptr, nullptr);
		result = ansi;

		delete[] uni;
		delete[] ansi;

		return result;
	}

	typedef std::codecvt<wchar_t, char, mbstate_t> cvt_facet;

	// reference : https://www.codeproject.com/Tips/197097/Converting-ANSI-to-Unicode-and-back-2
	/// <summary> convert ANSI to Unicode </summary>
	inline std::wstring LocalToWide(const std::string& s, const std::locale& loc) {
		uint16_t bufSize = static_cast<uint16_t>(s.length());
		if (bufSize == 0) {
			return std::wstring();
		}

		const cvt_facet& facet = std::use_facet<cvt_facet>(loc);
		mbstate_t state { };

		wchar_t* buf = new wchar_t[bufSize];
		const char* ipc = &s[0];
		wchar_t* opc = 0;
		cvt_facet::result result = facet.in(state, ipc, ipc + bufSize, ipc, buf, buf + bufSize, opc);

		if (result != cvt_facet::ok) {
			delete[] buf;
			return std::wstring();
		}

		std::wstring ws(buf, opc - buf);
		delete[] buf;

		return ws;
	}
	/// <summary> convert Unicode to ANSI </summary>
	inline std::string WideToLocal(const std::wstring& ws, const std::locale& loc) {
		uint16_t bufSize = static_cast<uint16_t>(ws.length() * 2);
		if (bufSize == 0) {
			return std::string();
		}

		const cvt_facet& facet = std::use_facet<cvt_facet>(loc);
		mbstate_t state { };

		char* buf = new char[bufSize];
		const wchar_t* ipc = &ws[0];
		char* opc = 0;
		cvt_facet::result result = facet.out(state, ipc, ipc + ws.length(), ipc, buf, buf + bufSize, opc);

		if (result != cvt_facet::ok) {
			delete[] buf;
			return std::string();
		}

		std::string s(buf, opc - buf);
		delete[] buf;

		return s;
	}
	/// <summary> convert Multibyte(ANSI) to UTF-8 </summary>
	inline std::string LocalToUTF8(const std::string& s, const std::locale& loc) {
		std::wstring ws = LocalToWide(s, loc);
		return ws.size() == 0 ? std::string() : WideToUTF8(ws);
	}
	/// <summary> convert UTF-8 to Multibyte(ANSI) </summary>
	inline std::string UTF8ToLocal(const std::string& s, const std::locale& loc) {
		return WideToLocal(UTF8ToWide(s), loc);
	}

	// reference : https://stackoverflow.com/questions/28270310/how-to-easily-detect-utf8-encoding-in-the-string
	/// <summary> check if it is UTF-8 string </summary>
	inline bool IsValidUTF8(const char* str) {
		if (!str) return true;

		const unsigned char* bytes = (const unsigned char*)str;
		uint32_t cp;
		uint8_t num;

		while (*bytes != 0x00) {
			if ((*bytes & 0x80) == 0x00) {
				// U+0000 to U+007F 
				cp = (*bytes & 0x7F);
				num = 1;
			} else if ((*bytes & 0xE0) == 0xC0) {
				// U+0080 to U+07FF 
				cp = (*bytes & 0x1F);
				num = 2;
			} else if ((*bytes & 0xF0) == 0xE0) {
				// U+0800 to U+FFFF 
				cp = (*bytes & 0x0F);
				num = 3;
			} else if ((*bytes & 0xF8) == 0xF0) {
				// U+10000 to U+10FFFF 
				cp = (*bytes & 0x07);
				num = 4;
			} else
				return false;

			bytes += 1;
			for (uint8_t i = 1; i < num; ++i) {
				if ((*bytes & 0xC0) != 0x80)
					return false;
				cp = (cp << 6) | (*bytes & 0x3F);
				bytes += 1;
			}

			if ((cp > 0x10FFFF) ||
				((cp >= 0xD800) && (cp <= 0xDFFF)) ||
				((cp <= 0x007F) && (num != 1)) ||
				((cp >= 0x0080) && (cp <= 0x07FF) && (num != 2)) ||
				((cp >= 0x0800) && (cp <= 0xFFFF) && (num != 3)) ||
				((cp >= 0x10000) && (cp <= 0x1FFFFF) && (num != 4)))
				return false;
		}

		return true;
	}


	// For convenience, frequently defined locales are statically registered. Decide whether or not to eliminate it later
	//static std::locale sKorLoc("Korean");
	//static std::locale sJpnLoc("Japanese");
}