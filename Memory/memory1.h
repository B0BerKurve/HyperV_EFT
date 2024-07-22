#pragma once

#include "includes.h"
#include "../HyperV/HyperV.h"

class CMemory
{

private:

	DWORD GetProcessID();

public:

	uintptr_t BaseAddress;
	HWND Window;
	DWORD GamePID;
	HyperV* _HyperV = new HyperV();

	template<typename type>
	inline type Read(uintptr_t address)
	{
		return _HyperV->ReadValue64<type>(address);
	}

	template<typename type>
	inline type Read2(uintptr_t PhysAddr)
	{
		return _HyperV->ReadGayPhys64<type>(PhysAddr);
	}

	template<typename type>
	inline bool Write(uintptr_t address, type value)
	{
		return _HyperV->WriteValue64<type>(address, value);
	}

	template<typename type>
	inline type ReadChain(uintptr_t base, std::vector<uintptr_t> chain)
	{
		return _HyperV->ReadChain<type>(base, chain);
	}

	/*template <typename T>
	T Read_Read(std::uint64_t address, std::vector<std::uint64_t> chain)
	{
		uint64_t cur_read = address;

		for (size_t r = 0; r < chain.size() - 1; ++r)
			cur_read = Read<std::uint64_t>(cur_read + chain[r]);

		return Read<T>(cur_read + chain[chain.size() - 1]);
	}*/

	bool Initialize();

}; inline CMemory Memory;