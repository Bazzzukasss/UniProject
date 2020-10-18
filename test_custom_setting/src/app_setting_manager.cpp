#include "app_setting_manager.h"

using namespace custom_setting;

AppSettingManager::AppSettingManager(QObject* parent) : Manager(parent)
{
    setConfigurations({{UserSettingsFilename, &mUserSettings}});
}

