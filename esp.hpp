#pragma once
#include "Skicript.hpp"

uintptr_t fps_camera{};
uintptr_t gom{};
baseplayer local_player;

struct unity_string
{
	char buffer[1024];
};





//uint64_t GetComponentFromGameObject(const char* compname)
//{
//	char* name;
//	uint64_t testicles = Memory.Read<uint64_t>(fps_camera + 0x30);
//	if (!testicles)return 0;
//
//
//	for (int i = 0x8; i < 0x1000; i += 0x10)
//	{
//		uint64_t Fields = Memory.Read<uint64_t>(Memory.Read<uint64_t>(testicles + i) + 0x28);
//		/*if (!Fields)
//			continue;*/
//		//if (!Fields)return 0;
//		uint64_t NameChain = Memory.Read<uint64_t>(Memory.Read<uint64_t>(Memory.Read<uint64_t>(Fields)) + 0x48);
//		/*if (!NameChain)
//			continue;*/
//	//	if (!NameChain)return 0;
//		name = Memory.Read<unity_string>(NameChain).buffer;
//		if (strcmp(name, compname) == 0)
//		{
//			return Fields;
//		}
//	}
//
//	/*for (int i = 0x8; i < 0x300; i += 0x10)
//	{
//		uint64_t Fields = Memory.Read<uint64_t>(Memory.Read<uint64_t>(testicles + i) + 0x28);
//		if (!Fields)return 0;
//		uint64_t NameChain = Memory.Read<uint64_t>(Memory.Read<uint64_t>(Memory.Read<uint64_t>(Fields)) + 0x48);
//		if (!NameChain)return 0;
//		name = Memory.Read<unity_string>(NameChain).buffer;
//		if (strcmp(name, compname) == 0)
//		{
//			return Fields;
//		}
//	}*/
//
//	return 0;
//}

void GearChams(uint64_t in)
{
	/*if (!this)
		return;*/

	uintptr_t player_body = Memory.Read<uintptr_t>((uintptr_t)in + 0xa8);;

	if (!player_body)
		return;

	uintptr_t slot_views = Memory.Read<uintptr_t>(player_body + 0x50);

	if (!slot_views)
		return;

	uintptr_t slot_views_list = Memory.Read<uintptr_t>(slot_views + 0x18);

	if (!slot_views_list)
		return;

	uintptr_t list_pointer = Memory.Read<uintptr_t>(slot_views_list + 0x10);

	uint32_t sz = Memory.Read<uint32_t>(slot_views_list + 0x18);

	for (int i = 0; i < sz; i++)
	{
		uintptr_t entry = Memory.Read<uintptr_t>(list_pointer + 0x20 + (0x8 * i));

		if (!entry)
			continue;

		uintptr_t dresses_array = Memory.Read<uintptr_t>(entry + 0x40);

		if (!dresses_array)
			continue;

		uint32_t dress_arr_sz = Memory.Read<uintptr_t>(dresses_array + 0x18);

		for (int j = 0; j < dress_arr_sz; j++)
		{
			uintptr_t dress_entry = Memory.Read<uintptr_t>(dresses_array + 0x20 + (0x8 * j));

			if (!dress_entry)
				continue;

			uintptr_t renderer_array = Memory.Read<uintptr_t>(dress_entry + 0x28);

			if (!renderer_array)
				continue;

			uint32_t render_arr_sz = Memory.Read<uint32_t>(renderer_array + 0x18);

			for (int k = 0; k < render_arr_sz; k++)
			{
				uintptr_t render_entry = Memory.Read<uintptr_t>(renderer_array + 0x20 + (0x8 * k));

				if (!render_entry)
					continue;

				uintptr_t material_dict = Memory.Read<uintptr_t>(render_entry + 0x10);

				if (!material_dict)
					continue;

				uint32_t mat_count = Memory.Read<uint32_t>(material_dict + 0x158);

				if (mat_count > 0 && mat_count < 6) // rofl
				{
					uintptr_t material_dictionary_base = Memory.Read<uintptr_t>(material_dict + 0x148);

					if (!material_dictionary_base)
						continue;

					for (int l = 0; l < mat_count; l++)
						Memory.Write<DWORD>(material_dictionary_base + (l * 0x4), 0);
				}
			}
		}
	}
}

