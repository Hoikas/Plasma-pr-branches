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

#include "HeadSpin.h"

#include "hsGeometry3.h"
#include "hsFastMath.h"

hsPoint2 statCosSinTable[9] = // must match length in inline
{
    { 1.f, 0.f },
    { hsConstants::inv_sqrt2<float>, hsConstants::inv_sqrt2<float> },
    { 0.f, 1.f },
    { -hsConstants::inv_sqrt2<float>, hsConstants::inv_sqrt2<float> },
    { -1.f, 0.f },
    { -hsConstants::inv_sqrt2<float>, -hsConstants::inv_sqrt2<float> },
    { 0.f, -1.f },
    { hsConstants::inv_sqrt2<float>, -hsConstants::inv_sqrt2<float> },
    { 1.f, 0.f }
};

const hsPoint2* hsFastMath::fCosSinTable = statCosSinTable;

unsigned char statSeedTable[] = {
    0x69,
    0x69,
    0x68,
    0x67,
    0x67,
    0x66,
    0x65,
    0x65,
    0x64,
    0x63,
    0x63,
    0x62,
    0x61,
    0x61,
    0x60,
    0x5f,
    0x5f,
    0x5e,
    0x5d,
    0x5d,
    0x5c,
    0x5b,
    0x5b,
    0x5a,
    0x5a,
    0x59,
    0x58,
    0x58,
    0x57,
    0x57,
    0x56,
    0x55,
    0x55,
    0x54,
    0x54,
    0x53,
    0x52,
    0x52,
    0x51,
    0x51,
    0x50,
    0x50,
    0x4f,
    0x4e,
    0x4e,
    0x4d,
    0x4d,
    0x4c,
    0x4c,
    0x4b,
    0x4b,
    0x4a,
    0x4a,
    0x49,
    0x48,
    0x48,
    0x47,
    0x47,
    0x46,
    0x46,
    0x45,
    0x45,
    0x44,
    0x44,
    0x43,
    0x43,
    0x42,
    0x42,
    0x41,
    0x41,
    0x40,
    0x40,
    0x3f,
    0x3f,
    0x3e,
    0x3e,
    0x3d,
    0x3d,
    0x3c,
    0x3c,
    0x3c,
    0x3b,
    0x3b,
    0x3a,
    0x3a,
    0x39,
    0x39,
    0x38,
    0x38,
    0x37,
    0x37,
    0x36,
    0x36,
    0x36,
    0x35,
    0x35,
    0x34,
    0x34,
    0x33,
    0x33,
    0x33,
    0x32,
    0x32,
    0x31,
    0x31,
    0x30,
    0x30,
    0x30,
    0x2f,
    0x2f,
    0x2e,
    0x2e,
    0x2e,
    0x2d,
    0x2d,
    0x2c,
    0x2c,
    0x2b,
    0x2b,
    0x2b,
    0x2a,
    0x2a,
    0x29,
    0x29,
    0x29,
    0x28,
    0x28,
    0x28,
    0x27,
    0x27,
    0x26,
    0x26,
    0x26,
    0x25,
    0x25,
    0x25,
    0x24,
    0x24,
    0x23,
    0x23,
    0x23,
    0x22,
    0x22,
    0x22,
    0x21,
    0x21,
    0x20,
    0x20,
    0x20,
    0x1f,
    0x1f,
    0x1f,
    0x1e,
    0x1e,
    0x1e,
    0x1d,
    0x1d,
    0x1d,
    0x1c,
    0x1c,
    0x1c,
    0x1b,
    0x1b,
    0x1b,
    0x1a,
    0x1a,
    0x1a,
    0x19,
    0x19,
    0x19,
    0x18,
    0x18,
    0x18,
    0x17,
    0x17,
    0x17,
    0x16,
    0x16,
    0x16,
    0x15,
    0x15,
    0x15,
    0x14,
    0x14,
    0x14,
    0x13,
    0x13,
    0x13,
    0x13,
    0x12,
    0x12,
    0x12,
    0x11,
    0x11,
    0x11,
    0x10,
    0x10,
    0x10,
    0xf,
    0xf,
    0xf,
    0xf,
    0xe,
    0xe,
    0xe,
    0xd,
    0xd,
    0xd,
    0xd,
    0xc,
    0xc,
    0xc,
    0xb,
    0xb,
    0xb,
    0xb,
    0xa,
    0xa,
    0xa,
    0x9,
    0x9,
    0x9,
    0x9,
    0x8,
    0x8,
    0x8,
    0x7,
    0x7,
    0x7,
    0x7,
    0x6,
    0x6,
    0x6,
    0x6,
    0x5,
    0x5,
    0x5,
    0x5,
    0x4,
    0x4,
    0x4,
    0x3,
    0x3,
    0x3,
    0x3,
    0x2,
    0x2,
    0x2,
    0x2,
    0x1,
    0x1,
    0x1,
    0x1,
    0x0,
    0x0,
    0x0,
    0xff,
    0xfe,
    0xfd,
    0xfc,
    0xfb,
    0xfa,
    0xf9,
    0xf8,
    0xf7,
    0xf7,
    0xf6,
    0xf5,
    0xf4,
    0xf3,
    0xf2,
    0xf1,
    0xf0,
    0xef,
    0xee,
    0xed,
    0xec,
    0xec,
    0xeb,
    0xea,
    0xe9,
    0xe8,
    0xe7,
    0xe6,
    0xe5,
    0xe5,
    0xe4,
    0xe3,
    0xe2,
    0xe1,
    0xe0,
    0xe0,
    0xdf,
    0xde,
    0xdd,
    0xdc,
    0xdb,
    0xdb,
    0xda,
    0xd9,
    0xd8,
    0xd8,
    0xd7,
    0xd6,
    0xd5,
    0xd4,
    0xd4,
    0xd3,
    0xd2,
    0xd1,
    0xd1,
    0xd0,
    0xcf,
    0xce,
    0xce,
    0xcd,
    0xcc,
    0xcb,
    0xcb,
    0xca,
    0xc9,
    0xc9,
    0xc8,
    0xc7,
    0xc7,
    0xc6,
    0xc5,
    0xc4,
    0xc4,
    0xc3,
    0xc2,
    0xc2,
    0xc1,
    0xc0,
    0xc0,
    0xbf,
    0xbe,
    0xbe,
    0xbd,
    0xbc,
    0xbc,
    0xbb,
    0xba,
    0xba,
    0xb9,
    0xb8,
    0xb8,
    0xb7,
    0xb7,
    0xb6,
    0xb5,
    0xb5,
    0xb4,
    0xb3,
    0xb3,
    0xb2,
    0xb2,
    0xb1,
    0xb0,
    0xb0,
    0xaf,
    0xaf,
    0xae,
    0xad,
    0xad,
    0xac,
    0xac,
    0xab,
    0xaa,
    0xaa,
    0xa9,
    0xa9,
    0xa8,
    0xa8,
    0xa7,
    0xa7,
    0xa6,
    0xa5,
    0xa5,
    0xa4,
    0xa4,
    0xa3,
    0xa3,
    0xa2,
    0xa2,
    0xa1,
    0xa0,
    0xa0,
    0x9f,
    0x9f,
    0x9e,
    0x9e,
    0x9d,
    0x9d,
    0x9c,
    0x9c,
    0x9b,
    0x9b,
    0x9a,
    0x9a,
    0x99,
    0x99,
    0x98,
    0x98,
    0x97,
    0x97,
    0x96,
    0x96,
    0x95,
    0x95,
    0x94,
    0x94,
    0x93,
    0x93,
    0x92,
    0x92,
    0x91,
    0x91,
    0x90,
    0x90,
    0x8f,
    0x8f,
    0x8e,
    0x8e,
    0x8d,
    0x8d,
    0x8c,
    0x8c,
    0x8b,
    0x8b,
    0x8b,
    0x8a,
    0x8a,
    0x89,
    0x89,
    0x88,
    0x88,
    0x87,
    0x87,
    0x87,
    0x86,
    0x86,
    0x85,
    0x85,
    0x84,
    0x84,
    0x83,
    0x83,
    0x83,
    0x82,
    0x82,
    0x81,
    0x81,
    0x80,
    0x80,
    0x80,
    0x7f,
    0x7f,
    0x7e,
    0x7e,
    0x7d,
    0x7d,
    0x7d,
    0x7c,
    0x7c,
    0x7b,
    0x7b,
    0x7b,
    0x7a,
    0x7a,
    0x79,
    0x79,
    0x79,
    0x78,
    0x78,
    0x77,
    0x77,
    0x77,
    0x76,
    0x76,
    0x75,
    0x75,
    0x75,
    0x74,
    0x74,
    0x74,
    0x73,
    0x73,
    0x72,
    0x72,
    0x72,
    0x71,
    0x71,
    0x71,
    0x70,
    0x70,
    0x6f,
    0x6f,
    0x6f,
    0x6e,
    0x6e,
    0x6e,
    0x6d,
    0x6d,
    0x6c,
    0x6c,
    0x6c,
    0x6b,
    0x6b,
    0x6b,
    0x6a,
    0x6a
};

