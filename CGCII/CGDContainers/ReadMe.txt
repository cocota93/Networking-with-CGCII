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
	 ���� ���ۿ� �ʿ��� ���� �ڷᱸ���� ���� ����� ���� template class����
	�����̴�.
	 �������� ����� ����� �����ϴ� �پ��� ������ ���̺귯������ ����������
	���뼺�� �������� �ϱ� ������ ������ �䱸�ϴ� ������ ����� ������.
	
	 CGData Classes�� ������ ������ ������ �پ��� �䱸���װ� ��ɵ��� ������
    Ŭ������ �����ϰ� �ִ�.
    
     ���� ��� Multi-Thread���� ������ ������ �����ϱ� ���� Thread-safe����� 
    �ʿ��ѵ� ������ ���� ����ϱ� ���ؼ��� Critical section�� ���� Thread-safe��
    �ܺο��� �����ؾ� �߱� ������ ������ �������� �κ��� �ִ�.
     ������ CGData Classes�� Lock Free �˰��� ���� ����Ͽ� �پ��� ���·�
    ������ Ŭ�������� �����ϰ� �ִ�.

	
2. CGDContainers Classes�� �ֿ� ���� ��ҵ�

	1) Sequencial Container
	   - array<T, N>			���������� ����� ����ũ���� vector
	   - vector<T>				�Ϲ����� vector
	   - list<T>				�Ϲ����� list (circulare linked list)
	   - circular<T>			���� �ڷᱸ���� ���� vector
	   - slist					�ܹ��� linked list
	   
	2) Associative Container
	   - map<T>					rea-balck tree�� ������ Container
	
	3) Thread-safe classes
	   - 
	   - locked_queue			Critical Section�� ����� queue
	   - locked_stack			Critical Section�� ����� stack
	   - interlocked_coutner	Interlocked�Լ��� ����� ī����
	   - Interlocked_self_stack		Interlockedpush/pop�Լ��� ����� stack
	   - lockfree_self_stack			CAS lock-free�� ����� stack
	   - lockfree_queue			CAS lock-free�� ����� queue
	   - tls_stack				TLS�� ����� stack

	4) ������ ���� Classes
	   - auto_delete			�ı��� ��ü�� �ڵ����� �����ִ� class
	   - shared_object			�ı��� ��ü�� reference count�� �������ִ� class
	   - auto_criticalsection	������ Enter�� �����ϰ� �ı��� Leave�� �����ϴ� class
	   - release				�ı��� 0�˻����� �ʰ� delete�� ȣ�����ִ� �Լ�.

	���� �ڼ��� ������ Source�� �׿� �پ� �ִ� �������� �ּ��� �����ϱ� �ٶ���.


3. Contact us
	@Mail: sangducks@cgcii.co.kr

	@Site: www.CGCII.co.kr
	
	�� ����Ʈ������ ��� ���۱��� CGLabs�� �ֽ��ϴ�.

