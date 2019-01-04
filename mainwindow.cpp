#include <QDir>
#include <QListWidget>
#include <QString>
#include <QProcess>
#include <QInputDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tmulti.h"


/*
 * Startup
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            QDesktopWidget()
               .screenGeometry(this)
        )
    );

    QDir curr = QDir();
    if (!curr.exists(PATH)) {
        curr.mkdir(PATH);
    }

    foreach(QString session, TMulti::getSessions()) {
        addItem(session);
    }

    if (ui->sessions->count() > 0) {
        ui->sessions->setFocus();
        ui->sessions->item(0)->setSelected(true);
    }
}


/*
 * Qt Wrap
*/

QString MainWindow::getSelectedItem() {
     QListWidgetItem *widget = ui->sessions->currentItem();
     return widget == nullptr ? nullptr : widget->text();
}

void MainWindow::showError(QString text) {
    QMessageBox msg;
    msg.setText(text);
    msg.setIcon(QMessageBox::Critical);
    msg.exec();
}

QString MainWindow::inputTextDialog(QString text) {
    return QInputDialog::getText(this, "", text,  QLineEdit::Normal);
}

void MainWindow::deleteSelectedItem() {
    qDeleteAll(ui->sessions->selectedItems());
}

void MainWindow::addItem(QString item) {
    ui->sessions->addItem(item);
    ui->sessions->sortItems();
    ui->sessions->setFocus();
}

void MainWindow::launchSession(QString name) {
    if (!QFile(TDESKTOP_PATH).exists()) {
        showError(tr("no_tdesktop"));
        return;
    }

    QProcess *process = new QProcess(this);
    QStringList args = {"-many", "-workdir", PATH + name};

    process->setArguments(args);
    process->setProgram(TDESKTOP_PATH);

    process->startDetached();
}

/*
 * onClick listener
 */

void MainWindow::on_start_clicked()
{
    QString name = getSelectedItem();
    if (name == nullptr) return;

    launchSession(name);
}

void MainWindow::on_add_clicked()
{
    QString name = inputTextDialog(tr("sess_name"));
    if (name == "") return;

    bool res = TMulti::addSession(name);

    if (res) {
        addItem(name);
        launchSession(name);
    } else {
        showError(tr("creation_err"));
    }
}

void MainWindow::on_remove_clicked()
{
    QString name = getSelectedItem();
    if (name == nullptr) return;

    bool res = TMulti::deleteSession(name);

    if (res) {
       deleteSelectedItem();
    } else {
       showError(tr("delete_err"));
    }
}

void MainWindow::on_edit_clicked()
{
    QString name = getSelectedItem();
    if (name == nullptr) return;

    QString new_name = inputTextDialog(tr("new_name"));
    if (new_name == "") return;

    bool res = TMulti::editSession(name, new_name);

    if (res) {
        deleteSelectedItem();
        addItem(new_name);
    } else {
        showError(tr("edit_err"));
    }
}

void MainWindow::on_sessions_itemDoubleClicked(QListWidgetItem *item)
{
    launchSession(item->text());
}
