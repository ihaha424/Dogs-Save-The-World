# Dogs-Save-The-World

(게임 인재원 1학기 개인 프로젝트 Master Branch에 있음)

-------------------------------------------------------------------------------------------------
    처음으로 WinAPI를 사용하여 게임을 만든 프로젝트이다.
    엔진(프레임워크)을 사실상 처음 구조를 잡고 짜봤다.
    게임자체는 클라이언트 부분보다 엔진쪽에 더 힘을 줘서 아쉽게 UI나 벨런싱, 편의성이 조금 부족하지만
    프레임 워크가 어떤식으로 동작하고, 또한 각각의 기능들 (ex> Render, Input, Time 등) 뿐만아니라 
    게임을 구성하는 프레임들 (ex> Resource, Scene, Object, COoponet, Collider 등) 직접 만들고 관리하면서 게임을 만들고
    내가 만든이 엔진들을 사용해서 Client부분까지 직접 생각하고 로직을 만든어서 추가하고 제어하는 것을 처음 해보는 매우 흥미로운 프로젝트였다.
    엔진을 만들고 CLient를 만는 도중 엔진을 다시 처음부터 구조를 잡고 뜯어 고치고 싶었으나 시간상의 이유로 못 고친 점이 아쉬웠다.
    또한 애니메이션이나 이벤트 처리, 카메라등을 구현하지 못한것이 아쉽고 처음 만드는 것이라서 코드의 최적화도 안된것이 아쉽다.
    반대로 처음 한 것 치고는 여러 상용엔진(유니티, 언리얼)등의 동작 방식을 보고 공부해서 구현해보는 것이(최적화의 차이는 엄청나겠지만)
    이런식으로 동작하지 않을까? 하고 어느 정도 비슷한 방향으로 만들어지는 것이 좋았다. (유니티 엔진을 많이 참고해서 만듬)
    마지막으로 시간상 코드가 체계적이지 못하고 조금 더럽게 짜진 것 같아서 아쉽지만, 교내 대회에 당당히 출품하고 여러 좋은 피드백을 얻을 수 있어서 좋은 경험이었다.

    +)싱글톤이 불필요하게 많이 사용되었다. 처음 공부하는 것에서 많음 부분들을 싱글톤으로 처리했는데 만들다보니 굳이? 라는 생각이 들정도로 과하게 사용된것 같다. 의존성이 너무 심해진다.
    +)malloc은 생성자를 호출하지 않기때문에 피해주자!
    +)dll로 분리 할것들이 보인다.
    +)마지막에 보스 몬스터의 공격 탄환인 Boomber를 잠시 Collider에서 제외 했었는데 이를 인지 하지 못하고 제출을 해서 실제로 보스 몬스터의 공격의 Collider가 동작하지 않는다.
    ->게임이 너무 어려워서 그런지 아니면 조작 방식의 문제였는지 아무도 몰라서 그나마 다행이지만 제작자로써 아쉬운 경험이였다... 버그는 확실하게 확인하고 가야한다는 것을 배울 수 있었다.

-------------------------------------------------------------------------------------------------
# 구조 설명
-------------------------------------------------------------------------------------------------
## Engine

### GameManager
  - 게임의 Core로 게임이 시작될 때 Init, 진행 되는 동안 FixedUpdata, Update, Render들을 호출해주고, 끝날때
    Finalize를 해주는 가장 큰 틀이다. 또한 한 사이클동안 Update와 Render가 이루어 지고 이 사이클마다 Message를
    받아 처리하기도 한다.
  - 모든 과정은 현재의 Scene에 있는 Object들을 가지고 진행 시켜준다.

### GameRender
  - 게임에서 오브젝트들을 Render를 도와주는 객체로 Front DC와 Back DC로 2중 버퍼로 이루어져 한 사이클 마다 BackDC에 각각의 오브젝트들이 그림을 찍고 이것을 한번에 FrontDC에 찍어서 FrontDC가 한번에 화면에 보이도록 출력함으로써 랜더링과정에서 자연스럽게 만들어 주는 역할을 한다.
  - WinAPI에서 Render는 CPU연산으로만 이루어지며 이에 맞는 Render로 만들어져있다.

### InputSystem
  - 이번 게임에서는 키보드와 Mouse의 인풋을 관리하주는 객체로 키보드의 몇몇 인풋과 마우스의 인풋을 배열로 관리하고 상태를 업데이트 해준다. 매 Update마다 실행이 되며 이전 Input의 값에 따라 현재 해당 KEY_STATE가 NONE, TAP, HOLD, AWAY인지 구분을 해주고 상태를 반환 할 수 있도록 만들었다.

