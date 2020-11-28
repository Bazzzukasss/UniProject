#include <QStandardItemModel>
#include <QListWidgetItem>
#include "list_view.h"
#include "item_delegate.h"

ListView::ListView(QWidget *parent)
    : QListView(parent)
{    
    mModel = new QStandardItemModel(this);
    setModel(mModel);

    mDelegate = new ItemDelegate(this);
    setItemDelegate(mDelegate);
}

void ListView::setItems(const QList<ListItemData> &items_data)
{

    int row{0};
    for(const auto& item_data : items_data)
    {
        auto item = new QStandardItem();
        item->setData(QVariant::fromValue(item_data), Qt::UserRole);
        mModel->setItem(row++, 0, item);
    }
}
