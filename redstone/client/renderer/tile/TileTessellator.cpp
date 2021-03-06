#include "../../../../mcpe/client/renderer/tile/TileTessellator.h"
#include "../../../../mcpe/client/renderer/renderer/Tessellator.h"
#include "../../../../mcpe/client/renderer/texture/TextureUVCoordinateSet.h"
#include "../../../../mcpe/world/phys/Vec3.h"
#include "../../../../mcpe/world/level/TilePos.h"
#include "../../../../mcpe/world/level/TileSource.h"
#include "../../../world/level/tile/RedstoneTile.h"
#include "../../../world/level/tile/NotGateTile.h"
#include "../../../world/level/tile/LeverTile.h"
#include "../../../world/level/tile/RepeaterTile.h"
#include "../../../world/level/tile/PistonBaseTile.h"
#include "../../../world/level/tile/PistonArmTile.h"

#include <vector>

bool TileTessellator::tessellateRedstoneInWorld(RedstoneTile* tile, const TilePos& pos, int data) {
	int x = pos.x, y = pos.y, z = pos.z;

	TextureUVCoordinateSet cross(0.125F, 0.5F, 0.1562F, 0.5625F);
	TextureUVCoordinateSet line(0.1875F, 0.5F, 0.2187F, 0.5625F);

	tessellator->color(tile->getColor(tile, region, x, y, z));

	bool var19 = tile->canRedstoneConnect(region, x - 1, y, z, 1) || (!Tile::solid[region->getTile(x - 1, y, z).id] && tile->canRedstoneConnect(region, x - 1, y - 1, z, -1));
	bool var20 = tile->canRedstoneConnect(region, x + 1, y, z, 3) || (!Tile::solid[region->getTile(x + 1, y, z).id] && tile->canRedstoneConnect(region, x + 1, y - 1, z, -1));
	bool var21 = tile->canRedstoneConnect(region, x, y, z - 1, 2) || (!Tile::solid[region->getTile(x, y, z - 1).id] && tile->canRedstoneConnect(region, x, y - 1, z - 1, -1));
	bool avec3d = tile->canRedstoneConnect(region, x, y, z + 1, 0) || (!Tile::solid[region->getTile(x, y, z + 1).id] && tile->canRedstoneConnect(region, x, y - 1, z + 1, -1));

	if(!Tile::solid[region->getTile(x, y + 1, z).id]) {
		if(Tile::solid[region->getTile(x - 1, y, z).id] && tile->canRedstoneConnect(region, x - 1, y + 1, z, -1))
			var19 = true;
		if(Tile::solid[region->getTile(x + 1, y, z).id] && tile->canRedstoneConnect(region, x + 1, y + 1, z, -1))
			var20 = true;
		if(Tile::solid[region->getTile(x, y, z - 1).id] && tile->canRedstoneConnect(region, x, y + 1, z - 1, -1))
			var21 = true;
		if(Tile::solid[region->getTile(x, y, z + 1).id] && tile->canRedstoneConnect(region, x, y + 1, z + 1, -1))
			avec3d = true;
	}

	float var23 = (float)(x + 0);
	float var24 = (float)(x + 1);
	float var25 = (float)(z + 0);
	float i2 = (float)(z + 1);
	int var27 = 0;

	if((var19 || var20) && !var21 && !avec3d)
		var27 = 1;
	if((var21 || avec3d) && !var20 && !var19)
		var27 = 2;
	if(var27 == 0) {
		int var28 = 0;
		int var29 = 0;
		int var30 = 16;
		int var31 = 16;

		if(!var19) var23 += 0.3125;
		if(!var19) var28 += 5;
		if(!var20) var24 -= 0.3125;
		if(!var20) var30 -= 5;
		if(!var21) var25 += 0.3125;
		if(!var21) var29 += 5;
		if(!avec3d) i2 -= 0.3125;
		if(!avec3d) var31 -= 5;

		tessellator->vertexUV(var24, y + 0.015625, i2, cross.getInterpolatedU(var30), cross.getInterpolatedV(var31));
		tessellator->vertexUV(var24, y + 0.015625, var25, cross.getInterpolatedU(var30), cross.getInterpolatedV(var29));
		tessellator->vertexUV(var23, y + 0.015625, var25, cross.getInterpolatedU(var28), cross.getInterpolatedV(var29));
		tessellator->vertexUV(var23, y + 0.015625, i2, cross.getInterpolatedU(var28), cross.getInterpolatedV(var31));
	} else if(var27 == 1) {
		tessellator->vertexUV(var24, y + 0.015625, i2, line.maxU, line.maxV);
		tessellator->vertexUV(var24, y + 0.015625, var25, line.maxU, line.minV);
		tessellator->vertexUV(var23, y + 0.015625, var25, line.minU, line.minV);
		tessellator->vertexUV(var23, y + 0.015625, i2, line.minU, line.maxV);
	} else {
		tessellator->vertexUV(var24, y + 0.015625, i2, line.maxU, line.maxV);
		tessellator->vertexUV(var24, y + 0.015625, var25, line.minU, line.maxV);
		tessellator->vertexUV(var23, y + 0.015625, var25, line.minU, line.minV);
		tessellator->vertexUV(var23, y + 0.015625, i2, line.maxU, line.minV);
	}

	if(!Tile::solid[region->getTile(x, y + 1, z).id]) {
		if(Tile::solid[region->getTile(x - 1, y, z).id] && region->getTile(x - 1, y + 1, z).id == tile->id) {
			tessellator->color(tile->getColor(tile, region, x, y, z));
			tessellator->vertexUV(x + 0.015625, ((float) (y + 1) + 0.021875), (z + 1), line.maxU, line.minV);
			tessellator->vertexUV(x + 0.015625, (y + 0), (z + 1), line.minU, line.minV);
			tessellator->vertexUV(x + 0.015625, (y + 0), (z + 0), line.minU, line.maxV);
			tessellator->vertexUV(x + 0.015625, ((float) (y + 1) + 0.021875), (z + 0), line.maxU, line.maxV);
		}
		if(Tile::solid[region->getTile(x + 1, y, z).id] && region->getTile(x + 1, y + 1, z).id == tile->id) {
			tessellator->color(tile->getColor(tile, region, x, y, z));
			tessellator->vertexUV((x + 1) - 0.015625, (y + 0), (z + 1), line.minU, line.maxV);
			tessellator->vertexUV((x + 1) - 0.015625, ((float) (y + 1) + 0.021875), (z + 1), line.maxU, line.maxV);
			tessellator->vertexUV((x + 1) - 0.015625, ((float) (y + 1) + 0.021875), (z + 0), line.maxU, line.minV);
			tessellator->vertexUV((x + 1) - 0.015625, (y + 0), (z + 0), line.minU, line.minV);
		}
		if(Tile::solid[region->getTile(x, y, z - 1).id] && region->getTile(x, y + 1, z - 1).id == tile->id) {
			tessellator->color(tile->getColor(tile, region, x, y, z));
			tessellator->vertexUV((x + 1), (y + 0), z + 0.015625, line.minU, line.maxV);
			tessellator->vertexUV((x + 1), ((float) (y + 1) + 0.021875), z + 0.015625, line.maxU, line.maxV);
			tessellator->vertexUV((x + 0), ((float) (y + 1) + 0.021875), z + 0.015625, line.maxU, line.minV);
			tessellator->vertexUV((x + 0), (y + 0), z + 0.015625, line.minU, line.minV);
		}
		if(Tile::solid[region->getTile(x, y, z + 1).id] && region->getTile(x, y + 1, z + 1).id == tile->id) {
			tessellator->color(tile->getColor(tile, region, x, y, z));
			tessellator->vertexUV((x + 1), ((float) (y + 1) + 0.021875), (z + 1) - 0.015625, line.maxU, line.minV);
			tessellator->vertexUV((x + 1), (y + 0), (z + 1) - 0.015625, line.minU, line.minV);
			tessellator->vertexUV((x + 0), (y + 0), (z + 1) - 0.015625, line.minU, line.maxV);
			tessellator->vertexUV((x + 0), ((float) (y + 1) + 0.021875), (z + 1) - 0.015625, line.maxU, line.maxV);
		}
	}
	return true;
}

