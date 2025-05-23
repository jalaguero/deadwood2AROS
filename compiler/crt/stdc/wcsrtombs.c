/*-
 * Copyright (c) 2002-2004 Tim J. Robbins.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

/*****************************************************************************

    NAME */

size_t wcsrtombs(

    /*  SYNOPSIS */
        char * restrict dst, 
        const wchar_t ** restrict src,
        size_t len, 
        mbstate_t * restrict ps)

/*  FUNCTION
        Converts a sequence of up to len wide characters from the array indirectly pointed to by src,
        into a sequence of corresponding multibyte characters that begins in the conversion
        state described by the object pointed to by ps.

    INPUTS
        dst - Pointer to an array of char elements long enough to store a C string of len bytes.
        src - Pointer to a C wide string to be translated.
        len - Maximum number of bytes characters to write to dst.
        ps  - Pointer to a mbstate_t object that defines a conversion state.

    RESULT
        The number of bytes written to dst, not including the eventual terminating null character.

    NOTES
        stdc.library currently only implements "C" locale.

    EXAMPLE

    BUGS

    SEE ALSO

    INTERNALS

******************************************************************************/
{
        static mbstate_t mbs;

        if (ps == NULL)
                ps = &mbs;
        return (wcsnrtombs(dst, src, SIZE_T_MAX, len, ps));
}