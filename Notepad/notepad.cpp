#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    setWindowTitle("Mam własny notatnik a wy co osiągnęliście w życiu xD ? #Pixel Guy");
    QFuture <void> autosave_thread = QtConcurrent::run(this,&Notepad::autosave);
}

Notepad::~Notepad()
{
    autosave_thread.cancel();
    should_stop_autosave = true;
    delete ui;
}

void Notepad::on_actionNowy_triggered()
{
    current_file.clear();
    ui->textEdit->setText(QString());
}

void Notepad::on_actionOtworz_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Wybierz plik");
    QFile file(filename);
    current_file = filename;

    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Błąd,"," Nie udało się otworzyć pliku " + filename + " błąd: " + file.errorString());
        return;
    }
    else
    {
        setWindowTitle(filename);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
        file.close();
    }
}

void Notepad::on_actionZapisz_jako_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Zapisz jako");
    QFile file(filename);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Błąd,"," Nie udało się zapisać pliku " + filename + " błąd: " + file.errorString());
        return;
    }
    else
    {
        setWindowTitle(filename);
        QTextStream out(&file);
        QString stuff_in_text_edit;
        stuff_in_text_edit = ui->textEdit->toHtml();
        out << stuff_in_text_edit;
        file.close();
        current_file = filename;
    }

}

void Notepad::on_actionWyjd_triggered()
{
    if(current_file == "" && ui->textEdit->toPlainText() !=""){
        QMessageBox msgBox;
        msgBox.setText(tr("Plik nie jest pusty i jednocześnie nie został zapisany.\nCzy chcesz zapisać go teraz?"));
        QAbstractButton* pButtonYes = msgBox.addButton(tr("Tak"), QMessageBox::YesRole);
        msgBox.addButton(tr("Nie"), QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton() == pButtonYes) {
            on_actionZapisz_jako_triggered();
        }
    }
    QApplication::quit();
}
void Notepad::on_actionKopiuj_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionWklej_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionWytnij_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionPrzywr_triggered()
{
    ui->textEdit->redo();
}

void Notepad::on_actionCofnij_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionCzerwony_triggered()
{

    ui->textEdit->setTextColor(Qt::GlobalColor::red);
}

void Notepad::on_actionNiebierski_triggered()
{
    ui->textEdit->setTextColor(Qt::GlobalColor::blue);
}


void Notepad::on_actionZielony_triggered()
{
    ui->textEdit->setTextColor(Qt::GlobalColor::green);
}

void Notepad::on_actionStandard_triggered()
{
    ui->textEdit->setTextColor(Qt::GlobalColor::black);
}


void Notepad::on_actionWiecej_kolorow_triggered()
{
    QColor color;
    color = QColorDialog::getColor();
    ui->textEdit->setTextColor(color);
}



void Notepad::on_actionCzcionka_triggered()
{
    QFont font;
    bool ok;
    font = QFontDialog::getFont(&ok, QFont( "Arial", 18 ), this, tr("Wybierz czcionkę") );

    if(ok){
        ui->textEdit->setFont(font);
    }
    else{
         QMessageBox::warning(this,"Błąd,"," Nie można użyć tej czcionki");
    }
}

void Notepad::closeEvent (QCloseEvent *event)
{
    if(current_file == "" && ui->textEdit->toPlainText() !=""){
        QMessageBox msgBox;
        msgBox.setText(tr("Plik nie jest pusty i jednocześnie nie został zapisany.\nCzy chcesz zapisać go teraz?"));
        QAbstractButton* pButtonYes = msgBox.addButton(tr("Tak"), QMessageBox::YesRole);
        msgBox.addButton(tr("Nie"), QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton() == pButtonYes) {
            on_actionZapisz_jako_triggered();
        }
    }
}

void Notepad::autosave()
{

    std::fstream file;
    bool should_init = true;
    QString last;

    while(!should_stop_autosave){
        if(current_file != "" && should_init){
         file.open(current_file.toStdString(), std::ios::out);
        }

        if(file.is_open()){
            last = ui->textEdit->toHtml();
            QThread::sleep(AUTOSAVE_SLEEP_TIME);
            if(last !=  ui->textEdit->toHtml()){
                file << last.toStdString();
            }
        }

    }

}
