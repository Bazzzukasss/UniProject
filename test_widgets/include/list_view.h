#pragma once

#include <QListView>
#include "item_data.h"

class ItemDelegate;
class QStandardItemModel;

class ListView : public QListView
{
public:
    ListView(QWidget* parent = nullptr);

    void setItems(const QList<ListItemData>& items_data);

signals:
    void sigItemSelected(const ListItemData& item_data);

private:
    ItemDelegate* mDelegate{nullptr};
    QStandardItemModel* mModel;
};
