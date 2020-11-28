#include <QPainter>
#include "item_delegate.h"
#include "item_data.h"
#include "item_widget.h"

ItemDelegate::ItemDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    QStyledItemDelegate::paint(painter, option, index);

    auto item_data = index.data(Qt::UserRole);
    if(item_data.isValid())
    {
        ItemWidget widget(qvariant_cast<ListItemData>(item_data));
        widget.setStyleSheet("background-color: transparent;");
        widget.setFixedSize(option.rect.size());

        if (option.state & QStyle::State_Selected)
                    painter->fillRect(option.rect, option.palette.highlight());

        QPixmap pixmap(widget.size());
        pixmap.fill(Qt::transparent);
        widget.render(&pixmap);
        painter->drawPixmap(option.rect, pixmap);
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto sHint = QStyledItemDelegate::sizeHint(option, index);
    auto item_data = index.data(Qt::UserRole);
    if(item_data.isValid())
        sHint.setHeight(82);

    return sHint;
}
