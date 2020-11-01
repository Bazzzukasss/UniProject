#pragma once

#include "custom_setting.h"

#define KEY(name) static const char* name{#name};

namespace custom_setting
{

namespace key
{

//UserSettings
KEY(kUserSettings)

// UserSettings
KEY(kUserEditable)
KEY(kUserNotEditable)
KEY(kUserGroups)

// UserSettings/Editable
KEY(kEditableBool)
KEY(kEditableInt)
KEY(kEditableDouble)
KEY(kEditableString)
KEY(kEditableList)
KEY(kEditableFont)
KEY(kEditableColor)
KEY(kEditableSourceDir)
KEY(kEditableSourceFile)
KEY(kEditableListString)
KEY(kEditableListDir)
KEY(kEditableListFile)
KEY(kEditableEditableList)

// UserSettings/Groups
KEY(kGroupsGroupA)
KEY(kGroupsGroupB)
KEY(kGroupsGroupC)
KEY(kGroupsGroupD)
KEY(kGroupsGroupE)

// UserSettings/Groups/Group
KEY(kGroupBool)
KEY(kGroupInt)
KEY(kGroupDouble)
KEY(kGroupString)

// UserSettings/NotEditable
KEY(kNotEditableByteArray)
KEY(kNotEditableStringArray)
KEY(kNotEditableArrayOfByteArray)
KEY(kNotEditableArrayOfRecords)

}  // namespace key

struct TestRecord
{
    QString str;
    bool bVal;
    double dVal;
    int iVal;

    bool operator!=(const TestRecord& rhv);
};

using CustomSettingArrayOfRecords = SettingArray<Data<TestRecord>>;
using CustomSettingArrayByteArray = SettingArray<DataByteArray>;

class UserSettings : public Setting
{
    class GroupsSettings : public SettingBool
    {
        class GroupSettings : public SettingBool
        {
         public:
            GroupSettings(const QString& key, const QString& caption, const QString& description, const DataBool& data,bool read_only = false, QObject* parent = nullptr);

            SettingBool mBool     {key::kGroupBool, "Boolean", "Tooltip text", {true}};
            SettingInt mInt       {key::kGroupInt, "Integer", "Tooltip text", {100, 0, 2147483647, 100}};
            SettingDouble mDouble {key::kGroupDouble, "Double", "Tooltip text", {0.0, 0, 100, 0.0, 3}};
            SettingString mString {key::kGroupString, "String", "Tooltip text", {"text", "default text"}};
        };
     public:
        GroupsSettings(const QString& key, const QString& caption, const QString& description,  const DataBool& data, bool read_only = false, QObject* parent = nullptr);

        GroupSettings mGroupA   {key::kGroupsGroupA, "Group A", "Tooltip text", {true, true}};
        GroupSettings mGroupB   {key::kGroupsGroupB, "Group B", "Tooltip text", {true, true}};
        GroupSettings mGroupC   {key::kGroupsGroupC, "Group C", "Tooltip text", {true, true}};
        GroupSettings mGroupD   {key::kGroupsGroupD, "Group D", "Tooltip text", {true, true}};
        GroupSettings mGroupE   {key::kGroupsGroupE, "Group E", "Tooltip text", {true, true}};
    };

    class EditableSettings : public Setting
    {
        static constexpr bool kIsReadOnly{false};
     public:
        EditableSettings(const QString& key, const QString& caption, const QString& description, bool read_only = false, QObject* parent = nullptr);

        SettingBool mBool                             {key::kEditableBool, "Boolean", "Tooltip text", {true}, kIsReadOnly};
        SettingInt mInt                               {key::kEditableInt, "Integer", "Tooltip text", {100, 0, 2147483647, 100}, kIsReadOnly};
        SettingDouble mDouble                         {key::kEditableDouble, "Double", "Tooltip text", {0.0, 0, 100, 0.0, 3}, kIsReadOnly};
        SettingString mString                         {key::kEditableString, "String", "Tooltip text", {"text", "default text"}, kIsReadOnly};
        SettingStringList mList                       {key::kEditableList, "List", "Tooltip text", {{"Red", "Green", "Blue"}, "Green"}, kIsReadOnly};
        SettingFont mFont                             {key::kEditableFont, "Font", "Tooltip text", {QFont(), QFont()}, kIsReadOnly};
        SettingColor mColor                           {key::kEditableColor, "Color", "Tooltip color", {QColor(), QColor()}, kIsReadOnly};
        SettingSource mSourceDir                      {key::kEditableSourceDir, "Directory", "Tooltip text", {"", "", DataSource::kDir}, kIsReadOnly};
        SettingSource mSourceFile                     {key::kEditableSourceFile, "File", "Tooltip text", {"", "", DataSource::kFile}, kIsReadOnly};
        SettingChangeableList mChangableListString    {key::kEditableListString, "Changable list", "Tooltip text", {{""}, {""}, DataChangeableList::kStringList, true, ""}, kIsReadOnly};
        SettingChangeableList mChangableListDir       {key::kEditableListDir, "Changable directories list", "Tooltip text", {{""}, {""}, DataChangeableList::kDirList, true, ""}, kIsReadOnly};
        SettingChangeableList mChangableListFile      {key::kEditableListFile, "Changable files list", "Tooltip text", {{""}, {""}, DataChangeableList::kFileList, true, "Text files (*.txt)"}, kIsReadOnly};
        SettingEditableList mEditableList             {key::kEditableEditableList, "Editable list", "Tooltip text", {{"111","222","333"},{"d111","d222","d333"}}, kIsReadOnly};
    };

    class NotEditableSettings : public Setting
    {
     public:
        NotEditableSettings(const QString& key, const QString& caption, const QString& description, bool read_only = false, QObject* parent = nullptr);

        SettingByteArray mByteArray                     {key::kNotEditableByteArray, "Byte array", "Tooltip text"};
        SettingArrayString mStringArray                 {key::kNotEditableStringArray, "String array", "Tooltip text"};
        CustomSettingArrayOfRecords mArrayOfRecords     {key::kNotEditableArrayOfRecords, "Array of records", "Tooltip text"};
        CustomSettingArrayByteArray mArrayOfByteArrays  {key::kNotEditableArrayOfByteArray, "Array of byte arrays", "Tooltip text"};
    };

 public:
    UserSettings(QObject* parent = nullptr);

    GroupsSettings mGroups              {key::kUserGroups, "Groups", "Tooltip text", {true, true}};
    EditableSettings mEditable          {key::kUserEditable, "Editable", "Tooltip text"};
    NotEditableSettings mNotEditable    {key::kUserNotEditable, "Not Editable", "Tooltip text"};
};

}  // namespace custom_setting

extern QDataStream& operator<<(QDataStream& stream, const custom_setting::TestRecord& record);
extern QDataStream& operator>>(QDataStream& stream, custom_setting::TestRecord& record);

Q_DECLARE_METATYPE(custom_setting::TestRecord)

