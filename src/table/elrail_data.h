/* $Id$ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file elrail_data.h Stores all the data for overhead wire and pylon drawing.
 *  @see elrail.c
 */

#ifndef ELRAIL_DATA_H
#define ELRAIL_DATA_H

static const uint NUM_TRACKS_PER_SIDE = 3;

/* This array stores which tracks can meet at a tile edge */
static const Track TracksAtTileSide[DIAGDIR_END][NUM_TRACKS_PER_SIDE] = {
	{TRACK_X, TRACK_UPPER, TRACK_RIGHT},
	{TRACK_Y, TRACK_LOWER, TRACK_RIGHT},
	{TRACK_X, TRACK_LOWER, TRACK_LEFT },
	{TRACK_Y, TRACK_UPPER, TRACK_LEFT },
};

/** Which PPPs are possible at all on a given PCP */
static const byte AllowedPPPonPCP[DIAGDIR_END] = {
	1 << DIR_N | 1 << DIR_E  | 1 << DIR_SE | 1 << DIR_S | 1 << DIR_W  | 1 << DIR_NW,
	1 << DIR_N | 1 << DIR_NE | 1 << DIR_E  | 1 << DIR_S | 1 << DIR_SW | 1 << DIR_W,
	1 << DIR_N | 1 << DIR_E  | 1 << DIR_SE | 1 << DIR_S | 1 << DIR_W  | 1 << DIR_NW,
	1 << DIR_N | 1 << DIR_NE | 1 << DIR_E  | 1 << DIR_S | 1 << DIR_SW | 1 << DIR_W,
};

/**
 * Which of the PPPs are inside the tile. For the two PPPs on the tile border
 * the following system is used: if you rotate the PCP so that it is in the
 * north, the eastern PPP belongs to the tile.
 */
static const byte OwnedPPPonPCP[DIAGDIR_END] = {
	1 << DIR_SE | 1 << DIR_S  | 1 << DIR_SW | 1 << DIR_W,
	1 << DIR_N  | 1 << DIR_SW | 1 << DIR_W  | 1 << DIR_NW,
	1 << DIR_N  | 1 << DIR_NE | 1 << DIR_E  | 1 << DIR_NW,
	1 << DIR_NE | 1 << DIR_E  | 1 << DIR_SE | 1 << DIR_S
};

/** Maps a track bit onto two PCP positions */
static const DiagDirection PCPpositions[TRACK_END][2] = {
	{DIAGDIR_NE, DIAGDIR_SW}, // X
	{DIAGDIR_SE, DIAGDIR_NW}, // Y
	{DIAGDIR_NW, DIAGDIR_NE}, // UPPER
	{DIAGDIR_SE, DIAGDIR_SW}, // LOWER
	{DIAGDIR_SW, DIAGDIR_NW}, // LEFT
	{DIAGDIR_NE, DIAGDIR_SE}, // RIGHT
};

#define PCP_NOT_ON_TRACK 0xFF
/**
 * Preferred points of each trackbit. Those are the ones perpendicular to the
 * track, plus the point in extension of the track (to mark end-of-track). PCPs
 * which are not on either end of the track are fully preferred.
 * @see PCPpositions
 */