### GameTime
  - WinAPI의 QueryPerformanceCounter와 QueryPerformanceFrequency를 사용하여 DeltaTime을 계산하여 시간을 얻는 객체로 Game의 모든 시간을 담당한다. 또한 TimeScale을 적용하여 시간에 배속도 가능하도록 제작하였다. 

### Scene & SceneManager
  - GameManager에서 사용되는 Scene들이 상속받는 부모 객체로 추상 클래스이다. 현재의 게임에서는 Scene안에 속한 모든 Object들을 관리하는 ObjectManager의 역할도 하고 있다. 이에 따라 FixedUpdata, Update, Render뿐만 아니라 Collider가 사용할 FinalUpdate와 사용이 끝날 Object를 삭제해줄 DestoryUpdate도 가지고 있다.
  - 만들어지는 곳은 처음 게임이 시작될떄 모든 Scene이 SceneManager에서 만들어지고 각Scene은 Enter와 Exit 함수를 통해 시작과 끝을 관리한다.
    (각각의 Scene이 만들어질때 Obeject들을 만들어 주고 끝날때 삭제 해준다. 또한 Collision의 Layer들을 어느 객체끼리 충동하는지도 설정해주고 해제해 준다.)
    (Game의 규모가 작아서 가능한 것 규모가 커지면 각각의 Scene이 들어 갈때 만들어지는 방식으로 할 경우도 있다고 생각함.)
  - ObjectManager역할도 하기 때문에 Object를 관리를 직접 만든 Vector를 사용 하여 관리하며 Object Type별로 Layer를 관리 한다.
  - 또한 각각의 오브젝트들이 서로를 가지고 있는 것을 방지하고자 Scene에서 Object를 찾아 그 Object를 리턴해주는 GetObjectSrc함수를 가진다.(Type과 name으로 원하는 오브젝트를 찾을 수 있음.)
  - GameManager에서 호출되어서 사용 하는 Object처리 들은 각 Object들의 상태에 따라 실행이 안될 수도 있다.(DeActive,Destroy 등)
  - SceneManager는 이러한 Scene을 관리하는 객체로 GameManager에서 SecneManager를 통해 현재Scene을 가져와서 각각의 기능들을 호출한다. 또한 Scene을 변환 할때 SceneMamager를 통해 Scene을 변환 해준다.

### PathManager
  - Resouce의 경로를 관리하는 객체로 현재 실행 파일 기점으로 Resource파일의 경로를 찾아준다.
  - GetCurrentDirectoryA라는 WinApi 함수를 통해 현재 경로를 가져오고 Release와 Debug에 상관없이 경로를 잡아주는 역할을 한다.

### ResourceManager
  - Resource들을 관리하는 객체로 이 게임에서는 Sound와 Texture를 관리한다.
  - PathManager를 통해 경로를 찾고 원하는 Texture를 직접만든 LinkedHashMap을 통해 관리한다. 처음 선언 되면 경로를 찾아 만들어서 Container에 넣어주고 같은 이름을 가진 Resource를 찾는 경우 LinkedHashMap에서 바로 가져와서 넣어준다.
  - Sound의 경우도 필요할때 찾아서 Texture와같이 넣어주도록 하였지만 이 게임에서는 처음 게임을 만들때 만들어준 Sound만 직접 배열로 관리해서 Fmod를 통해 Sound를 출력해준다. 소리를 위해 fmod.dll파일을 같이 경로에 넣어주어야 한다.
    
    #### Texture
      - WinAPI에서 제공되는 Render를 사용한 객체로 HDC, HBITMAP, BITMAP(Information)등을 가지고 있다.
      - Texture가 로드 될때 const char* 값으로 Key값을 받으며 ResourceManager에서 찾아서 Texture를 받아준다.
        (만들면서 생각한 방식이지만 굳이 각각의 Object가 각각의 Texture를 가질 필요가 있나? Texture의 정보만 가지고 ResourceManager에서 같은 texture를 반환해 주면 되지 않을까 라는 의문이 든다. -> 이 경우 메모리의 사용량은 적어지겠지만 모든 Render과정에서 ResouceManager에 정보를 받아와야 하는 cost가 더 큰것 같다. 현재의 방식은 처음 선언시에만 가져오면 되는 방식으로 게임의 속도적인 측면에서는 메모리를 조금 더 사용 하더라도 지금의 방식이 더 좋을 것 같다.)
      -  각각의 Texture들의 Render를 각각의 객체에서 직접 해준다. RenderSystem의 BackDC를 인자로 받아 출력해주며 기본적으로 WinAPI에서 제공되는 특정색을 제외하고 Dc에 출력하는 TransparentBlt와 투명도를 넣기 위해 AlphaBlend가 사용된다.
        +) AlphaBlend의 경우 WinAPI에서는 BitMap이 Alpha값을 가지지 않음으로 현재 BackDC에서 출력할 부분의 배경을 가져와 임시로 만든 DC에 배경을 BitBlt으로 출력해주고 그 위에 출력하고 싶은 Texture를 TransparentBlt로 출력하고 완성된 임시DC를 BackDC에 AlphaBlend로 출력을 해주는 방법을 사용 하고 있다.
         
    #### Sound
      - Fmod에서 제공되는 기능들을 담은 객체로 어떤 Sound가 있는지, 각각의 Sound에 대한 반복 여부나, 볼륨등을 관리한다.

