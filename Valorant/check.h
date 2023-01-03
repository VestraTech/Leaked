#pragma once
#include "stdafx.h"

namespace check {
	uintptr_t guard;

	bool zero_check(uintptr_t pointer)
	{
		constexpr uintptr_t filter = 0xFFFF0000FFFFFF00;
		uintptr_t result = pointer & filter;
		return result == 0x0000000000000000;
	}

	bool extras_check(uintptr_t pointer)
	{
		constexpr uintptr_t filter = 0xFFFF000000000000;
		uintptr_t result = pointer & filter;
		return result == 0x0000000000000000;
	}

	bool is_valid(uintptr_t pointer)
	{
		if (!pointer)
			return false;

		if (zero_check(pointer))
			return false;

		if (!extras_check(pointer))
			return false;

		return true;
	}
	
	bool is_guarded_2(uintptr_t pointer)
	{

		if (zero_check(pointer))
		{
			return false;
		}

		constexpr uintptr_t filter = 0xFFFFFFFFFF000000;
		uintptr_t result = pointer & filter;
		return result == 0x0000000000000000;
	}

	bool is_guarded(uintptr_t pointer)
	{
		constexpr uintptr_t filter = 0xFFFFFFFF00000000;
		uintptr_t result = pointer & filter;
		return result == 0x8000000000 || result == 0x10000000000;
	}

	uint64_t validate_pointer(uint64_t address)
	{
		if (is_guarded(address))
			return guard + (address & 0xFFFFFF);
		else
			return address;
	}
}