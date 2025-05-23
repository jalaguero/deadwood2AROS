/*
    Copyright (C) 1995-2010, The AROS Development Team. All rights reserved.

    Desc: Graphics function MoveSprite()
*/
#include <aros/debug.h>
#include <graphics/view.h>
#include <graphics/sprite.h>
#include <oop/oop.h>

#include "graphics_intern.h"
#include "gfxfuncsupport.h"

#include <interface/Hidd_AmigaGfx.h>

/*****************************************************************************

    NAME */
#include <proto/graphics.h>

        AROS_LH4(void, MoveSprite,

/*  SYNOPSIS */
        AROS_LHA(struct ViewPort *, vp, A0),
        AROS_LHA(struct SimpleSprite *, sprite, A1),
        AROS_LHA(WORD, x, D0),
        AROS_LHA(WORD, y, D1),

/*  LOCATION */
        struct GfxBase *, GfxBase, 71, Graphics)

/*  FUNCTION
        Move sprite to a new position on the screen. Coordinates
        are specified relatively to given ViewPort, or relatively
        to the entire View (physical display) if the ViewPort is NULL.

        This function works also with extended sprites, since
        struct SimpleSprite is a part of struct ExtSprite.

    INPUTS
        vp     - a ViewPort for relative sprite positioning or NULL
        sprite - a pointer to a sprite descriptor structure
        x      - a new X coordinate
        y      - a new Y coordinate

    RESULT
        None.

    NOTES
        ViewPort is also used in order to specify the physical display.
        If it's not specified, Amiga(tm) chipset display is assumed.
        This is available only on Amiga(tm) architecture.

    EXAMPLE

    BUGS

    SEE ALSO

    INTERNALS

    HISTORY


******************************************************************************/
{
    AROS_LIBFUNC_INIT

    OOP_Object *gfxhidd;
    struct monitor_driverdata *mdd;

    if (vp) {
        sprite->x = x + vp->DxOffset;
        sprite->y = y + vp->DyOffset;
        mdd = GET_BM_DRIVERDATA(vp->RasInfo->BitMap);
        gfxhidd = mdd->gfxhidd;
    } else {
        sprite->x = x;
        sprite->y = y;
        gfxhidd = (OOP_Object *)PrivGBase(GfxBase)->PlatformData;
    }

    if (sprite->num)
    {
        OOP_MethodID HiddAmigaGfxBase = OOP_GetMethodID(IID_Hidd_AmigaGfx, 0);
        HIDD_AMIGAGFX_SetSpritePos(gfxhidd, sprite->x, sprite->y, sprite->num);
    }
    else HIDD_Gfx_SetCursorPos(gfxhidd, sprite->x, sprite->y);

    AROS_LIBFUNC_EXIT
} /* MoveSprite */
