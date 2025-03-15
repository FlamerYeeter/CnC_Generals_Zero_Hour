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

// FILE: GrantUpgradeScience.h //////////////////////////////////////////////////////////////////////////
// Author: Flamer, March 2025
// Desc:   GrantUpgrade through science
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __GRANTUPGRADESCIENCE_H_
#define __GRANTUPGRADESCIENCE_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "GameLogic/Object.h"
#include "Common/GameCommon.h"
#include "Common/Science.h"
#include "GameLogic/Module/UpdateModule.h"

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class Thing;

//-------------------------------------------------------------------------------------------------
/** The GrantUpgrade create module */
//-------------------------------------------------------------------------------------------------

class GrantUpgradeScienceModuleData : public UpdateModuleData
{
public:
	AsciiString		m_upgradeName;			///< name of the upgrade to be granted.
	ScienceType		m_scienceRequired;

	GrantUpgradeScienceModuleData();
	static void buildFieldParse(MultiIniFieldParse& p);
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
class GrantUpgradeScience : public UpdateModule
{

	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( GrantUpgradeScience, "GrantUpgradeScience" );
	MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA( GrantUpgradeScience, GrantUpgradeScienceModuleData );


public:

	GrantUpgradeScience( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype provided by memory pool declaration

	/// the create method
	virtual UpdateSleepTime update( void );

protected:

};

#endif // __GRANTUPGRADESCIENCE_H_

