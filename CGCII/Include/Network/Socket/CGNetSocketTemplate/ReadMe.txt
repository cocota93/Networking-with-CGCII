==============================================================================
                                                                            
                      Cho sanghyun's Game Classes II                       
                       Ver 8.0 / Release 2015.01.05                         
                                                                           
                         Network Socket Templates
                                                                            
                                                                            
                                                                            
   This Program is programmed by Cho SangHyun. sangducks@gamil.com           
   Best for Game Developement and Optimized for Game Developement.          
                                                                            
                 ⓒ 2016 Cho Sanghyun All right reserved                    
                            http://www.CGCII.co.kr                          
                                                                            
==============================================================================

1. CGCII Network Socket Templates
    CGCII의 Socket은 몇개의 계층으로 구분되어 설계되어 있으며 필요에 따라 조합하여
   쓸수 있다
    Socket Template Classes에서는 자주 사용하는 Socket의 형태를 미리 조합해 놓은
   것들이다.
    모든 Socket은 단순한 Socket Component들의 상속을 통한조합만으로 구성되어 있으며 
   Template으로 만들어져 있다.
   	
2.  CGCII Network Socket Templates의 주요 구성 요소들

	1) Socket
	   접속을 위한 소켓으로 TCP/UDP에 모두 사용되고 Server/Client에 모두 사용된다.
	   Socket은 필요에 따라 여러 레이어를 조합하여 사용할수 있다. 
	   그중 가장 많이 사용되는 형태를 설정해 놓은 것이다.

	   - CGNet::Socket::CTCP<THEAD>	
	     가장 많이 사용하는 기본적인 TCP 소켓
	   - CGNet::Socket::CTCPNoGather<THEAD>
	     전송시 모아서 전송하기 기능 없는 매우 단순한 전송기능을 가진 소켓.
		 동작구조가 매우 간단한 대신 전송성능이 떨어지는 단점이 있다.
		 전송이 많이 않은 곳에서는 유용할 수 있다.
	   - CGNet::Socket::CTCPQueue<THEAD>
	     송신처리와 송센의 메시지 처리를 분리해서 처리하는 형태로 기본형태보다
		 전송 성능이 더 좋을 수 있다. 하지만 기본 동작에 더 많은 부하가 들기 때문에
		 간단한 전송에서는 필요이상의 부하가 들 가능성이 있으며 메모리를 많이 사용한다.
		 특별히 매우 높은 수신 성능이 필요할 경우 사용된다.

	   - CGNet::Socket::CTCPServer<THEAD>
		 서버용으로 세팅된 TCP 소켓
		 기본형 소켓에 일정 시간 지나면 자동적으로 접속 종료처리 등을 하는 기능이 추가된 형태다.
		 서버일 경우에도 기본형이 가장 많이 사용되며 이 형태는 필요한 경우에만 사용한다.
	   - CGNet::Socket::CTCPServerNoGather<THEAD>
	     CGNet::Socket::CTCPServer<THEAD>에 송신시 모아서 전송하는 기능만 제거한 것으로
		 서버입장에서 송신이 매우 드물게 일어나는 채팅서비스나 메신저 서비스 같은 경우
		 많이 사용된다.

	   - CGNet::Socket::CTCPFixed<THEAD>
	     고정된 메시지를 가진 소켓을 말한다.
	   - CGNet::Socket::CTCPFixedNoGather<THEAD>
	     CGNet::Socket::CTCPFixed<THEAD>에서 모아서 전송하기 기능만 제거한 것이다.
	   - CGNet::Socket::CTCPFixedQueue<THEAD>
	     CGNet::Socket::CTCPFixed<THEAD>에서 수신처리 성능을 향상시킨 것이다.

	   - CGNet::Socket::CTCPClient<THEAD>
	     클라이언트용 소켓으로 Connect 기능이 추가된 소켓이다.
	   - CGNet::Socket::CTCPClientReconnect<THEAD>
	     CGNet::Socket::CTCPClient<THEAD>에 접속 종료시 재접속 시도 기능을 추가한 소켓이다.

	   - CGNet::Socket::CUDP<T>
	     UDP용 소켓이다.
	   - CGNet::Socket::CUDPResend<T>
	     CGNet::Socket::CUDP<T>에 송신 시 ACK를 받을 때까지 재전송을 수행하는 기능을 추가한 것이다.

	2) Acceptor
	   Listen()을 하여 TCP접속을 받아들이는 객체로 서버에 사용된다.
	   - CGNet::CAcceptor<TSOCKET>
	   
	3) Connector
	   Connect()로 대규모 접속을 시도하는 Client 객체이다.
	   	

	보다 자세한 내용은 Source와 그에 붙어 있는 세부적인 주석을 참조하기 바란다.


3. Contact us
	@Mail: sangduck@cgcii.co.kr

	@Web: www.CGCII.co.kr
	
	본 소프트웨어의 모든 저작권은 '조상현(Cho Sanghyun)'에 있습니다.
