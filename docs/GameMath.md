
## GameMath
  - 게임에서 사용하는 수학 정보들 

  - 참고 블로그
    - https://wjs7347.tistory.com/17

---
# 좌표계 변환

  - 어떤 한 좌표계에서 일어나는 모든 움직임들은 `다른 좌표계`에서 보면 반대로 보인다.
    - `좌표계 내의 한 점`을 다른 좌표계로 이동시키는 것과, `좌표계` 자체를 이동시키는 것은 서로 반대다.
  - `좌표계` 의 이동은 `좌표계 단위 벡터`의 이동과 동일하다.
  - 어떤 한 좌표계를 다른 좌표계로 변환한다는 것은 `좌표계 단위 벡터`를 `다른 좌표계 단위 벡터`와 동일한 값으로 바꾼다는 말과 동일하다.
  - 이 때 `원래 좌표계`의 좌표들은 가만히 있지만, `좌표계`의 입장에서는 `상대적`으로 이동을 한 것처럼 보인다.
    - `원점`을 앞으로 이동시키면, `원래 좌표계에 있는 한 점`은 **원점에서 봤을 때 뒤로 간다.**
  - 결국 이동한 `원래 좌표계`는 `새로운 좌표계`가 되고, `원래 좌표계의 값`들은 좌표계 움직임의 반대로 이동한 것처럼 계산되어 `새로운 좌표`가 된다.

  - ### 위치 변환
    - 보통 같은 좌표계에서 이동할 때 해당 좌표를 더한다.
   
    - `좌표계 이동`은 상대적인 움직임이다.
    - 그러므로 `현재 좌표계`에서 `원하는 좌표계의 기준`을 빼주면 `좌표계` 변환이 된다.
    - `현재 좌표계 값` - `원하는 좌표계 원점`(현재 좌표계) = `원하는 좌표계 값`
    - `월드 좌표` - `카메라 위치`(월드 좌표계) = `카메라 좌표`(카메라 좌표계)
  
  - ### 회전 변환
    - 보통 `어떤 좌표`를 $\theta$ 만큼 회전시킬 때, **$\theta$ 회전 행렬 * 세로 좌표** 수식을 사용한다.
    
    - `좌표계 이동`은 상대적인 움직임이기 때문에 $-\theta$ 만큼 회전시키면 **$\theta$ 회전 변환이 된 좌표계** 내의 좌표값이 나온다.
    - **$\theta$ 회전 행렬 * 세로 좌표의 결과값** 과 **가로 좌표 * $-\theta$ 회전 행렬의 결과값** 은 동일하다.
    - `회전 변환`에서 `회전 행렬`을 좌표의 앞에 곱할 경우(행렬 * 세로 좌표), 해당 각도만큼 `좌표`가 회전이 되고, `회전 행렬`을 뒤에 곱할 경우(가로 좌표 * 행렬), 해당 각도만큼 `좌표계`가 회전이 된다.(좌표계 이동이 발생한다.)
      - `행렬 * 세로 좌표` : `좌표`가 이동. `좌표계`는 그대로 존재.
      - `가로 좌표 * 행렬` : `좌표계`가 이동. 좌표는 이동하지 않지만 새로운 값을 얻어 `새로운 좌표계`에서의 좌표를 나타내게 됨.
    - **보통 `좌표계`의 변환을 하는 경우가 많다.** `가로 좌표 * 행렬`의 식을 사용하거나, 회전 각도를 반대로 해서 `행렬 * 세로 좌표`의 식을 사용하면 된다.



---
# 선분의 방정식

  - 매개변수를 이용한 표현법 (내분점, 외분점)
  - t가 해당 범위를 벗어나면 `직선의 방정식`과 동일해진다.
  $$
\begin{align*}
  x &= (1 - t)x_1 + tx_2 \\
  y &= (1 - t)x_1 + tx_2 \quad (0 \le t \le 1)
\end{align*}
  $$
  - 직선의 방정식의 표준형 (기울기와 y절편을 이용한 표현)
  - 수평선이나 수직선은 기울기와 y절편의 정확한 값이 안나올 수 있다.

