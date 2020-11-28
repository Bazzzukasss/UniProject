#include "list_widget.h"
#include "item_widget.h"
#include "item_delegate.h"

ListWidget::ListWidget(QWidget *parent)
    : QListWidget(parent)
{    
}

void ListWidget::setItems(const QList<ListItemData> &items_data, ItemMode mode)
{
    clear();
    switch(mode)
    {
        case ItemMode::kWidgetBased:
            for(const auto& item_data : items_data)
            {
                auto widget = new ItemWidget(item_data);
                auto item   = new QListWidgetItem();

                connect(widget, &ItemWidget::sigSelected, this, &ListWidget::sigItemSelected);

                item->setSizeHint(widget->geometry().size());
                addItem(item);
                setItemWidget(item, widget);
            }
            break;
        case ItemMode::kDelegateBased:
        if(!mDelegate)
        {
            mDelegate = new ItemDelegate(this);
            setItemDelegate(mDelegate);
        }

            for(const auto& item_data : items_data)
            {
                auto item   = new QListWidgetItem();
                item->setData(Qt::UserRole, QVariant::fromValue(item_data));

                //connect(widget, &ListItemWidget::sigSelected, this, &ListWidget::sigItemSelected);
                addItem(item);
            }
            break;
    }
}
