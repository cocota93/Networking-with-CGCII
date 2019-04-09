==============================================================================
                                                                            
                       Cho sanghyun's Game Classes II                       
                         Ver 4.0 / Bulid 2009.05.24                         
                                                                            
                               CG Data Classes
                                                                            
                                                                            
                                                                            
   This Program is programmed by Cho SangHyun. sangducks@gmail.com
   Best for Game Developement and Optimized for Game Developement.          
                                                                            
                    (C) 2008 CGLabs All right reserved.                    
                           http://www.CGCII.co.kr
                                                                            
==============================================================================

1. CGDContainers Classes
	 게임 제작에 필요한 고성능 자료구조와 편리한 사용을 위한 template class들의
	모음이다.
	 기존에도 비슷한 기능을 수행하는 다양한 형태의 라이브러리들이 존재했지만
	범용성을 목적으로 하기 때문에 고성능을 요구하는 곳에는 희생이 따랐다.
	
	 CGData Classes는 게임의 제작이 적합한 다양한 요구사항과 기능들을 가지는
    클래스를 제공하고 있다.
    
     예를 들면 Multi-Thread에서 안정된 동작을 수행하기 위해 Thread-safe기능이 
    필요한데 기존의 것을 사용하기 위해서는 Critical section를 통해 Thread-safe를
    외부에서 제공해야 했기 때문에 성능이 떨어지는 부분이 있다.
     하지만 CGData Classes는 Lock Free 알고리즘 등을 사용하여 다양한 형태로
    고성능의 클래스들을 제공하고 있다.

	
2. CGDContainers Classes의 주요 구성 요소들

	1) Sequencial Container
	   - array<T, N>			지역변수를 사용한 고정크기의 vector
	   - vector<T>				일반적인 vector
	   - list<T>				일반적인 list (circulare linked list)
	   - circular<T>			원형 자료구조를 가진 vector
	   - slist					단방향 linked list
	   
	2) Associative Container
	   - map<T>					rea-balck tree로 구현한 Container
	
	3) Thread-safe classes
	   - 
	   - locked_queue			Critical Section을 사용한 queue
	   - locked_stack			Critical Section을 사용한 stack
	   - interlocked_coutner	Interlocked함수를 사용한 카운터
	   - Interlocked_self_stack		Interlockedpush/pop함수를 사용한 stack
	   - lockfree_self_stack			CAS lock-free를 사용한 stack
	   - lockfree_queue			CAS lock-free를 사용한 queue
	   - tls_stack				TLS를 사용한 stack

	4) 편리성을 위한 Classes
	   - auto_delete			파괴시 객체를 자동으로 지워주는 class
	   - shared_object			파괴시 객체의 reference count를 감소해주는 class
	   - auto_criticalsection	생성시 Enter를 수행하고 파괴시 Leave를 수행하는 class
	   - release				파괴시 0검사하지 않고 delete를 호출해주는 함수.

	보다 자세한 내용은 Source와 그에 붙어 있는 세부적인 주석을 참조하기 바란다.


3. Contact us
	@Mail: sangducks@cgcii.co.kr

	@Site: www.CGCII.co.kr
	
	본 소프트웨어의 모든 저작권은 CGLabs에 있습니다.

