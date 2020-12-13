#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapcollection.h"
#include "mapcollection.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineCourse->setValidator(&m_int_validator);
    ui->lineYear->setValidator(&m_int_validator);
    ui->lineMonth->setValidator(&m_int_validator);
    ui->lineDay->setValidator(&m_int_validator);
    ui->lineYear_2->setValidator(&m_int_validator);
    ui->lineMonth_2->setValidator(&m_int_validator);
    ui->lineDay_2->setValidator(&m_int_validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showCollection() {
    ui->collectionElements->clear();
    auto keys(m_data.allKeysReturn());
    auto values(m_data.allValuesReturn(m_data));
    for (size_t i = 0; i < m_data.size(); ++i) {
        output(QString("%1 pair: ").arg(i));
        output(QString("%1").arg(keys[i]));
        QString str = QString::fromStdString(values[i]);
        output(str + " ");
        output(QString("\n"));
    }
}

void MainWindow::on_pushButtonAdd_clicked() {
    std::string tmp_string;
    std::string tmp_student;
    tmp_string += ui->lineYear->text().toStdString();
    tmp_string += ui->lineMonth->text().toStdString();
    tmp_string += ui->lineDay->text().toStdString();
    std::size_t tmp_date = std::stoi(tmp_string);
    tmp_student += ui->lineFirstName->text().toStdString();
    tmp_student += ui->lineLastName->text().toStdString();
    tmp_student += ui->linePatronymic->text().toStdString();
    tmp_student += ui->lineCourse->text().toStdString();
    if (tmp_student != "" && tmp_string != "" && m_data.exist(tmp_date) == false) {
        m_data.insert(tmp_date, tmp_student);
        ui->pushButtonClear->setEnabled(true);
        log(QString("Pair was added"));
    }
    else
        log(QString("Pair is already exist"));
    ui->pushButtonWrite->setEnabled(true);
    showCollection();
}

void MainWindow::on_pushButtonClear_clicked() {
    m_data.clear();
    log(QString("Collection is emply; size is %1").arg(QString::number(m_data.size())));
    ui->pushButtonClear->setEnabled(false);
    ui->pushButtonRead->setEnabled(true);
    ui->collectionElements->clear();
}

void MainWindow::on_pushButtonRead_clicked() {
    ui->pushButtonClear->setEnabled(true);
    ui->pushButtonWrite->setEnabled(true);
    ui->pushButtonRead->setEnabled(false);
    ui->collectionElements->clear();
    m_data.clear();
    std::string filename;
    m_data.readFromFile(filename);
    showCollection();
    log(QString("Read collection from file"));
}

void MainWindow::on_pushButtonWrite_clicked() {
    std::string filename;
    m_data.writeToFile(filename);
    log(QString("Collection was written to file"));
}

void MainWindow::log(const QString &text_) {
    ui->textEdit->setText(ui->textEdit->toPlainText() + text_ + "\n");
}

void MainWindow::output(const QString &text_) {
    ui->collectionElements->setText(ui->collectionElements->toPlainText() + text_);
}

void MainWindow::on_lineYear_2_textChanged() {
    ui->pushButtonErase->setEnabled(true);
}

void MainWindow::on_pushButtonErase_clicked() {
    if (m_data.size() > 0) {
        std::string tmp_string;
        std::string tmp_student;
        tmp_string += ui->lineYear->text().toStdString();
        tmp_string += ui->lineMonth->text().toStdString();
        tmp_string += ui->lineDay->text().toStdString();
        std::size_t tmp_date = std::stoi(tmp_string);
        if (m_data.exist(tmp_date) == true) {
            m_data.erase(tmp_date);
            showCollection();
            log(QString("Pair was erased"));
        }
        else
            log(QString("Pair does not exist"));
    }
    else
        log(QString("Error! Collection is already empty"));
}