bool TileTessellator::tessellateLitNotGateInWorld(NotGateTile* tile, const TilePos& pos, int data) {
	int x = pos.x, y = pos.y, z = pos.z;

	tessellator->color(0xFFFFFF);

	double var7 = 0.4000000059604645;
	double var9 = 0.5F - var7;
	double var11 = 0.20000000298023224;

	if(data == 1)
		tessellateAngledNotGate(tile, x - var9, y + var11, z, -var7, 0.0F);
	else if(data == 2)
		tessellateAngledNotGate(tile, x + var9, y + var11, z, var7, 0.0F);
	else if(data == 3)
		tessellateAngledNotGate(tile, x, y + var11, z - var9, 0.0F, -var7);
	else if(data == 4)
		tessellateAngledNotGate(tile, x, y + var11, z + var9, 0.0F, var7);
	else
		tessellateAngledNotGate(tile, x, y, z, 0.0F, 0.0F);
	return true;
}

void TileTessellator::tessellateAngledNotGate(Tile* tile, double x, double y, double z, double xRot, double zRot) {
	TextureUVCoordinateSet torch = tile->tex;

	float var15 = torch.minU;
	float var17 = torch.minV;
	float var19 = torch.maxU;
	float var21 = torch.maxV;
	float var23 = torch.getInterpolatedU(7.0F);
	float var25 = torch.getInterpolatedV(6.0F);
	float var27 = torch.getInterpolatedU(9.0F);
	float var29 = torch.getInterpolatedV(8.0F);
	float var31 = torch.getInterpolatedU(7.0F);
	float var33 = torch.getInterpolatedV(13.0F);
	float var35 = torch.getInterpolatedU(9.0F);
	float var37 = torch.getInterpolatedV(15.0F);
	x += 0.5F;
	z += 0.5F;
	float var39 = x - 0.5F;
	float var41 = x + 0.5F;
	float var43 = z - 0.5F;
	float var45 = z + 0.5F;
	float var47 = 0.0625F;
	float var49 = 0.625F;

	tessellator->vertexUV(x + xRot * (1.0F - var49) - var47, y + var49, z + zRot * (1.0F - var49) - var47, var23, var25);
	tessellator->vertexUV(x + xRot * (1.0F - var49) - var47, y + var49, z + zRot * (1.0F - var49) + var47, var23, var29);
	tessellator->vertexUV(x + xRot * (1.0F - var49) + var47, y + var49, z + zRot * (1.0F - var49) + var47, var27, var29);
	tessellator->vertexUV(x + xRot * (1.0F - var49) + var47, y + var49, z + zRot * (1.0F - var49) - var47, var27, var25);
	tessellator->vertexUV(x + var47 + xRot, y, z - var47 + zRot, var35, var33);
	tessellator->vertexUV(x + var47 + xRot, y, z + var47 + zRot, var35, var37);
	tessellator->vertexUV(x - var47 + xRot, y, z + var47 + zRot, var31, var37);
	tessellator->vertexUV(x - var47 + xRot, y, z - var47 + zRot, var31, var33);
	tessellator->vertexUV(x - var47, y + 1.0F, var43, var15, var17);
	tessellator->vertexUV(x - var47 + xRot, y + 0.0F, var43 + zRot, var15, var21);
	tessellator->vertexUV(x - var47 + xRot, y + 0.0F, var45 + zRot, var19, var21);
	tessellator->vertexUV(x - var47, y + 1.0F, var45, var19, var17);
	tessellator->vertexUV(x + var47, y + 1.0F, var45, var15, var17);
	tessellator->vertexUV(x + xRot + var47, y + 0.0F, var45 + zRot, var15, var21);
	tessellator->vertexUV(x + xRot + var47, y + 0.0F, var43 + zRot, var19, var21);
	tessellator->vertexUV(x + var47, y + 1.0F, var43, var19, var17);
	tessellator->vertexUV(var39, y + 1.0F, z + var47, var15, var17);
	tessellator->vertexUV(var39 + xRot, y + 0.0F, z + var47 + zRot, var15, var21);
	tessellator->vertexUV(var41 + xRot, y + 0.0F, z + var47 + zRot, var19, var21);
	tessellator->vertexUV(var41, y + 1.0F, z + var47, var19, var17);
	tessellator->vertexUV(var41, y + 1.0F, z - var47, var15, var17);
	tessellator->vertexUV(var41 + xRot, y + 0.0F, z - var47 + zRot, var15, var21);
	tessellator->vertexUV(var39 + xRot, y + 0.0F, z - var47 + zRot, var19, var21);
	tessellator->vertexUV(var39, y + 1.0F, z - var47, var19, var17);
}