### Object
  - Client에서 사용될 모든 Object들이 상속 받는 객체로 추상클래스이다. 처음 구상 하다모니 아쉬움이 많은 객체이다.
    (Componet형식으로 만들고 싶었지만 처음 설계를 잘못하는 바람에 시간관계상 바꾸지 못하였다.)
  - 기본적으로 이름, 타입, Transform, 상태(DeActive, Active, UnVisible, Destroy)를 가지며 오브젝트에 따라 Texture와 Collider를 Component처럼 가질 수 있도록 구상 하였지만 처음 만드는 과정에서 아쉬운 점으로 UI같이 Collider가 필요 없거나 보이지 않은 Object처럼 Texture가 필요없는 Object들이 필요없는 맴버를 가지는 점이 매우 불만족스럽다. 추후 엔진을 보강하면서 좀더 상세하게 상속을 나누어서 OOP를 준수하면서 만들어 질 수 있도록 세분화 할 계획이다.
  - 이에 따라 필요없는 함수들까지 상속되고 기능이 붙으면서 엔진에는 필요없는 반하드코딩이 강요되는 경우가 생겨서 매우 아쉽다.
  - 기능은 모든 오브젝트가 가져야할 FixedUpdate, Update가 있으며 불리 하고 싶은 내용들로 Texture를 가진 Oject는 Render, Collider를 갖는 객체면 Collider의 위치를 업데이트 시켜주는 FinalUpdate와 ComponetRender(디버그 모드에서 Collider를 Render시켜주는 함수), Collider이벤트를 처리해주는 OnCollision, OnCollisionEnter, OnCollisionExit 들을 가지고 있다.

    #### UI
      - Object를 상속받는 객체로 필요없는 Componet를 분리 하지 못한 것이 아쉽지만 UI를 구상할때면 이미 너무 많이 만들어버려서 시간안에 구조를 다시 고치기 힘들 것같아서 그냥 만들었다.
      - Object의 값을 그대로 가져오고 Default 생성자로 Type만 UI로 만들어 주는 역할을 한다.
      - 기존의 Object와 구분을 위해 만든 객체
        
    #### Button
      - UI를 상속받는 객체로 Input의 마우스의 정보를 받아와 ButtonStatus라는 상태를 구분짓는다.
      - ButtonStatus는 Default, EnterMouse, OnMouse, ExitMouse로 구분되며 마우스의 위치에 따라 Button의 상태를 구분지어 준다.

### Collider & ColliderManager
  - 오브젝트의 Componet로써 필요한 오브젝트만 만들어서 사용한다.
    서로의 충돌을 확인 하는 class로 AABB기법을 사용하여 충돌을 확인했다.
    또한 오브젝트에게 충돌상태를 알려주어야 함으로 오브젝트의 정보를 가지고 있다.
  - Manager같은 경우는 오브젝트에서 AddCollider라는 함수를 통해 오브젝트에서 추가를 한다.
    Vector로 관리하며 각각의 Collider들을 관리한다.
  - 각각의 충돌은 아무것도 충동하지 않은 상태, Enter, 충돌중, Exit총 4가지 상태로 구분되며 이것을 이번
    충돌과 이전 충돌을 비교해서 각각의 함수를 호출 하도록 만들었다.
    이전 충돌 상태는 각각의 collider가 고유의 id값을 가지고 union을 사용해서 2개의 UINT값으로 구성된 id값을
    합쳐 LONGLONG 형태의 키값으로 만들고 이것을 직접 만든 LinkedHashMap을 사용해서 관리하였다.
  - 또한 충돌되는 Layer들을 설정해서 충돌되는 Object들만 판정을 하도록 구분하였다.

    
