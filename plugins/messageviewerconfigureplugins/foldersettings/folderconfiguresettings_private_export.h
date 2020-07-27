/*  This file is part of the KDE project
    Copyright (C) 2020 Laurent Montel <montel@kde.org>

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

#ifndef FOLDERCONFIGURESETTINGSPRIVATE_EXPORT_H
#define FOLDERCONFIGURESETTINGSPRIVATE_EXPORT_H

#include "libfolderconfiguresettings_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
# ifndef LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT
#  define LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT LIBFOLDERCONFIGURESETTINGS_EXPORT
# endif
#else /* not compiling tests */
# define LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT
#endif

#endif
