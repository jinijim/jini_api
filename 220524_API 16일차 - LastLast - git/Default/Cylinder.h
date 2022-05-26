
#include "Obj.h"
class CCylinder :
	public CObj
{
public:
	CCylinder();
	virtual ~CCylinder();

public:
	virtual void	Initialize()		override;
	virtual int		Update()			override;
	virtual	void	Late_Update()		override;
	virtual void	Render(HDC hDC)			override;
	virtual void	Release()			override;
	virtual void	Motion_Change()		override;

public:
	virtual		void	Update_InfoCollision();
};
