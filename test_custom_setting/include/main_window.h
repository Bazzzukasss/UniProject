#pragma once

#include <QMainWindow>
#include "app_setting_manager.h"
#include "custom_setting_item_tree_model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    custom_setting::AppSettingManager mSettingManager;
    custom_setting::ItemTreeModel mModel;
};
