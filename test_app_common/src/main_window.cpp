#include "main_window.h"
#include "ui_main_window.h"
#include "application.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet(Application::loadStyleSheet(":/styles/full_style.qss"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

