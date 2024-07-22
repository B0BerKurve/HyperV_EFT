
namespace structs {
	enum Bones : int
	{
		HumanBase = 0,
		HumanPelvis = 14,
		HumanLThigh1 = 15,
		HumanLThigh2 = 16,
		HumanLCalf = 17,
		HumanLFoot = 18,
		HumanLToe = 19,
		HumanRThigh1 = 20,
		HumanRThigh2 = 21,
		HumanRCalf = 22,
		HumanRFoot = 23,
		HumanRToe = 24,
		HumanSpine1 = 29,
		HumanSpine2 = 36,
		HumanSpine3 = 37,
		HumanLCollarbone = 89,
		HumanLUpperarm = 90,
		HumanLForearm1 = 91,
		HumanLForearm2 = 92,
		HumanLForearm3 = 93,
		HumanLPalm = 94,
		HumanRCollarbone = 110,
		HumanRUpperarm = 111,
		HumanRForearm1 = 112,
		HumanRForearm2 = 113,
		HumanRForearm3 = 114,
		HumanRPalm = 115,
		HumanNeck = 132,
		HumanHead = 133
	};

	struct BaseObject
	{
		uint64_t previousObjectLink; //0x0000
		uint64_t nextObjectLink; //0x0008
		uint64_t object; //0x0010
	};

	struct GameObjectManager
	{
		uint64_t LastTaggedNode; // 0x0
		uint64_t TaggedNodes; // 0x8
		uint64_t LastMainCameraTaggedNode; // 0x10
		uint64_t MainCameraTaggedNodes; // 0x18
		uint64_t LastActiveNode; // 0x20
		uint64_t ActiveNodes; // 0x28
	}; //Size: 0x0010

	class ListInternal
	{
	public:
		char pad_0x0000[0x20]; //0x0000
		uintptr_t* firstEntry; //0x0020 
	}; //Size=0x0028

}

class entity_list {
public:



	uintptr_t transform, entity;


};

class baseplayer : public entity_list {
private:
	uintptr_t _values;
public:



	bool is_local = false;
	void NoSwey()
	{
		uint64_t animation = Memory.Read<UINT64>(entity + 0x1A0);
		if (animation)
		{
			uint64_t breath = animation + 0x28;
			breath = Memory.Read<uint64_t>(breath);
			Memory.Write<float>(breath + 0xA4, 0.f); //breath intensity

			uint64_t Walk = animation + 0x30;
			Walk = Memory.Read<uint64_t>(Walk);
			Memory.Write<float>(Walk + 0x44, 0.f); //walk intensity

			uint64_t MotionReact = animation + 0x38;
			MotionReact = Memory.Read<uint64_t>(MotionReact);
			Memory.Write<float>(MotionReact + 0xD0, 0.f);// motion

			uint64_t ForceReact = animation + 0x40;
			ForceReact = Memory.Read<uint64_t>(ForceReact);
			Memory.Write<float>(ForceReact + 0x30, 0.f);//force 

			uint64_t shot = animation + 0x48;
			shot = Memory.Read<uint64_t>(shot);
			Memory.Write<float>(shot + 0x68, 0.); // shot
		}
	}



	//void SpeedHack() {
	//	uintptr_t time = (0x17FFAE0 + (7 * 8));//0x17F8AE0
	//	uint64_t time_scale = Memory.Read<uint64_t>(Memory._HyperV->GetProcessModule(L"UnityPlayer.dll") + time);
	//	Memory.Write<float>(time_scale + 0xFC, 1.7f);
	//}

	void remove_recoil()
	{
		auto procedural_weapon_animation = Memory.Read<uintptr_t>(entity + 0x1A0);
		if (procedural_weapon_animation)
		{
			Memory.Write<int>(procedural_weapon_animation + 0x118, 1); // mask
		}
	}



	void set_instant_aim()
	{
		Memory.Write<float>((uintptr_t)this + 0x1b8, 1000.f);//freefalltime
	}

	


	bool is_local_player() {
		bool local = Memory.Read<int>(entity + 0x18);//18
		return local;
	}


	void unlimited_stamina()
	{
		uint64_t physical = Memory.Read<uintptr_t>(entity + 0x530);// 0x4D0 [4C8] Physical :
		if (physical)
		{

			const uintptr_t body_stamina = Memory.Read<uintptr_t>(physical + 0x38);
			const uintptr_t hand_stamina = Memory.Read<uintptr_t>(physical + 0x40);

			Memory.Write<float>(body_stamina + 0x48, 75.f);
			Memory.Write<float>(hand_stamina + 0x48, 75.f);

		}
	}


	class movement_context {
	public:
		enum EPhysicalCondition {
			None = 0,
			OnPainkillers = 1,
			LeftLegDamaged = 2,
			RightLegDamaged = 4,
			BoggedDown = 8,
			LeftArmDamaged = 16,
			RightArmDamaged = 32,
			Tremor = 64,
			UsingMeds = 128,
			HealingLegs = 256
		};



		void fall_speed(float speed)
		{
			Memory.Write<float>((uintptr_t)this + 0x1F8, speed);//freefalltime
		}
	};

	//movement_context* get_movement()
	//{
	//	return Memory.Read<movement_context*>(entity + 0x40);
	//}
};
