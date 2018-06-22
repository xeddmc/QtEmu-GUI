/*
 * This file is part of QtEmu project.
 * Copyright (C) 2006-2009 Urs Wolfer <uwolfer @ fwo.ch> and Ben Klopfenstein <benklop gmail com>
 * Copyright (C) 2017-2018 Sergio Carlavilla <carlavilla @ mailbox.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

// Qt

// Local
#include "machineconfigaccel.h"

MachineConfigAccel::MachineConfigAccel(Machine *machine,
                                       QWidget *parent) : QWidget(parent) {

    m_moveUpAccelToolButton = new QToolButton();
    m_moveUpAccelToolButton -> setArrowType(Qt::UpArrow);

    m_moveDownAccelToolButton = new QToolButton();
    m_moveDownAccelToolButton -> setArrowType(Qt::DownArrow);

    m_tcgTreeItem = new QTreeWidgetItem(QTreeWidgetItem::Type);
    m_tcgTreeItem -> setText(0, "TCG - Tiny Code Generator");
    m_tcgTreeItem -> setToolTip(0, "TCG - Tiny Code Generator");
    m_tcgTreeItem -> setData(0, Qt::UserRole, "tcg");
    m_tcgTreeItem -> setCheckState(0, Qt::Unchecked);

    m_kvmTreeItem = new QTreeWidgetItem(QTreeWidgetItem::Type);
    m_kvmTreeItem -> setText(0, "KVM - Kernel-based Virtual Machine");
    m_kvmTreeItem -> setToolTip(0, "KVM - Kernel-based Virtual Machine");
    m_kvmTreeItem -> setData(0, Qt::UserRole, "kvm");
    m_kvmTreeItem -> setCheckState(0, Qt::Unchecked);

    m_xenTreeItem = new QTreeWidgetItem(QTreeWidgetItem::Type);
    m_xenTreeItem -> setText(0, "XEN");
    m_xenTreeItem -> setData(0, Qt::UserRole, "xen");
    m_xenTreeItem -> setCheckState(0, Qt::Unchecked);

    #ifdef Q_OS_WIN
    m_haxmTreeItem = new QTreeWidgetItem(QTreeWidgetItem::Type);
    m_haxmTreeItem -> setText(0, "HAXM - Hardware Accelerated Execution Manager");
    m_haxmTreeItem -> setToolTip(0, "HAXM - Hardware Accelerated Execution Manager");
    m_haxmTreeItem -> setData(0, Qt::UserRole, "hax");
    m_haxmTreeItem -> setCheckState(0, Qt::Unchecked);
    #endif

    m_acceleratorTree = new QTreeWidget();
    m_acceleratorTree -> setMaximumHeight(150);
    m_acceleratorTree -> setMaximumWidth(200);
    m_acceleratorTree -> setColumnCount(1);
    m_acceleratorTree -> setHeaderHidden(true);
    m_acceleratorTree -> setRootIsDecorated(false);
    m_acceleratorTree -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_acceleratorTree -> insertTopLevelItem(0, m_tcgTreeItem);
    m_acceleratorTree -> insertTopLevelItem(1, m_kvmTreeItem);
    m_acceleratorTree -> insertTopLevelItem(2, m_xenTreeItem);
    #ifdef Q_OS_WIN
    m_acceleratorTree -> insertTopLevelItem(3, m_haxmTreeItem);
    #endif

    m_accelTreeLayout = new QHBoxLayout();
    m_accelTreeLayout -> setAlignment(Qt::AlignTop);
    m_accelTreeLayout -> setSpacing(5);
    m_accelTreeLayout -> addWidget(m_acceleratorTree);
    m_accelTreeLayout -> addWidget(m_moveUpAccelToolButton);
    m_accelTreeLayout -> addWidget(m_moveDownAccelToolButton);

    m_acceleratorLayout = new QVBoxLayout();
    m_acceleratorLayout -> setAlignment(Qt::AlignTop);
    m_acceleratorLayout -> addItem(m_accelTreeLayout);

    m_acceleratorPageWidget = new QWidget();
    m_acceleratorPageWidget -> setLayout(m_acceleratorLayout);

    qDebug() << "MachineConfigAccel created";
}

MachineConfigAccel::~MachineConfigAccel() {
    qDebug() << "MachineConfigAccel destroyed";
}