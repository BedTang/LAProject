#ifndef HISTORY_FORM_H
#define HISTORY_FORM_H

#include <QWidget>

#include "sqlite_handler.h"

namespace Ui {
class HistoryForm;
}

class HistoryForm : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryForm(QWidget *parent = nullptr ,SqlDataHandler *object = nullptr);
    ~HistoryForm();

private slots:
    void LoadHistoryData();
    void WipeHistoryData();

private:
    Ui::HistoryForm *ui_;
    SqlDataHandler *sql_object_;
    QStandardItemModel *table_model_;
};

#endif // HISTORY_FORM_H