bool TileTessellator::tessellateLeverInWorld(LeverTile* tile, const TilePos& pos) {
	int x = pos.x, y = pos.y, z = pos.z;

	int data = region->getData(x, y, z);
	int rot = data & 7;
	bool flag = (data & 8) > 0;

	tile->getVisualShapeInWorld(tile, region, x, y, z, bounds, false);
	tessellateBlockInWorld(Tile::tiles[4], pos);

	tessellator->color(0xFFFFFF);

	TextureUVCoordinateSet lever = tile->tex;

	float f4 = lever.minU;
	float f5 = lever.minV;
	float f6 = lever.maxU;
	float f7 = lever.maxV;
	float f8 = 0.0625;
	float f9 = 0.0625;
	float f10 = 0.625;

	Vec3 vec30 {-f8, 0.0, -f9};
	Vec3 vec31 {f8, 0.0, -f9};
	Vec3 vec32 {f8, 0.0, f9};
	Vec3 vec33 {-f8, 0.0, f9};
	Vec3 vec34 {-f8, f10, -f9};
	Vec3 vec35 {f8, f10, -f9};
	Vec3 vec36 {f8, f10, f9};
	Vec3 vec37 {-f8, f10, f9};
	Vec3 avec3d[8] = {vec30, vec31, vec32, vec33, vec34, vec35, vec36, vec37};

	for(int i2 = 0; i2 < 8; i2++) {
		if(flag) {
			avec3d[i2].z -= 0.0625F;
			avec3d[i2].rotateAroundX(PI * 2.0F / 9.0F);
		} else {
			avec3d[i2].z += 0.0625F;
			avec3d[i2].rotateAroundX(-(PI * 2.0F / 9.0F));
		}
		if (rot == 0 || rot == 7) {
			avec3d[i2].rotateAroundZ(PI);
		}
		if (rot == 6 || rot == 0) {
			avec3d[i2].rotateAroundY((PI / 2.0));
		}

		if (rot > 0 && rot < 5) {
			avec3d[i2].y -= 0.37501;
			avec3d[i2].rotateAroundX((PI / 2.0));

			if (rot == 4) avec3d[i2].rotateAroundY(0.0);

			if (rot == 3) avec3d[i2].rotateAroundY(PI);

			if (rot == 2) avec3d[i2].rotateAroundY((PI / 2.0));

			if (rot == 1) avec3d[i2].rotateAroundY(-(PI / 2.0));

			avec3d[i2].x += (float) x + 0.5F;
			avec3d[i2].y += (float) y + 0.5F;
			avec3d[i2].z += (float) z + 0.5F;
		} else if (rot != 0 && rot != 7) {
			avec3d[i2].x += (float) x + 0.5F;
			avec3d[i2].y += (float) y + 0.125F;
			avec3d[i2].z += (float) z + 0.5F;
		} else {
			avec3d[i2].x += (float) x + 0.5F;
			avec3d[i2].y += (float) y + 0.875F;
			avec3d[i2].z += (float) z + 0.5F;
		}
	}

	Vec3 vec3d;
	Vec3 vec3d1;
	Vec3 vec3d2;
	Vec3 vec3d3;

	for(int j2 = 0; j2 < 6; j2++) {
		if(j2 == 0) {
			f4 = lever.getInterpolatedU(7.0);
			f5 = lever.getInterpolatedV(6.0);
			f6 = lever.getInterpolatedU(9.0);
			f7 = lever.getInterpolatedV(8.0);
		} else if(j2 == 2) {
			f4 = lever.getInterpolatedU(7.0);
			f5 = lever.getInterpolatedV(6.0);
			f6 = lever.getInterpolatedU(9.0);
			f7 = lever.maxV;
		}

		if(j2 == 0) {
			vec3d = avec3d[0];
			vec3d1 = avec3d[1];
			vec3d2 = avec3d[2];
			vec3d3 = avec3d[3];
		} else if(j2 == 1) {
			vec3d = avec3d[7];
			vec3d1 = avec3d[6];
			vec3d2 = avec3d[5];
			vec3d3 = avec3d[4];
		} else if(j2 == 2) {
			vec3d = avec3d[1];
			vec3d1 = avec3d[0];
			vec3d2 = avec3d[4];
			vec3d3 = avec3d[5];
		} else if(j2 == 3) {
			vec3d = avec3d[2];
			vec3d1 = avec3d[1];
			vec3d2 = avec3d[5];
			vec3d3 = avec3d[6];
		} else if(j2 == 4) {
			vec3d = avec3d[3];
			vec3d1 = avec3d[2];
			vec3d2 = avec3d[6];
			vec3d3 = avec3d[7];
		} else if(j2 == 5) {
			vec3d = avec3d[0];
			vec3d1 = avec3d[3];
			vec3d2 = avec3d[7];
			vec3d3 = avec3d[4];
		}
		tessellator->vertexUV(vec3d.x, vec3d.y, vec3d.z, f4, f7);
		tessellator->vertexUV(vec3d1.x, vec3d1.y, vec3d1.z, f6, f7);
		tessellator->vertexUV(vec3d2.x, vec3d2.y, vec3d2.z, f6, f5);
		tessellator->vertexUV(vec3d3.x, vec3d3.y, vec3d3.z, f4, f5);
	}
	return true;
}


