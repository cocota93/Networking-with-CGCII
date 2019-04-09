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
//*                 �� 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
// ----------------------------------------------------------------------------
//
// CCGStaticGraph
//
// 1. CCGStaticGraph��!
//    1) Graph�� �׷��ִ� Library�̴�.
//    2) AddGraph�� ���� ���ϴ� ����ŭ�� Graph�� �������� �߰��� �����ϴ�.
//       - �̶� line�� ����� vertical scale�� �����Ѵ�.
//       - �̶� Graph Index�� ���� �� �ִ�.
//       - �� Graph Index�� Remove�� �ϸ� ���� ���� �ִ�.
//    3) Vertical/Horizontal Scale�� ������ �� �ִ�.
//    4) AppendData�� ���� ����Ÿ�� �߰��� �� �ִ�.
//    5) Scroll�Լ��� ���� ��µǴ� �׷����� �ű� �� �ִ�.
//
//
// ----------------------------------------------------------------------------
class CGMFCCONTROL_EXT_CLASS CCGStaticGraph : 
// ****************************************************************************
// Inherited classes)
// ----------------------------------------------------------------------------
	public						CStatic		// Static��  ��ӹ��� ����.
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
