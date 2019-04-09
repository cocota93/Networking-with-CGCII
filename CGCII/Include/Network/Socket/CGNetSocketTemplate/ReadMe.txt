==============================================================================
                                                                            
                      Cho sanghyun's Game Classes II                       
                       Ver 8.0 / Release 2015.01.05                         
                                                                           
                         Network Socket Templates
                                                                            
                                                                            
                                                                            
   This Program is programmed by Cho SangHyun. sangducks@gamil.com           
   Best for Game Developement and Optimized for Game Developement.          
                                                                            
                 �� 2016 Cho Sanghyun All right reserved                    
                            http://www.CGCII.co.kr                          
                                                                            
==============================================================================

1. CGCII Network Socket Templates
    CGCII�� Socket�� ��� �������� ���еǾ� ����Ǿ� ������ �ʿ信 ���� �����Ͽ�
   ���� �ִ�
    Socket Template Classes������ ���� ����ϴ� Socket�� ���¸� �̸� ������ ����
   �͵��̴�.
    ��� Socket�� �ܼ��� Socket Component���� ����� �������ո����� �����Ǿ� ������ 
   Template���� ������� �ִ�.
   	
2.  CGCII Network Socket Templates�� �ֿ� ���� ��ҵ�

	1) Socket
	   ������ ���� �������� TCP/UDP�� ��� ���ǰ� Server/Client�� ��� ���ȴ�.
	   Socket�� �ʿ信 ���� ���� ���̾ �����Ͽ� ����Ҽ� �ִ�. 
	   ���� ���� ���� ���Ǵ� ���¸� ������ ���� ���̴�.

	   - CGNet::Socket::CTCP<THEAD>	
	     ���� ���� ����ϴ� �⺻���� TCP ����
	   - CGNet::Socket::CTCPNoGather<THEAD>
	     ���۽� ��Ƽ� �����ϱ� ��� ���� �ſ� �ܼ��� ���۱���� ���� ����.
		 ���۱����� �ſ� ������ ��� ���ۼ����� �������� ������ �ִ�.
		 ������ ���� ���� �������� ������ �� �ִ�.
	   - CGNet::Socket::CTCPQueue<THEAD>
	     �۽�ó���� �ۼ��� �޽��� ó���� �и��ؼ� ó���ϴ� ���·� �⺻���º���
		 ���� ������ �� ���� �� �ִ�. ������ �⺻ ���ۿ� �� ���� ���ϰ� ��� ������
		 ������ ���ۿ����� �ʿ��̻��� ���ϰ� �� ���ɼ��� ������ �޸𸮸� ���� ����Ѵ�.
		 Ư���� �ſ� ���� ���� ������ �ʿ��� ��� ���ȴ�.

	   - CGNet::Socket::CTCPServer<THEAD>
		 ���������� ���õ� TCP ����
		 �⺻�� ���Ͽ� ���� �ð� ������ �ڵ������� ���� ����ó�� ���� �ϴ� ����� �߰��� ���´�.
		 ������ ��쿡�� �⺻���� ���� ���� ���Ǹ� �� ���´� �ʿ��� ��쿡�� ����Ѵ�.
	   - CGNet::Socket::CTCPServerNoGather<THEAD>
	     CGNet::Socket::CTCPServer<THEAD>�� �۽Ž� ��Ƽ� �����ϴ� ��ɸ� ������ ������
		 �������忡�� �۽��� �ſ� �幰�� �Ͼ�� ä�ü��񽺳� �޽��� ���� ���� ���
		 ���� ���ȴ�.

	   - CGNet::Socket::CTCPFixed<THEAD>
	     ������ �޽����� ���� ������ ���Ѵ�.
	   - CGNet::Socket::CTCPFixedNoGather<THEAD>
	     CGNet::Socket::CTCPFixed<THEAD>���� ��Ƽ� �����ϱ� ��ɸ� ������ ���̴�.
	   - CGNet::Socket::CTCPFixedQueue<THEAD>
	     CGNet::Socket::CTCPFixed<THEAD>���� ����ó�� ������ ����Ų ���̴�.

	   - CGNet::Socket::CTCPClient<THEAD>
	     Ŭ���̾�Ʈ�� �������� Connect ����� �߰��� �����̴�.
	   - CGNet::Socket::CTCPClientReconnect<THEAD>
	     CGNet::Socket::CTCPClient<THEAD>�� ���� ����� ������ �õ� ����� �߰��� �����̴�.

	   - CGNet::Socket::CUDP<T>
	     UDP�� �����̴�.
	   - CGNet::Socket::CUDPResend<T>
	     CGNet::Socket::CUDP<T>�� �۽� �� ACK�� ���� ������ �������� �����ϴ� ����� �߰��� ���̴�.

	2) Acceptor
	   Listen()�� �Ͽ� TCP������ �޾Ƶ��̴� ��ü�� ������ ���ȴ�.
	   - CGNet::CAcceptor<TSOCKET>
	   
	3) Connector
	   Connect()�� ��Ը� ������ �õ��ϴ� Client ��ü�̴�.
	   	

	���� �ڼ��� ������ Source�� �׿� �پ� �ִ� �������� �ּ��� �����ϱ� �ٶ���.


3. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	�� ����Ʈ������ ��� ���۱��� '������(Cho Sanghyun)'�� �ֽ��ϴ�.
