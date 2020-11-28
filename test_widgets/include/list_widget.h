#pragma once

#include <QListWidget>

struct ListItemData;
class ItemDelegate;

class ListWidget : public QListWidget
{
    Q_OBJECT
public:
    enum class ItemMode{kWidgetBased, kDelegateBased};
    ListWidget(QWidget* parent = nullptr);

    void setItems(const QList<ListItemData>& items_data, ItemMode mode);

signals:
    void sigItemSelected(const ListItemData& item_data);

private:
    ItemDelegate* mDelegate{nullptr};
};
