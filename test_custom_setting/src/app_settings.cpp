#include "app_settings.h"
#include <QDataStream>

using namespace custom_setting;

UserSettings::UserSettings(QObject* parent) : Setting(key::kUserSettings, "User settings", "", false, parent)
{
    addSettings({&mEditable, &mGroups, &mNotEditable});
}

UserSettings::EditableSettings::EditableSettings(const QString &key, const QString &caption, const QString &description, bool read_only, QObject *parent)
    : Setting(key, caption, description, read_only, parent)
{
    addSettings({&mBool, &mInt, &mDouble, &mString, &mList, &mFont, &mColor, &mSourceFile, &mSourceDir,
                 &mChangableListDir, &mChangableListFile, &mChangableListString, &mEditableList});
}

UserSettings::NotEditableSettings::NotEditableSettings(const QString &key, const QString &caption, const QString &description, bool read_only, QObject *parent)
    : Setting(key, caption, description, read_only, parent)
{
    addSettings({&mByteArray});
}

UserSettings::GroupsSettings::GroupsSettings(const QString &key, const QString &caption, const QString &description, const DataBool &data, bool read_only, QObject *parent)
    : SettingBool(key, caption, description, data, read_only, parent)
{
    addSettings({&mGroupA, &mGroupB, &mGroupC, &mGroupD, &mGroupE});
}

UserSettings::GroupsSettings::GroupSettings::GroupSettings(const QString &key, const QString &caption, const QString &description, const DataBool &data, bool read_only, QObject *parent)
    : SettingBool(key, caption, description, data, read_only, parent)
{
    addSettings({&mBool, &mInt, &mDouble, &mString});
}

QDataStream& operator<<(QDataStream& stream, const TestRecord &rhv)
{
    stream << rhv.bVal << rhv.dVal << rhv.iVal << rhv.str;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, TestRecord& rhv)
{
    stream >> rhv.bVal;
    stream >> rhv.dVal;
    stream >> rhv.iVal;
    stream >> rhv.str;

    return stream;
}

bool TestRecord::operator!=(const TestRecord &rhv)
{
    return (bVal != rhv.bVal) || (dVal != rhv.dVal) || (iVal != rhv.iVal) || (str != rhv.str);
}
