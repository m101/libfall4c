/***************************************************************************
 *            stringManipulation.h
 *
 *  Sun Apr 29 18:16:19 2007
 *  Copyright  2007  User
 *  Email
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _STRINGMANIPULATION_H
#define _STRINGMANIPULATION_H

#ifdef __cplusplus
extern "C"
{
#endif

    struct string_t {
        char *string;
        size_t szString;
    };

    void clean(char *chaine);
    void purger(void);
    void read (size_t bufferLength);
    void readNumber (size_t bufferLength);
    long stringLength (char string[]);

#ifdef __cplusplus
}
#endif

#endif /* _STRINGMANIPULATION_H */

