#pragma once

namespace esp {
	bool outlines;
	void run() {
		for (int i = 1; i < offsets::entitymanager(offsets::gamemanager()).second; i++)
		{
			uint64_t player = read<uint64_t>(offsets::entitymanager(offsets::gamemanager()).first + (i * sizeof(uint64_t)));
			if (!player) continue;
			uint64_t pawn = offsets::player::pawn(player);
			if (!pawn) continue;
			uint64_t actor = offsets::player::actor(pawn);
			if (!actor) continue;

			offsets::player::outlines(actor);
			Sleep(0);
		}
	}
}