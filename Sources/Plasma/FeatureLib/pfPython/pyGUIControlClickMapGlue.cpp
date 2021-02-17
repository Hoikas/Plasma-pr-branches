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

#include <Python.h>
#include "pyKey.h"

#include "pyGUIControlClickMap.h"

// glue functions
PYTHON_CLASS_DEFINITION(ptGUIControlClickMap, pyGUIControlClickMap);

PYTHON_DEFAULT_NEW_DEFINITION(ptGUIControlClickMap, pyGUIControlClickMap)
PYTHON_DEFAULT_DEALLOC_DEFINITION(ptGUIControlClickMap)

PYTHON_INIT_DEFINITION(ptGUIControlClickMap, args, keywords)
{
    PyObject *keyObject = nullptr;
    if (!PyArg_ParseTuple(args, "O", &keyObject))
    {
        PyErr_SetString(PyExc_TypeError, "__init__ expects a ptKey");
        PYTHON_RETURN_INIT_ERROR;
    }
    if (!pyKey::Check(keyObject))
    {
        PyErr_SetString(PyExc_TypeError, "__init__ expects a ptKey");
        PYTHON_RETURN_INIT_ERROR;
    }

    pyKey *key = pyKey::ConvertFrom(keyObject);
    self->fThis->setKey(key->getKey());

    PYTHON_RETURN_INIT_OK;
}

PYTHON_METHOD_DEFINITION_NOARGS(ptGUIControlClickMap, getLastMousePoint)
{
    return self->fThis->GetLastMousePt();
}

PYTHON_METHOD_DEFINITION_NOARGS(ptGUIControlClickMap, getLastMouseUpPoint)
{
    return self->fThis->GetLastMouseUpPt();
}

PYTHON_METHOD_DEFINITION_NOARGS(ptGUIControlClickMap, getLastMouseDragPoint)
{
    return self->fThis->GetLastMouseDragPt();
}

PYTHON_START_METHODS_TABLE(ptGUIControlClickMap)
    PYTHON_METHOD_NOARGS(ptGUIControlClickMap, getLastMousePoint, "Returns the last point the mouse was at"),
    PYTHON_METHOD_NOARGS(ptGUIControlClickMap, getLastMouseUpPoint, "Returns the last point the mouse was released at"),
    PYTHON_METHOD_NOARGS(ptGUIControlClickMap, getLastMouseDragPoint, "Returns the last point the mouse was dragged to"),
PYTHON_END_METHODS_TABLE;

// Type structure definition
PLASMA_DEFAULT_TYPE_WBASE(ptGUIControlClickMap, pyGUIControl, "Params: ctrlKey\nPlasma GUI control Click Map");

// required functions for PyObject interoperability
PyObject *pyGUIControlClickMap::New(pyKey& gckey)
{
    ptGUIControlClickMap *newObj = (ptGUIControlClickMap*)ptGUIControlClickMap_type.tp_new(&ptGUIControlClickMap_type, nullptr, nullptr);
    newObj->fThis->fGCkey = gckey.getKey();
    return (PyObject*)newObj;
}

PyObject *pyGUIControlClickMap::New(plKey objkey)
{
    ptGUIControlClickMap *newObj = (ptGUIControlClickMap*)ptGUIControlClickMap_type.tp_new(&ptGUIControlClickMap_type, nullptr, nullptr);
    newObj->fThis->fGCkey = objkey;
    return (PyObject*)newObj;
}

PYTHON_CLASS_CHECK_IMPL(ptGUIControlClickMap, pyGUIControlClickMap)
PYTHON_CLASS_CONVERT_FROM_IMPL(ptGUIControlClickMap, pyGUIControlClickMap)

///////////////////////////////////////////////////////////////////////////
//
// AddPlasmaClasses - the python module definitions
//
void pyGUIControlClickMap::AddPlasmaClasses(PyObject *m)
{
    PYTHON_CLASS_IMPORT_START(m);
    PYTHON_CLASS_IMPORT(m, ptGUIControlClickMap);
    PYTHON_CLASS_IMPORT_END(m);
}