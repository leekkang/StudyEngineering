
## API Study

  - Windows API 관련 정보


---
# Document Link

  - ## [CPP Study](CPP_Study.md)


---
# CreateDIBSection func 사용법

```cpp

	mHPostDC = CreateCompatibleDC(mHDC);
	BITMAPINFO  mBmpInfo{};
	mBmpInfo.bmiHeader.biSize = sizeof(mBmpInfo.bmiHeader);
	mBmpInfo.bmiHeader.biWidth = mRS.width;
	mBmpInfo.bmiHeader.biHeight = mRS.height;
	mBmpInfo.bmiHeader.biPlanes = 1;
	mBmpInfo.bmiHeader.biBitCount = 24; // 이미지 사이즈 공식 : Floor((biBitCount * imageWidth + 31) / 32) * 4;
	mBmpInfo.bmiHeader.biCompression = BI_RGB;

	mHPostBmp = CreateDIBSection(mHPostDC, (BITMAPINFO*)&mBmpInfo, DIB_RGB_COLORS, (LPVOID*)&mPostBits, NULL, NULL);
	mHPostPrevBmp = (HBITMAP)SelectObject(mHPostDC, mHPostBmp);
```


---
# API Bitmap Blur func

  - 비트맵 블러 효과 적용
    - https://stackoverflow.com/questions/47209262/c-blur-effect-on-bit-map-is-working-but-colors-are-changed
    - 가우시안 블러 알고리즘 : https://blog.ivank.net/fastest-gaussian-blur.html

  - mHBackBmp는 `CreateCompatibleBitmap` 함수로 만든 `HBITMAP` 이다.

```cpp
	auto blur = [&](int radius) -> bool{
		BITMAPINFO info{0};
		info.bmiHeader.biSize = sizeof(info.bmiHeader);

		if (0 == GetDIBits(mHBackDC, mHBackBmp, 0, 0, nullptr, &info, DIB_RGB_COLORS)) {
			return false;
		}
		char* bits = new char[info.bmiHeader.biSizeImage];

		info.bmiHeader.biCompression = BI_RGB;

		if (0 == GetDIBits(mHBackDC, mHBackBmp, 0, info.bmiHeader.biHeight, bits, &info, DIB_RGB_COLORS)) {
			return false;
		}

		int w = info.bmiHeader.biWidth;
		int h = info.bmiHeader.biHeight;
		float rs = ceil(radius * 2.57);
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				double r = 0, g = 0, b = 0;
				double count = 0;

				for (int iy = i - rs; iy < i + rs + 1; ++iy) {
					for (int ix = j - rs; ix < j + rs + 1; ++ix) {
						auto x = min(static_cast<int>(w) - 1, max(0, ix));
						auto y = min(static_cast<int>(h) - 1, max(0, iy));

						auto dsq = ((ix - j) * (ix - j)) + ((iy - i) * (iy - i));
						auto wght = std::exp(-dsq / (2.0 * radius * radius)) / (3.14 * 2.0 * radius * radius);

						rgb32* temp = reinterpret_cast<rgb32*>(bits);
						rgb32* pixel = &temp[(h - 1 - y) * w + x];

						r += pixel->r * wght;
						g += pixel->g * wght;
						b += pixel->b * wght;
						count += wght;
					}
				}

				rgb32* temp = reinterpret_cast<rgb32*>(bits);
				rgb32* pixel = &temp[(h - 1 - i) * w + j];
				pixel->r = std::round(r / count);
				pixel->g = std::round(g / count);
				pixel->b = std::round(b / count);
			}
		}

		if (0 == SetDIBits(mHBackDC, mHBackBmp, 0, info.bmiHeader.biHeight, bits, &info, DIB_RGB_COLORS))
			return false;
		return true;
	};
```