static const byte PreferredPPPofTrackAtPCP[TRACK_END][DIAGDIR_END] = {
	{    // X
		1 << DIR_NE | 1 << DIR_SE | 1 << DIR_NW, // NE
		PCP_NOT_ON_TRACK,                        // SE
		1 << DIR_SE | 1 << DIR_SW | 1 << DIR_NW, // SW
		PCP_NOT_ON_TRACK                         // NE
	}, { // Y
		PCP_NOT_ON_TRACK,
		1 << DIR_NE | 1 << DIR_SE | 1 << DIR_SW,
		PCP_NOT_ON_TRACK,
		1 << DIR_SW | 1 << DIR_NW | 1 << DIR_NE
	}, { // UPPER
		1 << DIR_E | 1 << DIR_N | 1 << DIR_S,
		PCP_NOT_ON_TRACK,
		PCP_NOT_ON_TRACK,
		1 << DIR_W | 1 << DIR_N | 1 << DIR_S
	}, { // LOWER
		PCP_NOT_ON_TRACK,
		1 << DIR_E | 1 << DIR_N | 1 << DIR_S,
		1 << DIR_W | 1 << DIR_N | 1 << DIR_S,
		PCP_NOT_ON_TRACK
	}, { // LEFT
		PCP_NOT_ON_TRACK,
		PCP_NOT_ON_TRACK,
		1 << DIR_S | 1 << DIR_E | 1 << DIR_W,
		1 << DIR_N | 1 << DIR_E | 1 << DIR_W
	}, { // RIGHT
		1 << DIR_N | 1 << DIR_E | 1 << DIR_W,
		1 << DIR_S | 1 << DIR_E | 1 << DIR_W,
		PCP_NOT_ON_TRACK,
		PCP_NOT_ON_TRACK
	}
};
#undef PCP_NOT_ON_TRACK


#define NUM_IGNORE_GROUPS 3

/**
 * In case we have a straight line, we place pylon only every two tiles,
 * so there are certain tiles which we ignore. A straight line is found if
 * we have exactly two PPPs.
 */
static const byte IgnoredPCPconfigs[AXIS_END][NUM_IGNORE_GROUPS] = {
	{    // X axis
		1 << DIR_NW | 1 << DIR_SE,
		1 << DIR_E  | 1 << DIR_W,
		1 << DIR_N  | 1 << DIR_S,
	}, { // Y axis
		1 << DIR_NE | 1 << DIR_SW,
		1 << DIR_E  | 1 << DIR_W,
		1 << DIR_N  | 1 << DIR_S,
	}
};

/**
 * In case we have a straight line, we place pylon only every two tiles,
 * so there are certain tiles which we ignore. This struct encodes on
 * which tile sides pylons are omitted.
 */
static const byte IgnoredPCP[AXIS_END][2] = {
	{    // X axis
		0x6, // configurations to ignore on even X and even Y tile sides
		  0, // configurations to ignore on even X and odd Y tile sides
	}, { // Y axis
		0x5, // configurations to ignore on odd Y and even X tile sides
		0x3, // configurations to ignore on odd Y and odd X tile sides
	}
};

/** Which pylons can definitely NOT be built */
static const byte AllowedPPPofTrackAtPCP[TRACK_END] = {
	1 << DIR_N  | 1 << DIR_E  | 1 << DIR_SE | 1 << DIR_S  | 1 << DIR_W  | 1 << DIR_NW, // X
	1 << DIR_N  | 1 << DIR_NE | 1 << DIR_E  | 1 << DIR_S  | 1 << DIR_SW | 1 << DIR_W,  // Y
	1 << DIR_N  | 1 << DIR_NE | 1 << DIR_SE | 1 << DIR_S  | 1 << DIR_SW | 1 << DIR_NW, // UPPER
	1 << DIR_N  | 1 << DIR_NE | 1 << DIR_SE | 1 << DIR_S  | 1 << DIR_SW | 1 << DIR_NW, // LOWER
	1 << DIR_NE | 1 << DIR_E  | 1 << DIR_SE | 1 << DIR_SW | 1 << DIR_W  | 1 << DIR_NW, // LEFT
	1 << DIR_NE | 1 << DIR_E  | 1 << DIR_SE | 1 << DIR_SW | 1 << DIR_W  | 1 << DIR_NW, // RIGHT
};