float hsFastMath::IATan2OverTwoPi(float y, float x)
{
    const int tabSize = 16; // pad with one extra because hi can go hi
    const int tabMax = tabSize-1;
    static float tab[tabSize+1] = {
                    0.f,
                    0.0105947f,
                    0.0210962f,
                    0.0314165f,
                    0.0414762f,
                    0.0512082f,
                    0.0605595f,
                    0.0694914f,
                    0.0779791f,
                    0.0860104f,
                    0.0935835f,
                    0.100705f,
                    0.107388f,
                    0.113651f,
                    0.119514f,
                    0.125f,
                    0 };

    if( (x == 0)&&(y == 0) )
        return 0;

    int xNeg, yNeg;
    if((yNeg = (y < 0)))y = -y;
    if((xNeg = (x < 0)))x = -x;
    bool yBigger = y >= x;
    float div = yBigger ? x / y : y / x;

    float fInd = div * tabMax;
    int lo = int(fInd);
    int hi = lo+1;
    float frac = fInd - lo;

    float res = tab[lo];
    res += frac * (tab[hi] - res);

    // now move to proper half quadrant
    hsAssert((res >= 0)&&(res <= 0.25f), "Lookup atan2 out of bounds");
    if( yBigger )
        res = 0.25f - res;
    switch( (yNeg << 1)|xNeg )
    {
    case 0:
        break;
    case 1:
        res = 0.5f - res;
        break;
    case 3:
        res += 0.5f;
        break;
    case 2:
        res = 1.f - res;
        break;
    }
    return res;
}

