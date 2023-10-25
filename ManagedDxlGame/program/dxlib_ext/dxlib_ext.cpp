#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include "DxLib.h"
#include "dxlib_ext.h"

std::string g_drag_file_path;


void DrawStringEx(const float x, const float y, const int color, const char* _str, ...) {
	char buff[1024] = { 0 };
	va_list argptr;
	va_start(argptr, _str);
	vsprintf_s(buff, _str, argptr);
	va_end(argptr);

	float py = y;
	std::string str = buff;
	int font_size = GetFontSize();
	while (1) {
		auto pos = str.find_first_of("\n");
		if (pos == std::string::basic_string::npos) {
			DrawStringF(x, py, str.c_str(), color);
			break;
		}
		DrawStringF(x, py, str.substr(0, pos).c_str(), color);
		py += font_size;
		str = str.substr(pos+1, str.length()-1);
	}
}

void DrawFpsIndicator(const tnl::Vector3& pos, float delta_time) {
	static float sum_time = 0;
	static float sum_fps = 0;
	static float fps_rate = 0;
	static float width = 0;
	static int call_num = 0;

	sum_time += delta_time;
	sum_fps += GetFPS();
	call_num++;
	if (sum_time > 0.1f) {
		fps_rate = sum_fps / call_num;
		fps_rate /= DXE_FIX_FPS;
		sum_time = 0;
		sum_fps = 0;
		call_num = 0;
	}
	width += ((198 * fps_rate) - width) * 0.05f;
	int fs = GetFontSize();
	SetFontSize(10);
	int x = (int)pos.x;
	int y = (int)pos.y;
	DrawBox(x, y, x + 260, y + 10, 0, true);
	DrawBox(x + 1, y + 1, x + 199, y + 9, -1, false);
	DrawBox(x + 2, y + 2, x + (int)width, y + 8, 0xff77ff77, true);
	DrawStringEx(pos.x + 210, pos.y, -1, "%.1f fps", DXE_FIX_FPS * fps_rate);
	SetFontSize(fs);
}

void DrawStringToHandleEx(const float x, const float y, const int color, const int hdl, const char* _str, ...) {
	char buff[255] = { 0 };
	va_list argptr;
	va_start(argptr, _str);
	vsprintf_s(buff, _str, argptr);
	va_end(argptr);
	DrawStringToHandle((int)x, (int)y, buff, color, hdl);
}

void DrawLineEx(const tnl::Vector3& p, const tnl::Vector3& v, const float length, const int color) {
	tnl::Vector3 n = v;
	n.normalize();
	n *= length;
	DrawLine((int)p.x, (int)p.y, (int)p.x + (int)n.x, (int)p.y + (int)n.y, color, false);
}

void DrawBoxEx(const tnl::Vector3& p, const float width, const float height, const bool fill, const int color) {
	float lx = p.x - width * 0.5f;
	float rx = p.x + width * 0.5f;
	float up = p.y - height * 0.5f;
	float down = p.y + height * 0.5f;
	DrawBox((int)lx, (int)up, (int)rx, (int)down, color, fill);
}

void DrawRotaBox(const tnl::Vector3& pos, float w, float h, float rad, int color) {

	float hw = w / 2.0f;
	float hh = h / 2.0f;
	tnl::Vector3 v[4];
	tnl::Quaternion q = tnl::Quaternion::RotationAxis({ 0, 0, 1 }, rad);
	v[0] = tnl::Vector3(-hw, -hh, 0);
	v[1] = tnl::Vector3(hw, -hh, 0);
	v[2] = tnl::Vector3(hw, hh, 0);
	v[3] = tnl::Vector3(-hw, hh, 0);
	v[0] = pos + tnl::Vector3::TransformCoord(v[0], q);
	v[1] = pos + tnl::Vector3::TransformCoord(v[1], q);
	v[2] = pos + tnl::Vector3::TransformCoord(v[2], q);
	v[3] = pos + tnl::Vector3::TransformCoord(v[3], q);

	DrawLine((int)v[0].x, (int)v[0].y, (int)v[1].x, (int)v[1].y, color);
	DrawLine((int)v[1].x, (int)v[1].y, (int)v[2].x, (int)v[2].y, color);
	DrawLine((int)v[2].x, (int)v[2].y, (int)v[3].x, (int)v[3].y, color);
	DrawLine((int)v[3].x, (int)v[3].y, (int)v[0].x, (int)v[0].y, color);

}


