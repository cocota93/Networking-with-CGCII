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
// ICGLogFilter
//
// 1. ICGLogFilter��~
//    ������ Log�� ����ϰų� �����ϱ� ���� Filtering�� �����ϴ� Class�̴�.
//    �Ϲ������� CCGLogFile�̳� Server MFC Control�� CCGChildLogView� ���ȴ�.
//
// 2. ICGLogFilter�� �ٽ� �Լ�
//		1) Filtering �Լ�
//
//         bool ProcessFiltering(const CGMSG_LOG& _Msg) PURE;
//
//         ���������Լ��� ProcessFiltering�� �������Ͽ� Log�� ���� �ʿ䰡 �ִ�
//         ��Ȳ�� true�� ���ϵǾ� ������ �Լ��� ������ �ָ� �ȴ�.
//
//-----------------------------------------------------------------------------
class CCGLogFilterDefault :
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	virtual public				ICGLogFilter
{
// ****************************************************************************
// Constructor/Destructor)
// ----------------------------------------------------------------------------
public:
			CCGLogFilterDefault();
	virtual ~CCGLogFilterDefault();


// ****************************************************************************
// Definitions) 
// ----------------------------------------------------------------------------
public:
	struct FILTER_INFO
	{
	public:
		bool		bEnable;

		bool		bLimitLevel;
		int			iRangeLevel_Min;
		int			iRangeLevel_Max;

		bool		bLimitSource;
		int			iRangeSource_Min;
		int			iRangeSource_Max;

		bool		bLimitDestination;
		int			iRangeDestination_Min;
		int			iRangeDestination_Max;

		bool		bLimitLocation;
		int			iRangeLocation_Min;
		int			iRangeLocation_Max;

	public:
		FILTER_INFO();
	};


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			void				SetFilterInfo(_In_ eLOG_TYPE _LogType, _In_ const FILTER_INFO& p_eFilterInfo);
			FILTER_INFO			GetFilterInfo(_In_ eLOG_TYPE _LogType) const;

			void				EnableLog(_In_ eLOG_TYPE _LogType, _In_ bool _bEnable=true);
			void				DisableLog(_In_ eLOG_TYPE _LogType);

			void				EnableLevelRange(_In_ eLOG_TYPE _LogType, _In_ bool _bEnable=true);
			void				DisableLevelRange(_In_ eLOG_TYPE _LogType);
			void				SetLevelRange(_In_ eLOG_TYPE _LogType, _In_ int _iMin, _In_ int _Max);

			void				EnableSourceRange(_In_ eLOG_TYPE _LogType, _In_ bool _bEnable=true);
			void				DisableSourceRange(_In_ eLOG_TYPE _LogType);
			void				SetSourceRange(_In_ eLOG_TYPE _LogType, _In_ int _iMin, _In_ int _Max);
			void				SetDestinationRange(_In_ eLOG_TYPE _LogType, _In_ int _iMin, _In_ int _Max);

			void				EnableDestinationRange(_In_ eLOG_TYPE _LogType, _In_ bool _bEnable=true);
			void				DisableDestinationRange(_In_ eLOG_TYPE _LogType);

			void				EnableLocationRange(_In_ eLOG_TYPE _LogType, _In_ bool _bEnable=true);
			void				DisableLocationRange(_In_ eLOG_TYPE _LogType);
			void				SetLocationRange(_In_ eLOG_TYPE _LogType, _In_ int _iMin, _In_ int _Max);


// ****************************************************************************
// Framework) 
// ----------------------------------------------------------------------------
public:
	virtual bool				ProcessFiltering(_In_ const CGLOG_RECORD* _pLogRecord) override;


// ****************************************************************************
// Implementation) 
// ----------------------------------------------------------------------------
protected:
			FILTER_INFO			m_filterInfo[static_cast<int>(eLOG_TYPE::MAX)];
			

};

