

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
 - TODO



---
# SIMD(Single Instruction Multiple Data) 레지스터, SSE2 연산

  - DX가 연산할 때 사용하는 레지스터와 연산법
  
  - 16byte 연산을 한번에 처리한다. -> 엄청 빠르다!
  - TODO


---
# HLSL mul

  - `DirectX`는 `row-major (행우선)` 방식의 행렬을 사용한다.
    - 보통 수학시간에 배우는 `요소를 가로로 놓는 행렬`이 이것이다.
    - 행우선 방식을 사용하여 점과 행렬의 곱셈을 하는 것을 `left-hand multiplication (좌측 곱 변환)` 또는 `pre-multiplication` 이라고 한다.
    $$

    $$
  - 그렇기 때문에, cpp코드에서 `행벡터 x 행렬` 의 순서로 사용하는 행렬과 동일한 결과값을 내려면 쉐이더 코드에서 `행렬 x 열벡터`로 표현해야 한다.
  - DX는 `Input Assembler Stage`에서 값을 출력할 때 **열우선 방식으로 데이터를 변경**하여 쉐이더 상수에 저장한다. (패킹)
    - 메모리의 `Spatial Locality` 때문인가?
    - 과거의 잔재를 처리하지 못해서 그냥 놔둔 것일 수도 있음.
    - HLSL은 컴파일 결과물의 디폴트가 `열우선` 이기 때문에 메모리 지역성을 위해 바꾸는 것일 수도 있다. 자세히 찾아보자.
  - 쉐이더의 `mul()` 함수는 들어오는 매개변수에 따라 행렬곱을 다르게 처리한다.
    - `mul(벡터, 행렬)` 의 경우 `row-major (행우선)`
    - `mul(행렬, 벡터)` 의 경우 `column-major (열우선)`
    - https://learn.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-mul

  - $\therefore$ 쉐이더에서 `mul(좌표, 행렬)` 순서의 식을 사용하려면, 버퍼에 값을 추가할 때 `Transpose`해서 저장하면 된다.
  - 주의 : 쉐이더 내에서 생성한 행렬을 곱하는 경우 전치할 필요가 없다.
 
  - 참고
    - http://dolphin.ivyro.net/file/hlsl/tutorial06.html
    - https://www.gpgstudy.com/forum/viewtopic.php?p=108628
    - https://learn.microsoft.com/en-us/windows/win32/direct3d9/casting-and-conversion

---
# Instancing

  - `드로우 콜(draw call)`의 횟수를 줄여서 성능을 향상시키는 방법
  - TODO

---
# Surface

  - 실질적인 픽셀 정보를 가지고 있는 객체
  - 2d용 렌더타겟을 출력하는 백버퍼를 3d 백버퍼로 지정해서 같이 그려낸다. - 원래는 따로따로 버퍼를 만들어서 그렸다

렌더 타겟 타입은 하드웨어, 픽셀 포맷은 고정값

서피스는 내부적으로 레퍼런스 카운트를 가지고 있기 때문에 렌더타겟을 생성하고난 후에는 무조건 릴리즈 해줘야 한다.

dwrite로 폰트를 사용하려면 iDWriteFactory를 만들어야 한다.

입력 시스템 IME(Input Method Editor)
  - https://learn.microsoft.com/ko-kr/windows/win32/dxtecharts/using-an-input-method-editor-in-a-game



---
# Immediate Context, Deferred Context

  - 멀티 스레드 대응을 위해 `동일한 타입`의 컨텍스트를 두 가지 방법으로 사용한다.
  - `Immediate Context`
  - `Deferred Context`
  - https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=masca140&logNo=220719096462



---
# [FBX](https://help.autodesk.com/view/FBX/2016/ENU/?guid=__files_GUID_4F644045_380D_4B75_A2A3_D39DDE53BEDD_htm)

  - FBX SDK -> Manager, Scene 두 가지 기능으로 나뉜다.
  - FBX Manager
    - `.fbx`파일을 불러올 수 있는 `Importer`, `FBX Scene` 들을 생성할 수 있다.
    - `FBX Scene`이 가지고 있는 모든 노드, 메쉬 또는 기타 FBX 객체에 대한 메모리 할당을 담당한다.
  - ### FBX Scene
    - Scene Graph System : 정보들(fbx node)을 트리구조로 가지고 있음.
    - Importer를 통해 .fbx파일을 읽으면(Import()) 노드들로 채워진다.
    - dx 좌표계와 autodesk sdk가 사용하는 좌표계가 다르기 때문에 조정이 필요하다. (컨버터 함수가 있지만 동작하지 않는다.)
    - `3dsMax` 좌표계는 $x$ 가 오른쪽, $y$ 가 앞쪽, $z$ 가 위쪽이다. (오른손 좌표계) 
    - DX좌표계는 $x$ 가 오른쪽, $y$ 가 위쪽, $z$ 가 앞쪽이다. (왼손 좌표계)
    - 
