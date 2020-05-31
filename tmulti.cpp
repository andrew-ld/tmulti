#include <QList>
#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QProcessEnvironment>

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

    return QDir(PATH).rename(old_name, new_name);
}

bool TMulti::deleteSession(QString name) {
    QDir dataDir = QDir(PATH);
    
    return QDir(dataDir.absoluteFilePath(name)).removeRecursively();
}

bool TMulti::addSession(QString name) {
    if (isBadName(name)) return false;

    return QDir(PATH).mkpath(name);
}

bool TMulti::launchSession(QString name) {
    if (!QFile(getTdesktopPath()).exists()) {
        return false;
    }

    QProcess *process = new QProcess();
    QStringList args = {"-many", "-workdir", QDir(PATH).absoluteFilePath(name)};

    process->setArguments(args);
    process->setProgram(getTdesktopPath());

    process->startDetached();
    return true;
}

bool TMulti::isBadName(QString name) {
    return name.contains(".");
}

QString TMulti::getTdesktopPath() {
    QFile defaultPath(TDESKTOP_PATH);
    
    if (defaultPath.exists()) {
        return defaultPath.fileName();
    }
    
#if defined(Q_OS_WIN)
#else
    QProcessEnvironment env(QProcessEnvironment::systemEnvironment());
    QString envPath = env.value("PATH");
    
    foreach (QString path, envPath.split(":")) {
        QDir pathDir(path);
        QFile file(pathDir.filePath("telegram-desktop"));
        
        if (file.exists()) {
            return file.fileName();
        }
    }
#endif

    return defaultPath.fileName();
}
