#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tile.h"

#include <QGridLayout>
#include <QLabel>
#include <QVector>
#include <iostream>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    b = new Board(ui->board->layout(), this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
