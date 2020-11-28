#pragma once

#include <QWidget>
#include "item_data.h"

namespace Ui {
class ItemWidget;
}

class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(const ListItemData &item_data, QWidget *parent = nullptr);
    ~ItemWidget();

    void setData(const ListItemData& item_data);
    const ListItemData& getData() const;

signals:
    void sigSelected(const ListItemData& item_data);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::ItemWidget *ui;
    ListItemData mData;

    void construct();
};
