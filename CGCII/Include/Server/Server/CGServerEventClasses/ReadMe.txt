==============================================================================
                                                                             
                        Cho sanghyun's Game Classes II                       
                         Ver 8.0 / Release 2015.01.05                         
                                                                             
                             Server Event Classes                             
                                                                             
                                                                             
                                                                             
                                                                             
    This Program is programmed by Cho SangHyun. sangducks@gamil.com           
    Best for Game Developement and Optimized for Game Developement.          
                                                                             
                  �� 2016 Cho Sanghyun All right reserved                     
                             http://www.CGCII.co.kr
                                                                             
==============================================================================

1. CGCII Server Event Classes

  ���� � �� Ư���� �ð� Ȥ�� �����ð� ���� �����ؾ��ϴ� Event�� ���� ��� �̸�
 ���� Ŭ�������� �ǹ��Ѵ�.
  �Ϲ� ������ ���񽺸� ��� �� Ư�� �ð��� ������ ������Ű�ų� ����� �ϰų� 
 �����ڸ� �����ؼ� ����������Ű�ų� ��� Ư���� �ð� Ȥ�� ���� �ð����� ����Ǿ��
 �ϴ� ���� �ʿ��� ������ ���� ���ȴ�.

   Event Classes���� ũ�� �ѹ��� ����Ǵ� ��ü, �ݺ������� ����Ǵ� ��ü, ���۰�
  ���� ������ ���� ����Ǵ� ��ü, ������ ������ �ð����� ����Ǿ�� �ϴ� ��ü ����
  �����Ѵ�.
   �ʿ信 ���� �ش� ��ü�� ���ӹ޾� ������ �ϰų� �����Ͽ� Event Manager�� ���
  �����ν� ����ǰ� �ȴ�.
  
2. CGEvnet::Manager�� ICGEventObject Ŭ����
    CGEvent::Manager�� EventObject�� �����Ű�� ���հ����ڷμ� ������ Event Object��
   �ݵ�� Event Manger�� ��ϵǾ�� ����ȴ�.
    Event Manager�� �̱��� ��ü�� ���� ������ �ʿ� ���� ���������� �����ϰ� �ϳ���
   �����Ǿ� �ִ�.

3. CGEvent::Object Ŭ������

   1) ���ѹ� ����
      - CGEvent::Object::COnce
      - CGEvent::Object::COnceFunction<TFUNCTION>
   2) �ݺ������� ����
      - CGEvent::Object::CIteration
      - CGEvent::Object::CIterationFunction<TFUNCTION>

   3) ���۰� ������ ������ ����
      - CGEvent::Object::CStartEnd
      - CGEvent::Object::CStartEndFunction<TFUNCTION>

   4) ���۽����� �������� ����Ǹ� �� ���� �ð����� �����ð����� ����
      - CGEvent::Object::CStartIterationEnd
      - CGEvent::Object::CStartIterationEndFunction<TFUNCTION>

4. CGEvent Schedule ���� Ŭ������ ���
   Schedule�� ���� ���� ������ �ϳ��� ��ü���� ������ �� �ֵ��� ����Ǿ���.
   �� ���� Event ��ü�� �޸� ���� CSchedule ��ü�� �����Ͽ� �̸� Event ��ü��
   ����Ͽ� ����ϵ��� �Ǿ� �ִ�.

   1) CGEvent::Object::CSchedule Ŭ����

   2) CGEvent::Object::CScheduleFunction Ŭ����

   3) CGEvent::Schedule Ŭ����
      CGEvent Schedule��ü�� ��ϵǾ� ���Ǵ� ��ü�̴�.
	  ������ �ʿ��� ���� �����ϰ� �̸� Event Schedule ��ü�� ����Ѵ�.
      - CGEvent::Schedule::CFunction
      - CGEvent::Schedule::CLambda
      - CGEvent::Schedule::CMemberFunction<TCLASS>

5. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	�� ����Ʈ������ ��� ���۱��� '������(Cho Sanghyun)'�� �ֽ��ϴ�.

