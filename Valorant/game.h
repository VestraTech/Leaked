#pragma once
#include "stdafx.h"
#include "xor.h"
#include "driver.h"
#include "check.h"
#include "skStr.h"



#include "icons.h"
#include "iconcpp.h"




#define m_pi 3.1415926535
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



namespace game {
	int center_x = GetSystemMetrics(0) / 2 - 3;
	int center_y = GetSystemMetrics(1) / 2 - 3;

	float Width, Height = 0.f;

	//ue4 fvector class
	class fvector {
	public:
		fvector() : x(0.f), y(0.f), z(0.f)
		{

		}

		fvector(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
		{

		}
		~fvector()
		{

		}

		float x;
		float y;
		float z;

		inline float Dot(fvector v) {
			return x * v.x + y * v.y + z * v.z;
		}

		inline fvector& operator-=(const fvector& v) {
			x -= v.x; y -= v.y; z -= v.z; return *this;
		}

		inline fvector& operator+=(const fvector& v) {
			x += v.x; y += v.y; z += v.z; return *this;
		}

		inline fvector operator/(float v) const {
			return fvector(x / v, y / v, z / v);
		}

		inline float distance(fvector v) {
			return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
		}

		inline float lenght() {
			return sqrt(x * x + y * y + z * z);
		}

		bool operator==(fvector v) {
			return ((x == v.x) && (y == v.y) && (z == v.z));
		}

		fvector operator+(fvector v) {
			return fvector(x + v.x, y + v.y, z + v.z);
		}

		fvector operator-(fvector v) {
			return fvector(x - v.x, y - v.y, z - v.z);
		}

		fvector operator*(float v) {
			return fvector(x * v, y * v, z * v);
		}

		fvector operator/(float v) {
			return fvector(x / v, y / v, z / v);
		}
	};

	//ue4 fquat class
	struct fquat {
		float x;
		float y;
		float z;
		float w;
	};

	//ue4 ftransform class
	struct ftransform {
		fquat rot;
		fvector translation;
		char pad[4];
		fvector scale;
		char pad1[4];
		D3DMATRIX ToMatrixWithScale() {
			D3DMATRIX m;
			m._41 = translation.x;
			m._42 = translation.y;
			m._43 = translation.z;

			float x2 = rot.x + rot.x;
			float y2 = rot.y + rot.y;
			float z2 = rot.z + rot.z;

			float xx2 = rot.x * x2;
			float yy2 = rot.y * y2;
			float zz2 = rot.z * z2;
			m._11 = (1.0f - (yy2 + zz2)) * scale.x;
			m._22 = (1.0f - (xx2 + zz2)) * scale.y;
			m._33 = (1.0f - (xx2 + yy2)) * scale.z;

			float yz2 = rot.y * z2;
			float wx2 = rot.w * x2;
			m._32 = (yz2 - wx2) * scale.z;
			m._23 = (yz2 + wx2) * scale.y;

			float xy2 = rot.x * y2;
			float wz2 = rot.w * z2;
			m._21 = (xy2 - wz2) * scale.y;
			m._12 = (xy2 + wz2) * scale.x;

			float xz2 = rot.x * z2;
			float wy2 = rot.w * y2;
			m._31 = (xz2 + wy2) * scale.z;
			m._13 = (xz2 - wy2) * scale.x;

			m._14 = 0.0f;
			m._24 = 0.0f;
			m._34 = 0.0f;
			m._44 = 1.0f;

			return m;
		}
	};


	///added by devil hotkeys
	namespace hotkeys
	{
		int aimkey;
		int airstuckey;
		int instares;
	}

	static int keystatus = 0;
	static int realkey = 0;

	bool GetKey(int key)
	{
		realkey = key;
		return true;
	}
	void ChangeKey(void* blank)
	{
		keystatus = 1;
		while (true)
		{
			for (int i = 0; i < 0x87; i++)
			{
				if (GetKeyState(i) & 0x8000)
				{
					hotkeys::aimkey = i;
					keystatus = 0;
					return;
				}
			}
		}
	}

	static const char* keyNames[] =
	{
		"Press any key",
		"Left Mouse",
		"Right Mouse",
		"Cancel",
		"Middle Mouse",
		"Mouse 5",
		"Mouse 4",
		"",
		"Backspace",
		"Tab",
		"",
		"",
		"Clear",
		"Enter",
		"",
		"",
		"Shift",
		"Control",
		"Alt",
		"Pause",
		"Caps",
		"",
		"",
		"",
		"",
		"",
		"",
		"Escape",
		"",
		"",
		"",
		"",
		"Space",
		"Page Up",
		"Page Down",
		"End",
		"Home",
		"Left",
		"Up",
		"Right",
		"Down",
		"",
		"",
		"",
		"Print",
		"Insert",
		"Delete",
		"",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"",
		"",
		"",
		"",
		"",
		"Numpad 0",
		"Numpad 1",
		"Numpad 2",
		"Numpad 3",
		"Numpad 4",
		"Numpad 5",
		"Numpad 6",
		"Numpad 7",
		"Numpad 8",
		"Numpad 9",
		"Multiply",
		"Add",
		"",
		"Subtract",
		"Decimal",
		"Divide",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
	};
	

	//cheat settings for menu, etc
	namespace settings
	{
		float aim_constant_offset = 0.f;

		bool aimbot_enable = false;
		bool aimbot_constant = false;
		bool aimbot_mode_silent = false;
		bool aimbot_draw_fov = false;
		bool aimbot_draw_target_line = false;
		bool aimbot_ignore_with_useless_weapons = false;
		float aimbot_fov = 120.f;
		float aimbot_smooth = 17.f;


		//added by devil
		bool aimbot_random_aim_bone = false;
		float aimbot_random_aim_bone_interval = 5;
		bool aimbot_recoil_control = true;
		int aimbot_aimbone = 8;
		int aimbot_aimbone_selection = 0;
		int player_snapline_selection = 2;
		int player_box_selection = 2;
		static const char* aimbot_aimbone_items[]{ "Head", "Neck", "Pelvis" };
		static const char* player_snapline_items[]{ "Top", "Middle", "Bottom" };
		static const char* player_box_items[]{ "Filled", "3D Box", "Cornered Box" };
		
		bool headcircle = false;
		int headboxtype = 0;
		const char* headboxt[] = { ("Circle") ,("Filled Circle"), ("Dot") };

		bool fresnel_chams = false;
		float fresnel_intensity = 1.f;

		
		///////////////////////////////////////////////////
		bool player_box = false;
		bool player_box_3d = false;
		bool player_skeleton = false;
		bool player_snapline = false;
		bool player_view_angle = false;
		bool player_distance = false;
		bool player_healthbar = false;
		bool player_agent = false;
		bool player_weapon = false;

		bool player_ignore_dormant = false;
	}

	//boring copy pasta math shit
	namespace math
	{
		D3DMATRIX matrix(fvector rot, fvector origin = fvector(0, 0, 0)) {
			float radPitch = (rot.x * float(m_pi) / 180.f);
			float radYaw = (rot.y * float(m_pi) / 180.f);
			float radRoll = (rot.z * float(m_pi) / 180.f);

			float SP = sinf(radPitch);
			float CP = cosf(radPitch);
			float SY = sinf(radYaw);
			float CY = cosf(radYaw);
			float SR = sinf(radRoll);
			float CR = cosf(radRoll);

			D3DMATRIX matrix;
			matrix.m[0][0] = CP * CY;
			matrix.m[0][1] = CP * SY;
			matrix.m[0][2] = SP;
			matrix.m[0][3] = 0.f;

			matrix.m[1][0] = SR * SP * CY - CR * SY;
			matrix.m[1][1] = SR * SP * SY + CR * CY;
			matrix.m[1][2] = -SR * CP;
			matrix.m[1][3] = 0.f;

			matrix.m[2][0] = -(CR * SP * CY + SR * SY);
			matrix.m[2][1] = CY * SR - CR * SP * SY;
			matrix.m[2][2] = CR * CP;
			matrix.m[2][3] = 0.f;

			matrix.m[3][0] = origin.x;
			matrix.m[3][1] = origin.y;
			matrix.m[3][2] = origin.z;
			matrix.m[3][3] = 1.f;

			return matrix;
		}

		D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
		{
			D3DMATRIX pOut;
			pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
			pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
			pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
			pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
			pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
			pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
			pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
			pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
			pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
			pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
			pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
			pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
			pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
			pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
			pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
			pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

			return pOut;
		}
	}

	//if one of the pointers is guarded, guard_(n) will be set to 'devdrv'. if its not guarded, it's 0 and + 0 doesnt do anything so idk just leave it
	namespace guarded_pointers
	{
		uintptr_t guard_local_pawn = 0x0;
		uintptr_t guard_controller = 0x0;
	}

