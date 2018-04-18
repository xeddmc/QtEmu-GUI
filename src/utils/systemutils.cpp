/*
 * This file is part of QtEmu project.
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
#include "systemutils.h"

SystemUtils::SystemUtils() {
    qDebug() << "SystemUtils created";
}

SystemUtils::~SystemUtils() {
    qDebug() << "SystemUtils destroyed";
}

void SystemUtils::populateOSList(Machine *newMachine){

    // TODO: Get the data directory path from QSettings
    // Open the file
    QString dataDirectoryPath = QDir::toNativeSeparators(QDir::homePath() + "/.qtemu/");

    QString qtemuConfig = dataDirectoryPath.append("qtemu.json");

    QFile machinesFile(qtemuConfig);
    machinesFile.open(QIODevice::ReadWrite); // TODO: Check if open the file fails

    // Read all data included in the file
    QByteArray machinesData = machinesFile.readAll();
    QJsonDocument machinesDocument(QJsonDocument::fromJson(machinesData));
    QJsonObject machinesObject;

    // Read other machines
    QJsonArray machines = machinesDocument["machines"].toArray();

    // Create the new machine
    QJsonObject machine;
    machine["uuid"]       = newMachine -> getUuid();
    machine["name"]       = newMachine -> getName();
    machine["path"]       = newMachine -> getPath();
    machine["configpath"] = newMachine -> getConfigPath();
    machine["icon"]       = newMachine -> getOSVersion().toLower().replace(" ", "_");

    machines.append(machine);
    machinesObject["machines"] = machines;

    QJsonDocument machinesJSONDocument(machinesObject);

    machinesFile.seek(0);
    machinesFile.write(machinesJSONDocument.toJson());
    machinesFile.close();
}

void SystemUtils::getTotalMemory(int32_t &totalRAM) {

    struct sysinfo sys_info;

    if (sysinfo(&sys_info) != -1) {
        totalRAM = (((uint64_t)sys_info.totalram * sys_info.mem_unit) * 0.976562) / 1024 / 1024;
    }
}

void SystemUtils::setCPUTypesx86(QComboBox *CPUType) {

    // Intel among many others...IBM, Texas Instruments, AMD, Cyrix...
    CPUType -> addItem("486");

    // Intel
    CPUType -> addItem("Pentium");
    CPUType -> addItem("Pentium 2");
    CPUType -> addItem("Pentium 3");
    CPUType -> addItem("Intel Core Duo");
    CPUType -> addItem("Intel Core 2 Duo");
    CPUType -> addItem("Intel Atom N270");
    CPUType -> addItem("Broadwell");
    CPUType -> addItem("Broadwell no TSX");
    CPUType -> addItem("Conroe");
    CPUType -> addItem("Haswell");
    CPUType -> addItem("Haswell no TSX");
    CPUType -> addItem("Ivy Bridge");
    CPUType -> addItem("Nehalem");
    CPUType -> addItem("Penryn");
    CPUType -> addItem("Sandy Bridge");
    CPUType -> addItem("Skylake Client");
    CPUType -> addItem("Skylake Server");
    CPUType -> addItem("Westmere");

    // AMD
    CPUType -> addItem("AMD Opteron G1");
    CPUType -> addItem("AMD Opteron G2");
    CPUType -> addItem("AMD Opteron G3");
    CPUType -> addItem("AMD Opteron G4");
    CPUType -> addItem("AMD Opteron G5");
    CPUType -> addItem("AMD Phenom");
    CPUType -> addItem("AMD Athlon");

    // QEMU
    CPUType -> addItem("qemu32 Virtual CPU version 2.5+");
    CPUType -> addItem("qemu64 Virtual CPU version 2.5+");
    CPUType -> addItem("kvm32 Common 32-bit KVM processor");
    CPUType -> addItem("kvm64 Common KVM processor");

    // Host
    CPUType -> addItem("Base");
    CPUType -> addItem("Host");
    CPUType -> addItem("Max");
}

void SystemUtils::setGPUTypes(QComboBox *GPUType) {
    GPUType -> addItem("None");
    GPUType -> addItem("Default");
    GPUType -> addItem("Standard VGA(VESA 2.0)");
    GPUType -> addItem("Cirrus Logic GD5446");
    GPUType -> addItem("VMWare SVGA-II");
    GPUType -> addItem("QXL Paravirtual Graphic Card");
    GPUType -> addItem("Sun TCX Framebuffer");
    GPUType -> addItem("Sun Cgthree Framebuffer");
    GPUType -> addItem("Virtio VGA Card");
    GPUType -> addItem("Xen Framebuffer");
}

void SystemUtils::setKeyboardLayout(QComboBox *keyboardLayout) {
    keyboardLayout -> addItem("Arabic (ar)");
    keyboardLayout -> addItem("Danish (da)");
    keyboardLayout -> addItem("German (de)");
    keyboardLayout -> addItem("German (Switzerland) (de-ch)");
    keyboardLayout -> addItem("English (United Kingdom) (en-gb)");
    keyboardLayout -> addItem("English (United States) (en-us)");
    keyboardLayout -> addItem("Spanish (Spain) (es)");
    keyboardLayout -> addItem("Estonian (et)");
    keyboardLayout -> addItem("Finnish (fi)");
    keyboardLayout -> addItem("Faroese (fo)");
    keyboardLayout -> addItem("French (fr)");
    keyboardLayout -> addItem("French (Belgium) (fr-be)");
    keyboardLayout -> addItem("French (Canada) (fr-ca)");
    keyboardLayout -> addItem("French (Switzerland) (fr-ch)");
    keyboardLayout -> addItem("Croatian (hr)");
    keyboardLayout -> addItem("Hungarian (hu)");
    keyboardLayout -> addItem("Icelandic (is)");
    keyboardLayout -> addItem("Italian (it)");
    keyboardLayout -> addItem("Japanese (ja)");
    keyboardLayout -> addItem("Lithuanian (lt)");
    keyboardLayout -> addItem("Latvian (lv)");
    keyboardLayout -> addItem("Macedonian (mk)");
    keyboardLayout -> addItem("Dutch (nl)");
    keyboardLayout -> addItem("Dutch (Belgium) (nl-be)");
    keyboardLayout -> addItem("Norwegian (no)");
    keyboardLayout -> addItem("Polish (pl)");
    keyboardLayout -> addItem("Portuguese (pt)");
    keyboardLayout -> addItem("Portuguese (Brazil) (pt-br)");
    keyboardLayout -> addItem("Russian (ru)");
    keyboardLayout -> addItem("Slovenian (sl)");
    keyboardLayout -> addItem("Swedish (sv)");
    keyboardLayout -> addItem("Thai (th)");
    keyboardLayout -> addItem("Turkish (tr)");
}

QString SystemUtils::getOsIcon(const QString &osVersion) {

    if (osVersion.contains("Microsoft", Qt::CaseInsensitive)) {
        if (osVersion.contains("7", Qt::CaseInsensitive) ||
            osVersion.contains("8", Qt::CaseInsensitive) ||
            osVersion.contains("10", Qt::CaseInsensitive)) {
            return "windows";
        } else {
            return "windows_old";
        }
    } else if (osVersion.contains("GNU", Qt::CaseInsensitive)) {
        return "gnu";
    } else {
        return osVersion.toLower().replace(" ", "_");
    }
}

bool SystemUtils::createDisk(const QString &diskName, const QString &format,
                             const double size, bool useEncryption) {

    QProcess *qemuImgProcess = new QProcess();

    QStringList args;
    args << "create";

    if(useEncryption) {
        args << "-e";
    }

    args << "-f";
    args << format;
    args << diskName;
    args << QString::number(size) + "G"; // TODO: Implement other sizes, K, M, T

    QString program;

    #ifdef Q_OS_LINUX
    program = "qemu-img";
    #endif

    // TODO: Implement other platforms... :'(

    qemuImgProcess -> start(program, args);

    if( ! qemuImgProcess -> waitForStarted(2000)) {
        QMessageBox *qemuImgNotFoundMessageBox = new QMessageBox();
        qemuImgNotFoundMessageBox -> setWindowTitle(QObject::tr("Qtemu - Critical error"));
        qemuImgNotFoundMessageBox -> setIcon(QMessageBox::Critical);
        qemuImgNotFoundMessageBox -> setText(QObject::tr("<p>Cannot start qemu-img</p>"
                                                         "<p><strong>Image isn't created</strong></p>"
                                                         "<p>Ensure that you have installed qemu-img in your "
                                                         "system and it's available</p>"));
        qemuImgNotFoundMessageBox -> exec();

        return false;
    }

    if( ! qemuImgProcess -> waitForFinished()) {
        QMessageBox *qemuImgNotFinishedMessageBox = new QMessageBox();
        qemuImgNotFinishedMessageBox -> setWindowTitle(QObject::tr("Qtemu - Critical error"));
        qemuImgNotFinishedMessageBox -> setIcon(QMessageBox::Critical);
        qemuImgNotFinishedMessageBox -> setText(QObject::tr("<p>Cannot finish qemu-img</p>"
                                                            "<p><strong>Image isn't created</strong></p>"
                                                            "<p>There's a problem with qemu-img, the process "
                                                            "the process has not finished correctly</p>"));
        qemuImgNotFinishedMessageBox -> exec();

        return false;
    } else {
        QByteArray err = qemuImgProcess -> readAllStandardError();
        QByteArray out = qemuImgProcess -> readAllStandardOutput();

        if(err.count() > 0) {
            QMessageBox *qemuImgErrorMessageBox = new QMessageBox();
            qemuImgErrorMessageBox -> setWindowTitle(QObject::tr("Qtemu - Critical error"));
            qemuImgErrorMessageBox -> setIcon(QMessageBox::Critical);
            qemuImgErrorMessageBox -> setText(QObject::tr("<p>Cannot finish qemu-img</p>"
                                                          "<p><strong>Image isn't created</strong></p>"
                                                          "<p>Error: " + err + "</p>"));
            qemuImgErrorMessageBox -> exec();

            return false;
        }

        if(out.count() > 0) {
            QMessageBox *qemuImgOkMessageBox = new QMessageBox();
            qemuImgOkMessageBox -> setWindowTitle(QObject::tr("Qtemu - Image created"));
            qemuImgOkMessageBox -> setIcon(QMessageBox::Information);
            qemuImgOkMessageBox -> setText(QObject::tr("<p><strong>Image created</strong></p>"
                                                       "<p>" + out + "</p>"));
            qemuImgOkMessageBox -> exec();
        }

        return true;
    }

    return false;
}

QString SystemUtils::getMachinePath(const QUuid machineUuid) {

    QSettings settings;
    settings.beginGroup("DataFolder");

    QString dataDirectoryPath = settings.value("QtEmuData",
                                               QDir::toNativeSeparators(QDir::homePath() + "/.qtemu/")).toString();
    settings.endGroup();

    // Open the file with the machines
    QString qtemuConfig = dataDirectoryPath.append("qtemu.json");

    QFile machinesFile(qtemuConfig);
    machinesFile.open(QIODevice::ReadWrite); // TODO: Check if open the file fails

    // Read all the machines included in the file
    QByteArray machinesData = machinesFile.readAll();
    QJsonDocument machinesDocument(QJsonDocument::fromJson(machinesData));
    QJsonArray machines = machinesDocument["machines"].toArray();

    int machinePos = 0;
    bool machineExists = false;
    QString machinePath;
    while(machinePos < machines.size() && ! machineExists) {
        QJsonObject machineJSON = machines[machinePos].toObject();

        if (machineUuid == machineJSON["uuid"].toVariant()) {
            machineExists = true;
            machinePath = machineJSON["path"].toString();
        } else {
            ++machinePos;
        }
    }

    return machinePath;
}

QString SystemUtils::getMachineConfigPath(const QUuid machineUuid) {

    QSettings settings;
    settings.beginGroup("DataFolder");

    QString dataDirectoryPath = settings.value("QtEmuData",
                                               QDir::toNativeSeparators(QDir::homePath() + "/.qtemu/")).toString();
    settings.endGroup();

    // Open the file with the machines
    QString qtemuConfig = dataDirectoryPath.append("qtemu.json");

    QFile machinesFile(qtemuConfig);
    machinesFile.open(QIODevice::ReadWrite); // TODO: Check if open the file fails

    // Read all the machines included in the file
    QByteArray machinesData = machinesFile.readAll();
    QJsonDocument machinesDocument(QJsonDocument::fromJson(machinesData));
    QJsonArray machines = machinesDocument["machines"].toArray();

    int machinePos = 0;
    bool machineExists = false;
    QString machinePath;
    while(machinePos < machines.size() && ! machineExists) {
        QJsonObject machineJSON = machines[machinePos].toObject();

        if (machineUuid == machineJSON["uuid"].toVariant()) {
            machineExists = true;
            machinePath = machineJSON["configpath"].toString();
        } else {
            ++machinePos;
        }
    }

    return machinePath;
}
