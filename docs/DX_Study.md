

## DX Study

  - 몰랐거나 까먹기 쉬운 DX 정보를 기록해놓는 문서

  - 공식 문서 참고

---
# 용어 정리

  - 참고 
    - [Basic Concept of C++ Language](https://en.cppreference.com/w/cpp/language/basic_concepts) 


---
# Culling

 - ### BackFace Culling



---
# SIMD 레지스터, SSE2 연산

  - DX가 연산할 때 사용하는 레지스터와 연산법
  
  - 16byte 연산을 한번에 처리한다. -> 엄청 빠르다!


---
# HLSL

  - HLSL은 행렬 순서가 `column-major (열우선)` 이다.
  - `DirectX`는 `row-major (행우선)` 방식의 행렬을 사용한다.
    - 보통 수학시간에 배우는 `요소를 가로로 놓는 행렬`이 이것이다.
    - 행우선 방식을 사용하여 점과 행렬의 곱셈을 하는 것을 `left-hand multiplication (좌측 곱 변환)` 또는 `pre-multiplication` 이라고 한다.
    $$

    $$
  - 그렇기 때문에, cpp코드에서 `행벡터 x 행렬` 의 순서로 사용하는 행렬과 동일한 결과값을 내려면 쉐이더 코드에서 `행렬 x 열벡터`로 표현해야 한다.
  - DX는 `Input Assembler Stage`에서 값을 출력할 때 열우선 방식으로 데이터를 변경하여 HLSL에 전달한다.
    - 행렬곱을 할 때 `mul(행렬, 좌표)`식을 사용해야 한다.
  - 쉐이더에서 `mul(좌표, 행렬)` 순서의 식을 사용하려면, 버퍼에 값을 추가할 때 `transpose`해서 저장하면 된다.

---
# Instancing

  - `드로우 콜(draw call)`의 횟수를 줄여서 성능을 향상시키는 방법


서피스(Surface) - 실질적인 픽셀 정보를 가지고 있는 객체
2d용 렌더타겟을 출력하는 백버퍼를 3d 백버퍼로 지정해서 같이 그려낸다. - 원래는 따로따로 버퍼를 만들어서 그렸다

렌더 타겟 타입은 하드웨어, 픽셀 포맷은 고정값

서피스는 내부적으로 레퍼런스 카운트를 가지고 있기 때문에 렌더타겟을 생성하고난 후에는 무조건 릴리즈 해줘야 한다.

dwrite로 폰트를 사용하려면 iDWriteFactory를 만들어

입력 시스템 IME(Input Method Editor)
  - https://learn.microsoft.com/ko-kr/windows/win32/dxtecharts/using-an-input-method-editor-in-a-game