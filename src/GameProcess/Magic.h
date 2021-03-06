/******************************************************************************************************************
                                                                                                                   
	Module Name:
																													
	Author:
	Date:
																													
	[Date][Modifier] : Modified contents
                                                                                                                   
*******************************************************************************************************************/



#ifndef _CMAGIC_H
#define _CMAGIC_H



/******************************************************************************************************************

	CMagic Class
	

*******************************************************************************************************************/
class CMagic
{
private:
protected:
public:
	BYTE			m_bActiveState;							// Spell 활성화여부.(Spell소멸시에 사용된다.)
	BOOL			m_bRepeat;								// 애니메이션의 반복여부.
	BOOL			m_bFixed;								// Spell의 이동여부.
	BYTE			m_bMagicNum;							// Spell번호.

	CActor*			m_pxOwner;								// Spell발사주체.
	CActor*			m_pxTarget;								// Spell발사객체.
	CMapHandler*	m_pxMap;								// 맵참조포인터.

	// 좌표정보.
	SHORT	m_shScrnX, m_shScrnY;							// Spell스크린좌표.
	FLOAT	m_fFloatScrnX, m_fFloatScrnY;					// Spell스크린좌표.
	SHORT	m_shTileX, m_shTileY;							// Spell타일좌표.

	SHORT	m_shFireScrnX, m_shFireScrnY;					// Spell생성스크린좌표.
	SHORT	m_shFireTileX, m_shFireTileY;					// Spell생성타일좌표.

	SHORT	m_shTargetScrnX, m_shTargetScrnY;				// 목표점의 스크린좌표.
	SHORT	m_shTargetTileX, m_shTargetTileY;				// 목표점의 타일좌표.(변화될수있다.)

	// 렌더링정보.
	WORD	m_wCurrDelay;									// 지연시간저장값.
	WORD	m_wCurrLightDelay;
	WORD	m_wFrmDelay;									// Frame을 넘기기 위한 지연시간값.
	WORD	m_wMagicLife;									// Spell이 실행되고 있는 시간.(ms단위)


	BYTE	m_bLightRadius[2];								// 광원 너비.
	BYTE	m_bLightColor[2][3];							// 광원 색.
	BYTE	m_bMagicColor[3];								// 색.

	DWORD	m_dwFstFrame;									// 현재 Spell의 시작Frame.
	DWORD	m_dwEndFrame;									// 현재 Spell의 마지막Frame.
	DWORD	m_dwCurrFrame;									// Frame저장값.

	BYTE	m_bBlendType;									// Spell을 어떤형태로 그릴것인가를 결정.
	BYTE	m_bOpacity;										// 0 - 255단계. 0은 완전 투명(라이트형태), 255는 불투명.
	BYTE	m_bSwingCnt;									// Spell의 흔들림 조건을 준다.

	FLOAT	m_fGradient;
	INT		m_nShiftX;
	INT		m_nShiftY;
	INT		m_nDistanceX;
	INT		m_nDistanceY;
	INT		m_nPrevDistanceX;
	INT		m_nPrevDistanceY;

	BYTE	m_bDir16;
	BYTE	m_bCurrSwing;

	BOOL	m_bShowLight;

	D3DVERTEX			m_avMagic[4];
	CWHWilImageData*	m_pxMagicImg;

	INT		m_nDuplicateNum; 

	LPDIRECTDRAWSURFACE7 m_lpddsMagicTextr[60];

public:
	CMagic();
	~CMagic();

	virtual BOOL CreateMagic(BYTE bMagicNum, SHORT shFireTileX, SHORT shFireTileY, 
		                     SHORT shTargetTileX, SHORT shTargetTileY, CActor* pxOwner = NULL, INT nTarget = 0);


	virtual VOID DestoryMagic();
	virtual BOOL UpdateMagic(INT nLoopTime);
	virtual BOOL DrawMagic();
	virtual BOOL DrawLight(CLightFog* xLightFog, INT nLoopTime);
};


// _SKILL_FIRE, _SKILL_SHOOTLIGHTEN 전용.
class CMagicStream : public CMagic
{
private:
	WORD	m_wMagicStart;
	POINT	m_ptTileGap;
public:
	BOOL CreateMagic(BYTE bMagicNum, SHORT shFireTileX, SHORT shFireTileY, 
		             SHORT shTargetTileX, SHORT shTargetTileY, CActor* pxOwner, INT nTarget, WORD wStartMagicTime, POINT ptTileGap);
	BOOL UpdateMagic(INT nLoopTime);
	BOOL DrawMagic();
};


class CElecMagic : public CMagic
{
private:
	SHORT	m_shEPosX, m_shEPosY;
	BOOL	m_bArrived;

	CElec m_xElec;

public:
	virtual BOOL CreateMagic(BYTE bMagicNum, SHORT shFireTileX, SHORT shFireTileY, 
		                     SHORT shTargetTileX, SHORT shTargetTileY, CActor* pxOwner = NULL, INT nTarget = 0);
	virtual BOOL UpdateMagic(INT nLoopTime);
	virtual BOOL DrawMagic();
};



// _SKILL_HOLYSHIELD, _SKILL_EARTHFIRE 전용.
class CRepeatMagic : public CMagic
{
private:
public:
	DWORD	m_dwMagiLifeTotal;
	INT		m_nEventID;					// 이벤트로관리된다.

	_inline CRepeatMagic()
	{
		m_nEventID		  = 0;
		m_dwMagiLifeTotal = 0;
	}

	BOOL CreateMagic(INT nEventID, BYTE bMagicNum, SHORT shFireTileX, SHORT shFireTileY, 
	                 SHORT shTargetTileX, SHORT shTargetTileY, DWORD dwMagicLifeTotal, CActor* pxOwner = NULL, INT nTarget = 0);
	BOOL UpdateMagic(INT nLoopTime);
	BOOL DrawMagic();
};


#endif // _CMAGIC_H