### Random
  - 직접 만든 Random으로 사실 객체가 아니라 라이브러리 형식으로 만들어도 될 것을 처음 SingleTon패턴을 배우고 만들다보니 생각 없이 객체로 만들어진 경우이다. 실제 옛날 C언어의 Random을 참고 해서 만들었으며 사용 하기 편하게 만들었다.
  - 추가적으로 RandPercent라는 함수를 만들어서 확률을 가변 인자 또는 배열로 여러개 넣으면 그 확률에 맞게 Case로 반환 되는 함수를 제작하여서 확률들을 넣으면 그게 맞게 랜덤으로 Case가 반환 되어서 편하게 사용 할 수 있다.

### Transform
  - 주로 Object에 사용 되며, 직접만든 Vector3(3차원 벡터값)을 이용하여 Position과 Rotation, Scale, Offset을 가진다.

    #### Vector3
        - Vector3로 float형의 x, y, z값을 가지며 기본적인 연산들을 만들어서 적용 시켰다.
        - 모든 계산에 많이 사용 되며, Nomalization, Magnitude나 외적, 내적, 각도 계산등을 구현하여서 편하게 사용 할 수 있다.

### Container
  - 직접 만든 컨테이너들로써 DoubleLinkedList, LinkedHashMap, Queue, Vector을 구현 했으며 
  Templete과 Iterator를 처음 써봐서 좋은 경험이였다.(하지만 게임에서는 LinkedHashMap, Vector만 사용함)
-------------------------------------------------------------------------------------------------
## Client

### Object
  - Game에서 사용되는 Object들로 게임을 구성하는 것들이다.
    
    #### - BackGround
      - 배경 이미지를 가지고 Layer의 첫번쨰 순서로 가장먼저 Render가 되는 Object이다.

    #### - Player
      - Player오브젝트로 Player의 기능들을 가지고 있다.
      - 또한 스킬들의 정보와 상태의 정보, Player가 가지는 Weapon의 정보 또한 가지고 있다.
      - 종속 객체로 무기를 들고 있다.
      - 경험치에 따라 EventManager를 통해서 능력치가 바뀔 수 있도록 함수들을 가지고 있다.
      - Input에 맞게 움직임이 구현 되며 특정 Input에따라 스킬이나 Dash 등 여러 기능을 Action하도록 만들어져 있다. 
      - 스킬들의 쿨타임이나 지속 시간등에 대한 정보들을 가지고 있으며 그에 맞게 동작한다.
      - Weapon을 가지고 있으며 공격시 현재 들고 있는 무기의 Attack을 호출해준다.
      - 종속된 객체들의 Update나 Render을 같이 관리 해준다.
   
    #### - Weapon
      - 모든 무기들의 부모 객체로 추상 클래스이다.
      - 기본적인 무기들의 공통된 정보를 가지고 있다.
        (시간 관계상 하나의 무기만 추가하고 더 이상 진행하지 못함..)

          #### DogBowl
        - 투사체를 발사하는 형태의 무기로 총알을 ObjectPool형태로 가지고 있으며 Update, Render시 가지고 있는 객체를 같이 진행 해준다.
        - Player를 통해 능력치를 증가 시켜줄 수 있다.
        - Attack이 실행 되었을때 현제 순번에 있는 총알을 Active시켜주고 위치나 방향을 설정해준뒤 Update, Render될 수 있도록(Object Status를 Active해 주는 것) 해준다.
       
          #### Bone
          - DogBowl가 가지고 있는 총알로써 뼈다귀 형태를 취한다.
          - 생존시간과 방향 속도 등이 있으며 처음 세팅된 방향대로 일정시간동안 날라가면서 충돌검사를 진행한다.
          - 시간이 지나거나 몬스터와 충돌 시 DeActive상태로 바꾸어 줌으로써 비활성화만 시켜주고 다음 차례가 되었을때 다시 설정된 값으로 Active되는 방식으로 동작한다.

    #### - Monster
      - Monster들의 부모 객체로 추상 클래스이다.
      - Player와 Weapon과 충돌 판정이 이루어지며 각각의 Monster의 특성에 맞게 세분화 되어있다.
      - Player의 위치 정보를 파악해서 모든 Monster Object들이 사용하도록 Static의 형태로 저장한다.
      - 또한 사라질 때 DieUI를 생성하여 죽음을 직접적으로 보여주고 EventManager를 통해 죽을 때 마다 죽는 몬스터의 갯수도 파악한다.
      - 상태 또한 Destory 상태로 바꿔줌으로써 삭제를 진행 할 수 있도록 한다.

          #### Commom
        - 기본적인 몬스터로 플레이어의 위치를 쫓아 움직이는 몬스터이다.
          
          #### Soldier
        - 중간 정도의 몬스터로 이동방식은 Common이랑 동일 하나 갑옷이 있어서 체력의 3분의 1이하로 남으면 갑옷이 벗겨져 이동 속도가 느려지고 N초 동안 피격 당하지 않으면 체력이 회복되고 원래의 속도로 이동한다.
          
          #### Hero
        - 몬스터의 상위 객체로 이동방식이 N초 동안 기를 모아 가속도의 방식으로 점점빨라지는 형태의 대쉬를 한다.
        - 대쉬는 방향은 대쉬가 시작될 지점의 Player의 위치로 N초 동안 점점 빨라지는 방식으로 달려간다.
        - 대쉬 -> 기모으기 -> 대쉬의 방복으로 움직임이 이루어 진다.
          
          #### King
        - 보스 몬스터로 이동은 플레이러를 추적하지만 이동 -> 공격의 패턴으로 움직인다.
        - Boomer라는 하위 자폭병을 소환하여 날리는 방식으로 공격을 한다.
            #### Boomer
          - King의 탄환 개념으로 1초 동안 보스 몬스터의 특정 범위 안에서 소환되어서 플레이어의 소환 될 시점의 위치로 달려간다.
          - N초후 사라지는 탄환의 일종이다.
    #### - FactoryMonster
      - Monster들을 실제 Stage에서 관리 해주는 Factory 형태의 객체 이며 몬스터들이 특정 시간에 따라 소환 될 수 있도록 한다.
      - 생성되는 위치나 범위, 시간, 생성되는 객체의 종류, 확률 등을 관리해준다.


