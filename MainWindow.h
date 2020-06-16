#ifndef SIMPLE_INTERPRETER_MAINWINDOW_H
#define SIMPLE_INTERPRETER_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionClose_triggered();

    void on_pushButtonRun_clicked();

private:
    Ui::MainWindow *ui;
    void showDialogWithMessage(QString message);
};

#endif //SIMPLE_INTERPRETER_MAINWINDOW_H
