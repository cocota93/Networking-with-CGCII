//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                               MFC Controls                                *
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
// ----------------------------------------------------------------------------
//
// CCGStaticGraph
//
// 1. CCGStaticGraph란!
//    1) Graph를 그려주는 Library이다.
//    2) AddGraph를 통해 원하는 수만큼의 Graph를 동적으로 추가가 가능하다.
//       - 이때 line의 색깔과 vertical scale을 설정한다.
//       - 이때 Graph Index를 얻을 수 있다.
//       - 이 Graph Index를 Remove를 하면 변할 수도 있다.
//    3) Vertical/Horizontal Scale을 설정할 수 있다.
//    4) AppendData를 통해 데이타를 추가할 수 있다.
//    5) Scroll함수를 통해 출력되는 그래프를 옮길 수 있다.
//
//
// ----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CCGStaticGraph : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CStatic		// Static을  상속받은 것임.
{
// ****************************************************************************
// Constructor/Destructors
// ----------------------------------------------------------------------------
public:
			CCGStaticGraph(int _DataSize=4096, int _GridUnit=10);
	virtual ~CCGStaticGraph();


// ****************************************************************************
// Public) 
// ----------------------------------------------------------------------------
public:
			int					AddGraph(int _scaleVertical, COLORREF _colorLine);
			void				RemoveGraph(int _idxGraph);

			void				EnableGraph(int _Index, bool _bStatus=true);

			int					GetHorizontalScale() const				{	return m_scaleHorizontal;}
			void				SetHorizontalScale(int _Scale)			{	m_scaleHorizontal=_Scale; InvalidateRect(nullptr);}

			void				SetVerticalScale(int _Scale);
			void				SetVerticalScale(int _idxGraph, int _Scale);
			int					GetVerticalScale(int _idxGraph) const;

			int					GetGridUnit() const						{	return m_iGridUnit;}
			void				SetGridUnit(int _GridUnit)				{	m_iGridUnit=_GridUnit;}

			int					GetDataSize() const						{	return m_iDataSize;}

			void				AppendData(int _idxGraph, int _Data);

			void				Scroll(int p_iScroll);

			void				AddTargetWnd(CWnd* _pWnd);
			void				RemoveTargetWnd(CWnd* _pWnd);


// ****************************************************************************
// Implementation)
// ----------------------------------------------------------------------------
protected:
// MFC)
	DECLARE_DYNAMIC(CCGStaticGraph)
	DECLARE_MESSAGE_MAP()

	virtual void				DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)		{}
	afx_msg	void				OnPaint();
	afx_msg	void				OnDestroy();

// 1) Background Info
private:
			CBrush				m_brushBackground;
			CPen				m_penGrid;
			COLORREF			m_colorGrid;

			CBrush				m_brushBackground_Disabled;
			CPen				m_penGrid_Disabled;

			int					m_scaleHorizontal;
			uint32_t			m_positionView;

			int					m_iDataSize;
			int					m_iGridUnit;

			CDC					m_dcBack;

			class				CGraph;
			vector<CGraph*>		m_vectorGraph;

			circular_list<CWnd*> m_listWndTarget;

			void				SendMessageToTarget(WPARAM _Message, LPARAM _lParam);
};