### Scene
  - Scene을 상속받아서 사용되는 실제 게임 화면들이다.
    
    ### Start
    ####  - SceneStart:
    - 시작시 Scene으로 처음 게임이 시작될시 보여지는 Scene이다.
    - BGM과 여러 UI들과 버튼으로 구성되어 있다.
          
    ### Stage1
    #### - SceneStage01:
    - 메인 게임 화면이며 뱀파이서 서바이벌 형식의 게임 화면으로 주된 오브젝트들 만들과 관리하는 곳이다.
    = 이 씬에서 끝난 정보를 바탕으로 Data를 만들어서 다음 씬을 결정 해 준다.
    - BGM과 여러 UI, Object들로 구성되어 있다.
      
    #### - EvnetManager:
    -Stage1의 이벤트를 담당하는 객체로 플레이어의 경험치를 가지고 다 찼을때 5가지 증강을 화면에 보여주면서 선택하면 Player의 능력치를 수정할 수 있도록 관리 해주는 Client의 매니져 이다.
    - Player 객체를 가지고 있으며 Player의 함수를 호출하여서 Player의 능력치를 간접적으로 수정 할 수 있다.
    - 증강의 표시는 버튼의 형식으로 누르면 적용되는 방식으로 만들었다.
          
    ### End
    #### - SceneWin:
    - 승리시 변경되는 화면으로 게임이 끝난 시점의 시간과 Kill, 보스Kill Data를 가져와서 표시해준다.
  
    #### - SceneLose:
    - 패배시 변경되는 화면으로 게임이 끝난 시점의 시간과 Kill Data를 가져와서 표시해준다.


### SharedData
  - Scene이 전환 될때 공유하는 데이터의 객체로 Json과 같은 데이터를 사용 하여 값을 저장 후 전달 하고 싶었으나 Json을 공부 하지 못한 관계로 임시로 전달할 데이터의 형태를 만들어서 Scene이 전활 될때 데이터를 옮기는 방법을 사용 하였다.


### Define
  - 게임의 Object Type(Layer)이나 Scene의 갯수 및 Scene들 Sound의 종류나 Channel, FinxedUpdateTime이나 DebugFlag, Screen의 높이나 넓이 등이 정의 되어 있는 헤더파일이다.


### WinApp
  - WinAPI에서 제공하는 화면 인스턴스를 만들고 설정하는 main이 있는 파일로 여기서 초기 설정 후에 GamaManager를 호출 하여 게임의 초기 설정, 실행, 끝을 해주는 곳이다.

