#ifndef AJOUTERUTILISATEURDIALOGUI_H
#define AJOUTERUTILISATEURDIALOGUI_H

#include <QAbstractItemModel>

class ajouterutilisateurdialogui : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ajouterutilisateurdialogui(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // AJOUTERUTILISATEURDIALOGUI_H