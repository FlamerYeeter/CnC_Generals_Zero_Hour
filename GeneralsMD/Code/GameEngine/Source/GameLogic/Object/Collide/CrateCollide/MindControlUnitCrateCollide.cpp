/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//	
// FILE: MindControlUnitCrateCollide.cpp 
// Author: Flameryeeter, March 2025
// Desc:   A crate that forcibly mind controls a unit.
//	
///////////////////////////////////////////////////////////////////////////////////////////////////
 


// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameAudio.h"
#include "Common/MiscAudio.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Radar.h"
#include "Common/Team.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"

#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/InGameUI.h"  // useful for printing quick debug strings when we need to

#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/MindControlUnitCrateCollide.h"
#include "GameLogic/Module/HijackerUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Module/DozerAIUpdate.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
MindControlUnitCrateCollide::MindControlUnitCrateCollide( Thing *thing, const ModuleData* moduleData ) : CrateCollide( thing, moduleData )
{
} 

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
MindControlUnitCrateCollide::~MindControlUnitCrateCollide( void )
{
}  

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
Bool MindControlUnitCrateCollide::isValidToExecute( const Object *other ) const
{
	if( !CrateCollide::isValidToExecute(other) )
	{
		return FALSE;
	}

	if( other->isEffectivelyDead() )
	{
		return FALSE;// can't hijack a dead vehicle
	}
	
	if( other->isKindOf( KINDOF_IMMUNE_TO_CAPTURE ) )
	{
		return FALSE; //Kris: Patch 1.03 -- Prevent hijackers from being able to hijack battle buses.
	}

	if( other->isKindOf( KINDOF_AIRCRAFT ) )
	{
		//Can't hijack planes and boats!
		return FALSE;
	}

	if( other->isKindOf( KINDOF_DRONE ) )
	{
		//Can't hijack drones!
		return FALSE;
	}

	if( other->getStatusBits().test( OBJECT_STATUS_HIJACKED ) )
	{
		return FALSE;// oops, sorry, I'll jack the next one.
	}

	Relationship r = getObject()->getRelationship( other );
	//Only hijack enemy objects
	if( r != ENEMIES )
	{
		return FALSE;
	}

	if( other->isKindOf( KINDOF_TRANSPORT ) )
	{
		//Kris: Allow empty transports to be hijacked.
		if( other->getContain() && other->getContain()->getContainCount() > 0 )
		{
			return FALSE;// dustin sez: do not jack vehicles that may carry hostile passengers
		}
	}

	//Kris: Make sure you can't hijack any aircraft (or hijack-enter).
	if( other->isKindOf( KINDOF_AIRCRAFT ) )
	{
		return FALSE;
	}

	return TRUE;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
Bool MindControlUnitCrateCollide::executeCrateBehavior( Object *other )
{
    //Check to make sure that the other object is also the goal object in the AIUpdateInterface
    //in order to prevent an unintentional conversion simply by having the terrorist walk too close
    //to it.
    //Assume ai is valid because CrateCollide::isValidToExecute(other) checks it.
    Object *obj = getObject();
    AIUpdateInterface* ai = obj->getAIUpdateInterface();
    if (ai && ai->getGoalObject() != other)
    {
        return false;
    }

    Player *player = obj->getControllingPlayer(); // Get the sabotaging player
    if( player )
    {
        // Instead of damaging, make the target defect to the sabotaging player’s team.
        other->defect( player->getDefaultTeam(), 1 ); // Defect for 1 frame to create a flash effect
    }

    return TRUE;
}


// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void MindControlUnitCrateCollide::crc( Xfer *xfer )
{

	// extend base class
	CrateCollide::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void MindControlUnitCrateCollide::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	CrateCollide::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void MindControlUnitCrateCollide::loadPostProcess( void )
{

	// extend base class
	CrateCollide::loadPostProcess();

}  // end loadPostProcess