void cloth_chams(uint64_t in)
{
	//if (!this)
	//	return;

	uintptr_t player_body = Memory.Read<uintptr_t>((uintptr_t)in + 0xa8);;

	if (!player_body)
		return;

	uintptr_t skin_dictionary = Memory.Read<uintptr_t>(player_body + 0x38);

	if (!skin_dictionary)
		return;

	uint32_t skin_count = Memory.Read<uint32_t>(skin_dictionary + 0x40);

	uintptr_t skin_list = Memory.Read<uintptr_t>(skin_dictionary + 0x18);

	if (!skin_count || skin_count > 10000)
		return;

	for (int i = 0; i < skin_count; i++)
	{
		uintptr_t body_skins = Memory.Read<uintptr_t>(skin_list + 0x30 + (0x18 * i));

		if (!body_skins)
			continue;

		uintptr_t lod_array = Memory.Read<uintptr_t>(body_skins + 0x18);

		if (!lod_array)
			continue;

		int lod_count = Memory.Read<int>(lod_array + 0x18);

		if (lod_count > 128)
			continue;

		for (int j = 0; j < lod_count; j++)
		{

			uintptr_t lod_entry = Memory.Read<uintptr_t>(lod_array + 0x20 + (j * 0x8));
			if (!lod_entry)
				continue;

			uintptr_t skinned_mesh_renderer = Memory.Read<uintptr_t>(lod_entry + 0x20);
			if (!skinned_mesh_renderer)
				continue;

			uintptr_t material_dict = Memory.Read<uintptr_t>(skinned_mesh_renderer + 0x10);
			if (!material_dict)
				continue;

			uint32_t material_count = Memory.Read<uint32_t>(material_dict + 0x158);

			if (material_count > 0 && material_count < 10)
			{
				uintptr_t material_dirbase = Memory.Read<uintptr_t>(material_dict + 0x148);

				for (int k = 0; k < material_count; k++)
				{
					if (Memory.Read<uint64_t>(material_dirbase + (k * 0x4)) != 0)
						Memory.Write<uint64_t>(material_dirbase + (k * 0x4), 0);
				}
			}
			else
			{
				uintptr_t lod_entry = Memory.Read<uint64_t>(lod_array + 0x20 + (j * 0x8));
				if (!lod_entry)
					continue;

				uintptr_t skinned_mesh_renderer = Memory.Read<uintptr_t>(Memory.Read<uint64_t>(lod_entry + 0x20) + 0x20);
				if (!skinned_mesh_renderer)
					continue;

				uintptr_t material_dict = Memory.Read<uintptr_t>(skinned_mesh_renderer + 0x10);
				if (!material_dict)
					continue;

				uint32_t material_count = Memory.Read<uint32_t>(material_dict + 0x158);
				uintptr_t material_dirbase = Memory.Read<uintptr_t>(material_dict + 0x148);
				for (int k = 0; k < material_count; k++)
				{
					if (Memory.Read<uint64_t>(material_dirbase + (k * 0x4)) != 0)
						Memory.Write<uint64_t>(material_dirbase + (k * 0x4), 0);
				}
			}
		}
	}
}


class World
{
private:
	struct list_info
	{
		int size;
		uintptr_t base;
	};
public:


	void get_player_list()
	{

		uint64_t onlineusers = Memory.Read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0xA0);
		list_info info{};
		info.base = Memory.Read<uintptr_t>(onlineusers + 0x10);
		info.size = Memory.Read<uintptr_t>(onlineusers + 0x18);
	/*	if (info.size < 1)
		{
			Vars::Misc::test = false;

		}
		else
		{
			Vars::Misc::test = true;

		}*/


		
		/*if (!player_buffer) continue;*/


		constexpr auto BUFFER_SIZE = 1024;
		uint64_t player_buffer[BUFFER_SIZE];
		Memory._HyperV->ReadMem1(info.base + 0x20, player_buffer, sizeof(uint64_t) * info.size);//Memory.Read ReadMem
		//writevall(info.base + 0x20, player_buffer, sizeof(uint64_t) * info.size);//Memory.Read

		//uint64_t player_buffer = Memory.Read<uint64_t>(info.base + (0x20 + (info.size * 8)));
		//char* name = Memory.Read<unity_string>(class_name_ptr + 0x0).buffer;

