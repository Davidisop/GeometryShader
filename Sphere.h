#pragma once
#include "Object_Handling.h"

class Sphere : public Object_Handling
{

public:
	bool   Set_VertexData();
	bool   update_ConstantBuffer();
	bool   set_IndexData();

public:
	bool Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const char*  VS_pFuntionName, const TCHAR* pPsFile, const TCHAR* pGsFile, const TCHAR* pTexFile);


public:
	Sphere() {}
	virtual ~Sphere() {}
};

bool   Sphere::update_ConstantBuffer()
{
	g_pContext->UpdateSubresource(PipeLineSetup.m_pConstantBuffer, 0, NULL, &m_Constant_Data, 0, 0);

	return true;
}



bool  Sphere::Set_VertexData()
{
	m_VertexList.resize(24);
	int iner_index = 0;

	//�ո�

	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	// �޸�
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ������
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));


	// ����
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ����
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, 0.5f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, 0.5f, -0.5f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	// �Ʒ���
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, -0.5f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, -0.5f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[iner_index++] = SimpleVertex(D3DXVECTOR3(-0.5f, -0.5f, 0.5f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));


	m_icount_Vertexs = m_VertexList.size();

	return true;
}



bool   Sphere::set_IndexData()
{

	m_IndexList.resize(36);
	int iner_index = 0;

	m_IndexList[iner_index++] = 0;	m_IndexList[iner_index++] = 1;	m_IndexList[iner_index++] = 2;	m_IndexList[iner_index++] = 0;	m_IndexList[iner_index++] = 2;	m_IndexList[iner_index++] = 3;
	m_IndexList[iner_index++] = 4;	m_IndexList[iner_index++] = 5;	m_IndexList[iner_index++] = 6;	m_IndexList[iner_index++] = 4;	m_IndexList[iner_index++] = 6;	m_IndexList[iner_index++] = 7;
	m_IndexList[iner_index++] = 8;	m_IndexList[iner_index++] = 9;	m_IndexList[iner_index++] = 10;	m_IndexList[iner_index++] = 8;	m_IndexList[iner_index++] = 10;	m_IndexList[iner_index++] = 11;
	m_IndexList[iner_index++] = 12;	m_IndexList[iner_index++] = 13;	m_IndexList[iner_index++] = 14;	m_IndexList[iner_index++] = 12;	m_IndexList[iner_index++] = 14;	m_IndexList[iner_index++] = 15;
	m_IndexList[iner_index++] = 16;	m_IndexList[iner_index++] = 17;	m_IndexList[iner_index++] = 18;	m_IndexList[iner_index++] = 16;	m_IndexList[iner_index++] = 18;	m_IndexList[iner_index++] = 19;
	m_IndexList[iner_index++] = 20;	m_IndexList[iner_index++] = 21;	m_IndexList[iner_index++] = 22;	m_IndexList[iner_index++] = 20;	m_IndexList[iner_index++] = 22;	m_IndexList[iner_index++] = 23;

	m_icount_Indexes = m_IndexList.size();

	return true;

}

bool    Sphere::Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const char*  VS_pFuntionName, const TCHAR* pPsFile, const TCHAR* pGsFile, const TCHAR* pTexFile)
{
	PipeLineSetup.LoadTexture(pd3dDevice, pTexFile);
	PipeLineSetup.SetBlendState(pd3dDevice);
	PipeLineSetup.CreateVertextBuffer(pd3dDevice, &m_VertexList.at(0), m_icount_Vertexs);
	PipeLineSetup.CreateIndexBuffer(pd3dDevice, &m_IndexList.at(0), m_icount_Indexes);
	PipeLineSetup.CreateConstantBuffer(pd3dDevice, &m_Constant_Data);
	PipeLineSetup.CreateVertexShader(pd3dDevice, pVsFile, VS_pFuntionName);
	PipeLineSetup.CreateLayout(pd3dDevice);
	PipeLineSetup.CreateGeometryShader(pd3dDevice, pGsFile);
	PipeLineSetup.CreatePixelShader(pd3dDevice, pPsFile);


	PipeLineSetup.For_Viewport_get_set();
	PipeLineSetup.Create_RasterizerState();
	PipeLineSetup.CreateTexture2D_DepthStencilView();
	PipeLineSetup.CreateDepthStencilState();

	return true;
}