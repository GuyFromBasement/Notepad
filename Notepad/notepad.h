#ifndef NOTEPAD_H
#define NOTEPAD_H
#define AUTOSAVE_SLEEP_TIME 4

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QColorDialog>
#include <QFont>
#include <QFontDialog>
#include <QCloseEvent>
#include <QPushButton>
#include <QThread>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>
#include<fstream>

namespace Ui {
class Notepad;
}

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void closeEvent(QCloseEvent *event);

    void on_actionNowy_triggered();

    void on_actionOtworz_triggered();

    void on_actionZapisz_jako_triggered();

    void on_actionWyjd_triggered();

    void on_actionKopiuj_triggered();

    void on_actionWklej_triggered();

    void on_actionWytnij_triggered();

    void on_actionPrzywr_triggered();

    void on_actionCofnij_triggered();

    void on_actionCzerwony_triggered();

    void on_actionNiebierski_triggered();

    void on_actionZielony_triggered();

    void on_actionStandard_triggered();

    void on_actionWiecej_kolorow_triggered();

    void on_actionCzcionka_triggered();

    void autosave();

private:
    Ui::Notepad *ui;
    QString current_file = "";
    QFuture <void> autosave_thread;
    bool should_stop_autosave = false;
};

#endif // NOTEPAD_H