		for (int i = 0; i < info.size; i++)
		{
			uint64_t instance = player_buffer[i];

			baseplayer current_player;
			current_player.entity = instance;

			if (current_player.is_local_player())
			{
				current_player.is_local = true;
				local_player = current_player;
			}

			if (Vars::Misc::Chams) {
				GearChams(instance);
				cloth_chams(instance);
				
			}
		}
	}



};



bool isEnabled1 = false;


int isEnabled_int1 = 0;

struct base_object_t
{
	uint64_t previousObjectLink; //0x0000
	uint64_t nextObjectLink; //0x0008
	uint64_t object; //0x0010
};

struct game_object_manager_t
{
	uint64_t lastTaggedObject; //0x0
	uint64_t taggedObjects; //0x8
	uint64_t lastMainCameraTagged; // 0x10
	uint64_t MainCameraTagged; // 0x18
	uint64_t lastActiveObject; //0x20
	uint64_t activeObjects; // 0x28
};


uint64_t GetObjectFromList(uint64_t listPtr, uint64_t lastObjectPtr, const char* objectName)
{
	char* name;
	uint64_t classNamePtr = 0x0;
	using structs::BaseObject;
	BaseObject activeObject = Memory.Read<BaseObject>(listPtr);
	BaseObject lastObject = Memory.Read<BaseObject>(lastObjectPtr);

	if (activeObject.object != 0x0)
	{
		while (activeObject.object != 0 && activeObject.object != lastObject.object)
		{
			classNamePtr = Memory.Read<uint64_t>(activeObject.object + 0x60);
			if (!classNamePtr)
				continue;
			name = Memory.Read<unity_string>(classNamePtr + 0x0).buffer;
			if (strcmp(name, objectName) == 0)
			{
				return activeObject.object;
			}

			activeObject = Memory.Read<BaseObject>(activeObject.nextObjectLink);
		}
	}
	if (lastObject.object != 0x0)
	{
		classNamePtr = Memory.Read<uint64_t>(lastObject.object + 0x60);
		if (classNamePtr != 0)
		/*if (!classNamePtr)
			return;*/
		name = Memory.Read<unity_string>(classNamePtr + 0x0).buffer;
		if (strcmp(name, objectName) == 0)
		{
			return lastObject.object;
		}
	}

	return uint64_t();
}


class GameObjectManager
{
private:
public:

	World* get_game_world()
	{
		char name[1024];
		auto camera_objects = Memory.Read<std::array<uintptr_t, 2>>(reinterpret_cast<uintptr_t>(this) + 0x28);
		base_object_t activeObject = Memory.Read<base_object_t>(camera_objects[0]);
		uintptr_t class_name_ptr = 0x00;
		int  game_world_count = 1000;
		for (int i = 0; i < game_world_count; i++)
		{
			/*class_name_ptr = Memory.Read<uintptr_t>(activeObject.object + 0x60);
			if (!class_name_ptr)
				continue;*/
			class_name_ptr = Memory.Read<uintptr_t>(activeObject.object + 0x60);
			if (!class_name_ptr)
				continue;
			/*char* name = Memory.Read<unity_string>(class_name_ptr + 0x0).buffer;*/
			Memory._HyperV->ReadMem1(class_name_ptr + 0x0, &name, sizeof(name));
			/*Memory._HyperV->ReadMem1(class_name_ptr + 0x0, &name, sizeof(name));*/
			if (strcmp(name, skCrypt("GameWorld")) == 0)
			{
				auto unk1 = Memory.Read<uintptr_t>(activeObject.object + 0x30);
				if (!unk1)
					continue;
				auto unk2 = Memory.Read<uintptr_t>(unk1 + 0x18);
				if (!unk2)
					continue;

				return Memory.Read<World*>(unk2 + 0x28);
			}
			activeObject = Memory.Read<base_object_t>(activeObject.nextObjectLink);
		}
	}

};

World* world{};
class entity_list_t
{
public:
	GameObjectManager* game_object_manager{};

	std::vector<uintptr_t> players_list{};

