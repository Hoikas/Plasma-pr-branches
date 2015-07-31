/*==LICENSE==*

CyanWorlds.com Engine - MMOG client, server and tools
Copyright (C) 2011  Cyan Worlds, Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Additional permissions under GNU GPL version 3 section 7

If you modify this Program, or any covered work, by linking or
combining it with any of RAD Game Tools Bink SDK, Autodesk 3ds Max SDK,
NVIDIA PhysX SDK, Microsoft DirectX SDK, OpenSSL library, Independent
JPEG Group JPEG library, Microsoft Windows Media SDK, or Apple QuickTime SDK
(or a modified version of those libraries),
containing parts covered by the terms of the Bink SDK EULA, 3ds Max EULA,
PhysX SDK EULA, DirectX SDK EULA, OpenSSL and SSLeay licenses, IJG
JPEG Library README, Windows Media SDK EULA, or QuickTime SDK EULA, the
licensors of this Program grant you additional
permission to convey the resulting work. Corresponding Source for a
non-source form of such a combination shall include the source code for
the parts of OpenSSL and IJG JPEG Library used as well as that of the covered
work.

You can contact Cyan Worlds, Inc. by email legal@cyan.com
 or by snail mail at:
      Cyan Worlds, Inc.
      14617 N Newport Hwy
      Mead, WA   99021

*==LICENSE==*/
//////////////////////////////////////////////////////////////////////
//
// pyVaultAgeInfoNode   - a wrapper class to provide interface to the RelVaultNode
//
//////////////////////////////////////////////////////////////////////

#include <Python.h>
#pragma hdrstop

#include "pyVaultAgeInfoNode.h"

#include "pyVaultAgeInfoListNode.h"
#include "pyVaultPlayerInfoListNode.h"
#include "pyVaultPlayerInfoNode.h"
#include "pyVaultSDLNode.h"
#include "pyVaultAgeLinkNode.h"
#include "pyNetLinkingMgr.h"
#include "pyAgeInfoStruct.h"

#include "pnUUID/pnUUID.h"
#include "plVault/plVault.h"

// should only be created from C++ side
pyVaultAgeInfoNode::pyVaultAgeInfoNode(RelVaultNode* nfsNode)
: pyVaultNode(nfsNode)
{
}

//create from the Python side
pyVaultAgeInfoNode::pyVaultAgeInfoNode(int n)
: pyVaultNode(new RelVaultNode)
{
    fNode->SetNodeType(plVault::kNodeType_AgeInfo);
}

//============================================================================
/*
static PyObject * GetChildFolder (RelVaultNode * node, unsigned type) {
    PyObject * result = nil;
    if (RelVaultNode * rvn = node->GetChildFolderNodeIncRef(type, 1)) {
        result = pyVaultFolderNode::New(rvn);
        rvn->UnRef();
    }
    return result;
}
*/

//============================================================================
static PyObject * GetChildPlayerInfoList (RelVaultNode * node, unsigned type) {
    PyObject * result = nil;
    if (hsRef<RelVaultNode> rvn = node->GetChildPlayerInfoListNode(type, 1))
        result = pyVaultPlayerInfoListNode::New(rvn);
    return result;
}

//============================================================================
static PyObject * GetChildAgeInfoList (RelVaultNode * node, unsigned type) {
    PyObject * result = nil;
    if (hsRef<RelVaultNode> rvn = node->GetChildAgeInfoListNode(type, 1))
        result = pyVaultAgeInfoListNode::New(rvn);
    return result;
}

//==================================================================
// class RelVaultNode : public plVaultNode
//

PyObject * pyVaultAgeInfoNode::GetAgeOwnersFolder() const
{
    if (!fNode)
        PYTHON_RETURN_NONE;

    if (PyObject * result = GetChildPlayerInfoList(fNode, plVault::kAgeOwnersFolder))
        return result;

    // just return a None object.
    PYTHON_RETURN_NONE;
}

PyObject * pyVaultAgeInfoNode::GetCanVisitFolder() const
{
    if (!fNode)
        PYTHON_RETURN_NONE;

    if (PyObject * result = GetChildPlayerInfoList(fNode, plVault::kCanVisitFolder))
        return result;

    // just return a None object.
    PYTHON_RETURN_NONE;
}

PyObject* pyVaultAgeInfoNode::GetChildAgesFolder( void )
{
    if (!fNode)
        PYTHON_RETURN_NONE;

    if (PyObject * result = GetChildAgeInfoList(fNode, plVault::kChildAgesFolder))
        return result;

    // just return a None object.
    PYTHON_RETURN_NONE;
}