$$
  y = mx + b \\
  \begin{align*}
  (y - y_0)(x_1 - x_0) &= (x - x_0)(y_1 - y_0) \\
  y - y_0 &= \frac{y_1 - y_0}{x_1 - x_0} (x - x_0) \\
  m &= \frac{y_1 - y_0}{x_1 - x_0} \\
  b &= y_0 -\frac{y_1 - y_0}{x_1 - x_0}x_0
  \end{align*}
$$

  - 직선의 방정식의 일반형

$$
   Ax + By + C = 0 \\
  \begin{align*}
  (y - y_0)(x_1 - x_0) &= (x - x_0)(y_1 - y_0) \\
  y(x_1-x_0) - y_0(x_1-x_0) &= x(y_1 - y_0) - x_0(y_1 - y_0) \\
  0 &= x(y_1 - y_0) - y(x_1-x_0) - x_0(y_1 - y_0) + y_0(x_1-x_0) \\
  A &= (y_1 - y_0) \\
  B &= -(x_1 - x_0) \\
  C &= -x_0(y_1 - y_0) + y_0(x_1-x_0) = -(x_0y_1 - x_1y_0) = -외적값\\
  \end{align*}
$$

---
# 두 선분의 교차점 구하기

  - 직선의 방정식을 `기울기`와 `절편`으로 나타내는 대신 매개변수를 이용하여 나타내면 깔끔하게 구할 수 있다. (벡터 방정식)
    - `P_1`과 `P_2` 사이를 `t : (1 - t)` 비율로 분리한 것과 같다.
  $$
  P(t) = (1 - t)P_1 + tP_2
  $$

  - 두 직선의 방정식을 매개변수 t, s 로 표현할 때, 2개의 식을 하나로 만들면 다음과 같다. 이 때, t와 s가 0~1 사이의 값을 가지지 않으면, **직선은 교차하지만 선분은 교차하지 않는 상태가 된다.**
  $$
  (1 - t)P_1 + tP_2 = (1 - s)P_1 + sP_2
  $$

  - x와 y로 분리하면 다음과 같다.
  $$
  x_1 + t(x_2 - x_1) = x_3 + s(x_4 - x_3) \\
  y_1 + t(y_2 - y_1) = y_3 + s(y_4 - y_3) 
  $$

  - t와 s로 정리하면 다음과 같다. (분모 같음)
  $$
  t = \frac{(x_4 - x_3)(y_1 - y_3) - (y_4 - y_3)(x_1 - x_3)} 
           {(y_4 - y_3)(x_2 - x_1) - (x_4 - x_3)(y_2 - y_1)} \\
  
  s = \frac{(x_2 - x_1)(y_1 - y_3) - (y_2 - y_1)(x_1 - x_3)} 
           {(y_4 - y_3)(x_2 - x_1) - (x_4 - x_3)(y_2 - y_1)} \\
  $$

  - t와 s는 두 선이 서로 만날때의 값이기 때문에, 최종적으로 두 선의 교점은 다음과 같다. 
  - `p - p1 : p2 - p = t : 1 - t` 닮음비를 이용한다.
  $$
  x = x_1 + t(x_2 - x_1) \\
  y = y_1 + t(y_2 - y_1) \\
  $$

  - 두 선분의 교차만 확인하고 싶은 경우 (게임에서 자주 사용) `외적의 방향성`을 이용해서 쉽게 구분할 수 있다.
    - 이차원 내에서 외적의 방향성은 `부호`로 나타난다.
    - 선분의 한 점에서 시작하는 벡터를 기준으로 두 점까지의 `벡터 외적값의 부호`가 다르면 교차한다고 볼 수 있다.

      ![](img/cross.png)
   
    - 위의 그림처럼 $\vec{ab}$ 를 기준으로 `c`와 `d`의 외적값을 비교하고, $\vec{cd}$ 를 기준으로 `a`와 `b`의 외적값을 비교하면 된다.
  
  - TODO : [크라메르 공식 (Cramer's rule)](https://ko.wikipedia.org/wiki/%ED%81%AC%EB%9D%BC%EB%A9%94%EB%A5%B4_%EB%B2%95%EC%B9%99) 을 알아보자
  
```cpp
  bool CCollisionManager::CollisionLineToLine(Vector2& hitPoint, const LineInfo& src, const LineInfo& dest) {
    // 선분의 기울기가 같은 경우
    Vector2 srcSlope = src.p2 - src.p1;
    Vector2 destSlope = dest.p2 - dest.p1;
    float under = srcSlope.Cross(destSlope);
    if (under < EPSILON && under > -EPSILON) { // 외적이 0이다 == sin 세타의 값이 0이다. == 평행하다
      // 기울기는 같지만 만나지 않는 경우 (체크하지 말자)
      return false;
      // 한 라인에 다른 라인의 점이 포함되어 있는 경우 (체크하지 말자)
    }

    // 한 선분에서 다른 선분의 두 점의 외적 값의 곱이 음수이면 선분의 좌우에 점이 존재한다.
    if (srcSlope.Cross(dest.p1 - src.p1) * srcSlope.Cross(dest.p2 - src.p1) > 0 ||
      destSlope.Cross(src.p1 - dest.p1) * destSlope.Cross(src.p2 - dest.p1) > 0)
      return false;

    // 선분의 기울기가 다른 경우
    // 매개변수(피벗)를 이용한 직선 내 좌표 공식 : P(t) = (1 - t) * p1 + t * p2
    float _t = (dest.p2.x - dest.p1.x) * (src.p1.y - dest.p1.y) - (dest.p2.y - dest.p1.y) * (src.p1.x - dest.p1.x);
    // t는 _t/외적 이다. 0과 1사이의 값이면 교차, 아니면 교차하지 않는다.
    float t = _t / under;
    if (t < 0.f || t > 1.f)
      return false;
    // hit - p1 : p2 - hit = t : 1 - t 닮음비를 이용한다.
    hitPoint.x = src.p1.x + t * (src.p2.x - src.p1.x);
    hitPoint.y = src.p1.y + t * (src.p2.y - src.p1.y);

    // s를 써도 히트포인트는 똑같다. 안해도 됨
    //float _s = (src.p2.x - src.p1.x) * (src.p1.y - dest.p1.y) - (src.p2.y - src.p1.y) * (src.p1.x - dest.p1.x);
    return true;
  }
```

  - 참고
    - [두 선의 교차점 구하기](http://www.gisdeveloper.co.kr/?p=89)
    - [두 선분의 교차여부 체크](https://crazyj.tistory.com/140?category=753578)
    - [2d 충돌 처리](https://netcanis.tistory.com/112)
    - [A Minimal Ray-Tracer](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection)
    - [두 직선의 교점 구하기](https://wjs7347.tistory.com/17)
    - [외적을 이용해서 선분과 선분의 교차점 구하기](https://bowbowbow.tistory.com/17)


---
# [Cohen-Sutherland 선분 알고리즘](https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm)

  - 선분과 사각형의 포함관계를 확인하는 알고리즘이다.
  - `top, bottom, right, left` 순으로 0 또는 1의 값을 줘서 비트 연산 시 나오는 값을 통해 해당 선분이 존재하는 영역을 찾아낸다.
  - 0000 영역이 비교하는 사각형의 영역이다.
  ![](img/cohen_sutherland.jpg)

     1. or 연산 시 0이 나오면 두 점이 가운데 있는 것이다.
  	
     2. and 연산 시 0이 아니면 선분 전체가 클리핑 외부에 있는 것이다.
  	 3. 한 점이 0이고 다른 점이 0이 아니면 선분이 사각형 경계에 걸치는 것이다.
  	 4. 나머지 (두 점이 0이 아니고 and연산시 0이 아니면) 경우는 직선방정식을 이용한다.
  - $m = (y_1 - y_0)/(x_1 - x_0), y - y_0 = m(x - x_0)$ 두 식을 사용하여 사각형의 네 선분과 비교한다.
  - 시작점이 `top` 영역에 존재하는 경우
    - $x = x_0 + (x_1 - x_0) * (y_{max} - y_0) / (y_1 - y_0) \\ y = y_{max}$
  - 시작점이 `bottom` 영역에 존재하는 경우
    - $x = x_0 + (x_1 - x_0) * (y_{min} - y_0) / (y_1 - y_0) \\ y = y_{min}$
  - 시작점이 `right` 영역에 존재하는 경우
    - $x = x_{max} \\ y = y_0 + (y_1 - y_0) * (x_{max} - x_0) / (x_1 - x_0)$
  - 시작점이 `left` 영역에 존재하는 경우
    - $x = x_{min} \\ y = y_0 + (y_1 - y_0) * (x_{min} - x_0) / (x_1 - x_0)$

```cpp
  byte CCollisionManager::ComputeOutcode(const Vector2& point, const BoxInfo& box) {
    byte outcode = 0;
    if (point.x < box.LT.x)
      outcode |= 1;
    else if (point.x > box.RB.x)
      outcode |= 2;
    if (point.y < box.LT.y)
      outcode |= 4;
    else if (point.y > box.RB.y)
      outcode |= 8;
    return outcode;
  }
  bool CCollisionManager::CollisionLineToBox(Vector2& hitPoint, const LineInfo& line, const BoxInfo& box) {
    // Cohen-Sutherland 선분 알고리즘을 사용한다.
    // top bottom right left 순으로 0 또는 1의 값을 줘서 비트 연산 시 나오는 값을 통해 해당 선분이 존재하는 영역을 찾아낸다.
    // 원래 화면 클리핑을 위해 사용하는 알고리즘이다.
    // 1001  1000  1010      y 값을 거꾸로 하면    0101   0100   0110
    // 0001  0000  0010                           0001   0000   0010
    // 0101  0100  0110                           1001   1000   1010
    // 
    // 1. or 연산 시 0이 나오면 두 점이 가운데 있는 것이다.
    // 2. and 연산 시 0이 아니면 선분 전체가 클리핑 외부에 있는 것이다.
    // 3. 한 점이 0이고 다른 점이 0이 아니면 선분이 사각형 경계에 걸치는 것이다.
    // 4. 나머지 (두 점이 0이 아니고 and연산시 0이 아니면) 경우는 직선방정식을 이용한다.
    // m = (y_1 - y_0)/(x_1 - x_0), y - y_0 = m(x - x_0) 두 식을 사용하여 사각형의 네 선분과 비교한다.
    byte outcode1 = ComputeOutcode(line.p1, box);
    byte outcode2 = ComputeOutcode(line.p2, box);

    if ((outcode1 & outcode2) != 0)			// 선분 전체가 밖에 있다.
      return false;

    if ((outcode1 | outcode2) == 0) {		// 선분 전체가 안에 있다.
      hitPoint = (line.p1 + line.p2) * 0.5f;
      return true;
    } else if (!outcode1 || !outcode2) {	// 점 하나가 사각형 안에 있다.
      hitPoint = !outcode1 ? line.p1 : line.p2;
      return true;
    } else if (outcode1 + outcode2 == 3) {	// 선분이 사각형을 가로로 자른다 (히트포인트 부정확함)
      hitPoint.x = (box.LT.x + box.RB.x) * .5f;
      hitPoint.y = (line.p1.y + line.p2.y) * .5f;
      return true;
    } else if (outcode1 + outcode2 == 12) { // 선분이 사각형을 세로로 자른다 (히트포인트 부정확함)
      hitPoint.x = (line.p1.x + line.p2.x) * .5f;
      hitPoint.y = (box.LT.y + box.RB.y) * .5f;
      return true;
    }


    byte outcode = max(outcode1, outcode2);
    Vector2 point{};
    if (outcode & 8) {       // top 부분 점과 사각형 윗변 충돌 체크
      point.x = line.p1.x + (line.p2.x - line.p1.x) * (box.RB.y - line.p1.y) / (line.p2.y - line.p1.y);
      point.y = box.RB.y;
      if (!(point.x < box.LT.x || point.x > box.RB.x)) {
        hitPoint = point;
        return true;
      }
    } 
    if (outcode & 4) {		// bottom 부분 점과 사각형 아랫변 충돌 체크
      point.x = line.p1.x + (line.p2.x - line.p1.x) * (box.LT.y - line.p1.y) / (line.p2.y - line.p1.y);
      point.y = box.LT.y;
      if (!(point.x < box.LT.x || point.x > box.RB.x)) {
        hitPoint = point;
        return true;
      }
    } 
    if (outcode & 2) {		// right 부분 점과 사각형 오른쪽변 충돌 체크
      point.y = line.p1.y + (line.p2.y - line.p1.y) * (box.RB.x - line.p1.x) / (line.p2.x - line.p1.x);
      point.x = box.RB.x;
      if (!(point.y < box.LT.y || point.y > box.RB.y)) {
        hitPoint = point;
        return true;
      }
    } 
    if (outcode & 1) {		// left 부분 점과 사각형 왼쪽변 충돌 체크
      point.y = line.p1.y + (line.p2.y - line.p1.y) * (box.LT.x - line.p1.x) / (line.p2.x - line.p1.x);
      point.x = box.LT.x;
      if (!(point.y < box.LT.y || point.y > box.RB.y)) {
        hitPoint = point;
        return true;
      }
    }

    return false;
  }
```


---
# 선분과 원의 교차 확인

  - 선분이 두 점 A와 B로 이루어져 있을 때, 원의 중심점을 C라 하고, 점 C에서 선분 AB에 수선을 내렸을 때의 교점을 D라 할 때, 아래의 두 조건을 만족하면 선분과 원이 충돌했다고 할 수 있다.
    - $\overrightarrow{AB}$의 길이가 $\overline{AD}$의 길이와 같거나 크다.
    - $\overline{CD}$의 길이가 반지름보다 크다.
  
    ![](img/line_circle.jpg)

  - 먼저, 선분을 구성하는 **두 점 A, B가 원의 내부에 있는지 확인한다.** 무조건 교차하기 때문
  - 두 점 A, B가 모두 원의 외부에 있는 경우 아래의 순서대로 확인한다.
    - 선분 AB의 길이가 점 A에서 원에 접하는 접선의 길이보다 짧으면 **무조건 만나지 않는다.**
    $$
      \overline{AB} ^2 \lt \overline{AC} ^2 - \overline{CD} ^2 \quad \Rightarrow  not\;crossing
    $$
    - 접선보다 길 경우, 사인값 비교를 통해 선분 CD의 길이와 반지름 값을 비교한다.
    - 선분 CD의 길이가 반지름보다 짧으면 교차한다.
    $$
      \frac{\overline{CD}}{\overline{AC}} \le \frac{r}{\overline{AC}} \quad \Rightarrow collision
    $$
  
    - 실제 코드에서 확인은 외적의 제곱을 비교하는 식으로 하면 된다.
$$
  \begin{align*}
(\overline{AB} \times \overline{AC})^2 &= (\left\| \overline{AB} \right\| \left\|  \overline{AC} \right\| sin \theta)^2 \\
&= \left\| \overline{AB} \right\|^2 \left\|  \overline{CD} \right\|^2 \\

(\frac{\overline{AB} \times \overline{AC}}{\overline{AB}})^2 &=  \overline{CD} ^2 \\
 
\therefore (\frac{\overline{AB} \times \overline{AC}}{\overline{AB}})^2 \le  r^2 \quad \Rightarrow collision
  \end{align*}
$$

  - 교차점의 중심을 구하는 방법은 두 가지가 있다.
    - 원의 중심에서 선분 으로 정사영을 한 벡터로 구하는 방법
    $$
      \begin{align*}
      \overrightarrow{AD} =& \overrightarrow{AB} \frac{\left\| \overline{AD}\right\|}{\left\|\overline{AB} \right\|} \\
      \overrightarrow{AB} \cdot \overrightarrow{AC} = &
      \left\| \overline{AB} \right\| \left\| \overline{AC} \right\| \cos \theta \\ 
      =& \left\| \overline{AB} \right\| \left\| \overline{AD} \right\| \\
      \end{align*} 

      \begin{align*}
      \therefore D &= A + \overrightarrow{AD} \\
      &= A + \overrightarrow{AB} \frac{\left\| \overline{AD}\right\|}{\left\|\overline{AB} \right\|}  \\
      &= A + \overrightarrow{AB} \frac{1}{\left\|\overline{AB} \right\|} \frac{\overrightarrow{AB} \cdot \overrightarrow{AC}}{\left\|\overline{AB} \right\|} \\
        &= A + \frac{\overrightarrow{AB} (\overrightarrow{AB} \cdot \overrightarrow{AC})}{\left\| \overline{AB} \right\| ^2}
      \end{align*}\\
    $$

    - 직선의 방정식을 이용하여 x, y 절편을 구하는 방법
      - [위키](https://ko.wikipedia.org/wiki/%EC%A0%90%EA%B3%BC_%EC%A7%81%EC%84%A0_%EC%82%AC%EC%9D%B4%EC%9D%98_%EA%B1%B0%EB%A6%AC)에 공식이 나와있다.

```cpp
  bool CCollisionManager::CollisionLineToCircle(Vector2& hitPoint, const LineInfo& line, const CircleInfo& circle) {
    // 1. 선분의 끝점이 원 안에 있는지 확인
    // 2. 선분의 길이가 접선의 길이보다 짧은지 확인
    // 3. 수선의 길이가 반지름보다 작은지 확인

    if (circle.radius > circle.center.Distance(line.p1)) {
      hitPoint = line.p1;
      return true;
    } else if (circle.radius > circle.center.Distance(line.p2)) {
      hitPoint = line.p2;
      return true;
    }

    float lineSquare = line.p1.DistanceSquare(line.p2);
    float centerSquare = max(circle.center.DistanceSquare(line.p1), circle.center.DistanceSquare(line.p2));

    // 2. 선분의 길이가 접선의 길이보다 짧은지 확인 (긴 쪽을 비교해야 한다)
    if (lineSquare < centerSquare - circle.radius * circle.radius)
      return false;

    // 3. 수선의 길이가 반지름보다 작은지 확인
    float cross = (line.p2 - line.p1).Cross(circle.center - line.p1);
    if (cross * cross > circle.radius * circle.radius * lineSquare)
      return false;

    // 히트포인트는 원의 중심에서 선분으로 정사영을 한 벡터로 구한다.
    Vector2 vecAB = (line.p2 - line.p1);
    float dot = vecAB.Dot(circle.center - line.p1);
    hitPoint = vecAB * (dot / lineSquare);

    return true;
  }
```

  - 참고
    - [Line Circle Collision Detection](https://micropilot.tistory.com/2956)

  - 아래 해법은 결론이 나지 않아서 폐기
  - 근의 공식을 이용한다.

![](img/line_circle2.jpg)

$$
ax^2 + bx + c = 0 \\
 x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}
$$

  - t의 방정식에서 $b^2-4ac$는 항상 0보다 크기 때문에 해가 2개다.
  - 2개의 해 중 하나라도 선분의 범위에 있으면 선분과 원은 교차한다.
$$
\begin{align*}
a &= (B - A)^2 \\
b &= 2(B - A)(A - C) \\
c &= (A - C)^2  -r^2
\end{align*}
$$
  - $t$의 영역은 $0 \le t \le 1$이다. 범위 밖의 t값은 직선은 교차하지만 선분은 만나지 않는다는 뜻이다.
  - 좌표들로 t를 표현하면 아래와 같다.
$$
 t = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a} \\
\begin{align*}
 t &= \frac{-2(B - A)(A - C) \pm \sqrt{4r^2(B - A)^2}}{2(B - A)^2} \\
 t &= \frac{-2(B - A)(A - C) \pm 2r(B - A)}{2(B - A)^2} \\
 t &= \frac{(C - A) \pm r}{(B - A)} \\
\end{align*}
$$

  - TODO 결론이 뭐지? 나중에 다시 한번 더 알아보자.

  - 참고
    - [선분-원 충돌 검사](https://kr.hansnotes.com/218)
    - [원과 직선의 충돌검사 알고리듬](https://dronedev.tistory.com/26)