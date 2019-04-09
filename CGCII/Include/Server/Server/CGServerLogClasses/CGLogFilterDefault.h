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
//*                 ⓒ 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// ICGLogFilter
//
// 1. ICGLogFilter은~
//    설정된 Log만 출력하거나 저장하기 위해 Filtering을 수행하는 Class이다.
//    일반적으로 CCGLogFile이나 Server MFC Control의 CCGChildLogView등에 사용된다.
//
// 2. ICGLogFilter의 핵심 함수
//		1) Filtering 함수
//
//         bool ProcessFiltering(const CGMSG_LOG& _Msg) PURE;
//
//         순수가상함수인 ProcessFiltering을 재정의하여 Log를 남길 필요가 있는
//         상황에 true가 리턴되어 오도록 함수를 정의해 주면 된다.
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

