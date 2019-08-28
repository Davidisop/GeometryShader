//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer cb0
{
	matrix	g_matWorld		: packoffset(c0);
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
};

struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};


struct GS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};


struct PS_INPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};


PS_INPUT David_NormalizeVertex(PS_INPUT Vertex)
{
	GS_OUTPUT newvertex = (GS_OUTPUT)0;
	newvertex.p = float4(normalize(Vertex.p.xyz), 1);
	// ������ ������ �߽����� �ϴ� �븻 ���Ͱ� �ȴ�.
	newvertex.c = Vertex.c;
	newvertex.t = Vertex.t;

	float4 vWorld = mul(float4(newvertex.p.xyz, 1.0f), g_matWorld);
	float4 vView = mul(vWorld, g_matView);
	float4 vProj = mul(vView, g_matProj);
	newvertex.p = vProj;

	return newvertex;
}


void David_TriAppend(PS_INPUT V0, PS_INPUT V1, PS_INPUT V2, inout TriangleStream<PS_INPUT> yang_TriStream)
{
	yang_TriStream.Append(David_NormalizeVertex(V0));
	yang_TriStream.Append(David_NormalizeVertex(V1));
	yang_TriStream.Append(David_NormalizeVertex(V2));
	// �ﰢ�� ������ ��Ʈ������ ������� �Ѵ�.		
	yang_TriStream.RestartStrip();
}



[maxvertexcount(80)] // ���� *3
void GS(triangle VS_OUTPUT input[3], inout TriangleStream<PS_INPUT> David_triStream)
{
	// ���̽��� ������ ���Ѵ�.
	PS_INPUT vInput[3];
	



	vInput[0].p = input[0].p;
	vInput[0].c = input[0].c;
	vInput[0].t = input[0].t;

	vInput[1].p = input[1].p;
	vInput[1].c = input[1].c;
	vInput[1].t = input[1].t;

	vInput[2].p = input[2].p;
	vInput[2].c = input[2].c;
	vInput[2].t = input[2].t;

	vInput[0] = David_NormalizeVertex(vInput[0]);
	vInput[1] = David_NormalizeVertex(vInput[1]);
	vInput[2] = David_NormalizeVertex(vInput[2]);



	//

	PS_INPUT Center0, Center1, Center2;

	Center0.p = float4((input[0].p.xyz + input[1].p.xyz) / 2.0, 1.0f);
	Center0.c = (input[0].c + input[1].c) / 2.0;
	Center0.t = (input[0].t.xy + input[1].t.xy) / 2.0;

	Center1.p = float4((input[1].p.xyz + input[2].p.xyz) / 2.0, 1.0f);
	Center1.c = (input[1].c + input[2].c) / 2.0;
	Center1.t = (input[1].t.xy + input[2].t.xy) / 2.0;

	Center2.p = float4((input[0].p.xyz + input[2].p.xyz) / 2.0, 1.0f);
	Center2.c = (input[0].c + input[2].c) / 2.0;
	Center2.t = (input[0].t.xy + input[2].t.xy) / 2.0;


	//

	PS_INPUT Der0, Der1, Der2;
	PS_INPUT Der3, Der4, Der5;
	PS_INPUT Der6, Der7, Der8;

	//
	
	Der0.p = float4((vInput[0].p.xyz + Center0.p.xyz) / 2.0, 1.0f);
	Der0.c = (vInput[0].c + Center0.c) / 2.0;
	Der0.t = (vInput[0].t.xy + Center0.t.xy) / 2.0;

	Der1.p = float4((Center0.p.xyz + Center2.p.xyz) / 2.0, 1.0f);
	Der1.c = (Center0.c + Center2.c) / 2.0;
	Der1.t = (Center0.t.xy + Center2.t.xy) / 2.0;

	Der2.p = float4((vInput[0].p.xyz + Center2.p.xyz) / 2.0, 1.0f);
	Der2.c = (vInput[0].c + Center2.c) / 2.0;
	Der2.t = (vInput[0].t.xy + Center2.t.xy) / 2.0;

	//
	
	
	Der3.p = float4((Center0.p.xyz + vInput[1].p.xyz) / 2.0, 1.0f);
	Der3.c = (Center0.c + vInput[1].c) / 2.0;
	Der3.t = (Center0.t.xy + vInput[1].t.xy) / 2.0;

	Der4.p = float4((vInput[1].p.xyz + Center1.p.xyz) / 2.0, 1.0f);
	Der4.c = (vInput[1].c + Center1.c) / 2.0;
	Der4.t = (vInput[1].t.xy + Center1.t.xy) / 2.0;

	Der5.p = float4((Center0.p.xyz + Center1.p.xyz) / 2.0, 1.0f);
	Der5.c = (Center0.c + Center1.c) / 2.0;
	Der5.t = (Center0.t.xy + Center1.t.xy) / 2.0;
	
	//

	Der6.p = float4((Center1.p.xyz + vInput[2].p.xyz) / 2.0, 1.0f);
	Der6.c = (Center1.c + vInput[2].c) / 2.0;
	Der6.t = (Center1.t.xy + vInput[2].t.xy) / 2.0;

	Der7.p = float4((Center2.p.xyz + vInput[2].p.xyz) / 2.0, 1.0f);
	Der7.c = (Center2.c + vInput[2].c) / 2.0;
	Der7.t = (Center2.t.xy + vInput[2].t.xy) / 2.0;

	Der8.p = float4((Center1.p.xyz + Center2.p.xyz) / 2.0, 1.0f);
	Der8.c = (Center1.c + Center2.c) / 2.0;
	Der8.t = (Center1.t.xy + Center2.t.xy) / 2.0;


	//


	David_TriAppend(vInput[0], Der0, Der2, David_triStream);
	David_TriAppend(Der0, Der1, Der2, David_triStream);
	David_TriAppend(Der0, Center0, Der1, David_triStream);
	David_TriAppend(Der1, Center2, Der2, David_triStream);

	David_TriAppend(Center0, Der5, Der1, David_triStream);
	David_TriAppend(Der1, Der5, Der8, David_triStream);
	David_TriAppend(Der5, Center1, Der8, David_triStream);
	David_TriAppend(Der1, Der8, Center2, David_triStream);

	David_TriAppend(Center0, Der3, Der5, David_triStream);
	David_TriAppend(Der3, Der4, Der5, David_triStream);
	David_TriAppend(Der3, vInput[1], Der4, David_triStream);
	David_TriAppend(Der5, Der4, Center1, David_triStream);
	
	David_TriAppend(Center1, Der6, Der8, David_triStream);
	David_TriAppend(Der6, Der7, Der8, David_triStream);
	David_TriAppend(Der6, vInput[2], Der7, David_triStream);
	David_TriAppend(Der8, Der7, Center2, David_triStream);


}

