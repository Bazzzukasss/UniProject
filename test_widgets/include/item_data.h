#pragma once

#include <QMetaType>
#include <QString>

struct ListItemData{
    QString src;
    QString caption;
    QString description;
};

Q_DECLARE_METATYPE(ListItemData)
