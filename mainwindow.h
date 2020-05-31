#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include <QString>
#include <QProcess>


#define PATH QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)

#if defined(Q_OS_WIN)
#define TDESKTOP_PATH ".tmulti\\Telegram.exe"
#else
#define TDESKTOP_PATH "./.tmulti/Telegram"
#endif


namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void on_start_clicked();

    void on_add_clicked();

    void on_remove_clicked();

    void on_edit_clicked();

    void on_sessions_itemDoubleClicked(QListWidgetItem *item);

private:
    QList<QProcess> tasks;

    QString getSelectedItem();
    QString inputTextDialog(QString text);

    void showError(QString text);
    void deleteSelectedItem();
    void addItem(QString text);

    Ui::MainWindow *ui;
    QPushButton *add;
    QPushButton *remove;
    QPushButton *start;
    QPushButton *edit;
    QListWidget *sessions;
};

#endif // MAINWINDOW_H
