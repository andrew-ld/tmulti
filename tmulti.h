#ifndef TMULTI_H
#define TMULTI_H

#include <QList>
#include <QString>

class TMulti {
private:
    static bool isBadName(QString name);

public:
    static QList<QString> getSessions();
    static bool editSession(QString old_name, QString new_name);
    static bool deleteSession(QString name);
    static bool addSession(QString name);
    static bool launchSession(QString name);
};

#endif // TMULTI_H