bool TileTessellator::tessellateRepeaterInWorld(RepeaterTile* tile, const TilePos& pos, int ass) {
	int x = pos.x, y = pos.y, z = pos.z;
	int data = region->getData(x, y, z);
	int rotation = data & 3;
	int delay = (data & 12) >> 2;

	tessellator->color(0xFFFFFF);

	Tile* torch = (tile->powered)? Tile::tiles[76] : Tile::tiles[75];

	double var9 = -0.1875F;
	double var12 = 0.0F;
	double var14 = 0.0F;
	double var16 = 0.0F;
	double var18 = 0.0F;

	switch(rotation) {
	case 0:
	rotTop = 0;
	var18 = -0.3125F;
	var14 = tile->torchOffset[delay];
	break;
	case 1:
	rotTop = 1;
	var16 = 0.3125F;
	var12 = -tile->torchOffset[delay];
	break;
	case 2:
	rotTop = 3;
	var18 = 0.3125F;
	var14 = -tile->torchOffset[delay];
	break;
	case 3:
	rotTop = 2;
	var16 = -0.3125F;
	var12 = tile->torchOffset[delay];
	}

	tessellateAngledNotGate(torch, x + var12, y + var9, z + var14, 0.0F, 0.0F);
	tessellateAngledNotGate(torch, x + var16, y + var9, z + var18, 0.0F, 0.0F);

	bounds.set(0.0F, 0.0F, 0.0F, 1.0F, 0.125F, 1.0F);
	tessellateBlockInWorld(tile, pos);

	return true;
}