void DrawGridGround(const dxe::Camera* camera, const float square_size, int row_num, int color) {

	MATRIX view, proj;
	memcpy(view.m, camera->view_.m, sizeof(float) * 16);
	memcpy(proj.m, camera->proj_.m, sizeof(float) * 16);
	SetCameraViewMatrix(view);
	SetupCamera_ProjectionMatrix(proj);

	MATRIX im;
	CreateIdentityMatrix(&im);
	SetTransformToWorld(&im);

	row_num = (1 == row_num % 2) ? row_num + 1 : row_num;

	float l = square_size * row_num * 0.5f;
	float n = -l;
	for (int i = 0; i < row_num + 1; ++i) {
		if ((row_num >> 1) == i) {
			DrawLine3D({ n, 0, l }, { n, 0, -l }, 0xff0000ff);
			DrawLine3D({ l, 0, n }, { -l, 0, n }, 0xffff0000);
		}
		else {
			DrawLine3D({ n, 0, l }, { n, 0, -l }, color);
			DrawLine3D({ l, 0, n }, { -l, 0, n }, color);
		}
		n += square_size;
	}
	DrawLine3D({ 0, l, 0 }, { 0, -l, 0 }, 0xff00ff00);

}


void DrawAxis(const dxe::Camera* camera, const tnl::Vector3& pos, const tnl::Quaternion& rot, const float length)
{
	MATRIX view, proj;
	memcpy(view.m, camera->view_.m, sizeof(float) * 16);
	memcpy(proj.m, camera->proj_.m, sizeof(float) * 16);
	SetCameraViewMatrix(view);
	SetupCamera_ProjectionMatrix(proj);

	// オブジェクトのワールド行列の作成
	tnl::Matrix mt_trans;
	tnl::Matrix mt_rot;
	tnl::Matrix mt_obj_world;
	mt_trans = tnl::Matrix::Translation(pos.x, pos.y, pos.z);
	mt_rot = rot.getMatrix();
	MATRIX im;
	mt_obj_world = mt_rot * mt_trans;
	memcpy(im.m, mt_obj_world.m, sizeof(float) * 16);
	SetTransformToWorld(&im);

	tnl::Vector3 up(0, length, 0);
	tnl::Vector3 right(length, 0, 0);
	tnl::Vector3 depth(0, 0, length);
	DrawLine3D({ 0, 0, 0 }, { up.x, up.y, up.z }, 0xff00ff00);
	DrawLine3D({ 0, 0, 0 }, { right.x, right.y, right.z }, 0xff0000ff);
	DrawLine3D({ 0, 0, 0 }, { depth.x, depth.y, depth.z }, 0xffff0000);
}


void DrawOBB(const dxe::Camera* camera, const tnl::Vector3& pos, const tnl::Quaternion& rot, const tnl::Vector3& size, const int color)
{

	MATRIX view, proj;
	memcpy(view.m, camera->view_.m, sizeof(float) * 16);
	memcpy(proj.m, camera->proj_.m, sizeof(float) * 16);
	SetCameraViewMatrix(view);
	SetupCamera_ProjectionMatrix(proj);

	// オブジェクトのワールド行列の作成
	tnl::Matrix mt_trans;
	tnl::Matrix mt_rot;
	tnl::Matrix mt_obj_world;
	mt_trans = tnl::Matrix::Translation(pos.x, pos.y, pos.z);
	mt_rot = rot.getMatrix();
	MATRIX im;
	mt_obj_world = mt_rot * mt_trans;
	memcpy(im.m, mt_obj_world.m, sizeof(float) * 16);
	SetTransformToWorld(&im);


	float w = size.x * 0.5f;
	float h = size.y * 0.5f;
	float d = size.z * 0.5f;
	tnl::Vector3 v[8] = {
		{ -w,  h,  d }, {  w,  h,  d },  {  w,  h,  -d }, { -w,  h, -d },
		{ -w, -h,  d }, {  w, -h,  d },  {  w, -h,  -d }, { -w, -h, -d }
	};
	uint32_t col = color;
	for (int i = 0; i < 3; ++i) DrawLine3D({ v[i].x, v[i].y , v[i].z }, { v[i + 1].x, v[i + 1].y , v[i + 1].z }, col);
	for (int i = 0; i < 3; ++i) DrawLine3D({ v[4 + i].x, v[4 + i].y , v[4 + i].z }, { v[4 + i + 1].x, v[4 + i + 1].y , v[4 + i + 1].z }, col);
	for (int i = 0; i < 4; ++i) DrawLine3D({ v[i].x, v[i].y , v[i].z }, { v[i + 4].x, v[i + 4].y , v[i + 4].z }, col);
	DrawLine3D({ v[3].x, v[3].y , v[3].z }, { v[0].x, v[0].y , v[0].z }, col);
	DrawLine3D({ v[7].x, v[7].y , v[7].z }, { v[4].x, v[4].y , v[4].z }, col);
}