	void update()
	{

		game_object_manager = Memory.Read<GameObjectManager*>(Memory._HyperV->GetProcessModule(L"UnityPlayer.dll") + 0x17FFD28);
		if (game_object_manager != 0)
		world = game_object_manager->get_game_world();
		if (world)
		{
			world->get_player_list();


	//		if (GetAsyncKeyState(0x23) & 1)
	//		{
	//			isEnabled1 = !isEnabled1;
	//		}
	//		if (isEnabled1 && isEnabled_int1 != 1) {

	//			if (Vars::Misc::test)
	//			{
	//				gom = Memory.Read<uintptr_t>(Memory._HyperV->GetProcessModule(L"UnityPlayer.dll") + 0x17FFD28);
	//				if (!gom)
	//					return;
	//				auto tagged_objects = Memory.Read<std::array<uint64_t, 2>>(gom + 0x18);
	//				fps_camera = GetObjectFromList(tagged_objects[0], !tagged_objects[1], skCrypt("FPS Camera"));

	//				if (!fps_camera)
	//					return;
	//			}

	//
	//			isEnabled_int1 = 1;
	//		}
	//		else if (!isEnabled1 && isEnabled_int1 != 2) {

	//			if (Vars::Misc::test)
	//			{
	//				gom = Memory.Read<uintptr_t>(Memory._HyperV->GetProcessModule(L"UnityPlayer.dll") + 0x17FFD28);
	//				if (!gom)
	//					return;
	//				auto tagged_objects = Memory.Read<std::array<uint64_t, 2>>(gom + 0x18);
	//				fps_camera = GetObjectFromList(tagged_objects[0], !tagged_objects[1], skCrypt("FPS Camera"));

	//				if (!fps_camera)
	//					return;
	//			}

	///*			gom = Memory.Read<uintptr_t>(Memory._HyperV->GetProcessModule(L"UnityPlayer.dll") + 0x17FFD28);
	//			if (!gom)
	//				return;
	//			auto tagged_objects = Memory.Read<std::array<uint64_t, 2>>(gom + 0x18);
	//			fps_camera = GetObjectFromList(tagged_objects[0], !tagged_objects[1], skCrypt("FPS Camera"));

	//			if (!fps_camera)
	//				return;*/

	//			//entity_list.update();
	//			//entity_list.run();

	//			isEnabled_int1 = 2;
	//		}



			//if (Vars::Misc::test)
			//{
			//	gom = Memory.Read<uintptr_t>(Memory._HyperV->GetProcessModule(L"UnityPlayer.dll") + 0x17FFD28);
			//	if (!gom)
			//		return;
			//	auto tagged_objects = Memory.Read<std::array<uint64_t, 2>>(gom + 0x18);
			//	fps_camera = GetObjectFromList(tagged_objects[0], !tagged_objects[1], skCrypt("FPS Camera"));

			//	if (!fps_camera)
			//		return;
			//}
		}
	}




	bool isThermalVisionEnabled = false;


	int isThermalVisionEnabled_int = 0;


