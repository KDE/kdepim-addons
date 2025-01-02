# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
configure_file(gpg-agent.conf.in
  "${CMAKE_CURRENT_BINARY_DIR}/gpg-agent.conf" @ONLY)

configure_file(gpgsm.conf.in
  "${CMAKE_CURRENT_BINARY_DIR}/gpgsm.conf" @ONLY)

file(COPY
  ${CMAKE_CURRENT_SOURCE_DIR}
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/../"
)
