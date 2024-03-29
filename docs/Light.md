﻿- [Document Link](#document-link)
- [SI 기본 단위](#si-기본-단위)
- [용어 정리](#용어-정리)
- [Radiometry](#radiometry)
  - [복사선속 (Radiant Flux, Radiant Power)](#복사선속-radiant-flux-radiant-power)
  - [복사 세기, 복사 강도 (Radiant Intensity)](#복사-세기-복사-강도-radiant-intensity)
  - [복사조도 (Irradiance, 照度)](#복사조도-irradiance-照度)
  - [복사 방출, 복사 발산도 (Radiant Exitance)](#복사-방출-복사-발산도-radiant-exitance)
  - [라디오시티 (Radiosity)](#라디오시티-radiosity)
  - [복사 휘도, 복사도 (Radiance, 輝度)](#복사-휘도-복사도-radiance-輝度)
  - [참고](#참고)
- [Photometry (Optics)](#photometry-optics)
  - [광속, 광선속, 광전력, 광속량 (Luminous Flux, Luminous Power)](#광속-광선속-광전력-광속량-luminous-flux-luminous-power)
  - [광도, 발광 세기 (Luminous Intensity)](#광도-발광-세기-luminous-intensity)
  - [조도 (Illuminance, 照度)](#조도-illuminance-照度)
  - [휘도 (Luminance, 輝度)](#휘도-luminance-輝度)
  - [비시감도(比視感度), 상대 시감도 (Luminous Efficiency Function, Luminosity Function)](#비시감도比視感度-상대-시감도-luminous-efficiency-function-luminosity-function)
  - [광원 효율, 발광 효율(Luminousity Efficacy)](#광원-효율-발광-효율luminousity-efficacy)
  - [예시](#예시)
  - [참고](#참고-1)
  - [Luminance vs Luma](#luminance-vs-luma)
- [BSDF (Bidirectional Scattering Distribution Function)](#bsdf-bidirectional-scattering-distribution-function)
  - [BRDF (Bidirectional Reflection Distribution Function, 양방향 반사 분포 함수)](#brdf-bidirectional-reflection-distribution-function-양방향-반사-분포-함수)
  - [Micro-facet Theory](#micro-facet-theory)
  - [Cook-Torrance Model](#cook-torrance-model)
  - [프레넬 방정식(Fresnel Equation)](#프레넬-방정식fresnel-equation)
  - [참고](#참고-2)
- [Tone Mapping](#tone-mapping)
- [Gamma Correction](#gamma-correction)

---


## Light

  - 그래픽스 하위 문서. 라이트 관련 정보들을 저장해놓는 문서



---
# Document Link

  - ## [Graphics Study](Graphics.md)


---
# [SI 기본 단위](https://ko.wikipedia.org/wiki/%EA%B5%AD%EC%A0%9C%EB%8B%A8%EC%9C%84%EA%B3%84)

  - 세계적으로 가장 널리 사용되는 국제 표준 도량형
  - 프랑스어 `Le Système International d'Unités` 에서 유래됨
  - 7개의 기본단위와 이들로 유도되는 22개의 이름을 가진 유도단위, 단순히 기본 단위가 조합된 일반 유도 단위들을 요소로 갖는다.
  - 기본단위

| 단위 이름 | 단위 기호 | 물리량 이름 | 물리량 기호 | 차원 기호 | 
|:---:|:---:|:---:|:---:|:---:|
| 초 | ${\rm s}$ | 시간 | $l$ | ${\sf T}$ | 
| 미터 | ${\rm m}$ | 길이 | $m$ | ${\sf L}$ | 
| 킬로그램 | ${\rm kg}$ | 질량 | $t$ | ${\sf M}$ | 
| 암페어 | ${\rm A}$ | 전류 | $I$ | ${\sf I}$ | 
| 켈빈 | ${\rm K}$ | 온도 | $T$ | $\Theta$ | 
| 몰 | ${\rm mol}$ | 물질량 | $n$ | ${\sf N}$ | 
| 칸델라 | ${\rm cd}$ | 광도 | $I_v$ | ${\sf J}$ | 

  - 유도 단위 (필요한 것만 작성, 나머지는 위키 참조)
  
| 단위 이름 | 단위 기호 | 물리량 이름 | SI 기본 단위 | 다른 SI 단위 | 차원 |
|:---:|:---:|:---:|:---:|:---:|:---:|
| 라디안 | ${\rm rad}$ | 평면각 (plane angle) | ${\rm m \cdot m^{-1}}$ | 1 | ${\sf 1}$(무차원) |
| 스테라디안 | ${\rm sr}$ | 입체각 (solid angle) | ${\rm m^2 \cdot m^{-2}}$ | 1 | ${\sf 1}$(무차원) |
| 헤르츠 | ${\rm Hz}$  | 주파수 (frequency) | ${\rm s^{-1}}$ |  | ${\sf T^{-1}}$ |
| 뉴턴 | ${\rm N}$  | 힘 (force, weight) | ${\rm kg \cdot m \cdot s^{-2}}$ |  | ${\sf MLT^{-2}}$ |
| 파스칼 | ${\rm Pa}$  | 압력 (pressure, stress) | ${\rm kg \cdot m^{-1} \cdot s^{-2}}$ | ${\rm N \cdot m^{-2} = J \cdot m^{-3}}$ | ${\sf ML^{-1}T^{-2}}$ |
| 줄 | ${\rm J}$  | 에너지, 일, 열량 (energy, work, heat) | ${\rm kg \cdot m^2 \cdot s^{-2}}$ | ${\rm N \cdot m = Pa \cdot m^{3}}$ | ${\sf ML^{2}T^{-2}}$ |
| 와트 | ${\rm W}$  | 일률, 전력 (power, radiant flux) | ${\rm kg \cdot m^2 \cdot s^{-3}}$ | ${\rm J \cdot s^{-1}}$ | ${\sf ML^{2}T^{-3}}$ |
| 루멘 | ${\rm lm}$  | 광선속 (luminous flux) | ${\rm cd \cdot sr}$ |  | ${\sf J}$ |
| 럭스 | ${\rm lx}$  | 조도 (illuminance) | ${\rm cd \cdot sr \cdot m^{-2}}$ | ${\rm lm \cdot m^{-2}}$ | ${\sf JL^{-2}}$ |



---
# 용어 정리

  - ### [Flux](https://ko.wikipedia.org/wiki/%EC%84%A0%EC%86%8D)
    - 선속(線束->묶을 속), 선다발, 유속(流束), 플럭스
    - 단위면적에 대한 어떤 성질의 흐름의 비율 -> 차원은 $물리량 \cdot 시간^{-1}\cdot 길이^{-2}$ 이 된다.
      - 매초마다 강의 횡단면을 통과하는 물의 양을 해당 단면의 면적으로 나눈 값
      - 매초 일정 면적의 땅에 내리쬐는 햇빛의 양을 땅의 면적으로 나눈 값
    - `벡터 필드의 표면 적분` 으로 나타내진다. 선속 자체는 스칼라 값으로 표현된다.
      - $\large \Phi_{F} = \iint_{A} {\rm F \cdot dA}$
    - 모든 `벡터 필드`가 가지고 있는 성질이다.
    - 플럭스를 근본적인 `양(quantity)`으로 가정한다면 `벡터 필드`는 **선속 밀도 (flux density)** 가 된다.
      - 벡터 필드가 곡선으로 그려질 때, 벡터 필드의 크기는 선의 밀도이며, 면을 통과하는 선속의 크기는 선의 개수 이다.
    - 복사선속(Radiant Flux, $\rm W$), 광속(Luminous Flux, $\rm lm$), 전속($\rm Coulomb$), 자속($\rm Wb$), 전류($\rm A$), 유체 질량(Fluid Mass, $\rm kg$), 방사 에너지량($\rm J$) 등이 있다.

  - ### [Field](http://www.ktword.co.kr/test/view/view.php?m_temp1=3928&id=1172)
    - 장(場), 계(界), 필드
    - 공간에서 위치, 시간 등에 따라 그 성질이 달라지는 물리량
    - 스칼라 필드 : 각 점이 크기를 나타내며 분포되어 있는 공간
      - 대기의 각 점에서 온도, 밀도, 압력
      - 전하가 있는 공간에서 전위의 분포
      - 유체흐름의 속도 포텐셜
      - 음파의 세기 또는 압력(음압)
    - 벡터 필드 : 각 점이 크기, 방향을 갖는 벡터를 나타내며 분포되어 있는 공간
      - 속도장 : 각 점에 `속도 벡터`를 대응시킨 것
        - 해류 속도장, 풍속 속도장
      - 역장 : 각 점에 `힘 벡터`를 대응시킨 것
        - 중력장, 전기장, 자기장

  - ### [Black Body(흑체)](https://en.wikipedia.org/wiki/Black_body)
    - 모든 파장의 전자기파를 반사하지 않고 완전히 흡수하는 가상의(이상적인) 물체
    - 때문에 `온도`에 의해서만 복사(열 복사)가 발생한다. 
    - `열평형(Thermal Equilibrium)` 상태에 있는 (온도가 일정한) 흑체는 `흑체 복사`라는 전자기 복사를 방출한다.
    - 열평형 상태의 흑체는 방사율(Emissivity)이 $\epsilon = 1.0$ 이다.

  - ### [Black Body Radiation(흑체 복사)](https://ko.wikipedia.org/wiki/%ED%9D%91%EC%B2%B4)
    - `흑체`에서 온도에 따라 빛이 나오는 현상 (열 복사)
    - 방출 에너지량은 `절대온도`의 네제곱에 비례하며, `평균 진동수`는 `절대온도`에 정비례한다.
    - 흑체 온도가 약 400도 이하면, 가시광선 없이 적외선만 방출한다.
    - [키르히호프의 복사 법칙(Kirchhoff's law of thermal radiation)](https://en.wikipedia.org/wiki/Kirchhoff%27s_law_of_thermal_radiation)
      - 복사파의 분포가 물체의 종류에 따라 다르지 않고, 오직 온도에만 의존한다.
      - 뜨거운 물체는 같은 온도에서 같은 파장(색깔)을 가진다.
    - [빈의 변위 법칙(Wien's displacement law)](https://en.wikipedia.org/wiki/Wien%27s_displacement_law)
      - 흑체 복사의 파장 가운데 에너지 밀도가 가장 큰 파장과 흑체의 온도가 반비례한다.
      - 온도가 높아질 수록 흑체의 색깔이 빨강->파랑색 으로 변한다.
      - $\large \rm \lambda_{peak} \cdot T = 2.898 \times 10^{-3}m\cdot K$
    - [스테판-볼츠만 법칙(Stefan–Boltzmann law)](https://en.wikipedia.org/wiki/Stefan%E2%80%93Boltzmann_law)
      - 흑체의 단위 면적당 복사 에너지(방출)가 절대 온도의 4제곱에 비례한다.
      - $\large M_{e}^{\circ} = \sigma T^4$
        - $\sigma$ = 스테판-볼츠만 상수(Stefan-Boltzmann constant)
        - $\sigma = 5.670\ 374\ 419 \dots \times 10^{-8}\ {\rm Wm^{-2}K^{-4}}$
      - 실제 표면에서의 복사 방출은 아래와 같다.
      - $\large M_{e} = \epsilon M_{e}^{\circ} = \epsilon\sigma T^4$
        - $\epsilon$ = [방사율(Emissivity)](https://en.wikipedia.org/wiki/Emissivity)
    - [플랑크 법칙(Planck's law)](https://en.wikipedia.org/wiki/Planck%27s_law)
      - 온도 $T$에서 `열 평형 상태의 흑체`가 방출하는 전자기 복사의 스펙트럼 밀도를 설명한다.
      - 저주파(긴 파장)에서 [레일리-진스 법칙(Rayleigh-Jeans law)](https://en.wikipedia.org/wiki/Rayleigh%E2%80%93Jeans_law)과 유사해지고, 고주파(짧은파장)에서 [빈 근사치(Wein approximation)](https://en.wikipedia.org/wiki/Wien_approximation)와 유사해진다.
      - $B_{\lambda}(\lambda, T) = {\Large \frac{2hc^2}{\lambda^5}}  {\Large \frac{1}{ {\rm exp}{\Large( \frac{hc}{\lambda k_B T})} - 1}}$

  - 참고
    - http://www.ktword.co.kr/test/view/view.php?m_temp1=4259&id=75

---
# [Radiometry](https://en.wikipedia.org/wiki/Radiometry)

  - 전자기파의 복사(Electromagnetic Radiation)를 측정하는 과학(복사도학)
  - 전자기파(electromagnetic) 특성을 반영한다는 것을 알리기 위해 기호에 첨자 $\rm e$ 를 붙인다.

  - ### 복사 (Radiation)
    - 0 $(K)$ 이상 온도의 모든 물체는, 전자기 복사선에 의해 에너지를 방출할 수 있다.
    - `공간, 물질을 통해 에너지가 사방으로 방출되는 현상` 또는 `전자기파로 방출되어 전달되는 에너지 자체(파동)`를 총칭하여 복사, 방사라고 말한다.
    - 파장 범위가, 대략 0.1 ~ 100 $\rm\mu m$ 정도에서의 복사를 주로 `열 복사`라 한다.
      - 전자기파에 의해 열이 매질을 통하지 않고 고온에서 저온으로 전달되는 현상
 
## [복사선속 (Radiant Flux, Radiant Power)](https://en.wikipedia.org/wiki/Radiant_flux)
  - `단위 시간`당 `복사 에너지(Radiant Energy)의 량` 또는 `에너지 플럭스` 
  - 단위 : $\rm J / s = Watt$. 즉, 전력 단위
  - $\LARGE \Phi_e = \frac{dQ_e}{dt}$
    - $Q_e$ : 닫힌 표면에서 나오는 방향의 복사 에너지 플럭스

## [복사 세기, 복사 강도 (Radiant Intensity)](https://en.wikipedia.org/wiki/Radiant_intensity)
  - `단위 입체각` 당 방출, 반사, 투과 또는 수신되는 `복사선속`
  - 점원(點原)으로부터 `퍼져나가는 방사 형태`의 방출 세기, 강도
  - 단위 : $\rm W / sr$
  - $\LARGE I_{e, \Omega} = \frac{\partial\Phi_e}{\partial \Omega}$
    - $\partial$ : 편미분 기호
    - $\Phi_e$ : 방출, 반사, 투과 또는 수신된 복사선속
    - $\Omega$ : 입체각

## [복사조도 (Irradiance, 照度)](https://en.wikipedia.org/wiki/Irradiance)
  - `단위 면적`당 수신된 `복사선속` (照 : 비출 조)
  - 단위 : $\rm W \cdot m^{-2}$
  - $\LARGE E_e = \frac{\partial\Phi_e}{\partial \rm A}$
    - $\partial$ : 편미분 기호
    - $\Phi_e$ : 수신된 복사선속
    - $\rm A$ : 면적
  - 지구의 수평면에 대한 `전체 방사 조도(global irradiance)`는 직접(direct) 방사 조도, 확산(diffuse) 방사 조도, 반사(reflected) 방사 조도의 합으로 나타난다.
    - $\large E_e = E_{e,dir} + E_{e,diff\cdotp} + E_{e,refl\cdotp}$
    - 평균 지면 반사율은 대략 전체 조도의 20%이다.
    - 일정 시간 동안의 태양 복사 조도의 적분을 `solar exposure` 또는 `일사량(insolation)`이라 한다.

## [복사 방출, 복사 발산도 (Radiant Exitance)](https://en.wikipedia.org/wiki/Radiant_exitance)
  - `단위 면적` 당 방출되는 `복사선속`. = **복사선속 밀도(Radiant Flux Density)**
  - 복사원(輻射源)의 `면적 형태`의 복사 방출 세기, 강도 (복사선속 면적 밀도)
  - 다른 분야에서 종종 `강도(Intensity)`로 표현되지만, `복사 세기`와는 다른 개념이다.
  - 단위 : $\rm W \cdot m^{-2}$
  - $\LARGE M_{e} = \frac{\partial\Phi_e}{\partial \rm A}$
    - $\partial$ : 편미분 기호
    - $\Phi_e$ : 방출된 복사선속
    - $\rm A$ : 면적
  - [흑체](https://en.wikipedia.org/wiki/Black_body) 표면(Black Surface)에서의 복사 방출은 `스테판-볼츠만 법칙(Stefan-Boltzmann Law)`에 의해 다음과 같이 표현된다.
    - $\large M_{e}^{\circ} = \sigma T^4$
    - 실제 표면에서의 복사 방출은 아래와 같다.
    - $\large M_{e} = \epsilon M_{e}^{\circ} = \epsilon\sigma T^4$
      - $\sigma$ = 스테판-볼츠만 상수(Stefan-Boltzmann constant)
      - $\epsilon$ = [방사율(Emissivity)](https://en.wikipedia.org/wiki/Emissivity)

## [라디오시티 (Radiosity)](https://en.wikipedia.org/wiki/Radiosity_(radiometry))
  - `단위 면적` 당 표면을 떠나는(방출, 반사, 투과) `복사선속`
  - 단위 : $\rm W \cdot m^{-2}$
  - $\LARGE J_{e} = \frac{\partial\Phi_e}{\partial \rm A} = J_{e,em} + J_{e,r} + J_{e,tr}$
    - $\partial$ : 편미분 기호
    - $\Phi_e$ : 방출된 복사선속
    - $\rm A$ : 면적
    - $J_{e,em} = M_e$ : 라디오시티의 방출(emitted) 요소. 복사 방출과 같다
    - $J_{e,r}$ : 라디오시티의 반사(reflected) 요소
    - $J_{e,tr}$ : 라디오시티의 투과(transmitted) 요소
  - `불투명 표면`에서는, 투과 요소가 사라지고 나머지 2개의 요소로 라디오시티를 표현한다.
    - $\large J_{e} = M_e + J_{e,r} = \epsilon\sigma T^4 + (1-\sigma)E_e$
      - $\epsilon$ = 방사율(Emissivity)
      - $\sigma$ = 스테판-볼츠만 상수(Stefan-Boltzmann constant)
      - $T$ = 표면의 온도
      - $E_e$ = 복사 조도

## [복사 휘도, 복사도 (Radiance, 輝度)](https://en.wikipedia.org/wiki/Radiance)
  - `단위 면적`, `단위 입체각` 당 방출, 반사, 투과 또는 수신되는 `복사선속` (輝 : 빛날 휘)
  - 단위 : $\rm W \cdot sr^{-1} \cdot m^{-2}$
  - $\LARGE L_{e, \Omega} = \frac{\partial^2\Phi_e}{\partial \Omega\partial A cos\theta}$
    - $\partial$ : 편미분 기호
    - $\Phi_e$ : 방출, 반사, 투과 또는 수신된 복사선속
    - $\Omega$ : 입체각
    - $\rm Acos\theta$ : 투영된 면적

![](img/Light/flux,%20irradiant,%20radiant.png)
  - ## (a) : Flux, (b) : Irradiance, (c) : Radiance

## 참고
  - [복사와 방사의 차이](https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=kore2758_&logNo=221415392684)
  - [정보통신기술용어해설](http://www.ktword.co.kr/test/view/view.php?m_temp1=4520)


---
# Photometry (Optics)

  - 인간의 눈에 대한 밝기(Brightness) 측면에서 빛을 측정하는 과학(광도학, 측광학)
    - `밝기(brightness)`는 `복사도학(radiometry)`의 전력(power)과 대응된다.
    - 전자기파 주파수 스펙트럼 전체가 아닌 `가시광선` 영역만 측정
  - 시각(visual) 특성을 반영한다는 것을 알리기 위해 기호에 첨자 $\rm v$ 를 붙인다.

![Radiometry vs Photometry](img/Light/compare.png)


## [광속, 광선속, 광전력, 광속량 (Luminous Flux, Luminous Power)](https://en.wikipedia.org/wiki/Luminous_flux)
  - 인지할 수 있는 빛의 전력 척도
  - 인간의 눈으로 느껴지는 빛의 선속량
  - 각 파장 별로 눈의 반응 정도가 달라지는데, 이 때 가시광선 대역의 모든 파장에서 가중치의 합(적분)이 광속이다. 자세한건 [비시감도](#비시감도比視感度-상대-시감도-luminous-efficiency-function-luminosity-function) 참고
  - 단위 : ${\rm 1\ lm = 1\ cd \times 1\ sr}$
  - 기호 : ${\large \Phi_{\rm v}}$

## [광도, 발광 세기 (Luminous Intensity)](https://en.wikipedia.org/wiki/Luminous_intensity)
  - `단위 입체각` 당 특정 방향으로 광원에서 방출되는 `광선속(Luminous Flux)`
  - `시감도`에 기초하여, 광원의 밝기를 나타내는 값
  - 단위 : $\rm cd\ (= lm / sr)$
  - 기호 : ${\large I_{\rm v}}$
  - 진동수 $540 × 10^{12}$ 헤르츠에서 `단위 입체각` 당 ${\rm 1 W}$의 전자기 에너지를 발산하는 광원의 광도는 ${\rm 683\ cd}$ 가 된다.
    - 해당 광원은 파장이 ${\rm 555\ nm}$ 인 녹색 단색광이다.
  - [램버트 코사인 법칙(Lambert's cosine Law)](https://en.wikipedia.org/wiki/Lambert%27s_cosine_law)
    - 이상적인 난반사 표면 또는 디퓨즈 라디에이터에서 발생하는 `복사 강도 또는 광도`는 **입사광의 방향과 표면 법선 사이의 각도 $\theta$의 코사인에 정비례**한다.
    - $I = I_0\ cos\theta$
    - 표면의 광채는 광원과 법선의 각도에 영향을 받지만, 관측자와 법선의 각도에는 영향을 받지 않는다. -> 계산 시 한번만 고려하면 된다.
    - 해당 법칙에 의해 `최고점 광도와 총 광선속의 관계`는 다음과 같다
      - $F_{tot} = \pi sr \cdot I_{max}$
      - 자세한 내용은 위키의 `Relating peak luminous intensity and luminous flux` 섹션 참고

## [조도 (Illuminance, 照度)](https://en.wikipedia.org/wiki/Illuminance)
  - `단위 면적`당 표면에 입사하는 총 `광선속` (照 : 비출 조)
  - 단위 : $\rm lx\ (= lm / m^2)$
  - 기호 : ${\large E_{\rm v}}$
  - 등방성(Isotropic) 광원의 광선속과 광원까지의 거리를 알 때 조도를 구하는 방법
    - 광원이 비추는 면적의 넓이는 입체각의 정의에 따라 스테라디안 * $r^2$ 이 된다.
    - 광선속의 입체각의 크기는 $4\pi$ 이다. (등방성이기 때문에)
    - **$\therefore$ 조도는 광선속 / $4\pi \cdot r^2$ 이다.**
    - 광도는 단위 입체각 당 광선속이다. -> 광선속 / $4\pi$
    - **$\therefore$ 조도는 광도 / $r^2$ 이다.**
  - 휘도와 조도의 관계식
    - $\int_{\Omega_\Sigma}\ L_{\rm v}\ d\Omega_\Sigma\  cos\theta_\Sigma\ = M_{\rm v} = E_{\rm v}R$
      - $M_{\rm v}$ : 표면의 광 방출량(luminous exitance)
      - $E_{\rm v}$ : 조도
      - $R$ : 반사율 (= 알베도)
  - `램버시안 표면(Lambertian Reflector, a perfectly diffuse reflector)`인 경우, 휘도는 램버트 코사인 법칙에 따라 등방성이 된다. 관계식을 다음과 같이 간단히 정리할 수 있다.
    - $L_{\rm v} = {\Large \frac{E_{\rm v}R}{\pi}}$
  

## [휘도 (Luminance, 輝度)](https://en.wikipedia.org/wiki/Luminance)
  - 주어진 방향으로 이동하는 `단위 면적` 당 `광도(Luminous Intensity)` (輝 : 빛날 휘)
  - 디스플레이 같은 표면광원(발광면적이 0이 아닌 광원, 점광원의 반대)에서 주로 사용한다.
  - 단위 : $\rm cd / m^2, nt$
  - $\LARGE L_{\rm v} ={\rm \frac{d^2\Phi_v}{d\Sigma d\Omega_\Sigma  cos\theta_\Sigma}}$
    - ${\rm d^2\Phi_v}$ : ${\rm d\Omega_\Sigma}$ 입체각 내 ${\rm d\Sigma}$ 영역을 떠나는 광선속
    - ${\rm d\Sigma}$ : 특정 포인트를 포함하는 광원의 극소(infinitesimal) 면적
    - ${\rm d\Omega_\Sigma}$ : 특정 방향을 포함하는 극소 입체각
    - $\theta_\Sigma$ : 광원 표면의 법선벡터와 방향 사이의 각도


## [비시감도(比視感度), 상대 시감도 (Luminous Efficiency Function, Luminosity Function)](https://en.wikipedia.org/wiki/Luminous_efficiency_function)
  - 시감도(視感度) : 파장(색)별로 밝기 강도를 다르게 느끼는 감응력
  - 최대 시감도 : 밝은 곳에 순응했을 때 인간의 눈이 최대 감도로 파장에서 느끼는 강도
    - $\rm 555\ nm$ 파장의 이상적인 단색광(녹색)의 경우 $\rm 683.002\ lm / W$
  - 비시감도 : 최대 시감도 대비 다른 파장의 시감도를 비율로 나타낸 것
  - 정리하면, `인간의 눈이 빛의 각 파장별 밝기를 느끼는 강도를 수치로 나타낸 것`
  
  - [국제조명위원회(CIE)](https://en.wikipedia.org/wiki/International_Commission_on_Illumination) 와 [국제도량형총회(CGPM)](https://en.wikipedia.org/wiki/General_Conference_on_Weights_and_Measures) 에서 `표준 비시감도`를 규정한다.
  - 밝은 조명에서 [명소시(Photopic)](https://en.wikipedia.org/wiki/Photopic_vision) 표준 비시감도를, 어두운 조명에서 [암소시(Scotopic)](https://en.wikipedia.org/wiki/Scotopic_vision) 표준 비시감도를 적용한다.
    - 보통 특정하지 않는 경우, `명소시(Photopic Vision)`를 사용한다.
  - 표준 비시감도 함수 ${\it \overline{y}(\lambda)\ or\ V(\lambda)}$ 를 사용하여 **복사계(Radiometric) 단위와 광도계(Photometric) 단위간의 변환**을 할 수 있다.
    - $V(\lambda) = 1.019\ {\rm exp}(-285.4(\lambda - 0.559)^2)$
  - 다음 식은 광원의 총 광선속을 계산한다. (복사계 -> 광도계) 
  - -> 적분항은 `광원의 복사선속 * 비시감도`와 동일하고, 상수항은 정규화 인자(normalization factor) 이다.
  - ${\rm \large \Phi_v = 683.002\ (lm / W)\cdot \int_{0}^{\infty} \overline{y}(\lambda) \Phi_{e, \lambda}(\lambda) d\lambda}$
    - $\rm \Phi_v$ : 광선속 (루멘 단위)
    - $\rm \Phi_{e, \lambda}$ : 스펙트럼 복사선속(= 파장별 복사선속) (와트 단위)
    - $\it \overline{y}(\lambda)\ or\ V(\lambda)$ : 비시감도 함수
    - $\rm \lambda$ : 파장, 단위 : $\rm nm$

![](img/Light/Relative_luminous_efficiency_curve.png)

  - `Photopic(black)` and `scotopic(green)` luminous efficiency functions
    - The CIE 1931 standard (실선)
    - The Judd–Vos 1978 modified data (파선(破線))
    - The Sharpe, Stockman, Jagla & Jägle 2005 data (점선)

## [광원 효율, 발광 효율(Luminousity Efficacy)](https://en.wikipedia.org/wiki/Luminous_efficacy)

  - 광원이 가시광선을 얼마나 잘 생성하는지를 측정하는 척도
  - 광출력(전력)에 대한 광선속의 비율로, 와트당 루멘 $\rm (lm / W)$ 이다.
  - 계산에 사용되는 `Power` 가 무엇이냐에 따라 명칭이 약간 달라진다.
  - `Luminous Efficacy of Radiation` = 시감도
    - 복사선속(Radiant Flux)을 `Power`로 사용한다.
    - $\rm 555\ nm$ 파장의 이상적인 단색광(녹색)의 경우 최대 광원효율은 $\rm 683.002\ lm / W$ 이다.
    - 광선속 / 복사선속 이다.
    - $K = {\rm {\LARGE \frac{\Phi_v}{\Phi_e}} = {\Large \frac{\int_{0}^{\infty} {\it K}(\lambda) \Phi_{e, \lambda}(\lambda) d\lambda}{\int_{0}^{\infty} \Phi_{e, \lambda}(\lambda) d\lambda}}}$
      - $\rm \Phi_v$ : 광선속 (루멘 단위)
      - $\rm \Phi_e$ : 복사선속 (와트 단위)
      - $\rm \Phi_{e, \lambda}$ : 스펙트럼 복사선속(= 파장별 복사선속) (와트 단위)
      - ${K(\lambda) = K_{\rm m}V(\lambda)}$ : 파장 별 시감도
  - `Luminous Efficacy of a Light Source, Overall Luminous Efficacy`
    - 소스가 소비하는 총 전력(전력, 화학 에너지, 기타 등)을 `Power`로 사용한다. -> `wall-plug efficacy` 라고도 한다.
    - 입력 에너지가 열 또는 전자기파가 아닌 다른 것으로도 방출된다.
    - 백열전구와 같은 필라멘트의 열 방출에 의존하는 광원은 전반적인 효율이 낮다. -> 대부분 열 적외선
    - 단위는 같지만 시감도와 구분을 위해 기호로 $\eta$ 를 사용한다.

## 예시

  - 60 ${\rm W}$의 백열등 전구의 광선속은 1000 ${\rm lm}$이고, 빛이 전구로부터 모든 방향으로 동일하게 방출된다고 가정하자.
  1. 전구의 발광효율(Luminousity Efficacy)
     - 1000 / 60 = 16.7 ${\rm lm / W}$ 
  2. 전구의 광도(Luminous Intensity)
     - 1000 / 4$\pi$ = 1000 / 12.57 = 79.6 ${\rm cd}$ 
  3. 전구 밑 1.5m에 위치한 책상 위의 조도(illuminance)
     - 면적 = 스테라디안의 크기 * $r^2$
     - 1000 / (4$\pi \cdot r^2)$  = 1000 / (12.57 * 2.25) = 35.357 ${\rm lux}$ 
  4. 전구로부터의 거리 r에서 조도와 광도간의 관계식
     - $E_{\rm v} = I_{\rm v} / r^2$
  4. 전구로부터의 거리 r에서 조도와 광선속간의 관계식
     - $E_{\rm v} = \Phi_{\rm v} / 4\pi \cdot r^2$ (3번의 풀이에 사용한 식)

## 참고
  - [정보통신기술용어해설](http://www.ktword.co.kr/test/view/view.php?m_temp1=4520)
  - [시감도 함수와 발광효율](https://m.blog.naver.com/namgoocha/220236955232)
  - [광량 간의 관계](https://blog.signifykorea.com/?p=10821)
  - [Light-Emitting Diodes](https://ocw.snu.ac.kr/sites/default/files/NOTE/791.pdf)


## Luminance vs Luma

  - `Luminance(휘도)`
    - 어떤 방향으로 이동하는 빛의 단위 면적당 광도
    - 빛의 강도에 대한 물리적 측정이며, 단위는 평방미터 당 칸델라이다. $(cd/m^2)$
      - 광도(Luminous Intensity) : 광원에서 특정 방향으로 나오는 가시광의 강도 (칸델라, $cd, \frac{lm}{sr}$)
 
      - 광속(Luminous Power) : 광원으로부터 나오는 가시광의 총량 (루멘, $lm$)
      - 조도(Illuminance) : 물체의 단위 면적에 들어오는 빛의 양 (룩스, $lx, \frac{lm}{m^2}$)
      - 휘도(Luminance) : 광원으로부터 복사되는 빛의 밝기 (니트, $nt, \frac{cd}{m^2}$) [위키](https://ko.wikipedia.org/wiki/%ED%9C%98%EB%8F%84)
      - 광효율(Luminous Efficacy) : 단위전력당 방출되는 광량 (루멘 퍼 와트, $\frac{lm}{W}$)

  - `Relative Luminance(상대 휘도)`
    - 사람이 무언가를 얼마나 밝게 보는지를 측정하는 단일 스칼라 값
    - `CIE standard`가 `표준 관찰자`를 정의하며, 0 ~ 1 또는 0 ~ 100의 정규화된 범위를 가진다. (높은 값이 reference white)
    - 우리는 초록색이 파란색보다 좀 더 밝다고 느낀다.
    - 때문에 기존 RGB-Triple의 값을 그대로 사용하면 우리가 인식하는 것과 약간 다른 색상이 나온다.
    - $Y=0.2126R+0.7152G+0.0722B$
      - `CIE Yxy 색표계`의 Y값이 휘도와 동일하다고 하는데 더 알아볼 필요가 있다.
    - 휘도를 사용하는 톤매핑 연산자는 RGB 채널을 휘도로 변환 후 매핑을 하고, 결과값을 새 휘도값으로 스케일링 한다.
      - 라인하르트 말고 다른 톤매핑에서는 그냥 상수값으로 조절하더라..
  - `Luma`
    - 감마 압축 비디오 신호에서 수행되는 상대 휘도 계산
    - == `감마 보정된 RGB` 성분의 가중치 합
    - 실제 광원을 가지고 이미지 센서를 가리키면, 센서는 $R'G'B'$ 값을 출력한다. 프라임 == 감마 컴프레션
    - $Y'=0.2126R'+0.7152G'+0.0722B'$

  ![](img/Light/luminance_unit.png)

  - 참고
    - https://cs.stackexchange.com/questions/92569/what-is-the-difference-between-luma-and-luminance
    - [아트세미텍 ppt - LED 광 측정 단위](https://slidesplayer.org/slide/12638978/)
    - [시감도 함수와 발광효율](https://m.blog.naver.com/namgoocha/220236955232)

  ![](img/Light/luminance_unit1.png)

  ![](img/Light/luminance_unit2.png)

  ![](img/Light/luminance_unit_conversion.png)





---
# [BSDF (Bidirectional Scattering Distribution Function)](https://en.wikipedia.org/wiki/Bidirectional_scattering_distribution_function)

  - 빛이 어떤 물체에 부딪혔을 때 산란되는 방식을 설명하는 함수
  - 보통 `BRDF(Reflected)`와 `BTDF(Transmitted)`의 집합을 이야기한다.
    - 공식은 비슷하다. [BTDF 공식](https://www.ies.org/definitions/bidirectional-transmittance-distribution-function-btdf/)

## [BRDF (Bidirectional Reflection Distribution Function, 양방향 반사 분포 함수)](https://en.wikipedia.org/wiki/Bidirectional_reflectance_distribution_function)
  - 표면이 반사하는 빛의 양을 평가하는 데 쓰이는 함수 (수학 공식)
    - `BSSRDF(Bidirectional Surface Scattering Reflection Distribution Function)`의 간략화 버전
    - `BSSRDF`는 8차 함수, `BRDF`는 4차 함수 이다.
  - 일반적으로 빛의 속성과 표면의 재질 속성, 시점 또는 카메라의 위치를 포함한 여러 개의 입력 매개변수들을 사용한다.
  - 난반사(diffuse) 모델, 정반사(specular) 모델로 나뉜다. 둘을 한번에 설명할 수 있는 모델이 없다.
  - 난반사 모델에는 보통 `램버시안(Lambertian)`, `벌리(Burley)` 두 가지 모델이 사용된다.
    - `벌리(Burley)` 모델은 좀 무겁기 때문에 실시간 그래픽스에서는 많이 쓰이진 않는다.
  - 정반사 모델에는 거의 대부분 `쿡-토런스(Cook-Torrance)` 모델을 사용한다.

  - 물리 기반 BRDF 모델의 경우 아래의 속성이 존재한다.
    - Positivity : 분포 함수의 결과값이 0보다 같거나 크다.
    - Obeying [Helmholtz reciprocity](https://en.wikipedia.org/wiki/Helmholtz_reciprocity) : 입사와 반사의 방향이 바뀌어도 그 결과가 동일하다.
    - Conserving Energy : 반사광의 에너지는 입사광의 에너지보다 작거나 같다.
  - 에너지 보존의 경우, 모든 경우를 고려하면 계산이 복잡해지기 때문에 보통 `Diffuse`와 `Specular`에만 적용한다.
  - Unreal Engine4의 경우 컬러 수식은 아래와 같다.
    - $\large Color = \sum_{l = 1}^{n}(D_{dl}\cdot (1-metalic) + S_{dl}\cdot metalic + T_{dl}) + E + (D_{il} + S_{il})$
      - $dl$ : 직접광
      - $il$ : 간접광

![BRDF Models](img/Light/BRDFModels.png)

## [Micro-facet Theory](https://lifeisforu.tistory.com/352)

  - 물체의 표면이 미세면(Microfacet)들로 이루어져 있다는 이론
    - 미세면 : 임의의 크기와 각도를 가지는 작고 평평한 거울 집합
  - 물리 기반 렌더링 모델에서 거칠기(Roughness)로 표현되는 부분이다.
  - 각각의 미세면(Microsurface) 법선 벡터(m)가 메쉬 표면(Macrosurface)의 법선 벡터(n)와 동일한 방향으로 빛을 반사한다.
  - 미세면 법선 벡터(m)의 분포도를 표현한 함수를 `미세면 분포 함수(Microfacet Distribution Function, D)` 이라 한다.
  - 미세면 사이로 빛이 들어와 반사되는 빛이 다른 미세면에 가려지는 정도를 표현한 함수를 `그림자-마스킹 함수(Shadowing-Masking Function, G)` 라 한다.
    - 마스킹(Masking), 섀도잉(Shadowing), 상호 반사(Interreflection) 세 가지의 중요한 기하학적 효과가 있다.
    - 때문에 정확한 공식을 만드는 것이 거의 불가능하다.

## Cook-Torrance Model

  - `Robert L.Cook`, `Kenneth E.Torrance`가 발표한 정반사 모델
  - `등방성(isotropic)` 재질의 미세면 모델의 경우, 쿡-토렌스 모델과 정확하게 일치한다.
    - `미세면 분산 함수`를 변경하면 `비등방성(Anisotropic)` 재질도 표현이 가능하다.

  - $f_{spec}(l, v) = {\Large \frac{F(l, h)}{4} \frac{D(h)\ G(l, v, h)}{(n \cdot v)(n \cdot l)}}$
    - $D$ = Microfacet Distribution Function
    - $F$ = Fresnel Equation
    - $G$ = Geometry Function
    - $n$ = Normal Vector
    - $v$ = View Vector
    - $l$ = Light Vector
    - $h$ = Half Vector (View Vector + Light Vector)
  - 원래 $\pi$를 나누었으나, 2007년 [Bruce Walter의 논문](https://www.cs.cornell.edu/~srm/publications/EGSR07-btdf.pdf)에서 4로 나눈 공식을 제시한다. (공동저자 목록에 Torrance가 있다.)
  - `미세면 분산 함수(D)`와 `그림자 마스킹 함수(G)`는 러프니스(Roughness)와 관련이 있고, `프레넬 방정식(F)`은 금속성(Metallic)과 관련이 있다.
    - `Roughness` 는 반사의 선명도 및 확산과 관련이 있으며, `Metallic` 은 반사의 세기 및 각도와 관련이 있다.
  - `Unreal Engine4` 에서는 $D$, $G$, $F$ 함수로 아래의 식들을 사용한다. (다른 식도 선택 가능하긴 함)
    - 전체 함수 목록은 [여기](http://graphicrants.blogspot.com/2013/08/specular-brdf-reference.html) 참고
    - `GGX` 라는 단어의 어원? : [페이퍼](https://jcgt.org/published/0007/04/01/paper.pdf)
  - $D$ : GGX(Trowbridge-Reitz)
    - $D_{GGX}(m) = {\Large \frac{\alpha^2}{\pi ((n \cdot m)^2(\alpha^2 - 1) + 1)^2}}$
  - $G$ : Schlick-GGX Model
    - $k = {\Large \frac{(Roughness + 1)^2}{8}}$
    - $G_1(v) = {\Large \frac{n\cdot v}{(n\cdot v)(1 - k) + k}}$
    - $\therefore \large G(l, v, h) = G_1(l)G_1(v)$
  - $F$ : Schlick's Approximation
    - $F_{Schlick}({\rm v, h}) = F_0 + (1 - F_0)(1 - ({\rm v \cdot h}))^5$

## [프레넬 방정식(Fresnel Equation)](https://en.wikipedia.org/wiki/Fresnel_equations)

  - TODO




## 참고

  - [PBR 이란 무엇인가](https://lifeisforu.tistory.com/386)
  - [Specular BRDF Reference](http://graphicrants.blogspot.com/2013/08/specular-brdf-reference.html)
  - [Autodesk Standard Surface](https://autodesk.github.io/standard-surface/)
  - [Physically Based Shading at Disney](https://media.disneyanimation.com/uploads/production/publication_asset/48/asset/s2012_pbs_disney_brdf_notes_v3.pdf)
  - [GGX와 Schlick Fresnel, 쿡-토런스 함수](https://m.blog.naver.com/canny708/221551990444)
  - [Microfacet Models](https://www.pbr-book.org/3ed-2018/Reflection_Models/Microfacet_Models)
  - [Microfacet BRDF](https://m.blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=hsg556&logNo=110129600105)
  - [BRDF 구현하기](https://prooveyourself.tistory.com/6)

---
# Tone Mapping

  - 이미지의 전체 밝기와 대비(contrast)를 조정하고 출력 장치에 맞게 이미지의 색상 범위를 줄이는 데 사용되는 기술
  - `HDR`을 사용할 때 반드시 필요하다.
  - `감마 보정`되지 않은 선형성의 색상을 가지고 연산을 진행해야 정확한 값이 나온다. -> 출력 시 감마 인코딩을 해야 한다.

  - ### Reinhard's Operator (라인하르트의 연산자)
    - 가장 간단하고 널리 쓰이는 연산자이다.
    - [자세한 내용은 여기서 참고](https://expf.wordpress.com/2010/05/04/reinhards_tone_mapping_operator/)
    - 가장 밝은 지역을 없애기 위해 상한값을 지정하는 수정 버전도 있다.
    - 라인하르트 연산자는 휘도를 사용하는 연산자이기 때문에 정확한 연산을 하려면 RGB값을 휘도로 변경할 필요가 있다.


  $$
\begin {aligned} 
TMO(C) &= \frac{C}{1 + C(x,y)} \\
TMO_{ext}(C) &= \frac{C * (1 + \frac{C}{C^2_{white}})}{1 + C} \quad C_{white} = cutoff\ parameter
\end {aligned} 
  $$

  - ### Reinhard's Operator (Luminance Tone Map)
    - 기존 수정된 라인하르트 연산자에 rgb값 대신 휘도를 넣어서 계산하는 방식

$$
\begin {aligned} 
  TMO_{extlum}(C) &= C\ \frac{L_d(x,y)}{L(x,y)} \quad C = RGB \\
L_d(x,y) &= \frac{L(x,y) (1 + \frac{L(x,y)}{L^2_{white}})}{1 + L(x,y)} \quad L_{white} = cutoff\ parameter
\end {aligned} 
$$

```cpp
float GetLuminance(float3 rgb) {
	return dot(rgb, float3(0.2126f, 0.7152f, 0.0722f));
}

float3 ReinhardLuminance(float3 hdr, float averageLum, float middleGray, float cutoffWhite) {
	float lum = GetLuminance(hdr);
	lum *= middleGray / averageLum;	// middleGray ~~ camera exposure configuration
	float lumOut = (lum * (1.0f + (lum / (cutoffWhite * cutoffWhite)))) / (1.0f + lum);
	return hdr * (lumOut / lum);
}
```

  - ### Filmic Tone Mapping Operator
    - 말 그대로 영화처럼 보이게 만들어주는 톤 매핑
    - Radiance(X축)-Brightness(Y축) 그래프에서 라인하르트 연산자와 비교했을 때, 끝 부분 (toe, shoulder)이 굴곡진다.
    - 감마 보정이 필요 없도록 조정된(Baked) 연산자도 있다.

![](img/Light/filmic-curve.png)

  - ### [Uncharted2](https://www.gdcvault.com/play/1012351/Uncharted-2-HDR)
    - John Hable이 Uncharted2 HDR Lighting 발표 문서에서 소개한 내용
    - 최초 버전은 감마 보정 불필요, 수정된 버전은 감마 보정 필요

```cpp
// 감마값이 포함된 톤맵핑. John Hable이 발표함
float3 ToneMapFilmicALU(in float3 color) {
	color = max(0, color - 0.004f);
	color = (color * (6.2f * color + 0.5f)) / (color * (6.2f * color + 1.7f) + 0.06f);
	return color;
}

float3 ToneMapUncharted2Partial(float3 x) {
	float A = 0.15f;	// Shoulder Strength
	float B = 0.50f;	// Linear Strength
	float C = 0.10f;	// Linaer Angle
	float D = 0.20f;	// Toe Strength
	float E = 0.02f;	// Toe Numerator
	float F = 0.30f;	// Toe Denominator
	return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;
}
float3 ToneMapUncharted2(float3 col) {
	float exposureBias = 2.0f;
	float3 curr = ToneMapUncharted2Partial(col * exposureBias);

	float W = 11.2f;	// Linear White Point Value
	float3 whiteScale = 1.0f / ToneMapUncharted2Partial(W);
	return curr * whiteScale;
}
```

  - ### ACES (Academy Color Encoding System)
    - `영화 예술 과학 아카데미(Academy of Motion Picture Arts and Sciences)`의 후원 하에 개발된 무료 개방형 장치 독립형 색상 관리 및 이미지 교환 시스템
    - 색 공간을 표준화하기 위해 만들어졌으며 넓은 색 공간을 사용하기 때문에 사실적이다.
    - 언리얼 엔진4에서 사용하는 TMO이다.

```cpp
// sRGB => XYZ => D65_2_D60 => AP1 => RRT_SAT
static const float3x3 ACESInputMat = {
	{ 0.59719f, 0.35458f, 0.04823f },
	{ 0.07600f, 0.90834f, 0.01566f },
	{ 0.02840f, 0.13383f, 0.83777f }
};

// ODT_SAT => XYZ => D60_2_D65 => sRGB
static const float3x3 ACESOutputMat = {
	{ 1.60475f, -0.53108f, -0.07367f },
	{ -0.10208f, 1.10813f, -0.00605f },
	{ -0.00327f, -0.07276f, 1.07602f }
};
float3 RRTAndODTFit(float3 v) {
	float3 a = v * (v + 0.0245786f) - 0.000090537f;
	float3 b = v * (0.983729f * v + 0.4329510f) + 0.238081f;
	return a / b;
}
float3 ToneMapACESFitted(float3 color) {
	color = mul(ACESInputMat, color);

    // Apply RRT and ODT
	color = RRTAndODTFit(color);

	color = mul(ACESOutputMat, color);

    // Clamp to [0, 1]
	return saturate(color);
}
```

  - ### [ACES Approximate](https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/)
    - `ACES` 연산 부하를 줄인 간단한 버전. 밝은 색상을 좀 더 강조(과포화)한다.

```cpp
float3 ToneMapACES(float3 x) {
	x *= 0.6f;
    // Narkowicz 2015, "ACES Filmic Tone Mapping Curve"
	const float a = 2.51f;
	const float b = 0.03f;
	const float c = 2.43f;
	const float d = 0.59f;
	const float e = 0.14f;
	
	return saturate((x * (a * x + b)) / (x * (c * x + d) + e));
}
```

![](img/Light/ACES_approximate.png)

  - 참고
    - https://64.github.io/tonemapping/
    - https://bruop.github.io/tonemapping/
    - [Reinhard's Tone-Mapping Operator](https://expf.wordpress.com/2010/05/04/reinhards_tone_mapping_operator/)


---
# Gamma Correction

  - ### Gamma : 픽셀의 숫자 값과 실제 광도 사이의 관계를 정의한다. 엄밀히 말하면 `센서나 표시장치와 같은 하드웨어 장치의 비선형성`을 의미한다.
    - 광자 수가 두 배로 늘어나면 카메라의 센서에 두 배의 신호가 수신된다. (선형 관계)
    - 우리 눈은 광자 수가 두 배로 늘어나면 **그보다 훨씬 더 밝다고 인식한다.** (비선형 관계) 밝기가 올라갈수록 그 차이는 점점 줄어든다.
    - 결론적으로, **우리 눈은 밝은 톤보다 어두운 톤에 더 민감하다**고 할 수 있다.
    - 카메라 센서와 눈의 인식 차이에서 발생하는 데이터상의 밝기값 손실을 방지하기 위해 디지털 이미지는 `감마 인코딩`을 한다.

    ![](img/Light/gamma_tone.jpg)

  - ### Gamma Compression(감마 압축) : 선형 데이터를 파일 형식으로 압축하여 샘플당 비트 수를 줄이는 기술
    - Gamma Encoding 의 목적은 이미지를 디스플레이에 표시하기 위한 것이 아니라 `색상의 손실 없이 이미지를 기록하기 위한 것`이다.
    - 인코딩을 하지 않으면(실제 밝기 값을 우리 눈에 바로 적용하면) 어두운 톤의 부분(사람이 민감하게 인식하는)이 많이 사라지기 때문이다.
    - 감마 인코딩 값을 데이터로 가지는 색 공간을 **sRGB**라고 한다.
    - encode/decode 를 하드웨어에서 지원한다. 해당 형태로 저장된 이미지는 화면에 보여질 때 자동으로 감마 디코딩이 되어서 보여진다. 
  
  - ### sRGB : 마이크로소프트와 HP가 협력하여 만든 모니터 및 프린터 표준 RGB 색 공간.
  - `비공식적 표준 규격`이다. (대부분의 이미지는 해당 공간을 사용한다.)
  
![](img/Light/gamma_linear.jpg)

![](img/Light/gammagraph.jpg)

- ### Linear Color Space : 수치적 강도 값이 사람이 인지하는 강도와 비례하여 일치하는 색 공간. 색상을 올바르게 추가하고 곱할 수 있다.

- 감마 인코딩 된 이미지는 정확한 수치의 강도를 저장한다. (사람 눈에는 밝게 보인다)
- 실제 이미지를 나타낼 때, 256레벨의 정보(8비트)만 있으면 충분히 부드럽게 이미지가 프린팅된다. 그러나 해당 정보량으로 linear encoding을 시도하면 `posterization` 현상이 발생한다.
  - posterization : 색과 색 사이의 중간값을 표현할 정보가 없어 이미지에서 색이 변경되는 곳이 명확하게 나뉘어지는 현상.
  - 여기서 설명하는 linear encoding이란, `카메라에 들어온 값을 그대로 이미지에 적는 것`이다.
  - 선형 인코딩을 사용할 때 posterization 현상을 피하려면 8배의 정보가 필요하다. (11비트)

- 우리가 정상적으로 인식하는 이미지의 감마 값을 1이라 할 때, **이미지에 저장되는 값들은 감마 인코딩을 거쳐서 저장된다. (gamma 0.45)** 이 경우 이미지는 `원래의 이미지보다 훨씬 밝아진다.`
- 감마 디코딩을 거치지 않은 데이터 정보 그대로를 표현한 이미지는 모니터로 출력될 때 예상했던 이미지보다 훨씬 어둡게 나온다.
  - 디스플레이에서 자동으로 우리 눈에 적합하게 디코딩을 하기 때문이다.
  - 이미지 보정 프로그램들의 컬러 픽커(색 편집)에서 `명도`조절을 해보면 확실해진다. 0.5에 해당하는 값은 실제 0.5의 색이 아닌 좀 더 진한 값($0.5^{2.2} == 0.217$)이 출력된다.

- ### Physically Based Rendering을 하려면 **선형 파이프 라인을 사용해야 한다.**
  - 정확한(실제 세상과 비슷한) 대비를 표현해야 하기 때문이다.

![](img/Light/gamma_pbr.jpg)

- 감마 인코딩을 하면 어두운 톤을 나타내는 비트가 늘어나는데 왜 이미지가 밝아지나?
  - 어두운 톤을 표현하기 위해 많은 비트를 할애하기 때문에 선형 인코딩과 비교했을 때 어두운 톤이 더 큰 데이터를 가진다.(0을 어두운 쪽이라 가정했을 때)
  - 감마 인코딩된 데이터 값을 선형 그래프로 그렸을 때, 그 값이 일반적인 계산값보다 크기 때문에 이미지가 더 밝게 보인다.

  - 참고
    - [UNDERSTANDING GAMMA CORRECTION](https://www.cambridgeincolour.com/tutorials/gamma-correction.htm)
    - [WHAT EVERY CODER SHOULD KNOW ABOUT GAMMA](https://blog.johnnovak.net/2016/09/21/what-every-coder-should-know-about-gamma/)
    - [LearnOpenGL - Gamma Correction](https://learnopengl.com/Advanced-Lighting/Gamma-Correction)
