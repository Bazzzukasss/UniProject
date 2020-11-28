#include <QApplication>
#include "main_window.h"
#include "list_widget.h"
#include "list_view.h"
#include "item_data.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if(1)
    ListView w;
    w.setItems({
                   ListItemData{":/user_icons/1.svg","User 1","simple user 1"},
                   ListItemData{":/user_icons/2.svg","User 2","simple user 2"},
                   ListItemData{":/user_icons/3.svg","User 3","simple user 3"},
                   ListItemData{":/user_icons/4.svg","User 4","simple user 4"},
                   ListItemData{":/user_icons/5.svg","User 5","simple user 5"}
               });
#else
    ListWidget w;
    w.setItems({
                   ListItemData{":/user_icons/1.svg","User 1","simple user 1"},
                   ListItemData{":/user_icons/2.svg","User 2","simple user 2"},
                   ListItemData{":/user_icons/3.svg","User 3","simple user 3"},
                   ListItemData{":/user_icons/4.svg","User 4","simple user 4"},
                   ListItemData{":/user_icons/5.svg","User 5","simple user 5"}
               },
               ListWidget::ItemMode::kDelegateBased);
#endif
    //MainWindow w;
    w.show();
    return a.exec();
}
