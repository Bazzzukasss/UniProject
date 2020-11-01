#pragma once

#include "app_settings.h"
#include "custom_setting_manager.h"

namespace custom_setting
{
/**
 * Class AppConfigurator
 * @brief Singleton class derived from Configurator end extended by application settings. responced for
 * saving/loadind/storaging of application settings
 */
class AppSettingManager : public Manager
{
    Q_OBJECT

public:
    AppSettingManager(QObject* parent = nullptr);

    UserSettings mUserSettings;

};
}  // namespace custom_setting
