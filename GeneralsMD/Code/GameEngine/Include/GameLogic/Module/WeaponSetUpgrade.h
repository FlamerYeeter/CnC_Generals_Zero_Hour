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

// FILE: WeaponSetUpgrade.h /////////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, March 2002
// Desc:	 UpgradeModule that sets a weapon set bit for the Best Fit weapon set chooser to discover
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __WEAPON_SET_UPGRADE_H_
#define __WEAPON_SET_UPGRADE_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "GameLogic/Module/UpgradeModule.h"

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class Thing;

//-------------------------------------------------------------------------------------------------
/** The default	die module */
//-------------------------------------------------------------------------------------------------

// New code, now you get to choose what flag to set 
// (allowing you to have multiple weaponset flag choices, good for units that wanted to have different weapon sets or kits)
enum WeaponSetType;
//-----------------------------------------------------------------------------
class WeaponSetUpgradeModuleData : public UpgradeModuleData
{
public:
	WeaponSetType m_weaponSetFlag;

	WeaponSetUpgradeModuleData();

	static void buildFieldParse(MultiIniFieldParse& p);
};

//-----------------------------------------------------------------------------
class WeaponSetUpgrade : public UpgradeModule
{

	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( WeaponSetUpgrade, "WeaponSetUpgrade" )
	MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA( WeaponSetUpgrade, WeaponSetUpgradeModuleData );

public:

	WeaponSetUpgrade( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype defined by MemoryPoolObject

protected:
	virtual void upgradeImplementation( ); ///< Here's the actual work of Upgrading
	virtual Bool isSubObjectsUpgrade() { return false; }

};


#endif // __DEFAULTDIE_H_