	//maybe we need some pointers everywhere so we just store them here lmao (global)
	namespace pointer
	{
		
		uintptr_t local_pawn;
		uintptr_t local_pawn_old;
		uintptr_t player_controller;
		uintptr_t camera_manager;
		uintptr_t root_comp;
		uintptr_t actor_array;
		uintptr_t local_players;

		uintptr_t for_actor;
		uintptr_t for_mesh;

		uintptr_t actor;
		uintptr_t mesh;
		uintptr_t bone_array;

		uintptr_t root_component;
		uintptr_t damage_handler;

		INT32 bone_count;
		INT32 ammo_count;

		std::string weapon_name;
		std::string agent_name;
		std::string player_name;

	}

	//we need camera everywhere. lets store it here
	namespace camera
	{
		fvector location;
		fvector rotation;
		float fov;
	}

	//hell yeah we want different fonts for everything #COOL-ESP
	namespace fonts {
		ImFont* standard_font;
		ImFont* intro_font;
	}

	//color struct by devil
	namespace ColorStructs
	{

		typedef struct
		{
			DWORD R;
			DWORD G;
			DWORD B;
			DWORD A;
		}RGBA;

		class Color
		{
		public:
			RGBA red = { 255,0,0,255 };
			RGBA Magenta = { 255,0,255,255 };
			RGBA yellow = { 255,255,0,255 };
			RGBA grayblue = { 128,128,255,255 };
			RGBA green = { 128,224,0,255 };
			RGBA darkgreen = { 0,224,128,255 };
			RGBA brown = { 192,96,0,255 };
			RGBA pink = { 255,168,255,255 };
			RGBA DarkYellow = { 216,216,0,255 };
			RGBA SilverWhite = { 236,236,236,255 };
			RGBA purple = { 144,0,255,255 };
			RGBA Navy = { 88,48,224,255 };
			RGBA skyblue = { 0,136,255,255 };
			RGBA graygreen = { 128,160,128,255 };
			RGBA blue = { 0,96,192,255 };
			RGBA orange = { 255,128,0,255 };
			RGBA peachred = { 255,80,128,255 };
			RGBA reds = { 255,128,192,255 };
			RGBA darkgray = { 96,96,96,255 };
			RGBA Navys = { 0,0,128,255 };
			RGBA darkgreens = { 0,128,0,255 };
			RGBA darkblue = { 0,128,128,255 };
			RGBA redbrown = { 128,0,0,255 };
			RGBA purplered = { 128,0,128,255 };
			RGBA greens = { 25,255,25,140 };
			RGBA envy = { 0,255,255,255 };
			RGBA black = { 0,0,0,255 };
			RGBA neger = { 215, 240, 180, 255 };
			RGBA negernot = { 222, 180, 200, 255 };
			RGBA gray = { 128,128,128,255 };
			RGBA white = { 255,255,255,255 };
			RGBA blues = { 30,144,255,255 };
			RGBA lightblue = { 135,206,250,255 };
			RGBA Scarlet = { 220, 20, 60, 160 };
			RGBA white_ = { 255,255,255,200 };
			RGBA gray_ = { 128,128,128,200 };
			RGBA black_ = { 0,0,0,200 };
			RGBA red_ = { 255,0,0,200 };
			RGBA Magenta_ = { 255,0,255,200 };
			RGBA yellow_ = { 255,255,0,200 };
			RGBA grayblue_ = { 128,128,255,200 };
			RGBA green_ = { 128,224,0,200 };
			RGBA darkgreen_ = { 0,224,128,200 };
			RGBA brown_ = { 192,96,0,200 };
			RGBA pink_ = { 255,168,255,200 };
			RGBA darkyellow_ = { 216,216,0,200 };
			RGBA silverwhite_ = { 236,236,236,200 };
			RGBA purple_ = { 144,0,255,200 };
			RGBA Blue_ = { 88,48,224,200 };
			RGBA skyblue_ = { 0,136,255,200 };
			RGBA graygreen_ = { 128,160,128,200 };
			RGBA blue_ = { 0,96,192,200 };
			RGBA orange_ = { 255,128,0,200 };
			RGBA pinks_ = { 255,80,128,200 };
			RGBA Fuhong_ = { 255,128,192,200 };
			RGBA darkgray_ = { 96,96,96,200 };
			RGBA Navy_ = { 0,0,128,200 };
			RGBA darkgreens_ = { 0,128,0,200 };
			RGBA darkblue_ = { 0,128,128,200 };
			RGBA redbrown_ = { 128,0,0,200 };
			RGBA purplered_ = { 128,0,128,200 };
			RGBA greens_ = { 0,255,0,200 };
			RGBA envy_ = { 0,255,255,200 };

			RGBA glassblack = { 0, 0, 0, 160 };
			RGBA GlassBlue = { 65,105,225,80 };
			RGBA glassyellow = { 255,255,0,160 };
			RGBA glass = { 200,200,200,60 };

			RGBA filled = { 0, 0, 0, 150 };

			RGBA Plum = { 221,160,221,160 };

		};
		Color Col;
	}

	using namespace ColorStructs;

