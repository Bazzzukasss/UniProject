#include "main_window.h"
#include "ui_main_window.h"
#include "custom_setting_item.h"
#include "custom_setting_tree_widget.h"

using namespace custom_setting;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSettingManager.loadConfigurations();

    ui->mSettingsWidget->setItemWidth(-1);
    //ui->mSettingsWidget->setItemHeight(-1);
    ui->mSettingsWidget->setOneClickMode(true);
    ui->mSettingsWidget->view()->setAlternatingRowColors(false);
    ui->mSettingsWidget->view()->setColumnWidth(0, 230);

    ui->mSettingsWidget->add(&mSettingManager.mUserSettings);

    auto itemEditable = new Item("", "Editable", "Editable item");
    itemEditable->addSettings({
                                  &mSettingManager.mUserSettings.mEditable.mBool,
                                  &mSettingManager.mUserSettings.mEditable.mInt,
                                  &mSettingManager.mUserSettings.mEditable.mDouble,
                                  &mSettingManager.mUserSettings.mEditable.mString
                              });

    auto itemGroupA = new Item("", "Group A", "Group A item");
    itemGroupA->addSettings({
                                &mSettingManager.mUserSettings.mGroups.mGroupA.mBool,
                                &mSettingManager.mUserSettings.mGroups.mGroupA.mDouble,
                                &mSettingManager.mUserSettings.mGroups.mGroupA.mInt,
                                &mSettingManager.mUserSettings.mGroups.mGroupA.mString
                            });

    auto itemGroups = new Item("", "Groups", "Groups item");
    itemGroups->addSettings({
                                &mSettingManager.mUserSettings.mGroups.mGroupA,
                                &mSettingManager.mUserSettings.mGroups.mGroupB,
                                &mSettingManager.mUserSettings.mGroups.mGroupC,
                                &mSettingManager.mUserSettings.mGroups.mGroupD
                            });

    auto itemRoot = new Item("", "Root", "Root item");
    itemRoot->addItems({itemEditable, itemGroupA, itemGroups});

    ui->mSettingsWidget->add(itemRoot);
}

MainWindow::~MainWindow()
{
    mSettingManager.saveConfigurations();
    delete ui;
}

