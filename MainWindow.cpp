#include <string>
#include <QFileDialog>
#include <QTextStream>
#include <QLabel>
#include <QWindow>
#include <QInputDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Interpretation.h"
#include "Collections/BST.h"
#include "Collections/Heap.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open code file"), "", tr("Text Files (*.txt)"));
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString fileText = QTextStream(&file).readAll();
        ui->plainTextEdit->setPlainText(fileText);
    }
}

void MainWindow::on_actionClose_triggered() {
    exit(-1);
}

void MainWindow::showDialogWithMessage(QString message) {
    QDialog d(this);
    d.setWindowIconText(QString("Results"));
    QLabel label(message);
    QFont font = label.font();
    font.setPointSize(16);
    label.setFont(font);
    QVBoxLayout layout(&d);
    layout.addWidget(&label);
    layout.setSizeConstraint(QLayout::SetFixedSize);
    d.setLayout(&layout);
    d.exec();
}

void MainWindow::on_pushButtonRun_clicked() {
    QString text = ui->plainTextEdit->toPlainText();
    QTextStream stream(&text);
    Interpretation interpretation;
    while (!stream.atEnd()) {
        string line = stream.readLine().toUtf8().toStdString();
        try {
            interpretation.process(line);
        } catch (string ex) {
            QString errorResult("Error in the line:\n");
            errorResult.append(line.c_str()).append('\n');
            errorResult.append(ex.c_str());
            showDialogWithMessage(errorResult);
            return;
        }
    }

    auto map = interpretation.getVariables();

    Heap<string, Value> heap(map.size());
    BST<string, Value> bst;

    for (const auto &variable : map) {
        if (variable.second.isBoolValue()) continue;
        heap.put(variable.first, variable.second);
        bst.put(variable.first, variable.second);
    }
    heap.sort();

    QString result("Your program results:\n");

    result.append("Sorted by variable name:\n");
    bst.inOrder(&result);

    result.append("\nSorted by variable value:\n");
    heap.print(&result);

    showDialogWithMessage(result);

}