void DrawAABB(const dxe::Camera* camera, const tnl::Vector3& pos, const tnl::Vector3& size, const int color)
{
	MATRIX view, proj;
	memcpy(view.m, camera->view_.m, sizeof(float) * 16);
	memcpy(proj.m, camera->proj_.m, sizeof(float) * 16);
	SetCameraViewMatrix(view);
	SetupCamera_ProjectionMatrix(proj);

	// オブジェクトのワールド行列の作成
	tnl::Matrix mt_trans;
	tnl::Matrix mt_obj_world;
	mt_trans = tnl::Matrix::Translation(pos.x, pos.y, pos.z);
	MATRIX im;
	mt_obj_world = mt_trans;
	memcpy(im.m, mt_obj_world.m, sizeof(float) * 16);
	SetTransformToWorld(&im);

	float w = size.x * 0.5f;
	float h = size.y * 0.5f;
	float d = size.z * 0.5f;
	tnl::Vector3 v[8] = {
		{ -w,  h,  d }, {  w,  h,  d },  {  w,  h,  -d }, { -w,  h, -d },
		{ -w, -h,  d }, {  w, -h,  d },  {  w, -h,  -d }, { -w, -h, -d }
	};
	uint32_t col = color;
	for (int i = 0; i < 3; ++i) DrawLine3D({ v[i].x, v[i].y , v[i].z }, { v[i + 1].x, v[i + 1].y , v[i + 1].z }, col);
	for (int i = 0; i < 3; ++i) DrawLine3D({ v[4 + i].x, v[4 + i].y , v[4 + i].z }, { v[4 + i + 1].x, v[4 + i + 1].y , v[4 + i + 1].z }, col);
	for (int i = 0; i < 4; ++i) DrawLine3D({ v[i].x, v[i].y , v[i].z }, { v[i + 4].x, v[i + 4].y , v[i + 4].z }, col);
	DrawLine3D({ v[3].x, v[3].y , v[3].z }, { v[0].x, v[0].y , v[0].z }, col);
	DrawLine3D({ v[7].x, v[7].y , v[7].z }, { v[4].x, v[4].y , v[4].z }, col);

}

void DrawBdSphere(const dxe::Camera* camera, const tnl::Vector3& pos, const float radius)
{
	MATRIX view, proj;
	memcpy(view.m, camera->view_.m, sizeof(float) * 16);
	memcpy(proj.m, camera->proj_.m, sizeof(float) * 16);
	SetCameraViewMatrix(view);
	SetupCamera_ProjectionMatrix(proj);

	// オブジェクトのワールド行列の作成
	tnl::Matrix mt_trans;
	tnl::Matrix mt_rot;
	tnl::Matrix mt_obj_world;
	mt_trans = tnl::Matrix::Translation(pos.x, pos.y, pos.z);
	MATRIX im;
	mt_obj_world = mt_rot * mt_trans;
	memcpy(im.m, mt_obj_world.m, sizeof(float) * 16);
	SetTransformToWorld(&im);

	const int ring_vtx_num = 16;
	int s = ring_vtx_num - 1;
	int e = 0;

	tnl::Vector3 vx[ring_vtx_num];
	tnl::Vector3 vy[ring_vtx_num];
	tnl::Vector3 vz[ring_vtx_num];

	// X軸リング
	for (int i = 0; i < ring_vtx_num; ++i) {
		vx[i].x = 0;
		vx[i].y = cos(tnl::ToRadian(360.0f / ring_vtx_num) * i) * radius;
		vx[i].z = sin(tnl::ToRadian(360.0f / ring_vtx_num) * i) * radius;
	}
	for (int i = 0; i < (ring_vtx_num - 1); ++i) {
		DrawLine3D({ vx[i].x, vx[i].y, vx[i].z },
			{ vx[i + 1].x, vx[i + 1].y, vx[i + 1].z }, 0xffff0000);
	}
	DrawLine3D({ vx[s].x, vx[s].y, vx[s].z },
		{ vx[e].x, vx[e].y, vx[e].z }, 0xffff0000);


	// Y軸リング
	for (int i = 0; i < ring_vtx_num; ++i) {
		vy[i].x = sin(tnl::ToRadian(360.0f / ring_vtx_num) * i) * radius;
		vy[i].y = 0;
		vy[i].z = cos(tnl::ToRadian(360.0f / ring_vtx_num) * i) * radius;
	}
	for (int i = 0; i < (ring_vtx_num - 1); ++i) {
		DrawLine3D({ vy[i].x, vy[i].y, vy[i].z },
			{ vy[i + 1].x, vy[i + 1].y, vy[i + 1].z }, 0xff00ff00);
	}
	DrawLine3D({ vy[s].x, vy[s].y, vy[s].z },
		{ vy[e].x, vy[e].y, vy[e].z }, 0xff00ff00);

	// Z軸リング
	for (int i = 0; i < ring_vtx_num; ++i) {
		vz[i].x = sin(tnl::ToRadian(360.0f / ring_vtx_num) * i) * radius;
		vz[i].y = cos(tnl::ToRadian(360.0f / ring_vtx_num) * i) * radius;
		vz[i].z = 0;
	}
	for (int i = 0; i < (ring_vtx_num - 1); ++i) {
		DrawLine3D({ vz[i].x, vz[i].y, vz[i].z },
			{ vz[i + 1].x, vz[i + 1].y, vz[i + 1].z }, 0xff2255ff);
	}
	DrawLine3D({ vz[s].x, vz[s].y, vz[s].z },
		{ vz[e].x, vz[e].y, vz[e].z }, 0xff2266ff);

}

std::string GetDragFilePathReadTrigger() {
	std::string path = g_drag_file_path;
	g_drag_file_path.clear();
	return path;
}