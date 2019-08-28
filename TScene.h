#include "Plane.h"
#include "Box.h"
#include "Line.h"
#include "Sphere.h"



int end_decision;

enum TSceneState
{
	GAME_SCENE_LOBBY = 0,
	GAME_SCENE_PLAY = 1,
	GAME_SCENE_END = 2,
};

class TScene
{
public:
	int		m_iSceneID;
	bool	m_bNextSceneStart;

public:
	virtual bool	Init() { return true; }
	virtual bool	Frame() { return true; }
	virtual bool	Render() { return true; }
	virtual bool	Release() { return true; }

public:
	TScene()
	{
		m_bNextSceneStart = false;
	}
	virtual ~TScene() {}
};



class TSceneLobby : public TScene
{
public:

	Canon_Camera Main_Camera;

public:
	
	Box			FBox;
	Sphere		FSphere;
	Plane		FPLANE;

	Line_Axis_s F_Axis_x;
	Line_Axis_s F_Axis_y;
	Line_Axis_s F_Axis_z;


	Line_Axis_s Object_Axis_x;
	Line_Axis_s Object_Axis_y;
	Line_Axis_s Object_Axis_z;

public:
	virtual bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	TSceneLobby();
	virtual ~TSceneLobby();
};

bool	TSceneLobby::Init()
{
	Main_Camera.Set_View_Matrix();
	Main_Camera.Set_Projection_Matrix(0.5, 1, 1, 100);

	FSphere.Set_VertexData(); FSphere.set_IndexData();
	//FSphere.transposition(D3DXVECTOR3(-3.0f,0.0f,0.0f));
	FSphere.Create(g_pd3dDevice, L"HLSL.vsh", "VS_NoMatrix", L"HLSL.psh", L"GeometryShader.hlsl", L"../../../data/bitmap1.bmp");

	
	FBox.Set_VertexData(); FBox.set_IndexData();
	FBox.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../../data/bitmap1.bmp");
	
	FPLANE.Set_VertexData(); FPLANE.set_IndexData();
	FPLANE.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../../data/bitmap1.bmp");
	


	F_Axis_x.Set_VertexData(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f,0.0f,0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
	F_Axis_x.set_IndexData();
	F_Axis_x.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../../data/kgca.jpg","PSLine");

	F_Axis_y.Set_VertexData(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1000.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
	F_Axis_y.set_IndexData();
	F_Axis_y.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../../data/kgca.jpg", "PSLine");
	

	F_Axis_z.Set_VertexData(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
	F_Axis_z.set_IndexData();
	F_Axis_z.Create(g_pd3dDevice, L"HLSL.vsh", L"HLSL.psh", L"../../../data/kgca.jpg", "PSLine");
	



	return true;
};

 
bool	TSceneLobby::Frame()
{

	D3DXVECTOR4   vYawPitchRoll(0, 0, 0, 0);


	// 요
	if (I_Input.Key('U'))
	{
		vYawPitchRoll.x += 0.1f*g_fSecPerFrame;
	}

	
	if (I_Input.Key('I'))
	{
		vYawPitchRoll.x -= 0.1f*g_fSecPerFrame;
	}

	// 피치

	if (I_Input.Key('J'))
	{
		vYawPitchRoll.y += 0.1f*g_fSecPerFrame;
	}

	if (I_Input.Key('K'))
	{
		vYawPitchRoll.y -= 0.1f*g_fSecPerFrame;
	}

	// 롤

	if (I_Input.Key('N'))
	{
		vYawPitchRoll.z += 0.1f*g_fSecPerFrame;
	}

	if (I_Input.Key('M'))
	{
		vYawPitchRoll.z -= 0.1f*g_fSecPerFrame;
	}


	// 스피드 부스터
	if (I_Input.Key('B'))
	{
		Main_Camera.SetSpeed(g_fSecPerFrame*3.0f);
	}

	// 위 아래 걸음


	if (I_Input.Key('Q'))
	{		Main_Camera.Move_on_Up_line(-g_fSecPerFrame * 5.0f);	}

	if (I_Input.Key('W'))
	{		Main_Camera.Move_on_Up_line(g_fSecPerFrame*5.0f);	}



	// 앞,뒤 걸음

	if (I_Input.Key('A'))
	{
		Main_Camera.Move_on_Look_line(-g_fSecPerFrame*5.0f);
	}

	if (I_Input.Key('S'))
	{
		Main_Camera.Move_on_Look_line(g_fSecPerFrame * 5.0f);
	}

	// 양 옆 게 걸음

	if (I_Input.Key('Z'))
	{
		Main_Camera.Move_on_Right_line(-g_fSecPerFrame * 5.0f);
	}

	if (I_Input.Key('X'))
	{
		Main_Camera.Move_on_Right_line(g_fSecPerFrame*5.0f);
	}

	Main_Camera.ViewMatrix_Update_From_Keyboard_Mouse(vYawPitchRoll);

	////Main_Camera.Speed_auto_Lessen();




	float t = g_fGameTimer * D3DX_PI;

	D3DXMATRIX mTranslate; 	D3DXMATRIX mTranslate_2; D3DXMATRIX mTranslate_3; D3DXMATRIX mTranslate_4;
	D3DXMATRIX earth_mOrbit; D3DXMATRIX moon_Orbit; D3DXMATRIX plane_Orbit;
	D3DXMATRIX earth_mSpin; D3DXMATRIX moon_Spin;
	D3DXMATRIX mScale; D3DXMATRIX mScale_2;  D3DXMATRIX mScale_3; 
	



	// 플래인


	D3DXMatrixTranslation(&mTranslate_4, 3.0f, 0.0f, 0.0f); // 트랜스래잇 행렬
	D3DXMatrixRotationY(&plane_Orbit, t*0.3);


	D3DXMatrixTranslation(&mTranslate, 0.0f, 3.0f, 0.0f); // 트랜스래잇 행렬
	D3DXMatrixRotationZ(&earth_mOrbit, t*0.2);


	D3DXMatrixTranslation(&mTranslate_2, 0.0f, 0.0f, 3.0f); // 트랜스래잇 행렬
	D3DXMatrixRotationX(&moon_Orbit, t*0.5);

	
	FPLANE.m_matWorld = mTranslate_4 * plane_Orbit;
	//FSphere.m_matWorld = mTranslate * earth_mOrbit;
	FBox.m_matWorld = mTranslate_2 * moon_Orbit;
	


	return true;
};


bool	TSceneLobby::Render()
{
	//

	FSphere.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FSphere.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);
	FSphere.update_ConstantBuffer();

	////

	FBox.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FBox.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);
	FBox.update_ConstantBuffer();

	////

	FPLANE.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&FPLANE.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);
	FPLANE.update_ConstantBuffer();

	////

	F_Axis_x.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_x.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);
	F_Axis_x.update_ConstantBuffer();

	//

	F_Axis_y.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_y.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);
	F_Axis_y.update_ConstantBuffer();

	//
	F_Axis_z.HandOver_world_view_projection_Matrixs_to_ConstantData_Final_extract(&F_Axis_z.m_matWorld, &Main_Camera.m_matView, &Main_Camera.m_matProj);
	F_Axis_z.update_ConstantBuffer();

	
	//
	FSphere.Render(g_pContext);
	FBox.Render(g_pContext);
	FPLANE.PreRender(g_pContext);
	FPLANE.PostRender(g_pContext);

	//

	F_Axis_x.PreRender(g_pContext);
	F_Axis_x.PostRender(g_pContext);
	F_Axis_y.PreRender(g_pContext);
	F_Axis_y.PostRender(g_pContext);
	F_Axis_z.PreRender(g_pContext);
	F_Axis_z.PostRender(g_pContext);


	return true;
};