/* Several PPPs maybe exist, here they are sorted in order of preference. */
static const Direction PPPorder[2][2][DIAGDIR_END][DIR_END] = {
	{    // X even
		{    // Y even
			{DIR_NE, DIR_NW, DIR_SE, DIR_SW, DIR_N, DIR_E, DIR_S, DIR_W}, // NE
			{DIR_NE, DIR_NW, DIR_SE, DIR_SW, DIR_S, DIR_E, DIR_N, DIR_W}, // SE
			{DIR_NE, DIR_NW, DIR_SE, DIR_SW, DIR_S, DIR_W, DIR_N, DIR_E}, // SW
			{DIR_NE, DIR_NW, DIR_SE, DIR_SW, DIR_N, DIR_W, DIR_S, DIR_E}, // NW
		}, { // Y odd
			{DIR_NE, DIR_SE, DIR_SW, DIR_NW, DIR_S, DIR_W, DIR_N, DIR_E}, // NE
			{DIR_NE, DIR_SE, DIR_SW, DIR_NW, DIR_N, DIR_W, DIR_S, DIR_E}, // SE
			{DIR_NE, DIR_SE, DIR_SW, DIR_NW, DIR_N, DIR_E, DIR_S, DIR_W}, // SW
			{DIR_NE, DIR_SE, DIR_SW, DIR_NW, DIR_S, DIR_E, DIR_N, DIR_W}, // NW
		}
	}, { // X odd
		{    // Y even
			{DIR_SW, DIR_NW, DIR_NE, DIR_SE, DIR_S, DIR_W, DIR_N, DIR_E}, // NE
			{DIR_SW, DIR_NW, DIR_NE, DIR_SE, DIR_N, DIR_W, DIR_S, DIR_E}, // SE
			{DIR_SW, DIR_NW, DIR_NE, DIR_SE, DIR_N, DIR_E, DIR_S, DIR_W}, // SW
			{DIR_SW, DIR_NW, DIR_NE, DIR_SE, DIR_S, DIR_E, DIR_N, DIR_W}, // NW
		}, { // Y odd
			{DIR_SW, DIR_SE, DIR_NE, DIR_NW, DIR_N, DIR_E, DIR_S, DIR_W}, // NE
			{DIR_SW, DIR_SE, DIR_NE, DIR_NW, DIR_S, DIR_E, DIR_N, DIR_W}, // SE
			{DIR_SW, DIR_SE, DIR_NE, DIR_NW, DIR_S, DIR_W, DIR_N, DIR_E}, // SW
			{DIR_SW, DIR_SE, DIR_NE, DIR_NW, DIR_N, DIR_W, DIR_S, DIR_E}, // NW
		}
	}
};

/* Geometric placement of the PCP relative to the tile origin */
static const int8 x_pcp_offsets[DIAGDIR_END] = {0,  8, 16, 8};
static const int8 y_pcp_offsets[DIAGDIR_END] = {8, 16,  8, 0};
/* Geometric placement of the PPP relative to the PCP*/
static const int8 x_ppp_offsets[DIR_END] = {-2, -4, -2,  0,  2,  4,  2,  0};
static const int8 y_ppp_offsets[DIR_END] = {-2,  0,  2,  4,  2,  0, -2, -4};

/**
 * Offset for pylon sprites from the base pylon sprite.
 */
enum PylonSpriteOffset {
	PSO_Y_NE,
	PSO_Y_SW,
	PSO_X_NW,
	PSO_X_SE,
	PSO_EW_N,
	PSO_EW_S,
	PSO_NS_W,
	PSO_NS_E,
};

/* The type of pylon to draw at each PPP */
static const uint8 pylon_sprites[] = {
	PSO_EW_N,
	PSO_Y_NE,
	PSO_NS_E,
	PSO_X_SE,
	PSO_EW_S,
	PSO_Y_SW,
	PSO_NS_W,
	PSO_X_NW,
};

/**
 * Offset for wire sprites from the base wire sprite.
 */
enum WireSpriteOffset {
	WSO_X_SHORT,
	WSO_Y_SHORT,
	WSO_EW_SHORT,
	WSO_NS_SHORT,
	WSO_X_SHORT_DOWN,
	WSO_Y_SHORT_UP,
	WSO_X_SHORT_UP,
	WSO_Y_SHORT_DOWN,