	void run()
	{

		if (local_player.entity)
		{
			if (Vars::Misc::no_recoil)
			{
				local_player.remove_recoil();
			}

			if (Vars::Misc::instant_aim)
			{
				local_player.set_instant_aim();
			}




			//if (Vars::Misc::speedHack)
			if (GetAsyncKeyState(0xA0))
			{
				//local_player.SpeedHack();

				uintptr_t time = (0x17FFAE0 + (7 * 8));//0x17F8AE0
				uint64_t time_scale = Memory.Read<uint64_t>(Memory._HyperV->GetProcessModule(L"UnityPlayer.dll") + time);
				Memory.Write<float>(time_scale + 0xFC, 1.7f);
			}
			else
			{
				uintptr_t time = (0x17FFAE0 + (7 * 8));//0x17F8AE0
				uint64_t time_scale = Memory.Read<uint64_t>(Memory._HyperV->GetProcessModule(L"UnityPlayer.dll") + time);
				Memory.Write<float>(time_scale + 0xFC, 1.f);
			}

			

			if (Vars::Misc::no_sway)
				local_player.NoSwey();

			if (Vars::Misc::infinite_stamine)
				local_player.unlimited_stamina();


		/*	if (GetAsyncKeyState(0x05) & 1)
			{
				isNightVisionEnabled = !isNightVisionEnabled;
			}
			if (isNightVisionEnabled && isThermalVisionEnabled_int != 1) {
					auto NightVision = GetComponentFromGameObject(skCrypt("NightVision"));
					Memory.Write<int>(NightVision + 0xEC, true);
				
				isThermalVisionEnabled_int = 1;
			}
			else if (!isNightVisionEnabled && isNightVisionEnabled_int != 2) {
			    auto NightVision = GetComponentFromGameObject(skCrypt("NightVision"));
				Memory.Write<int>(NightVision + 0xEC, false);
			
				isNightVisionEnabled_int = 2;
			}*/



				//if (Vars::Misc::NightVision)
				//{
				//	auto NightVision = GetComponentFromGameObject(skCrypt("NightVision"));
				//	Memory.Write<int>(NightVision + 0xEC, 1);
				//}

				//if (!Vars::Misc::NightVision)
				//{
				//	auto NightVision = GetComponentFromGameObject(skCrypt("NightVision"));
				//	Memory.Write<int>(NightVision + 0xEC, 0);
				//}

			//if (Vars::Misc::ThermalVision)
		/*	if (GetAsyncKeyState(0x06))
			{
				auto ThermalVision = GetComponentFromGameObject(skCrypt("ThermalVision"));
				Memory.Write<bool>(ThermalVision + 0xD8, true);
				Memory.Write<bool>(ThermalVision + 0x40, true);
			}
			if (GetAsyncKeyState(0xA4))
			{
				auto ThermalVision = GetComponentFromGameObject(skCrypt("ThermalVision"));
				Memory.Write<bool>(ThermalVision + 0xD8, false);
				Memory.Write<bool>(ThermalVision + 0x40, false);
			}*/


		

			//if (GetAsyncKeyState(0x06) & 1)
			//{
			//	isThermalVisionEnabled = !isThermalVisionEnabled;
			//}
			//if (isThermalVisionEnabled && isThermalVisionEnabled_int != 1) {
			//	auto ThermalVision = GetComponentFromGameObject(skCrypt("NightVision"));
			//	if (ThermalVision != 0)
			//	//if (!ThermalVision)
			//	//	return;


			//	Memory.Write<bool>(ThermalVision + 0xEC, true);
			//	//Memory.Write<bool>(ThermalVision + 0x40, true);
			//	isThermalVisionEnabled_int = 1;
			//}
			//else if (!isThermalVisionEnabled && isThermalVisionEnabled_int != 2) {
			//	auto ThermalVision = GetComponentFromGameObject(skCrypt("NightVision"));
			//	if (ThermalVision != 0)
			//	//if (!ThermalVision)
			//	//	return;
			//	Memory.Write<bool>(ThermalVision + 0xEC, false);

			//	//Memory.Write<bool>(ThermalVision + 0x40, false);
			//	isThermalVisionEnabled_int = 2;
			//}




			//if (GetAsyncKeyState(0x06) & 1)
			//{
			//	isThermalVisionEnabled = !isThermalVisionEnabled;
			//}
			//if (isThermalVisionEnabled && isThermalVisionEnabled_int != 1) {
			//	auto ThermalVision = GetComponentFromGameObject(skCrypt("ThermalVision"));
			//	/*if (!ThermalVision)
			//		return;*/
			//	Memory.Write<bool>(ThermalVision + 0xD8, true);
			//	Memory.Write<bool>(ThermalVision + 0x40, true);

			//	//Memory.Write<bool>(ThermalVision + 0xEC, true);
			//	//Memory.Write<bool>(ThermalVision + 0x40, true);
			//	isThermalVisionEnabled_int = 1;
			//}
			//else if (!isThermalVisionEnabled && isThermalVisionEnabled_int != 2) {
			//	auto ThermalVision = GetComponentFromGameObject(skCrypt("ThermalVision"));
			//	/*if (!ThermalVision)
			//		return;*/

			//	Memory.Write<bool>(ThermalVision + 0xD8, false);
			//	Memory.Write<bool>(ThermalVision + 0x40, false);

			//	//Memory.Write<bool>(ThermalVision + 0xEC, false);
			//	//Memory.Write<bool>(ThermalVision + 0x40, false);
			//	isThermalVisionEnabled_int = 2;
			//}




			//if (Vars::Misc::Visor)
			//{
			//	auto nVision3 = GetComponentFromGameObject(skCrypt("VisorEffect"));
			//	if (nVision3 != 0)

			//	//if (!nVision3)
			//	//	return;
			//	Memory.Write(nVision3 + 0xC0, 0.f);

			//}



		}
	}

} entity_list;