# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
if(UNIX)
  install( PROGRAMS kmail_clamav.sh kmail_sav.sh kmail_fprot.sh kmail_antivir.sh  DESTINATION ${KDE_INSTALL_BINDIR} )
endif()
