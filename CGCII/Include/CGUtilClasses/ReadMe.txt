==============================================================================
                                                                             
                        Cho sanghyun's Game Classes II                       
                          Ver 8.0 / Release 2015.01.05                         
                                                                             
                                Util Classes
                                                                             
                                                                             
                                                                             
                                                                             
    This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr           
    Best for Game Developement and Optimized for Game Developement.          
                                                                             
                     (C) 2008 CGCIII All right reserved.                     
                             http://www.CGCII.co.kr                          
                                                                             
==============================================================================

1. CGCII Util Classes
	 ���������� ���α׷��� �����ϴ� ������ Thread�� �� ���� ���� �� ���ۿ� 
	���õ� class���� �����Ѵ�.
	
	 �⺻���� Thread�� ��� �� ������ ���� class�� ���� Thread�� ������ ȿ������
	����� ���� class���� �����Ѵ�.
	
	 �� �� Thread�� �۾��� ȿ�������� �и��Ͽ� ó���ϱ� ���� class���� �����Ǹ�
	Excetionó���� ���� ���� ���� �����ȴ�.

	
2. CGCII Util Classes�� �ֿ� ���� ��ҵ�

	1) APIs (Low level classes)
	    Thread�ǿ� ���õ� �Ͱ� IOCP�� ���õ� API������ class�� ������ �ش�.
	   
	   - Thread					���������� ����� ����ũ���� vector
	   - ThreadPool				�Ϲ����� vector
	   - IOCompletionPort		�Ϲ����� list (circulare linked list)
	
	2) Concurrency-Division Load balancing Support.
	    
	   - Executor				Executor�� �����ϴ� ������.(�Ϲ������� Thread)
	   - Excutor with IOCP		IOCP�� �̿��Ͽ� ������ Executor
	   - Completr				Executor�� ����Ǵ� ������ ����.


	3) Exception classes
	   - ICGReferenceable		Count�� 0�� �Ǹ� OnFinalRelease/ProcessDispose
	                            �Լ��� ȣ�����ִ� Class
	   - ReferenceCountWaiter	����ȭ�� ���� class
	   - Exception classes		Throw�� ���� class��...


	���� �ڼ��� ������ Source�� �׿� �پ� �ִ� �������� �ּ��� �����ϱ� �ٶ���.


3. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	�� ����Ʈ������ ��� ���۱��� CGCIII�� �ֽ��ϴ�.

