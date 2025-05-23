/*
    Copyright (C) 1995-2010, The AROS Development Team. All rights reserved.

    Desc: Graphics function ChangeExtSpriteA()
*/

#include <aros/debug.h>
#include <graphics/gfxbase.h>
#include <graphics/clip.h>
#include <graphics/view.h>
#include <graphics/sprite.h>
#include <utility/tagitem.h>
#include <proto/utility.h>

#include "graphics_intern.h"
#include "gfxfuncsupport.h"

#include <interface/Hidd_AmigaGfx.h>

/*****************************************************************************

    NAME */
#include <proto/graphics.h>

        AROS_LH4(LONG, ChangeExtSpriteA,

/*  SYNOPSIS */
        AROS_LHA(struct ViewPort *, vp, A0),
        AROS_LHA(struct ExtSprite *, oldsprite, A1),
        AROS_LHA(struct ExtSprite *, newsprite, A2),
        AROS_LHA(struct TagItem *, tags, A3),

/*  LOCATION */
        struct GfxBase *, GfxBase, 171, Graphics)

/*  FUNCTION

    INPUTS
        vp        - pointer to ViewPort structure that this sprite is
                    relative to, or NULL if relative only top of View
        oldsprite - pointer to the old ExtSprite structure
        newsprite - pointer to the new ExtSprite structure
        tags      - pointer to taglist

    RESULT
        success - 0 if there was an error

    NOTES

    EXAMPLE

    BUGS

    SEE ALSO

    INTERNALS
        With vp set to NULL the function always fails at the moment.

    HISTORY


******************************************************************************/
{
    AROS_LIBFUNC_INIT

    OOP_Object *bitmap;
    struct monitor_driverdata *mdd;
    LONG res;

    D(bug("ChangeExtSpriteA(0x%p, 0x%p, 0x%p)\n", vp, oldsprite, newsprite));

    /* Pick up position from old sprite */
    newsprite->es_SimpleSprite.x = oldsprite->es_SimpleSprite.x;
    newsprite->es_SimpleSprite.y = oldsprite->es_SimpleSprite.y;
    D(bug("Sprite position: (%d, %d)\n", newsprite->es_SimpleSprite.x, newsprite->es_SimpleSprite.y));

    bitmap = OBTAIN_HIDD_BM(newsprite->es_BitMap);
    D(bug("HIDD bitmap object: 0x%p\n", bitmap));

    if (vp) {
        /* Pick up display driver from ViewPort's bitmap */
        mdd = GET_BM_DRIVERDATA(vp->RasInfo->BitMap);

        if(newsprite->es_SimpleSprite.num == 0)
        {
            res = HIDD_Gfx_SetCursorShape(mdd->gfxhidd, bitmap, 0, 0);
            if (res)
                HIDD_Gfx_SetCursorVisible(mdd->gfxhidd, TRUE);
        }
        else
        {
            OOP_MethodID HiddAmigaGfxBase = OOP_GetMethodID(IID_Hidd_AmigaGfx, 0);
            res = HIDD_AMIGAGFX_SetSpriteShape(mdd->gfxhidd, bitmap, 0, 0, newsprite->es_SimpleSprite.num);
            if (res)
                HIDD_AMIGAGFX_SetSpriteVisible(mdd->gfxhidd, TRUE, newsprite->es_SimpleSprite.num);
        }
    } else
        /* TODO: NULL ViewPort means Amiga(tm) chipset display */
        res = FALSE;

    RELEASE_HIDD_BM(bitmap, newsprite->es_BitMap);
    return res;

    AROS_LIBFUNC_EXIT
} /* ChangeExtSpriteA */
