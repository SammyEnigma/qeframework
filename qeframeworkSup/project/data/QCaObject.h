/*  QCaObject.h
 *
 *  This file is part of the EPICS QT Framework, initially developed at the
 *  Australian Synchrotron.
 *
 *  SPDX-FileCopyrightText: 2009-2026 Australian Synchrotron
 *  SPDX-License-Identifier: LGPL-3.0-only
 *
 *  Author:     Anthony Owen
 *  Maintainer: Andrew Starritt
 *  Contact:    andrews@ansto.gov.au
 */

#ifndef QCA_OBJECT_H
#define QCA_OBJECT_H

#include <QEChannel.h>

// Alias to support the transition from qcaobject::QCaObject to QEChannel.
//
namespace qcaobject {
   using QCaObject [[deprecated("Use QEChannel instead.")]] = QEChannel;
}

#endif // QCA_OBJECT_H
