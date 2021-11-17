#include "main_window.h"
#include "ui_main_window.h"
#include "custom_setting_item.h"
#include "custom_setting_tree_widget.h"
#include "custom_setting_item_delegate.h"

using namespace custom_setting;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mSettingManager.loadConfigurations();

    ui->mSettingsWidget->setItemsWidth(-1);
    //ui->mSettingsWidget->setItemsHeight(-1);
    ui->mSettingsWidget->setOneClickMode(true);
    ui->mSettingsWidget->setAlternatingRowColors(false);
    ui->mSettingsWidget->setColumnWidth(0, 230);

    ui->mSettingsWidget->add(&mSettingManager.mUserSettings);

    auto itemEditable = new Item("", "Editable", "Editable item");
    itemEditable->addSettings({
                                  &mSettingManager.mUserSettings.mEditable.mBool,
                                  &mSettingManager.mUserSettings.mEditable.mInt,
                                  &mSettingManager.mUserSettings.mEditable.mDouble,
                                  &mSettingManager.mUserSettings.mEditable.mString,
                                  &mSettingManager.mUserSettings.mEditable.mChangableListDir,
                                  &mSettingManager.mUserSettings.mEditable.mChangableListFile,
                                  &mSettingManager.mUserSettings.mEditable.mColor,
                                  &mSettingManager.mUserSettings.mEditable.mEditableList,
                                  //&mSettingManager.mUserSettings.mEditable.mFont,
                                  &mSettingManager.mUserSettings.mEditable.mList,
                                  &mSettingManager.mUserSettings.mEditable.mSourceDir,
                                  &mSettingManager.mUserSettings.mEditable.mSourceFile
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

    auto itemRoot = new Item("", "Root", "Root item", this);
    itemGroups->addItems({itemGroupA});
    itemRoot->addItems({itemEditable, itemGroups});

    ui->mSettingsWidget->add(itemRoot);

    mModel.setRootItem(itemRoot);
    mModel.setHeaders({"1","2","3","4","5","7","8","9","10","11","12","13"});
    auto delegate = new Delegate(this);
    ui->mTreeView->setModel(&mModel);
    ui->mTreeView->setItemDelegate(delegate);
    ui->mTreeView->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

MainWindow::~MainWindow()
{
    mSettingManager.saveConfigurations();
    delete ui;
}

