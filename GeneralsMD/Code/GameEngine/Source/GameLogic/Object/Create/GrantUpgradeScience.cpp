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

// FILE: GrantUpgradeScience.cpp ////////////////////////////////////////////////////////////////////////
// Author: Flamer, March 2025
// Desc:   GrantUpgrade through science
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Player.h"
#include "Common/Upgrade.h"
#include "Common/Xfer.h"
#include "GameLogic/Module/GrantUpgradeScience.h"
#include "GameLogic/Object.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
GrantUpgradeScienceModuleData::GrantUpgradeScienceModuleData()
{
	m_upgradeName = "";
    m_scienceRequired = SCIENCE_INVALID;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void GrantUpgradeScienceModuleData::buildFieldParse(MultiIniFieldParse& p)
{
  UpdateModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "UpgradeToGrant",	INI::parseAsciiString,							NULL, offsetof( GrantUpgradeScienceModuleData, m_upgradeName ) },
		{ "ScienceRequired",		INI::parseScience,	NULL, offsetof( GrantUpgradeScienceModuleData, m_scienceRequired ) },
		{ 0, 0, 0, 0 }
	};

  p.add(dataFieldParse);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
GrantUpgradeScience::GrantUpgradeScience( Thing *thing, const ModuleData* moduleData ) : UpdateModule( thing, moduleData )
{
}  // end GrantUpgradeScience

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
GrantUpgradeScience::~GrantUpgradeScience( void )
{

}  // end ~GrantUpgradeScience

//-------------------------------------------------------------------------------------------------
/** The create callback. */
//-------------------------------------------------------------------------------------------------
UpdateSleepTime GrantUpgradeScience::update(void)
{
    const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade( getGrantUpgradeScienceModuleData()->m_upgradeName );
    if( !upgradeTemplate )
        return UPDATE_SLEEP_NONE;

	const GrantUpgradeScienceModuleData *md = getGrantUpgradeScienceModuleData();
	Player *player = getObject()->getControllingPlayer();
	if( player && (md->m_scienceRequired == SCIENCE_INVALID || player->hasScience( md->m_scienceRequired )) )
    {
        if( upgradeTemplate->getUpgradeType() == UPGRADE_TYPE_PLAYER )
        {
            player->addUpgrade( upgradeTemplate, UPGRADE_STATUS_COMPLETE );
        }
        else
        {
            getObject()->giveUpgrade( upgradeTemplate );
        }

        player->getAcademyStats()->recordUpgrade( upgradeTemplate, TRUE );
    }
    return UPDATE_SLEEP_NONE; // Adjust this return value based on your game logic
}
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void GrantUpgradeScience::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void GrantUpgradeScience::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void GrantUpgradeScience::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
