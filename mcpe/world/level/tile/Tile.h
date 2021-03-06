#pragma once

#include <string>
#include <stdint.h>
#include "../../../world/phys/AABB.h"
#include "../../../client/renderer/texture/TextureUVCoordinateSet.h"
#include "../../../../addresses.h"
class Material;
class Random;
struct ItemInstance;
class TileSource;

class Tile {
public:
	Tile(int, TextureUVCoordinateSet, Material*, const std::string&);
	void init();
	void popResource(TileSource*, int, int, int, const ItemInstance&);

	static void (*$init)(Tile*);
	static void (*$popResource)(Tile*, TileSource*, int, int, int, const ItemInstance&);
	static uint8_t* lightBlock;
	static Tile** tiles;
	static bool* solid;
	static bool* shouldTick;
	static void** _vtable;

	void** vtable;
	bool replaceable;
	AABB hitbox;
	TextureUVCoordinateSet tex;
	unsigned char id;
	void* soundType;
	bool canBuildOver;
	int renderPass;
	int renderType;
	int tileType;
	int tileEntityType;
	float thickness;
	bool hasGravity;
	bool ticks;
	float gravity;
	Material* material;
	float friction;
	float destroyTime;
	float explosionResistance;
	int creativeTab;
	bool fancy;
	unsigned int textureIsotropic;
	std::string name;

	static Tile* redstoneDust;
	static Tile* pistonNormal;
	static Tile* pistonSticky;
	static Tile* pistonArm;
	static Tile* notGate_on;
	static Tile* notGate_off;
	static Tile* buttonStone;
	static Tile* buttonWood;
	static Tile* plateWood;
	static Tile* plateStone;
	static Tile* plateGold;
	static Tile* plateIron;
	static Tile* lever;
	static Tile* lamp_off;
	static Tile* lamp_on;
	static Tile* diode_off;
	static Tile* diode_on;
};