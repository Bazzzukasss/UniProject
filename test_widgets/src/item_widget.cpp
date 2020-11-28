#include <QMouseEvent>
#include "item_widget.h"
#include "ui_item_widget.h"

ItemWidget::ItemWidget(const ListItemData &item_data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget),
    mData(item_data)
{
    ui->setupUi(this);
    construct();
}

ItemWidget::~ItemWidget()
{
    delete ui;
}

void ItemWidget::setData(const ListItemData &item_data)
{
    mData = item_data;
    construct();
}

const ListItemData &ItemWidget::getData() const
{
    return mData;
}

void ItemWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::MouseButton::LeftButton)
        emit sigSelected(mData);

    QWidget::mousePressEvent(event);
}

void ItemWidget::construct()
{
    ui->mCaptionLabel->setText(mData.caption);
    ui->mDescriptionLabel->setText(mData.description);
    ui->mSrcButton->setIcon(QIcon(mData.src));
}
