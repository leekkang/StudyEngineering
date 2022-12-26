
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
# World, View, Projection

  - https://stackoverflow.com/questions/28075743/how-do-i-compose-a-rotation-matrix-with-human-readable-angles-from-scratch/28084380#28084380
  - https://nickchooshin.tistory.com/7
  - 어떤 물체의 `월드 변환 행렬`은 기준 좌표계가 이미 월드이기 때문에 현재 물체의 요소를 그대로 사용하게 된다.
    - 메쉬의 꼭짓점들이 대상이 되며, 모두 `0,0,0`을 기준점으로 가지도록 설계한다.
    - `DirectX::XMMatrixScaling`, `DirectX::XMQuaternionRotationRollPitchYaw`, `DirectX::XMMatrixTranslation`
    - 결과로 나오는 행렬을 보면 전치 없이 그대로 값을 사용한 것을 볼 수 있다. -> **각도만큼 회전, 좌표만큼 이동**
  - 어떤 물체의 `뷰 변환 행렬`은 좌표계가 `뷰 공간`으로 변경되기 때문에 좌표축의 변환이 발생한다.
    - 월드 좌표로 표현한 `뷰 공간`의 기저 벡터를 행렬로 표현할 수 있는데(보통 카메라의 월드 좌표축이 대상이 된다.) `변환 행렬`과 곱했을 때 `항등 행렬`이 나온다.
    - `월드 좌표축` * `뷰 변환 행렬` = `항등 행렬`
    - 이동 변환의 경우, `-현재 월드 좌표`를 변환식에 추가하면 된다.
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
