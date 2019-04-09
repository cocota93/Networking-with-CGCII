//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                            Server Log Classes                             *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CCGLogHub
//
// 1. CCGLogHub��~
//    �ϳ��� Log�� ���� ���� Log�� ����� ���� Log�� Hub ��ü��� �Ҽ� �ִ�.
//    �پ��� ���¿� ������ Log��ü�� CCGLogHub ��ü�� RegisterMessageable()
//    �Լ��� ����� ������ CCGLogHub ��ü�� Log�� ���޵Ǿ��� �� ��� ��ϵ�
//    Log ��ü�鿡�� �޽����� �����Ѵ�.
//
// 2. Log�� ����
//		0) Date/Time	Log�� ���� �ð��̴�.(�ڵ����)
//		1) Type			Log�� �����̴�. Errror, Progress, Warning, Info, ...
//	    2) Level		Log�� �߿䵵�̴�.
//		3) Message		���� Log Message�� �ǹ��Ѵ�.
//
//-----------------------------------------------------------------------------
class CCGLogHub : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						NCGDispatchable,
	public						NCGObjectState,
	public						NCGInitializable,
	virtual public				ICGMessageable
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGLogHub();
	virtual ~CCGLogHub();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
	// 1) Filtering
			void				SetFilter(_In_ ICGLogFilter* _pLogFilter){	m_pLogFilter=_pLogFilter;}
			CGPTR<ICGLogFilter>	GetFilter() const						{	return m_pLogFilter;}


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
	// 1) Filters
			CGPTR<ICGLogFilter>	m_pLogFilter;

	// 2) Process Message
	virtual	int					ProcessMessage(CGMSG& _Msg) override;

	//! @brief �ڽ� ����� �ı� ó���� ����� �� ó���� ������ �����ϴ� �Լ� @param _MSg �ʱ�Ȱ �� �� ���޵� �޽���
	virtual void				_ProcessDestroy() override;
};