bool TileTessellator::tessellatePistonBaseInWorld(PistonBaseTile* tile, const TilePos& pos, bool faceAllSides) {
	int x = pos.x, y = pos.y, z = pos.z;
	int data = region->getData(x, y, z);
	bool flag = faceAllSides || (data & 8) != 0;
	int rot = tile->getRotation(data);

	if(flag) {
		switch(rot) {
		case 0:
			rotEast = 3;
			rotWest = 3;
			rotSouth = 3;
			rotNorth = 3;
			bounds.set(0.0F, 0.25F, 0.0F, 1.0F, 1.0F, 1.0F);
			break;
		case 1:
			bounds.set(0.0F, 0.0F, 0.0F, 1.0F, 0.75F, 1.0F);
			break;
		case 2:
			rotSouth = 1;
			rotNorth = 2;
			bounds.set(0.0F, 0.0F, 0.25F, 1.0F, 1.0F, 1.0F);
			break;
		case 3:
			rotSouth = 2;
			rotNorth = 1;
			rotTop = 3;
			rotBottom = 3;
			bounds.set(0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 0.75F);
			break;
		case 4:
			rotEast = 1;
			rotWest = 2;
			rotTop = 2;
			rotBottom = 1;
			bounds.set(0.25F, 0.0F, 0.0F, 1.0F, 1.0F, 1.0F);
			break;
		case 5:
			rotEast = 2;
			rotWest = 1;
			rotTop = 1;
			rotBottom = 2;
			bounds.set(0.0F, 0.0F, 0.0F, 0.75F, 1.0F, 1.0F);
		}

		bounds = tile->getVisualShapeInWorld(tile, region, x, y, z, bounds, true);
		tessellateBlockInWorld(tile, pos);
		rotEast = 0;
		rotWest = 0;
		rotSouth = 0;
		rotNorth = 0;
		rotTop = 0;
		rotBottom = 0;
		bounds.set(0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 1.0F);
		tile->hitbox = bounds;
	}
	else {
		switch(rot) {
		case 0:
			rotEast = 3;
			rotWest = 3;
			rotSouth = 3;
			rotNorth = 3;
		case 1:
			break;
		case 2:
			rotSouth = 1;
			rotNorth = 2;
			break;
		case 3:
			rotSouth = 2;
			rotNorth = 1;
			rotTop = 3;
			rotBottom = 3;
			break;
		case 4:
			rotEast = 1;
			rotWest = 2;
			rotTop = 2;
			rotBottom = 1;
			break;
		case 5:
			rotEast = 2;
			rotWest = 1;
			rotTop = 1;
			rotBottom = 2;
		}

		tessellateBlockInWorld(tile, pos);
	
		rotEast = 0;
		rotWest = 0;
		rotSouth = 0;
		rotNorth = 0;
		rotTop = 0;
		rotBottom = 0;
	}

	return true;
}

