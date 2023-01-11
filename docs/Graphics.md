- [Document Link](#document-link)
- [Rendering Pipeline](#rendering-pipeline)
- [World, View, Projection Transformation](#world-view-projection-transformation)
- [Class Default Object](#class-default-object)
- [Deferred Rendering](#deferred-rendering)
- [Light](#light)
  - [Tone Mapping](#tone-mapping)
  - [Gamma Correction](#gamma-correction)

---


## Graphics

  - 그래픽스 관련 정보들을 저장해놓는 문서




- 참고
  - 알파 블렌딩
    - https://showmiso.tistory.com/139 
  - 비트맵 관련
    - https://blog.naver.com/tipsware/220996998423




---
# Document Link

  - ## [CPP Study](CPP_Study.md)


---
# Rendering Pipeline

  - TODO
  - [Unity 3D Rendering Pipeline](unity3d_rendering_pipeline.md)


---
# World, View, Projection Transformation

  - https://stackoverflow.com/questions/28075743/how-do-i-compose-a-rotation-matrix-with-human-readable-angles-from-scratch/28084380#28084380
  - https://nickchooshin.tistory.com/7

  - ### 좌표계 A의 한 점을 좌표계 B로 변환할 때, 두 가지 방법으로 변환행렬을 만들 수 있다.
    - `좌표계 B로 표현한 좌표계 A의 기저벡터` 로 만든 행렬
      - ex: `뷰 좌표계`로 변경된 `탄젠트 좌표계`의 `기저벡터`들로 만든 행렬은 노말 텍스쳐의 값을 `뷰 좌표계`의 `노말 벡터`로 변환한다.
    - `좌표계 A로 표현한 좌표계 B의 기저벡터` 로 만든 행렬의 역행렬
      - 위치 변환 행렬의 역행렬 * 회전, 크기변환 행렬의 역행렬
      - ex: `월드 좌표계`의 카메라 위치, 회전축 벡터로 만든 행렬의 `역행렬`으로 `월드 좌표계`의 물체를 `뷰 좌표계`로 변환한다.
    - [자세한 내용: 좌표계 변환](Transformation/transformations.md#좌표계의-변환)
  - 어떤 물체의 `월드 변환 행렬`은 기준 좌표계가 이미 월드이기 때문에 현재 물체의 요소를 그대로 사용하게 된다.
    - 메쉬의 꼭짓점들이 대상이 되며, 모두 `0,0,0`을 기준점으로 가지도록 설계한다.
    - `DirectX::XMMatrixScaling`, `DirectX::XMQuaternionRotationRollPitchYaw`, `DirectX::XMMatrixTranslation`
    - 결과로 나오는 행렬을 보면 전치 없이 그대로 값을 사용한 것을 볼 수 있다.
      - **각도만큼 회전, 좌표만큼 이동**
  - 어떤 물체의 `뷰 변환 행렬`은 좌표계가 `뷰 공간`으로 변경되기 때문에 좌표축의 변환이 발생한다.
    - `월드 좌표로 표현한 뷰 공간`의 기저 벡터를 행렬로 표현할 수 있는데(보통 카메라의 월드 좌표축이 대상이 된다.) `변환 행렬`과 곱했을 때 `항등 행렬`이 나온다.
    - `월드 좌표축` * `뷰 변환 행렬` = `항등 행렬`
    - 이동 변환의 경우, `-현재 월드 좌표와 해당 요소 회전축의 내적`을 변환식에 추가하면 된다.
  - 어떤 물체의 `투영 변환 행렬`은 이 물체를 출력할 모니터 좌표계로 변환한다.

  - TODO


---
# Class Default Object

  - TODO


---
# Deferred Rendering

  - 물체를 그린 후 라이트를 따로 그리는 렌더링 방식
  - 기존 렌더링(Forward Rendering)은 물체를 그릴 대 조명 처리를 한다. (물체 수 * 조명 수)
  - 포워드 렌더링의 연산 수를 줄이기 위해 물체를 그린 후 조명 처리를 한다. (물체 수 + 조명 수)
  - 베이스 물체를 출력하는 렌더링 타겟을 `알베도 타겟` 이라고 한다.
  - 렌더 타겟은 최대 8개 만들어 낼 수 있다. (DX9 는 4개) -> 멀티 렌더 타겟(MRT)
  - `알베도 타겟`, `노말 타겟`, `뎁스 타겟`들을 `G버퍼` 라고 한다. (기하 정보 버퍼)
  - 알파값을 가지는 물체는 조명 처리가 끝난 후 따로 그려준다.


---
# Light

  - TODO
  - [basic_light](basic_light/basic_light.md)
 
  - ### BRDF (Bidirectional Reflection Distribution Function, 양방향 반사 분포 함수)
    - 표면이 반사하는 빛의 양을 평가하는 데 쓰이는 함수 (수학 공식)
    - 일반적으로 빛의 속성과 표면의 재질 속성, 시점 또는 카메라의 위치를 포함한 여러 개의 입력 매개변수들을 사용한다.
    - `블린-퐁(Blinn-Phong)` 모델의 BDRF를 기본값으로 자주 사용한다.

## Tone Mapping

  - 이미지의 전체 밝기와 대비(contrast)를 조정하고 출력 장치에 맞게 이미지의 색상 범위를 줄이는 데 사용되는 기술
  - `HDR`을 사용할 때 반드시 필요하다.
  - ### Reinhard's Operator (라인하르트의 연산자)
    - 가장 간단하고 널리 쓰이는 연산자이다.
    - [자세한 내용은 여기서 참고](https://expf.wordpress.com/2010/05/04/reinhards_tone_mapping_operator/)

  $$
L(x,y) = L_w * ( (L(x,y)\ /\ L_w)\ /\ (1 + L(x,y)\ /\ L_w) )
  $$


## Gamma Correction

  - ### Gamma : 픽셀의 숫자 값과 실제 광도 사이의 관계를 정의한다. 실제 계산식에서 지수로 사용됨.
    - 광자 수가 두 배로 늘어나면 카메라의 센서에 두 배의 신호가 수신된다. (선형 관계)
    - 우리 눈은 광자 수가 두 배로 늘어나면 **그보다 훨씬 더 밝다고 인식한다.** (비선형 관계) 밝기가 올라갈수록 그 차이는 점점 줄어든다.
    - 결론적으로, **우리 눈은 밝은 톤보다 어두운 톤에 더 민감하다**고 할 수 있다.

    ![](img/gamma_tone.jpg)

    - 카메라 센서와 눈의 인식 차이에서 발생하는 데이터상의 밝기값 손실을 방지하기 위해 디지털 이미지는 `감마 인코딩`을 한다.

    - 감마 인코딩 값을 데이터로 가지는 색 공간을 **sRGB**라고 한다.
    - sRGB : 마이크로소프트와 HP가 협력하여 만든 모니터 및 프린터 표준 RGB 색 공간. 
    - encode/decode 를 하드웨어에서 지원한다. 해당 형태로 저장된 이미지는 화면에 보여질 때 자동으로 감마 인코딩이 되어서 보여진다. 
    - `비공식적 표준 규격`이다. (대부분의 이미지는 해당 공간을 사용한다.)
  - Gamma Encoding 의 목적은 이미지를 디스플레이에 표시하기 위한 것이 아니라 `색상의 손실 없이 이미지를 기록하기 위한 것`이다.
    - 인코딩을 하지 않으면(실제 밝기 값을 우리 눈에 바로 적용하면) 어두운 톤의 부분(사람이 민감하게 인식하는)이 많이 사라지기 때문이다.
  
![](img/gamma_linear.jpg)

![](img/gammagraph.jpg)

- ### Linear Color Space : 수치적 강도 값이 사람이 인지하는 강도와 비례하여 일치하는 색 공간. 색상을 올바르게 추가하고 곱할 수 있다.

- 감마 인코딩 된 이미지는 정확한 수치의 강도를 저장한다. (사람 눈에는 밝게 보인다)
- 실제 이미지를 나타낼 때, 256레벨의 정보(8비트)만 있으면 충분히 부드럽게 이미지가 프린팅된다. 그러나 해당 정보량으로 linear encoding을 시도하면 `posterization` 현상이 발생한다.
  - posterization : 색과 색 사이의 중간값을 표현할 정보가 없어 이미지에서 색이 변경되는 곳이 명확하게 나뉘어지는 현상.
  - 여기서 설명하는 linear encoding이란, `카메라에 들어온 값을 그대로 이미지에 적는 것`이다.
  - 선형 인코딩을 사용할 때 posterization 현상을 피하려면 8배의 정보가 필요하다. (11비트)

- 우리가 정상적으로 인식하는 이미지의 감마 값을 1이라 할 때, **이미지에 저장되는 값들은 감마 인코딩을 거쳐서 저장된다. (gamma 0.45)** 이 경우 이미지는 `원래의 이미지보다 훨씬 밝아진다.`
- 감마 인코딩을 거치지 않은 데이터 정보 그대로를 표현한 이미지는 모니터로 출력될 때 예상했던 이미지보다 훨씬 어둡게 나온다.
  - 디스플레이에서 자동으로 우리 눈에 적합하게 디코딩을 하기 때문이다.

- ### Physically Based Rendering을 하려면 **선형 파이프 라인을 사용해야 한다.**
  - 정확한(실제 세상과 비슷한) 대비를 표현해야 하기 때문이다.

![](img/gamma_pbr.jpg)

- 감마 인코딩을 하면 어두운 톤을 나타내는 비트가 늘어나는데 왜 이미지가 밝아지나?
  - 어두운 톤을 표현하기 위해 많은 비트를 할애하기 때문에 선형 인코딩과 비교했을 때 어두운 톤이 더 큰 데이터를 가진다.(0을 어두운 쪽이라 가정했을 때)
  - 감마 인코딩된 데이터 값을 선형 그래프로 그렸을 때, 그 값이 일반적인 계산값보다 크기 때문에 이미지가 더 밝게 보인다.

  - 참고
    - [UNDERSTANDING GAMMA CORRECTION](https://www.cambridgeincolour.com/tutorials/gamma-correction.htm)
    - [GAMMA AND LINEAR SPACE - WHAT THEY ARE AND HOW THEY DIFFER](http://www.kinematicsoup.com/news/2016/6/15/gamma-and-linear-space-what-they-are-how-they-differ)
    - [LearnOpenGL - Gamma Correction](https://learnopengl.com/Advanced-Lighting/Gamma-Correction)