#include <QList>
#include <QDir>
#include <QDirIterator>
#include <QString>

#include "tmulti.h"
#include "mainwindow.h"

QList<QString> TMulti::getSessions() {
    QList<QString> sessions = QDir(PATH)
            .entryList(QDir::Filter::Dirs);

    foreach(QString name, sessions) {
        if (isBadName(name)) {
            sessions.removeAll(name);
        }
    }

    return sessions;
}

bool TMulti::editSession(QString old_name, QString new_name) {
    if (isBadName(new_name)) return false;

    return QDir().rename(PATH + old_name, PATH + new_name);
}

bool TMulti::deleteSession(QString name) {
    return QDir(PATH + name).removeRecursively();
}

bool TMulti::addSession(QString name) {
    if (isBadName(name)) return false;

    return QDir().mkdir(PATH + name);
}

bool TMulti::launchSession(QString name) {
    if (!QFile(TDESKTOP_PATH).exists()) {
        return false;
    }

    QProcess *process = new QProcess();
    QStringList args = {"-many", "-workdir", PATH + name};

    process->setArguments(args);
    process->setProgram(TDESKTOP_PATH);

    process->startDetached();
    return true;
}

bool TMulti::isBadName(QString name) {
    return name.contains(".");
}