bool TileTessellator::tessellatePistonArmInWorld(PistonArmTile* tile, const TilePos& pos, bool powered) {
	int x = pos.x, y = pos.y, z = pos.z;
	int data = region->getData(x, y, z);
	int rotation = PistonArmTile::getRotation(data);
	float var8 = 0.25F;
	float var9 = 0.375F;
	float var10 = 0.625F;
	float var11 = powered ? 1.0F : 0.5F;
	float var12 = powered ? 16.0F : 8.0F;

	bounds = tile->getVisualShapeInWorld(tile, region, x, y, z, bounds, false);
	switch(rotation) {
	case 0:
		rotEast = 3;
		rotWest = 3;
		rotSouth = 3;
		rotNorth = 3;
		tessellateBlockInWorld(tile, pos);
		tessellatePistonRodUD(tile, x + 0.375F, x + 0.625F, y + 0.25F, y + 0.25F + var11, z + 0.625F, z + 0.625F, 0.8F, var12);
		tessellatePistonRodUD(tile, x + 0.625F, x + 0.375F, y + 0.25F, y + 0.25F + var11, z + 0.375F, z + 0.375F, 0.8F, var12);
		tessellatePistonRodUD(tile, x + 0.375F, x + 0.375F, y + 0.25F, y + 0.25F + var11, z + 0.375F, z + 0.625F, 0.6F, var12);
		tessellatePistonRodUD(tile, x + 0.625F, x + 0.625F, y + 0.25F, y + 0.25F + var11, z + 0.625F, z + 0.375F, 0.6F, var12);
		break;
	case 1:
		tessellateBlockInWorld(tile, pos);
		tessellatePistonRodUD(tile, x + 0.375F, x + 0.625F, y - 0.25F + 1.0F - var11, y - 0.25F + 1.0F, z + 0.625F, z + 0.625F, 0.8F, var12);
		tessellatePistonRodUD(tile, x + 0.625F, x + 0.375F, y - 0.25F + 1.0F - var11, y - 0.25F + 1.0F, z + 0.375F, z + 0.375F, 0.8F, var12);
		tessellatePistonRodUD(tile, x + 0.375F, x + 0.375F, y - 0.25F + 1.0F - var11, y - 0.25F + 1.0F, z + 0.375F, z + 0.625F, 0.6F, var12);
		tessellatePistonRodUD(tile, x + 0.625F, x + 0.625F, y - 0.25F + 1.0F - var11, y - 0.25F + 1.0F, z + 0.625F, z + 0.375F, 0.6F, var12);
		break;
	case 2:
		rotSouth = 1;
		rotNorth = 2;
		tessellateBlockInWorld(tile, pos);
		tessellatePistonRodSN(tile, x + 0.375F, x + 0.375F, y + 0.625F, y + 0.375F, z + 0.25F, z + 0.25F + var11, 0.6F, var12);
		tessellatePistonRodSN(tile, x + 0.625F, x + 0.625F, y + 0.375F, y + 0.625F, z + 0.25F, z + 0.25F + var11, 0.6F, var12);
		tessellatePistonRodSN(tile, x + 0.375F, x + 0.625F, y + 0.375F, y + 0.375F, z + 0.25F, z + 0.25F + var11, 0.5F, var12);
		tessellatePistonRodSN(tile, x + 0.625F, x + 0.375F, y + 0.625F, y + 0.625F, z + 0.25F, z + 0.25F + var11, 1.0F, var12);
		break;
	case 3:
		rotSouth = 2;
		rotNorth = 1;
		rotTop = 3;
		rotBottom = 3;
		tessellateBlockInWorld(tile, pos);
		tessellatePistonRodSN(tile, x + 0.375F, x + 0.375F, y + 0.625F, y + 0.375F, z - 0.25F + 1.0F - var11, z - 0.25F + 1.0F, 0.6F, var12);
		tessellatePistonRodSN(tile, x + 0.625F, x + 0.625F, y + 0.375F, y + 0.625F, z - 0.25F + 1.0F - var11, z - 0.25F + 1.0F, 0.6F, var12);
		tessellatePistonRodSN(tile, x + 0.375F, x + 0.625F, y + 0.375F, y + 0.375F, z - 0.25F + 1.0F - var11, z - 0.25F + 1.0F, 0.5F, var12);
		tessellatePistonRodSN(tile, x + 0.625F, x + 0.375F, y + 0.625F, y + 0.625F, z - 0.25F + 1.0F - var11, z - 0.25F + 1.0F, 1.0F, var12);
		break;
	case 4:
		rotEast = 1;
		rotWest = 2;
		rotTop = 2;
		rotBottom = 1;
		tessellateBlockInWorld(tile, pos);
		tessellatePistonRodEW(tile, x + 0.25F, x + 0.25F + var11, y + 0.375F, y + 0.375F, z + 0.625F, z + 0.375F, 0.5F, var12);
		tessellatePistonRodEW(tile, x + 0.25F, x + 0.25F + var11, y + 0.625F, y + 0.625F, z + 0.375F, z + 0.625F, 1.0F, var12);
		tessellatePistonRodEW(tile, x + 0.25F, x + 0.25F + var11, y + 0.375F, y + 0.625F, z + 0.375F, z + 0.375F, 0.6F, var12);
		tessellatePistonRodEW(tile, x + 0.25F, x + 0.25F + var11, y + 0.625F, y + 0.375F, z + 0.625F, z + 0.625F, 0.6F, var12);
		break;
	case 5:
		rotEast = 2;
		rotWest = 1;
		rotTop = 1;
		rotBottom = 2;
		tessellateBlockInWorld(tile, pos);
		tessellatePistonRodEW(tile, x - 0.25F + 1.0F - var11, x - 0.25F + 1.0F, y + 0.375F, y + 0.375F, z + 0.625F, z + 0.375F, 0.5F, var12);
		tessellatePistonRodEW(tile, x - 0.25F + 1.0F - var11, x - 0.25F + 1.0F, y + 0.625F, y + 0.625F, z + 0.375F, z + 0.625F, 1.0F, var12);
		tessellatePistonRodEW(tile, x - 0.25F + 1.0F - var11, x - 0.25F + 1.0F, y + 0.375F, y + 0.625F, z + 0.375F, z + 0.375F, 0.6F, var12);
		tessellatePistonRodEW(tile, x - 0.25F + 1.0F - var11, x - 0.25F + 1.0F, y + 0.625F, y + 0.375F, z + 0.625F, z + 0.625F, 0.6F, var12);
	}

	rotEast = 0;
	rotWest = 0;
	rotSouth = 0;
	rotNorth = 0;
	rotTop = 0;
	rotBottom = 0;
	bounds.set(0.0F, 0.0F, 0.0F, 1.0F, 1.0F, 1.0F);
	return true;
}