bool	TSceneLobby::Release()
{
	
	
	return true;
};
TSceneLobby::TSceneLobby()
{
	m_iSceneID = GAME_SCENE_LOBBY;
	m_bNextSceneStart = false;
}
TSceneLobby::~TSceneLobby()
{

}

















class TSceneGame : public TScene
{
public:
	virtual bool    Init();
	bool    Frame();
	bool    Render();
	bool    Release();

public:

	TSceneGame();
	virtual ~TSceneGame();
};



TSceneGame::TSceneGame()
{
	m_iSceneID = GAME_SCENE_PLAY;
	m_bNextSceneStart = false;
}

bool   TSceneGame::Init()
{

	return true;
};

bool    TSceneGame::Frame()
{

	return true;
}

bool   TSceneGame::Render()
{

	return true;
}

bool    TSceneGame::Release()
{
	return true;
}

TSceneGame::~TSceneGame()
{
}



class TSceneEnd : public TScene
{

public:

public:
	virtual bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:

	TSceneEnd();
	virtual ~TSceneEnd();
};




bool	TSceneEnd::Init()
{



	return true;
};
bool	TSceneEnd::Frame()
{


	return true;
};

bool	TSceneEnd::Render()
{

	return true;
};

bool	TSceneEnd::Release()
{
	return true;
};

TSceneEnd::TSceneEnd()
{
	m_iSceneID = GAME_SCENE_END;
	m_bNextSceneStart = false;
}

TSceneEnd::~TSceneEnd()
{}

