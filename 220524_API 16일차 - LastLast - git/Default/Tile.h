#pragma once
#include "Obj.h"
class CTile :
	public CObj
{
public:
	CTile();
	virtual ~CTile();

public :
	const int&		Get_DrawID() { return m_iDrawID; } // DrawID 원본을 넘겨주지만 수정불가하도록.
	const int&		Get_Option() { return m_iOption; }
	const int&		Get_Index()	 { return m_iIndex; }
	TILETAG	Get_TileTag() { return m_TileTag; }
	//const int&		Get_TileTagInt()
	//{ 
	//	switch (m_TileTag)
	//	{
	//	case TILE_STAGE:
	//		return 0;
	//	case TILE_TUTORIAL:
	//		return 1;
	//	case TILE_SHOP:
	//		return 2;
	//	case TILE_RUN:
	//		return 3;
	//	case TILE_END:
	//	default:
	//		return 4;
	//	}
	//}

public :
	void			Set_DrawID(const int& _iDrawID)		{ m_iDrawID = _iDrawID; }
	//void			Set_Option(const int& _iOption)		{ m_iOption = _iOption; }
	void			Set_Index(const int& _iIndex)	{ m_iIndex = _iIndex; }
	void			Set_TileTag(TILETAG _tag)	{ m_TileTag = _tag; }

public:
	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	Late_Update()	override;
	virtual void	Render(HDC hDC)		override;
	virtual void	Release()		override;
	virtual void	Motion_Change()		override;

private:
	int			m_iDrawID;
	//int			m_iOption;
	int			m_iIndex;
	TILETAG		m_TileTag;
};