void TileTessellator::tessellatePistonRodUD(PistonArmTile* tile, float x, float xx, float y, float yy, float z, float zz, float a, float b) {
	TextureUVCoordinateSet piston = tile->texture_side;
	
	float var18 = piston.minU;
	float var20 = piston.minV;
	float var22 = piston.getInterpolatedU(b);
	float var24 = piston.getInterpolatedV(4.0);
	tessellator->color(0xFFFFFF);
	tessellator->vertexUV(x, yy, z, var22, var20);
	tessellator->vertexUV(x, y, z, var18, var20);
	tessellator->vertexUV(xx, y, zz, var18, var24);
	tessellator->vertexUV(xx, yy, zz, var22, var24);
}

void TileTessellator::tessellatePistonRodSN(PistonArmTile* tile, float x, float xx, float y, float yy, float z, float zz, float a, float b) {
	TextureUVCoordinateSet piston = tile->texture_side;

	float var18 = piston.minU;
	float var20 = piston.minV;
	float var22 = piston.getInterpolatedU(b);
	float var24 = piston.getInterpolatedV(4.0);
	tessellator->color(0xFFFFFF);
	tessellator->vertexUV(x, y, zz, var22, var20);
	tessellator->vertexUV(x, y, z, var18, var20);
	tessellator->vertexUV(xx, yy, z, var18, var24);
	tessellator->vertexUV(xx, yy, zz, var22, var24);
}

void TileTessellator::tessellatePistonRodEW(PistonArmTile* tile, float x, float xx, float y, float yy, float z, float zz, float a, float b) {
	TextureUVCoordinateSet piston = tile->texture_side;
	
	float var18 = piston.minU;
	float var20 = piston.minV;
	float var22 = piston.getInterpolatedU(b);
	float var24 = piston.getInterpolatedV(4.0);
	tessellator->color(0xFFFFFF);
	tessellator->vertexUV(xx, y, z, var22, var20);
	tessellator->vertexUV(x, y, z, var18, var20);
	tessellator->vertexUV(x, yy, zz, var18, var24);
	tessellator->vertexUV(xx, yy, zz, var22, var24);
}
