#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include <QIntValidator>
#include "mapcollection.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showCollection();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonRead_clicked();

    void on_pushButtonWrite_clicked();

    void on_lineYear_2_textChanged();

    void on_pushButtonErase_clicked();


private:
    Ui::MainWindow *ui;
    void log(const QString& text_);
    void output(const QString& text_);
    QIntValidator m_int_validator;
    QDoubleValidator m_double_validator;
    MapCollection<size_t, string> m_data;
};
#endif // MAINWINDOW_H