	void DrawCircle(int x, int y, int radius, RGBA* color, float segments)									
	{
		ImGui::GetForegroundDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 17.0, color->B / 238.0, color->A / 1.0)), segments);
	}

	void DrawCircleFilled(int x, int y, int radius, RGBA* color, float segments)
	{
		ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 17.0, color->B / 238.0, color->A / 1.0)), segments);
	}



	//we store the following info for each player so we are cooler
	struct player
	{
		
		uintptr_t for_actor;
		uintptr_t for_mesh;

		uintptr_t actor;
		uintptr_t mesh;
		uintptr_t bone_array;
		
		uintptr_t root_component;
		uintptr_t damage_handler;

		INT32 bone_count;
		INT32 ammo_count;

		std::string weapon_name;
		std::string agent_name;
		std::string player_name;

		float distance;
		float health;
		float shield;

		bool is_valid;
		bool is_damage_handler_guarded;
		bool is_mesh_guarded;
	};

	//create list of all players :D
	std::vector<player> player_pawns;

	//we need this operator, otherwise we can't pushback to our player list
	inline bool operator==(const player& a, const player& b) {
		if (a.actor == b.actor)
			return true;

		return false;
	}

	



	//draw text, view args
	void draw_text(const char* content, ImVec2 screen_position, ImVec4 color, bool outlined, bool background) {
		if (background) {
			ImVec2 text_size = ImGui::CalcTextSize(content);
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(screen_position.x - 2, screen_position.y - 1), ImVec2(screen_position.x + text_size.x + 2, screen_position.y + text_size.y + 1), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 0.f, 0);
		}

		if (outlined) {
			ImGui::GetOverlayDrawList()->AddText(ImVec2(screen_position.x + 1, screen_position.y + 1), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), content);
			ImGui::GetOverlayDrawList()->AddText(ImVec2(screen_position.x - 1, screen_position.y - 1), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), content);
			ImGui::GetOverlayDrawList()->AddText(ImVec2(screen_position.x + 1, screen_position.y - 1), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), content);
			ImGui::GetOverlayDrawList()->AddText(ImVec2(screen_position.x - 1, screen_position.y + 1), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), content);
		}

		ImGui::GetOverlayDrawList()->AddText(screen_position, ImGui::GetColorU32({ color.x, color.y, color.z, color.w }), content);
	}
	namespace off
	{
		constexpr uintptr_t game_instance = 0x1A0; // world + game_instance // TYPE=uintptr_t
		constexpr uintptr_t persistent_level = 0x38; // world + persistent_level // TYPE=uintptr_t

		constexpr uintptr_t local_player_array = 0x40; // game_instance + local_player_array // TYPE=uintptr_t
		constexpr uintptr_t local_player_controller = 0x38; // local_player + local_player_controller // TYPE=uintptr_t
		constexpr uintptr_t local_player_pawn = 0x460; // local_player_controller + local_player_pawn // TYPE=uintptr_t (=actor)

		constexpr uintptr_t camera_manager = 0x478; // local_player_controller + camera_manager // TYPE=uintptr_t
		constexpr uintptr_t camera_rotation = 0x126C;  // camera_manager + camera_rotation // TYPE=Vector3

		constexpr uintptr_t actor_array = 0xA0; // persistent_level + actor_array // TYPE=uintptr_t
		constexpr uintptr_t actor_count = 0xB8; // persistent_level + actor_count // TYPE=int

		constexpr uintptr_t unique_id = 0x38;  // actor + actor_id // TYPE=uintptr_t
		constexpr uintptr_t mesh_component = 0x430; // actor + mesh_component // TYPE=uintptr_t
		
		constexpr uintptr_t bone_array = 0x5C0; // mesh_component + bone_array // TYPE=uintptr_t
		constexpr uintptr_t bone_count = 0x5C8; // actor + bone_count // TYPE=uintptr_t

		constexpr uintptr_t root_component = 0x230; // actor + root_component // TYPE=uintptr_t

		constexpr uintptr_t damage_handler = 0x9A8; // actor/local_player_pawn + damage_handler // TYPE=uintptr_t
		constexpr uintptr_t health = 0x1B0; // damage_handler + health // TYPE=float

		constexpr uintptr_t fresnel_intensity = 0x6b8;

		constexpr uintptr_t GameState = 0x140;
		constexpr uintptr_t	MapLoadModel = 0x140;
		constexpr uintptr_t ClientGameInstance = 0x678;
	}
	//required for visible check
	float read_visible(player _player, int num)
	{
		return read<float>(_player.for_mesh + _player.mesh + num);
	}

	//returns true if player is visible
	bool is_visible(player _player) {

		int i = 848;

		float v1 = read_visible(_player, i);
		i += 0x8;
		float v2 = read_visible(_player, i);

		float difference = v1 - v2;
		if (difference < 0.f)
		{
			difference *= -1;
		}

		if (difference < 0.01f)
			return true;

		return false;
	}

	//returns true if player is active
	bool is_dormant(player _player)
	{
		return read<bool>(_player.for_actor + _player.actor + 0x100);
	}

	//returns agent name as a string
	std::string get_agent_name_by_id(int id) {
		switch (id)
		{
		case 12814502: return "ASTRA";
			break;
		case 14230510: return "JETT";
			break;
		case 14211583: return "CHAMBER";
			break;
		case 14219028: return "KILLJOY";
			break;
		case 14209948: return "RAZE"; //ok
			break;
		case 14228884: return "REYNA"; //ok
			break;
		case 14228027: return "SAGE"; //ok
			break;
		case 12807475: return "SKYE";
			break;
		case 14225108: return "NEON";
			break;
		case 14220733: return "VIPER";
			break;
		case 12801214: return "BREACH";
			break;
		case 14224190: return "BRIMSTONE";
			break;
		case 14216462: return "CYPHER";
			break;
		case 14229275: return "OMEN";
			break;
		case 14221852: return "PHOENIX"; //ok
			break;
		case 14218064: return "SOVA"; //ok
			break;
		case 12818495: return "YORU";
			break;
		case 12806381: return "KAY/O";
			break;
		case 14207406: return "FADE";
			break;
		case 14228837: return  "BOT"; //ok
			break;
		case 14228831: return "Train BOT"; //ok
			break;
		default:
			return std::to_string(id);
			break;
		}
	}

	//returns player name as a string
	std::string get_player_name(int id) {
		return "";
	}

	//returns weapon name as a string
	std::string get_weapon_name_by_id(int id) {
		switch (id)
		{
		case 14391138:
			return "Knife";
		case 14228426:
			return "Classic";
		case 14344067:
			return "Shorty";
		case 14317610:
			return "Frenzy";
		case 14331757:
			return "Ghost";
		case 14337438:
			return "Sherif";
		case 14381275:
			return "Stinger";
		case 14372361:
			return "Spectre";
		case 14311125:
			return "Bucky";
		case 14306695:
			return "Judge";
		case 14290828:
			return "Bulldog";
		case 14359098:
			return "Guardian";
		case 14295709:
			return "Phantom";
		case 14281714:
			return "Vandal";
		case 14367103:
			return "Marshal";
		case 14347794:
			return "Operator";
		case 14277173:
			return "Ares";
		case 14273531:
			return "Odin";
		case 14230480:
			return "Jett Ult";
		case 14213014:
			return "Chamber Ult";
		case 14212558:
			return "Chamber Sherif";
		case 14225417:
			return "Neon Ult";
		default:
			return "Ability";
		}
	}

	//worldtoscreen what do i say xD
	fvector w2s(fvector world_location) {
		fvector ScreenLocation;
		D3DMATRIX tempMatrix = math::matrix(camera::rotation);
		fvector vAxisX, vAxisY, vAxisZ;
		vAxisX = fvector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = fvector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = fvector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
		fvector vDelta = world_location - camera::location;
		fvector vTransformed = fvector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
		if (vTransformed.z < .1f)
			vTransformed.z = .1f;
		float ScreenCenterX = center_x;
		float ScreenCenterY = center_y;
		ScreenLocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(camera::fov * (float)m_pi / 360.f)) / vTransformed.z;
		ScreenLocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(camera::fov * (float)m_pi / 360.f)) / vTransformed.z;
		return ScreenLocation;
	}

	//function to check if something is in rect (screen)
	boolean in_rect(double centerX, double centerY, double radius, double x, double y) {
		return x >= centerX - radius && x <= centerX + radius &&
			y >= centerY - radius && y <= centerY + radius;
	}

	//function to create legit movements for aimbot
	void calculate_random_for_constant_aimbot()
	{
		while (true)
		{
			settings::aim_constant_offset = 15.f;
			Sleep(200);

			settings::aim_constant_offset = 2.f;
			Sleep(200);

			settings::aim_constant_offset = 8.f;
			Sleep(200);

			settings::aim_constant_offset = 20.f;
			Sleep(200);

			settings::aim_constant_offset = 4.f;
			Sleep(200);

			settings::aim_constant_offset = 12.f;
			Sleep(200);
		}
		
	}

	//avg normalize function
	void normalize(fvector& in)
	{
		if (in.x > 89.f) in.x -= 360.f;
		else if (in.x < -89.f) in.x += 360.f;

		while (in.y > 180)in.y -= 360;
		while (in.y < -180)in.y += 360;
		in.z = 0;
	}

	//simple function to smooth angles
	fvector smooth_aim(fvector target, fvector delta_rotation, float smooth)
	{
		fvector diff = target - delta_rotation;
		normalize(diff);
		return delta_rotation + diff / smooth;
	}

	//converter
	float degree_to_radian(float degree)
	{
		return degree * (M_PI / 180);
	}

	//function to calculate an angle
	void angle_rotation(const fvector& angles, fvector* forward)
	{
		float	sp, sy, cp, cy;

		sy = sin(degree_to_radian(angles.y));
		cy = cos(degree_to_radian(angles.y));

		sp = sin(degree_to_radian(angles.x));
		cp = cos(degree_to_radian(angles.x));

		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	//bone matrix (its fixed now :D)
	fvector bone_matrix(int index, player _player)
	{
		size_t size = sizeof(ftransform);
		ftransform first_bone, comp_to_world;

		first_bone = read<ftransform>(_player.bone_array + (size * index));
		if (_player.is_mesh_guarded)
		{
			comp_to_world = read<ftransform>(devdrv + _player.mesh + 0x250);
		}
		else
		{
			comp_to_world = read<ftransform>(_player.mesh + 0x250);
		}
		
		D3DMATRIX matrix = math::MatrixMultiplication(first_bone.ToMatrixWithScale(), comp_to_world.ToMatrixWithScale());
		return fvector(matrix._41, matrix._42, matrix._43);
	}

	//3d box for esp, etc.
	void draw_3d_box(fvector base, fvector top_reach, float wide, ImVec4 col, float thickness)
	{

		//calculate bottom rect
		fvector bottom_rect_1 = fvector(base.x + wide, base.y + wide, base.z);
		fvector bottom_rect_2 = fvector(base.x + wide, base.y - wide, base.z);
		fvector bottom_rect_3 = fvector(base.x - wide, base.y + wide, base.z);
		fvector bottom_rect_4 = fvector(base.x - wide, base.y - wide, base.z);

		//calculate top rect
		fvector top_rect_1 = fvector(top_reach.x + wide, top_reach.y + wide, top_reach.z);
		fvector top_rect_2 = fvector(top_reach.x + wide, top_reach.y - wide, top_reach.z);
		fvector top_rect_3 = fvector(top_reach.x - wide, top_reach.y + wide, top_reach.z);
		fvector top_rect_4 = fvector(top_reach.x - wide, top_reach.y - wide, top_reach.z);

		//w2s bottom rect
		bottom_rect_1 = w2s(bottom_rect_1);
		bottom_rect_2 = w2s(bottom_rect_2);
		bottom_rect_3 = w2s(bottom_rect_3);
		bottom_rect_4 = w2s(bottom_rect_4);

		//w2s top rect
		top_rect_1 = w2s(top_rect_1);
		top_rect_2 = w2s(top_rect_2);
		top_rect_3 = w2s(top_rect_3);
		top_rect_4 = w2s(top_rect_4);

		//render bottom rect
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_1.x, bottom_rect_1.y), ImVec2(bottom_rect_2.x, bottom_rect_2.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_2.x, bottom_rect_2.y), ImVec2(bottom_rect_4.x, bottom_rect_4.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_4.x, bottom_rect_4.y), ImVec2(bottom_rect_3.x, bottom_rect_3.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_3.x, bottom_rect_3.y), ImVec2(bottom_rect_1.x, bottom_rect_1.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

		//render top rect
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_1.x, top_rect_1.y), ImVec2(top_rect_2.x, top_rect_2.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_2.x, top_rect_2.y), ImVec2(top_rect_4.x, top_rect_4.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_4.x, top_rect_4.y), ImVec2(top_rect_3.x, top_rect_3.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_3.x, top_rect_3.y), ImVec2(top_rect_1.x, top_rect_1.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		
		//render connection lines
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_1.x, bottom_rect_1.y), ImVec2(top_rect_1.x, top_rect_1.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_2.x, bottom_rect_2.y), ImVec2(top_rect_2.x, top_rect_2.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_3.x, bottom_rect_3.y), ImVec2(top_rect_3.x, top_rect_3.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_4.x, bottom_rect_4.y), ImVec2(top_rect_4.x, top_rect_4.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	}

	//todo
	void draw_corner_box(int x, int y, int w, int h, ImVec4 Color, int thickness) {
		float lineW = (w / 4.f);
		float lineH = (h / 4.f);
		ImDrawList* p = ImGui::GetOverlayDrawList();

		//oben links nach unten
		p->AddLine(ImVec2(x, y), ImVec2(x, y + lineH), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//oben links nach rechts (l-mittig)
		p->AddLine(ImVec2(x, y), ImVec2(x + lineW, y), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//oben rechts (r-mittig) nach rechts
		p->AddLine(ImVec2(x + w - lineW, y), ImVec2(x + w, y), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//oben rechts nach vert-rechts (oberhalb)
		p->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + lineH), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten vert-links (unterhalb) nach unten links
		p->AddLine(ImVec2(x, y + h - lineH), ImVec2(x, y + h), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten links nach rechts (mittig)
		p->AddLine(ImVec2(x, y + h), ImVec2(x + lineW, y + h), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten rechts (mittig) nach rechts
		p->AddLine(ImVec2(x + w - lineW, y + h), ImVec2(x + w, y + h), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten rechts nach vert-rechts (unterhalb)
		p->AddLine(ImVec2(x + w, y + h - lineH), ImVec2(x + w, y + h), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);
	}

	//simple skeleton esp for each gender
	void draw_skeleton(player _player, ImVec4 col, float thickness)
	{
		fvector bone_head, bone_neck, bone_chest, bone_pelvis, bone_rshoulder, bone_relbow, bone_rhand, bone_rthigh, bone_rknee, bone_rfoot, bone_lshoulder, bone_lelbow, bone_lhand, bone_lthigh, bone_lknee, bone_lfoot;
		bone_head = bone_matrix(8, _player);
		bone_chest = bone_matrix(6, _player);
		bone_pelvis = bone_matrix(3, _player);

		if (_player.bone_count == 99) //female
		{
			bone_neck = bone_matrix(19, _player);

			bone_lshoulder = bone_matrix(21, _player);
			bone_lelbow = bone_matrix(40, _player);
			bone_lhand = bone_matrix(42, _player);

			bone_rshoulder = bone_matrix(46, _player);
			bone_relbow = bone_matrix(65, _player);
			bone_rhand = bone_matrix(67, _player);

			bone_lthigh = bone_matrix(78, _player);
			bone_lknee = bone_matrix(75, _player);
			bone_lfoot = bone_matrix(77, _player);

			bone_rthigh = bone_matrix(80, _player);
			bone_rknee = bone_matrix(82, _player);
			bone_rfoot = bone_matrix(84, _player);
		}
		else if (_player.bone_count == 99) //npc
		{
			bone_neck = bone_matrix(9, _player);

			bone_lshoulder = bone_matrix(33, _player);
			bone_lelbow = bone_matrix(30, _player);
			bone_lhand = bone_matrix(32, _player);

			bone_rshoulder = bone_matrix(58, _player);
			bone_relbow = bone_matrix(55, _player);
			bone_rhand = bone_matrix(57, _player);

			bone_lthigh = bone_matrix(63, _player);
			bone_lknee = bone_matrix(65, _player);
			bone_lfoot = bone_matrix(69, _player);

			bone_rthigh = bone_matrix(77, _player);
			bone_rknee = bone_matrix(79, _player);
			bone_rfoot = bone_matrix(83, _player);
		}
		else //male
		{
			bone_neck = bone_matrix(19, _player);

			bone_lshoulder = bone_matrix(21, _player);
			bone_lelbow = bone_matrix(22, _player);
			bone_lhand = bone_matrix(49, _player);

			bone_rshoulder = bone_matrix(47, _player);
			bone_relbow = bone_matrix(48, _player);
			bone_rhand = bone_matrix(49, _player);

			bone_lthigh = bone_matrix(75, _player);
			bone_lknee = bone_matrix(76, _player);
			bone_lfoot = bone_matrix(78, _player);

			bone_rthigh = bone_matrix(82, _player);
			bone_rknee = bone_matrix(83, _player);
			bone_rfoot = bone_matrix(85, _player);
		}

		bone_head = w2s(bone_head);
		bone_neck = w2s(bone_neck);
		bone_chest = w2s(bone_chest);
		bone_pelvis = w2s(bone_pelvis);
		bone_lshoulder = w2s(bone_lshoulder);
		bone_lelbow = w2s(bone_lelbow);
		bone_lhand = w2s(bone_lhand);
		bone_rshoulder = w2s(bone_rshoulder);
		bone_relbow = w2s(bone_relbow);
		bone_rhand = w2s(bone_rhand);
		bone_lthigh = w2s(bone_lthigh);
		bone_lknee = w2s(bone_lknee);
		bone_lfoot = w2s(bone_lfoot);
		bone_rthigh = w2s(bone_rthigh);
		bone_rknee = w2s(bone_rknee);
		bone_rfoot = w2s(bone_rfoot);

		ImDrawList* draw = ImGui::GetOverlayDrawList();

		//top stuff
		draw->AddLine(ImVec2(bone_head.x, bone_head.y), ImVec2(bone_neck.x, bone_neck.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_neck.x, bone_neck.y), ImVec2(bone_chest.x, bone_chest.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_pelvis.x, bone_pelvis.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

		//right arm
		draw->AddLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_rshoulder.x, bone_rshoulder.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_rshoulder.x, bone_rshoulder.y), ImVec2(bone_relbow.x, bone_relbow.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_relbow.x, bone_relbow.y), ImVec2(bone_rhand.x, bone_rhand.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

		//left arm
		draw->AddLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_lshoulder.x, bone_lshoulder.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_lshoulder.x, bone_lshoulder.y), ImVec2(bone_lelbow.x, bone_lelbow.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_lelbow.x, bone_lelbow.y), ImVec2(bone_lhand.x, bone_lhand.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

		//right foot
		draw->AddLine(ImVec2(bone_pelvis.x, bone_pelvis.y), ImVec2(bone_rthigh.x, bone_rthigh.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_rthigh.x, bone_rthigh.y), ImVec2(bone_rknee.x, bone_rknee.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_rknee.x, bone_rknee.y), ImVec2(bone_rfoot.x, bone_rfoot.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

		//left foot
		draw->AddLine(ImVec2(bone_pelvis.x, bone_pelvis.y), ImVec2(bone_lthigh.x, bone_lthigh.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_lthigh.x, bone_lthigh.y), ImVec2(bone_lknee.x, bone_lknee.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
		draw->AddLine(ImVec2(bone_lknee.x, bone_lknee.y), ImVec2(bone_lfoot.x, bone_lfoot.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	}

	//start from bottom (x, y), to top (w, h)
	void draw_health_bar(ImVec2 min, ImVec2 max, float health)
	{
		float health_percentage = health;
		health_percentage *= 0.01f;

		float lenght_left_to_right = max.x - min.x;
		lenght_left_to_right *= health_percentage;
		
		float healthbar_size_y = 5.f;

		float g = health_percentage * 255.f;
		float r = 255.f - g;
		float b = 0.f;

		r /= 255.f;
		g /= 255.f;
		b /= 255.f;

		//background
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(max.x, max.y), ImGui::GetColorU32({ 0.1f, 0.1f, 0.1f, 1.f }), 0.f, 15);

		//health bar
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(min.x + lenght_left_to_right, max.y), ImGui::GetColorU32({ r, g, b, 1.f }), 0.f, 15);

		//outline
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(max.x, max.y), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 0.f, 15, 1.f);
	}
	
	auto GetWorld(uintptr_t Pointer) -> uintptr_t
	{
		std::uintptr_t uworld_addr =  read<uintptr_t>(Pointer + 0x50);

		unsigned long long uworld_offset;

		if (uworld_addr > 0x10000000000)
		{
			uworld_offset = uworld_addr - 0x10000000000;
		}
		else {
			uworld_offset = uworld_addr - 0x8000000000;
		}

		return Pointer + uworld_offset;
	}

	static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
	{
		const char* const* items = (const char* const*)data;
		if (out_text)
			*out_text = items[idx];
		return true;
	}

	inline void HotkeyButton(int aimkey, void* changekey, int status)
	{
		const char* preview_value = NULL;
		if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
			Items_ArrayGetter(keyNames, aimkey, &preview_value);

		std::string aimkeys;
		if (preview_value == NULL)
			aimkeys = skCrypt("Select Key");
		else
			aimkeys = preview_value;

		if (status == 1)
		{
			aimkeys = skCrypt("Press the Key");
		}
		if (ImGui::Button(aimkeys.c_str(), ImVec2(120, 22)))
		{
			if (status == 0)
			{
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
			}
		}
	}

	void find() //find players
	{
		while (true)
		{
			Sleep(250); //delay must be on top of loop, otherwise it would be useless. delay is 250ms rn

			uintptr_t world = read<uintptr_t>(devdrv + 0x60);
			world = check::validate_pointer(world);
			if (!world) continue;

			uintptr_t game_instance = read<uintptr_t>(devdrv + world + off::game_instance);
			if (!game_instance) continue;

			uintptr_t persistent_level = read<uintptr_t>(devdrv + world + off::persistent_level);
			persistent_level = check::validate_pointer(persistent_level);
			if (!persistent_level) continue;

			uintptr_t local_players = read<uintptr_t>(game_instance + off::local_player_array);
			if (!local_players) continue;

			uintptr_t local_player = read<uintptr_t>(local_players);
			if (!local_player) continue;

			pointer::player_controller = read<uintptr_t>(local_player + off::local_player_controller);

			if (check::is_guarded(pointer::player_controller))
			{
				guarded_pointers::guard_controller = devdrv;

				pointer::player_controller = check::validate_pointer(pointer::player_controller);
			}
			else guarded_pointers::guard_controller = 0;
			if (!pointer::player_controller) continue;

			uintptr_t local_pawn = read<uintptr_t>(guarded_pointers::guard_controller + pointer::player_controller + off::local_player_pawn);
			if (check::is_guarded(local_pawn))
			{
				guarded_pointers::guard_local_pawn = devdrv;
				local_pawn = check::validate_pointer(local_pawn);
			}
			else guarded_pointers::guard_local_pawn = 0;

			pointer::local_pawn = local_pawn;
			if (!pointer::local_pawn || (pointer::local_pawn != pointer::local_pawn_old)) { //this clears the player list every time a new round starts (in game round, not an entire match. pretty useful :D)

				if (!player_pawns.empty())
					player_pawns.clear();
				pointer::local_pawn_old = pointer::local_pawn;
				continue;
			}

			pointer::camera_manager = read<uintptr_t>(pointer::player_controller + off::camera_manager);
			if (!pointer::camera_manager)
			{
				pointer::camera_manager = read<uintptr_t>(devdrv + pointer::player_controller + off::camera_manager);
				if (!pointer::camera_manager) continue;
			}

			if (check::is_guarded(pointer::camera_manager))
			{
				pointer::camera_manager = check::validate_pointer(pointer::camera_manager);
			} if (!pointer::camera_manager) continue;

			uintptr_t actor_array = read<uintptr_t>(devdrv + persistent_level + off::actor_array);
			if (!actor_array) continue;

			INT32 actor_count = read<INT32>(devdrv + persistent_level + off::actor_count);
			if (!actor_count) continue;

			for (int x = 0; x < actor_count; x++)
			{
				bool is_damage_handler_guarded = false; //needed for adfghadfhg
				bool is_mesh_guarded = false; //needed for adfghadfhg

				uintptr_t for_actor = 0; //if actor is guarded, this will be set to the devdrv
				uintptr_t for_mesh = 0; //if mesh is guarded, this will be set to the devdrv

				uintptr_t actor = read<uintptr_t>(actor_array + (x * 8));
				if (!actor) continue;
				if (!check::is_valid(actor)) continue;

				if (check::is_guarded(actor))
				{
					for_actor = devdrv; //this is actually 500iq, just look at it and try to understand.
					actor = check::validate_pointer(actor);
					if (!check::is_valid(actor)) continue;
				}

				//todo: check for object_id (offset is 0x18)

				INT32 unique_id = read<INT32>(for_actor + actor + off::unique_id);
				if (unique_id != 18743553) continue; //18743553 is the player id

				uintptr_t mesh = read<uintptr_t>(for_actor + actor + off::mesh_component);
				if (!mesh) continue;
				if (!check::is_valid(mesh)) continue;

				if (check::is_guarded(mesh))
				{
					is_mesh_guarded = true;
					for_mesh = devdrv; //same thing with mesh
					mesh = check::validate_pointer(mesh);
					if (!check::is_valid(mesh)) continue;
				}

				int team_color_diff = read<int>(for_actor + actor + 0x698);
				if (team_color_diff != 2) continue;

				uintptr_t root_comp = read<uintptr_t>(for_actor + actor + off::root_component);
				if (!root_comp) continue;

				uintptr_t damage_handler = read<uintptr_t>(for_actor + actor + off::damage_handler);
				if (!damage_handler) continue;

				//health & damage handler (should work fine now)
				float health = 0.f;
				if (check::is_guarded(damage_handler))
				{
					is_damage_handler_guarded = true;
					damage_handler = check::validate_pointer(damage_handler);
					if (!check::is_valid(damage_handler)) continue;
					health = read<float>(devdrv + damage_handler + off::health);
					//std::cout << "\n[guarded] health: " << health;
				}
				else
				{
					health = read<float>(damage_handler + off::health);
					//std::cout << "\n[] health: " << health;
				}

				if (health <= 0) continue;

				uintptr_t bone_array = read<uintptr_t>(for_mesh + mesh + off::bone_array);
				if (!bone_array) continue;

				INT32 bone_count = read<INT32>(for_mesh + mesh + off::bone_count);
				if (!bone_count) continue;
				player this_player{
					for_actor, //guarded region ptr
					for_mesh, //guarded region ptr
					actor,
					mesh,
					bone_array,
					root_comp,
					damage_handler,
					bone_count,
					0, //ammo count
					"", //weapon name
					"", //agent name
					"", //player name
					0.f, //distance
					health, //health
					0.f, //shleid
					true,
					is_damage_handler_guarded,
					is_mesh_guarded
				};

				//pushback player (if he isnt in the actor list yet)
				if (!player_pawns.empty()) {
					auto found_player = std::find(player_pawns.begin(), player_pawns.end(), this_player);
					if (found_player == player_pawns.end())
					{

						player_pawns.push_back(this_player);
					}


				}
				else
				{

					player_pawns.push_back(this_player);
				}
				uintptr_t GameState = read<uintptr_t>(world + off::GameState); //struct AGameStateBase* GameState; // 0x140(0x08)
				uintptr_t ClientGameInstance = read<uintptr_t>(GameState + off::ClientGameInstance); //struct UAresClientGameInstance* ClientGameInstance; // 0x678(0x08)
				//pointer::MapLoadModel = read<uintptr_t>(ClientGameInstance + off::MapLoadModel); //struct UMapLoadModel* MapLoadModel; // 0x400(0x08)

			}
		}
	}


	//update camera (fast!) :D
	void update_camera()
	{
		camera::location = read<fvector>(devdrv + pointer::camera_manager + 0x1260/*0x1240*/);
		camera::rotation = read<fvector>(devdrv + pointer::camera_manager + 0x126C/*0x124C*/);
		camera::fov = read<float>(devdrv + pointer::camera_manager + 0x1278/*0x1258*/);
	}

	//render all targets via imgui
	void render_players()
	{
		update_camera();

		/*uintptr_t inventory = read<uintptr_t>(guarded_pointers::guard_local_pawn + pointer::local_pawn + 0x948);
		uintptr_t current_equip = read<uintptr_t>(inventory + 0x218);
		int weapon_id = read<int>(current_equip + 0x18);
		std::cout << "\n weapon_id: " << weapon_id;*/



		//fvector control_rotation = read<fvector>(guarded_pointers::guard_controller + pointer::player_controller + 0x440);
		//x = pitch
		//y = yaw
		//z = pitch (always 0)


		//for dev
		char players_found[256];
		sprintf_s(players_found, "players found: %d", player_pawns.size());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(0, 0), ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.f }), players_found);

		int closest_player = 1337;
		float closest_distance = FLT_MAX;
		
		for (int x = 0; x < player_pawns.size(); x++)
		{
			player this_player = player_pawns[x];

			float health = 0;
			if (this_player.is_damage_handler_guarded)
			{
				health = read<float>(devdrv + this_player.damage_handler + off::health);
			}
			else
			{
				health = read<float>(this_player.damage_handler + off::health);
			}

			if (health <= 0.f || health > 999.f) //dead nigga
			{
				player_pawns[x].is_valid = false;
			}

			if (!this_player.is_valid)
			{
				auto erase_player = std::find(player_pawns.begin(), player_pawns.end(), this_player);
				player_pawns.erase(erase_player);
				continue;
			}

			fvector zero = bone_matrix(0, this_player);
			fvector head = bone_matrix(8, this_player);

			fvector zero_r = fvector(zero.x, zero.y, zero.z - 5);
			fvector head_r = fvector(head.x, head.y, head.z + 20);
			fvector head_r_2 = fvector(head.x, head.y, head.z + 30);

			fvector zero_w2s = w2s(zero);
			fvector head_w2s = w2s(head);

			fvector zero_w2s_r = w2s(zero_r);
			fvector head_w2s_r = w2s(head_r);

			fvector head_w2s_r_2 = w2s(head_r_2);

			float BoxHeight = abs(head_w2s.y - zero_w2s.y);
			float BoxWidth = BoxHeight * 0.55;

			if (settings::player_healthbar)
			{
				float BoxHeight = zero_w2s_r.y - head_w2s_r.y;
				float BoxWidth = BoxHeight / 2.f;

				float x1 = zero_w2s_r.x - (BoxWidth / 2);
				float x2 = zero_w2s_r.x + (BoxWidth / 2);

				draw_health_bar(ImVec2(x1, head_w2s_r_2.y), ImVec2(x2, head_w2s_r_2.y), health);
			}

			ImVec4 esp_color = ImVec4(0.7f, 0.7f, 0.7f, 1.f);   //0.157, 0.353, 0.788          //old 0.7f, 0.7f, 0.7f   //red 0.894, 0.043, 0.039  //purple 1.0f, 0.067f, 0.933f
			bool active = is_dormant(this_player);
			if (settings::player_ignore_dormant && !active)
				continue;

			if (active)
				esp_color = ImVec4(1.0f, 0.067f, 0.933f, 1.f);

			bool visible = is_visible(this_player);
			if (visible)
				esp_color = ImVec4(1.0f, 0.067f, 0.933f, 1.f);

			auto dx = head_w2s.x - center_x;
			auto dy = head_w2s.y - center_y;
			auto dist = sqrtf(dx * dx + dy * dy);
			if (visible && (dist < closest_distance)) {
				closest_distance = dist;
				closest_player = x;
			}

			if (settings::player_box)
			{
				if (settings::player_box_3d)
					draw_3d_box(zero, fvector(head.x, head.y, head.z + 20), 43, esp_color, 1.f);
				else
				{
					float BoxHeight = zero_w2s_r.y - head_w2s_r.y;
					float BoxWidth = BoxHeight / 2.f;
					draw_corner_box(zero_w2s_r.x - (BoxWidth / 2), head_w2s_r.y,
						BoxWidth, BoxHeight, esp_color, 1.f);

				}
			}

			if (settings::player_skeleton)
			{
				draw_skeleton(this_player, esp_color, 1.3f);
			}

			int bottom_text_offset = 2;

			if (settings::player_agent)
			{
				int id = read<int>(this_player.for_actor + this_player.actor + 0x18);
				std::string agent_name = get_agent_name_by_id(id);
				ImVec2 text_size = ImGui::CalcTextSize(agent_name.c_str());

				ImGui::GetOverlayDrawList()->AddText(ImVec2(zero_w2s_r.x - (text_size.x / 2), zero_w2s_r.y + bottom_text_offset), ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), agent_name.c_str());
				bottom_text_offset += 14;
			}

			if (settings::player_weapon)
			{
				uintptr_t inventory = read<uintptr_t>(this_player.for_actor + this_player.actor + 0x948);
				uintptr_t current_equip = read<uintptr_t>(inventory + 0x218);
				int weapon_id = read<int>(current_equip + 0x18);
				std::string weapon_name = get_weapon_name_by_id(weapon_id);
				ImVec2 text_size = ImGui::CalcTextSize(weapon_name.c_str());

				ImGui::GetOverlayDrawList()->AddText(ImVec2(zero_w2s_r.x - (text_size.x / 2), zero_w2s_r.y + bottom_text_offset), ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), weapon_name.c_str());
				bottom_text_offset += 14;
			}

			if (settings::player_distance)
			{
				float distance = camera::location.distance(zero) / 100.f;
				char distance_text[256];
				//sprintf_s(distance_text, "%.fm", distance);
				ImVec2 text_size = ImGui::CalcTextSize(distance_text);
				ImGui::GetOverlayDrawList()->AddText(ImVec2(zero_w2s_r.x - (text_size.x / 2), zero_w2s_r.y + bottom_text_offset), ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), distance_text);
				bottom_text_offset += 14;
			}
			
			if (settings::player_snapline)
			{
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(center_x, center_y * 2), ImVec2(zero_w2s_r.x, zero_w2s_r.y + bottom_text_offset), ImGui::GetColorU32({ esp_color.x, esp_color.y, esp_color.z, esp_color.w }), 1.f);
			}

			if (settings::player_view_angle)
			{
				fvector view_angle = read<fvector>(this_player.root_component + 0x170);

				fvector test2, headpos;

				headpos = head;

				angle_rotation(view_angle, &test2);
				test2.x *= 260;
				test2.y *= 260;
				test2.z *= 260;

				fvector end = headpos + test2;
				fvector test1, test3;
				test1 = w2s(headpos);
				test3 = w2s(end);

				ImGui::GetOverlayDrawList()->AddLine(ImVec2(test1.x, test1.y), ImVec2(test3.x, test3.y), ImGui::GetColorU32({ 0.0f, 1.0f, 0.0f, 1.0f }), 1.f);
				draw_3d_box(end, fvector(end.x, end.y, end.z + 20), 30, ImVec4(0.0f, 1.0f, 0.0f, 1.0f), 1.f);
			}

			//////head cicle added by devil
			if (settings::headcircle)
			{
				if (settings::headboxtype == 0)
				{
					DrawCircle(zero_w2s.x, head_w2s.y, BoxHeight / 10, &Col.pink, 100);
				}

				else if (settings::headboxtype == 1)
				{
					DrawCircle(zero_w2s.x, head_w2s.y, BoxHeight / 10, &Col.pink, 100);
					DrawCircleFilled(zero_w2s.x, head_w2s.y, BoxHeight / 10, &Col.filled, 100);
				}

				else if (settings::headboxtype == 2)

				{
					DrawCircleFilled(zero_w2s.x, head_w2s.y, BoxHeight / 20, &Col.pink, 100);
					DrawCircle(zero_w2s.x, head_w2s.y, BoxHeight / 20, &Col.pink, 100);
				}

				//DrawCircle(vBaseBoneOut.x, vHeadBoneOut.y, BoxHeight / 10, &Col.white, 100);
			}

			if (settings::fresnel_chams)
			{
				write<float>(this_player.actor + 0x6b8, settings::fresnel_intensity);
			}

			char c_timer[64];

			float timer = read<float>(this_player.actor + 0x4D4);
			float defuse = read<float>(this_player.actor + 0x500);
			float DefusePercentage = defuse * 100 / 6.984602;



			//sprintf(c_timer, skCrypt("Spike [%.2fs]\nDefuse: %s%s"), timer, std::to_string((int)DefusePercentage), "%");
			ImGui::GetOverlayDrawList()->AddText(ImVec2(0, 0), ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.f }), c_timer);
			
			//for dev to get bone id's
			/*for (int i = 0; i < 100; i++) {
				fvector bone_zero = bone_matrix(i, this_player);
				fvector bone_screen = w2s(bone_zero);
				ImGui::GetOverlayDrawList()->AddText(ImVec2(bone_screen.x, bone_screen.y), ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.f }), std::to_string(i).c_str());
			}*/



			/*
			fvector CameraLocation = read<Vector3>(devdrv + pointer::camera_manager + 0x1240);
			fvector CameraRotation = read<Vector3>(devdrv + pointer::camera_manager + 0x124C);
			float Camerafov = read<float>(devdrv + pointer::camera_manager + 0x1258);

			Vector3 world_location = read<Vector3>(this_player.root_component + 0x164);
			Vector3 screen_location = ProjectWorldToScreen(world_location, CameraLocation, CameraRotation, Camerafov);
			ImGui::GetOverlayDrawList()->AddLine(ImVec2(0, 0), ImVec2(screen_location.x, screen_location.y), ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.f }), 1.f);*/
		}




		if (settings::aimbot_draw_fov)
		{
			ImGui::GetOverlayDrawList()->AddCircle(ImVec2(center_x, center_y), settings::aimbot_fov, ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), 64, 1.f);
		}
		
		if (closest_player != 1337 && settings::aimbot_enable)
		{
			player target = player_pawns[closest_player];			
			fvector head = bone_matrix(settings::aimbot_aimbone, target);

			//fvector head = bone_matrix(8, target);
			fvector head_screen = w2s(head);
			if (settings::aimbot_draw_target_line && in_rect(center_x, center_y, settings::aimbot_fov, head_screen.x, head_screen.y))
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(center_x, center_y), ImVec2(head_screen.x, head_screen.y), ImGui::GetColorU32({ 1.f, 0.f, 0.f, 1.f }), 1.f);

			if (settings::aimbot_recoil_control)
			{
				if (GetAsyncKeyState(hotkeys::aimkey) && in_rect(center_x, center_y, settings::aimbot_fov, head_screen.x, head_screen.y))
				{
					fvector control_rotation = read<fvector>(guarded_pointers::guard_controller + pointer::player_controller + 0x440);
					fvector camera_rotation = camera::rotation;
					fvector new_aim_rotation;
					fvector recoil;

					recoil.x = camera_rotation.x - control_rotation.x;
					recoil.y = camera_rotation.y - control_rotation.y;
					recoil.z = 0.f;

					fvector vector_pos = head - camera::location;
					float distance = (double)(sqrtf(vector_pos.x * vector_pos.x + vector_pos.y * vector_pos.y + vector_pos.z * vector_pos.z));
					float x, y, z;
					x = -((acosf(vector_pos.z / distance) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510)) - 90.f);
					y = atan2f(vector_pos.y, vector_pos.x) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510);
					z = 0;

					fvector target_rotation = fvector(x, y, z);
					new_aim_rotation.x = target_rotation.x - recoil.x - recoil.x;
					new_aim_rotation.y = target_rotation.y - recoil.y - recoil.y;
					new_aim_rotation.z = 0;

					float smooth = settings::aimbot_smooth;
					if (settings::aimbot_constant)
					{
						smooth += settings::aim_constant_offset;
					}

					if (!is_dormant(target));

					fvector new_rotation = smooth_aim(new_aim_rotation, control_rotation, smooth);
					if (new_rotation.x < 0)
					{
						new_rotation.x += 360.f;
					}
					if (new_rotation.y < 0)
					{
						new_rotation.y += 360.f;
					}
					new_rotation.z = 0;

					write<fvector>(guarded_pointers::guard_controller + pointer::player_controller + 0x440, new_rotation);
				}
			}

			else
			{
				if (GetAsyncKeyState(hotkeys::aimkey) && in_rect(center_x, center_y, settings::aimbot_fov, head_screen.x, head_screen.y)) //TODO: FIX THE BOUNCE
				{
					fvector camera_rotation = camera::rotation;
					fvector new_aim_rotation;

					fvector vector_pos = head - camera::location;
					float distance = (double)(sqrtf(vector_pos.x * vector_pos.x + vector_pos.y * vector_pos.y + vector_pos.z * vector_pos.z));
					float x, y, z;
					x = -((acosf(vector_pos.z / distance) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510)) - 90.f);
					y = atan2f(vector_pos.y, vector_pos.x) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510);
					z = 0;

					fvector target_rotation = fvector(x, y, z);
					new_aim_rotation.x = target_rotation.x;
					new_aim_rotation.y = target_rotation.y;
					new_aim_rotation.z = 0;

					float smooth = settings::aimbot_smooth;
					if (settings::aimbot_constant)
					{
						smooth += settings::aim_constant_offset;
					}

					if (!is_dormant(target));

					fvector new_rotation = smooth_aim(new_aim_rotation, camera_rotation, smooth);
					if (new_rotation.x < 0)
					{
						new_rotation.x += 360.f;
					}
					if (new_rotation.y < 0)
					{
						new_rotation.y += 360.f;
					}
					new_rotation.z = 0;

					write<fvector>(guarded_pointers::guard_controller + pointer::player_controller + 0x440, new_rotation);
				}
			}

			
		}
	}

	static HWND Window = NULL;
	IDirect3D9Ex* p_Object = NULL;
	static LPDIRECT3DDEVICE9 D3dDevice = NULL;
	static LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;
	HWND hwnd = NULL;
	RECT GameRect = { NULL };
	D3DPRESENT_PARAMETERS d3dpp;
	const MARGINS Margin = { -1 };

	DWORD ScreenCenterX = 960;
	DWORD ScreenCenterY = 540;
	MSG Message = { NULL };

	bool menu_open = true;
	bool first_time = true;
	float colr[4];

	

	void render() {
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		static int menu_tab;

		if (GetAsyncKeyState(VK_F1) & 1) menu_open = !menu_open; // abckup keyt
		if (GetAsyncKeyState(VK_INSERT) & 1) menu_open = !menu_open;


		if (!menu_open)
			render_players();

		if (GetAsyncKeyState(VK_INSERT) & 1)
			menu_open = !menu_open;

		if (menu_open) {

			ImGui::PushFont(fonts::standard_font);
			
			static bool open_menu = true;
			auto menu_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

		
			ImGui::Begin("Vestra", &open_menu, menu_flags);
			ImGui::SetWindowSize(ImVec2(480, 440));
			ImGui::SetWindowPos(ImVec2(3, 200));	

			char title[256];
			ImGui::BeginChild("##ChildIdentifier", ImVec2(465, 400)/*SIZE OF THE CHILD*/, true /*IF YOU WANT A BORDER OR NOT*/);
					

			ImGui::SameLine();
			if (ImGui::Button("Combat", ImVec2(140, 40))) {
				menu_tab = 0;
			}
			ImGui::SameLine();
			if (ImGui::Button("Visuals", ImVec2(140, 40))) {
				menu_tab = 1;
			}


			ImGui::EndChild();
			ImGui::SameLine();
	
			

			//aimbot tab
			if (menu_tab == 0)
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 8);
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 466); 
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 55);
				ImGui::BeginChild("Aimbot (Risk)", ImVec2(220, 305)/*SIZE OF THE CHILD*/, true /*IF YOU WANT A BORDER OR NOT*/);
				ImGui::Checkbox("Enable", &settings::aimbot_enable);
				//ImGui::Checkbox("Silent", &settings::aimbot_mode_silent);
				ImGui::Checkbox("Recoil Control(Must Enable)", &settings::aimbot_recoil_control);
				ImGui::Checkbox("Target Aim Bone", &settings::aimbot_draw_target_line);
				ImGui::Checkbox("Constant", &settings::aimbot_constant);
				ImGui::Checkbox("Only whitelisted guns", &settings::aimbot_ignore_with_useless_weapons); //todo for naze
				ImGui::Checkbox("Show field of view", &settings::aimbot_draw_fov);
				ImGui::Checkbox("Show target line", &settings::aimbot_draw_target_line);

				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChild("Adjustment", ImVec2(220, 305)/*SIZE OF THE CHILD*/, true /*IF YOU WANT A BORDER OR NOT*/);
				ImGui::Spacing(); ImGui::Spacing();
				ImGui::Spacing(); ImGui::Spacing();
				HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus); // AIMKEYYY
				ImGui::Spacing(); ImGui::Spacing();
				ImGui::Spacing(); ImGui::Spacing();
				ImGui::Spacing(); ImGui::Spacing();
				ImGui::SliderFloat("Field of view", &settings::aimbot_fov, 1.f, 1000.f, "%.f"); //i will make this to degrees later
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::SliderFloat("Smooth", &settings::aimbot_smooth, 1.f, 30.f, "%.f"); //i will make this to degrees later
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();

				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
				ImGui::SetCursorPosX(8);
				ImGui::PushItemWidth(121); ImGui::Combo(skCrypt("##aimbone"), &settings::aimbot_aimbone_selection, settings::aimbot_aimbone_items, sizeof(settings::aimbot_aimbone_items) / sizeof(*settings::aimbot_aimbone_items));
				ImGui::PopStyleVar();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Spacing();

				if (settings::aimbot_aimbone_selection == 0) settings::aimbot_aimbone = 8;
				if (settings::aimbot_aimbone_selection == 1) settings::aimbot_aimbone = 21;
				if (settings::aimbot_aimbone_selection == 2) settings::aimbot_aimbone = 6;
						
				ImGui::Spacing();

				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 8);
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 458);
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 310);
				ImGui::BeginChild("Colors", ImVec2(222, 30)/*SIZE OF THE CHILD*/, true /*IF YOU WANT A BORDER OR NOT*/);
				ImGui::Text("     OWNER : xandu#7795");
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("DEV", ImVec2(222, 30)/*SIZE OF THE CHILD*/, true /*IF YOU WANT A BORDER OR NOT*/);
				ImGui::Text("     DEV : SageMage#9508");
				ImGui::EndChild();
				ImGui::SameLine();
				
			}

			//player tab
			else if (menu_tab == 1)
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 8);
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 466);
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 55);
				ImGui::BeginChild("Player ESP", ImVec2(220, 305)/*SIZE OF THE CHILD*/, true /*IF YOU WANT A BORDER OR NOT*/);
				ImGui::Checkbox("BOX", &settings::player_box);
				ImGui::Checkbox("3D Box", &settings::player_box_3d);
				ImGui::Checkbox("Skeletons", &settings::player_skeleton);
				ImGui::Checkbox("Headcircle", &settings::headcircle);
				ImGui::Checkbox("Snapline", &settings::player_snapline);
				ImGui::Checkbox("View angle", &settings::player_view_angle);
				ImGui::Checkbox("Distance", &settings::player_distance);
				ImGui::Checkbox("Healthbar", &settings::player_healthbar);
				//ImGui::Checkbox("Agent", &settings::player_agent);
				//ImGui::Checkbox("Weapon", &settings::player_weapon);
				ImGui::Checkbox("Ignore dormant", &settings::player_ignore_dormant);
				ImGui::EndChild();

				ImGui::SameLine();
				ImGui::BeginChild("Customize", ImVec2(220, 305)/*SIZE OF THE CHILD*/, true /*IF YOU WANT A BORDER OR NOT*/);
				ImGui::Text("  RISK ");
				ImGui::Separator();
				ImGui::Spacing();
				ImGui::Checkbox("GLOWX", &settings::fresnel_chams);
				if (&settings::fresnel_chams)
				{
					ImGui::SliderFloat(skCrypt(""), &settings::fresnel_intensity, 1.f, 1000.f, skCrypt("%.f"));
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 8);
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 458);
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 310);
				ImGui::BeginChild("Bottom1", ImVec2(222, 30)/*SIZE OF THE CHILD*/, true /*IF YOU WANT A BORDER OR NOT*/);
				ImGui::Text("      Vestra");
				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("Bottom2", ImVec2(222, 30)/*SIZE OF THE CHILD*/, true /*IF YOU WANT A BORDER OR NOT*/);
				ImGui::Text("        Valorant");
				ImGui::EndChild();
				ImGui::SameLine();
							
			}
			ImGui::End();

			ImGui::PopFont();
		}

		//cheat_loop();

		ImGui::EndFrame();
		D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		if (D3dDevice->BeginScene() >= 0) {
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			D3dDevice->EndScene();
		}
		HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

		if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			D3dDevice->Reset(&d3dpp);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}

	bool start_directx() {
		if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
			return false;

		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferWidth = Width;
		d3dpp.BackBufferHeight = Height;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.hDeviceWindow = Window;
		d3dpp.Windowed = TRUE;

		p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		fonts::standard_font = io.Fonts->AddFontDefault();
		fonts::intro_font = io.Fonts->AddFontFromFileTTF("adfg.ttf", 300.f);
	//	fonts::standard_font = io.Fonts->AddFontDefault();
		
		

		ImGui_ImplWin32_Init(Window);
		ImGui_ImplDX9_Init(D3dDevice);

		p_Object->Release();
		return true;
	}

	void wait_for_window() {
		while (true) {
			HWND foreground_window = GetForegroundWindow();
			HWND target_window = FindWindowA(0, "VALORANT  ");

			if (foreground_window == target_window)
				break;

			Sleep(200);
		}
	}

	void render_loop() {
		static RECT old_rc;
		ZeroMemory(&Message, sizeof(MSG));

		while (Message.message != WM_QUIT)
		{
			if (PeekMessage(&Message, Window, 0, 0, 0x0001))
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}

			HWND hwnd_active = GetForegroundWindow();

			if (hwnd_active == hwnd) {
				HWND hwndtest = GetWindow(hwnd_active, 3);
				SetWindowPos(Window, hwndtest, 2, 2, -3, -3, 0x0002 | 0x0001);
			}
			
			RECT rc;
			POINT xy;

			ZeroMemory(&rc, sizeof(RECT));
			ZeroMemory(&xy, sizeof(POINT));
			GetClientRect(hwnd, &rc);
			ClientToScreen(hwnd, &xy);
			rc.left = xy.x;
			rc.top = xy.y;

			ImGuiIO& io = ImGui::GetIO();
			io.ImeWindowHandle = hwnd;
			io.DeltaTime = 1.0f / 60.0f;

			POINT p;
			GetCursorPos(&p);
			io.MousePos.x = p.x - xy.x;
			io.MousePos.y = p.y - xy.y;

			if (GetAsyncKeyState(VK_LBUTTON)) {
				io.MouseDown[0] = true;
				io.MouseClicked[0] = true;
				io.MouseClickedPos[0].x = io.MousePos.x;
				io.MouseClickedPos[0].x = io.MousePos.y;
			}
			else
				io.MouseDown[0] = false;
			
			if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
			{
				old_rc = rc;

				Width = rc.right;
				Height = rc.bottom;

				d3dpp.BackBufferWidth = Width;
				d3dpp.BackBufferHeight = Height;
				SetWindowPos(Window, (HWND)0, xy.x + 2 , xy.y + 2, Width - 3, Height - 3, 0x0008);
				D3dDevice->Reset(&d3dpp);
			}

			render();

		}
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		DestroyWindow(Window);
	}
	void stop_render() {
		TriBuf->Release();
		D3dDevice->Release();
		p_Object->Release();

		DestroyWindow(Window);
		UnregisterClassW((_(L"Untitled - Notepad")), NULL);
	}

	LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
			return true;

		switch (Message)
		{
		case WM_DESTROY:
			stop_render();
			PostQuitMessage(0);
			exit(4);
			break;
		case WM_SIZE:
			if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
			{
				ImGui_ImplDX9_InvalidateDeviceObjects();
				d3dpp.BackBufferWidth = LOWORD(lParam);
				d3dpp.BackBufferHeight = HIWORD(lParam);
				HRESULT hr = D3dDevice->Reset(&d3dpp);
				if (hr == D3DERR_INVALIDCALL)
					IM_ASSERT(0);
				ImGui_ImplDX9_CreateDeviceObjects();
			}
			break;
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
		return 0;
	}

	void create_window() {
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(wc));
		wc.cbSize = sizeof(wc);
		wc.lpszClassName = (_(L"Untitled - Notepad"));
		wc.lpfnWndProc = WinProc;
		RegisterClassEx(&wc);

		if (hwnd)
		{
			GetClientRect(hwnd, &GameRect);
			POINT xy;
			ClientToScreen(hwnd, &xy);
			GameRect.left = xy.x;
			GameRect.top = xy.y;

			Width = GameRect.right;
			Height = GameRect.bottom;
		}
		else
			exit(2);

		//something is detected here, i will fix it later
		Window = CreateWindowExW(NULL, _(L"Untitled - Notepad"), _(L"Untitled - Notepad"), 0x80000000L | 0x10000000L, 2, 2, Width - 2, Height - 2, 0, 0, 0, 0);

		DwmExtendFrameIntoClientArea(Window, &Margin);
		SetWindowLong(Window, (-20), 0x00000020L | 0x00000080L | 0x00080000);

		ShowWindow(Window, SW_SHOW);
		UpdateWindow(Window);
	}

	void rndmBone()
	{
		for (;;)
		{
			std::vector<int> boneidList{ 8, 21, 6 };

			int index = rand() % boneidList.size();
			int value = boneidList[index];

			if (settings::aimbot_random_aim_bone)
			{
				settings::aimbot_aimbone = value;
				std::cout << value << "\n";
			}

			Sleep(settings::aimbot_random_aim_bone_interval * 1000);
		}
	}

	void start_cheat() {
		hwnd = FindWindowA(0, _("VALORANT  ")); //window name

		create_window();

		start_directx();

		wait_for_window();

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)find, NULL, NULL, NULL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)calculate_random_for_constant_aimbot, NULL, NULL, NULL);

		render_loop();

		stop_render();
	}
}