PyObject * pyVaultAgeInfoNode::GetAgeSDL() const
{
    if (!fNode)
        PYTHON_RETURN_NONE;

    hsAssert(false, "eric, port me");
    // just return a None object.
    PYTHON_RETURN_NONE
}

PyObject * pyVaultAgeInfoNode::GetCzar() const
{
    if (!fNode)
        PYTHON_RETURN_NONE;

    hsAssert(false, "eric, port me");

    // just return a None object.
    PYTHON_RETURN_NONE
}

PyObject * pyVaultAgeInfoNode::GetParentAgeLink () const
{
    if (!fNode)
        PYTHON_RETURN_NONE;

    if (hsRef<RelVaultNode> rvn = fNode->GetParentAgeLink())
        return pyVaultAgeLinkNode::New(rvn);

    // just return a None object.
    PYTHON_RETURN_NONE
}


plString pyVaultAgeInfoNode::GetAgeFilename() const
{
    if (fNode) {
        VaultAgeInfoNode access(fNode);
        return access.GetAgeFilename();
    }
    return "";
}

void pyVaultAgeInfoNode::SetAgeFilename(const plString& v)
{
}

plString pyVaultAgeInfoNode::GetAgeInstanceName() const
{
    if (fNode) {
        VaultAgeInfoNode access(fNode);
        return access.GetAgeInstanceName();
    }
    return "";
}

void pyVaultAgeInfoNode::SetAgeInstanceName(const plString& v)
{
}

plString pyVaultAgeInfoNode::GetAgeUserDefinedName() const
{
    if (fNode) {
        VaultAgeInfoNode access(fNode);
        return access.GetAgeUserDefinedName();
    }
    return "";
}

void pyVaultAgeInfoNode::SetAgeUserDefinedName(const plString& v)
{
}

plUUID pyVaultAgeInfoNode::GetAgeInstanceGuid() const
{
    if (fNode) {
        VaultAgeInfoNode access(fNode);

        return access.GetAgeInstanceGuid();
    }
    return kNilUuid;
}

void pyVaultAgeInfoNode::SetAgeInstanceGuid( const char * sguid )
{
}

plString pyVaultAgeInfoNode::GetAgeDescription() const
{
    if (fNode) {
        VaultAgeInfoNode access(fNode);
        return access.GetAgeDescription();
    }
    return "";
}

void pyVaultAgeInfoNode::SetAgeDescription(const plString& v)
{
}

int32_t pyVaultAgeInfoNode::GetSequenceNumber() const
{
    if (!fNode)
        return -1;

    VaultAgeInfoNode access(fNode);
    return access.GetAgeSequenceNumber();
}

void pyVaultAgeInfoNode::SetSequenceNumber( int32_t v )
{
}

int32_t pyVaultAgeInfoNode::GetAgeLanguage() const
{
    if (!fNode)
        return -1;

    VaultAgeInfoNode access(fNode);
    return access.GetAgeLanguage();
}

void pyVaultAgeInfoNode::SetAgeLanguage( int32_t v )
{
}

uint32_t pyVaultAgeInfoNode::GetAgeID() const
{
    return 0;
}

void pyVaultAgeInfoNode::SetAgeID( uint32_t v )
{
}

uint32_t pyVaultAgeInfoNode::GetCzarID() const
{
    hsAssert(false, "eric, port me");
    return 0;
}


bool pyVaultAgeInfoNode::IsPublic() const
{
    if (fNode) {
        VaultAgeInfoNode access(fNode);
        return access.GetIsPublic();
    }
    return false;
}

plString pyVaultAgeInfoNode::GetDisplayName() const
{
    if (fNode) {
        VaultAgeInfoNode access(fNode);
        if (access.GetAgeSequenceNumber() > 0)
            return plFormat("{}({}) {}", access.GetAgeUserDefinedName(), access.GetAgeSequenceNumber(), access.GetAgeInstanceName());
        else
            return plFormat("{} {}", access.GetAgeUserDefinedName(), access.GetAgeInstanceName());
    }
    return "";
}

PyObject * pyVaultAgeInfoNode::AsAgeInfoStruct() const
{
    plAgeInfoStruct info;
    VaultAgeInfoNode access(fNode);
    access.CopyTo(&info);
    return pyAgeInfoStruct::New(&info);
}