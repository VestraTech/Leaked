#pragma once
#include "driver.hpp"
#include "hexrays.h"
#include "globals.hpp"

#include <utility>

namespace offsets {

	uint64_t DecryptPtr(uint64_t encryptedValue, uint64_t addr, int v1, int v2, int type)
	{
		uint64_t table = sdk::module_base + 0x6821160;

		uint64_t decodedAnd = encryptedValue & 0xFFFFFFFFFFFFll;
		uint64_t decodedShift = encryptedValue >> 0x30;

		uint64_t finalDecoded = read<uint32_t>(table + (((v1 * (uint32_t)decodedShift + v2 * (uint32_t)(addr >> 3)) >> 0x16) & 0xFFFFFFFC));

		uint64_t decrypted = decodedAnd;
		if (type == 0)
			decrypted ^= ((finalDecoded >> 0x10) | ((uint64_t)(uint16_t)finalDecoded << 0x10) | ((uint64_t)(uint16_t)finalDecoded << 0x20));
		else if (type == 1)
			decrypted ^= ((uint16_t)finalDecoded | ((uint64_t)finalDecoded >> 16 << 16) | ((uint64_t)finalDecoded >> 16 << 32));
		else if (type == 2)
			decrypted ^= ((((uint64_t)(finalDecoded & 0xFFFF0000)) << 16) | ((uint16_t)finalDecoded) | ((uint64_t)(uint16_t)finalDecoded << 16));

		return decrypted;
	}

	std::uint64_t gamemanager() { //yes
		uint64_t addr = sdk::module_base + 0x8E8B4D0;
		uint64_t gameManager = read<uint64_t>(addr);
		gameManager = __ROL8__((__ROL8__(gameManager, 28) ^ 0x20ll) - 58ll, 21);

		return DecryptPtr(gameManager, addr, 0xCD2FA710, 0xBE2A24F5, 2);
	}

	std::uint32_t roundstate() { //yes

		uint32_t current_key_id = 0x7093AA8;
		uint32_t key_table = 0x6821160;

		auto address = sdk::module_base + 0x7B538D8;
		auto decryption = __ROL8__(__ROL8__(read<std::uintptr_t>(sdk::module_base + 0x7B538D8), 24) ^ 0x9BD91A30B343A04i64, 51) & 0xFFFFFFFFFFFF;

		uint32_t key_offset = ((0x40621E9 * read<std::uint32_t>(sdk::module_base + current_key_id) + 0x7AEBD9AB * uint32_t(address >> 3)) >> 22) & 0xFFFFFFFC;
		uint64_t key = read<std::uint32_t>(sdk::module_base + key_table + key_offset);

		uint64_t decryption_key = ((key >> 16) | ((unsigned __int64)(unsigned __int16)key << 16) | ((unsigned __int64)(unsigned __int16)key << 32));

		uint64_t round_manager = decryption ^ decryption_key;

		//std::uintptr_t roundmanager = memory.read<std::uintptr_t>(memory.base + 0x793ED58 - 10) ^ 0x70BD8A15ACF90558i64; //no
		return (((read<std::uint64_t>(round_manager + 0xF8) ^ 0xE3D68D1D) - 0x71F3D53D) ^ 0x1761671F); //yes
	}

	static std::pair<uint64_t, uint32_t> entitymanager(uint64_t game_manager) //yes
	{
		const auto decryption = [&game_manager](const uint32_t offset = 0) -> uint64_t
		{
			return __ROL8__(read<uint64_t>(game_manager + 0xF0 + offset) ^ 0x2106866287C1430C, 0x1F) - 0x869397FABC5DC66F;
		};

		return { decryption(0x0), static_cast<uint32_t>(decryption(8) & 0x3FFFFFFF) };
	}

	namespace player {
		std::uint64_t pawn(std::uint64_t controller) { //yes
			return __ROL8__(read<std::uint64_t>(controller + 0x38) - 0x45668882F60F626Ci64, 9) ^ 0xF3A5054D7BC49AC3;
		}

		std::uint64_t actor(std::uint64_t pawn) { //yes
			return __ROL8__(read<std::uint64_t>(pawn + 0x18) ^ 0x2895D11816D31479i64, 31) - 56i64;
		}

		inline std::uint64_t outline_component(std::uint64_t actor) { //yes
			return __ROL8__(__ROL8__(read<std::uintptr_t>(actor + 0x1C8), 0x11) - 0xD8CF67ED3D8755B0ui64, 0x25);
		}

		inline void outlines(std::uint64_t actor) {
			std::uintptr_t outlinestate = read<std::uintptr_t>(outline_component(actor) + 0xB0);
			outlinestate = read<std::uintptr_t>(outline_component(actor) + 0xB0);
			if (outlinestate != 0 && outlinestate != 0x20748000)
				write<std::uintptr_t>(outline_component(actor) + 0xB0, 0x20748000000300ee);
		}

		inline void removeOutlines(std::uint64_t actor) {
			std::uintptr_t outlinestate = read<std::uintptr_t>(outline_component(actor) + 0xB0);
			outlinestate = read<std::uintptr_t>(outline_component(actor) + 0xB0);
			if (outlinestate == 0x20748000)
				write<std::uintptr_t>(outline_component(actor) + 0xB0, 0x20748000000300ee);
		}
	}
}