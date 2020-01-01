/*  This file is part of the KDE project
    Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef LIBKMAILMARKDOWNPRIVATE_EXPORT_H
#define LIBKMAILMARKDOWNPRIVATE_EXPORT_H

#include "libkmailmarkdown_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
# ifndef LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT
#  define LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT LIBKMAILMARKDOWN_EXPORT
# endif
#else /* not compiling tests */
# define LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT
#endif

#endif