	WSO_X_SW,
	WSO_Y_SE,
	WSO_EW_E,
	WSO_NS_S,
	WSO_X_SW_DOWN,
	WSO_Y_SE_UP,
	WSO_X_SW_UP,
	WSO_Y_SE_DOWN,

	WSO_X_NE,
	WSO_Y_NW,
	WSO_EW_W,
	WSO_NS_N,
	WSO_X_NE_DOWN,
	WSO_Y_NW_UP,
	WSO_X_NE_UP,
	WSO_Y_NW_DOWN,

	WSO_ENTRANCE_NE,
	WSO_ENTRANCE_SE,
	WSO_ENTRANCE_SW,
	WSO_ENTRANCE_NW,

	WSO_INVALID = 0xFF,
};

struct SortableSpriteStructM {
	uint8 image_offset[4];
	int8 x_offset;
	int8 y_offset;
	int8 x_size;
	int8 y_size;
	int8 z_size;
	int8 z_offset;
};

/** Distance between wire and rail */
static const uint ELRAIL_ELEVATION = 10;
/** Wires that a draw one level higher than the north corner. */
static const uint ELRAIL_ELEVRAISE = ELRAIL_ELEVATION + TILE_HEIGHT;

static const SortableSpriteStructM CatenarySpriteData[TRACK_END] = {
	{ { WSO_INVALID, WSO_X_NE, WSO_X_SW, WSO_X_SHORT  },  0,  7, 15,  1,  1, ELRAIL_ELEVATION }, // X flat
	{ { WSO_INVALID, WSO_Y_SE, WSO_Y_NW, WSO_Y_SHORT  },  7,  0,  1, 15,  1, ELRAIL_ELEVATION }, // Y flat
	{ { WSO_INVALID, WSO_EW_W, WSO_EW_E, WSO_EW_SHORT },  7,  0,  1,  1,  1, ELRAIL_ELEVATION }, // UPPER
	{ { WSO_INVALID, WSO_EW_E, WSO_EW_W, WSO_EW_SHORT }, 15,  8,  3,  3,  1, ELRAIL_ELEVATION }, // LOWER
	{ { WSO_INVALID, WSO_NS_S, WSO_NS_N, WSO_NS_SHORT },  8,  0,  8,  8,  1, ELRAIL_ELEVATION }, // LEFT
	{ { WSO_INVALID, WSO_NS_N, WSO_NS_S, WSO_NS_SHORT },  0,  8,  8,  8,  1, ELRAIL_ELEVATION }, // RIGHT
};

static const SortableSpriteStructM CatenarySpriteDataSW =
	{ { WSO_INVALID, WSO_X_NE_UP,   WSO_X_SW_UP,   WSO_X_SHORT_UP   },  0,  7, 15,  8,  1, ELRAIL_ELEVRAISE }; // X up

static const SortableSpriteStructM CatenarySpriteDataSE =
	{ { WSO_INVALID, WSO_Y_SE_UP,   WSO_Y_NW_UP,   WSO_Y_SHORT_UP   },  7,  0,  8, 15,  1, ELRAIL_ELEVRAISE }; // Y up

static const SortableSpriteStructM CatenarySpriteDataNW =
	{ { WSO_INVALID, WSO_Y_SE_DOWN, WSO_Y_NW_DOWN, WSO_Y_SHORT_DOWN },  7,  0,  8, 15,  1, ELRAIL_ELEVATION }; // Y down

static const SortableSpriteStructM CatenarySpriteDataNE =
	{ { WSO_INVALID, WSO_X_NE_DOWN, WSO_X_SW_DOWN, WSO_X_SHORT_DOWN },  0,  7, 15,  8,  1, ELRAIL_ELEVATION }; // X down


#endif /* ELRAIL_DATA_H */
