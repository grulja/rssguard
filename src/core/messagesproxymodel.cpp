#include "core/messagesproxymodel.h"
#include "core/messagesmodel.h"


MessagesProxyModel::MessagesProxyModel(QObject *parent)
  : QSortFilterProxyModel(parent) {
  m_sourceModel = new MessagesModel(this);

  setObjectName("MessagesProxyModel");
  setSortRole(Qt::EditRole);
  setSortCaseSensitivity(Qt::CaseInsensitive);
  setFilterCaseSensitivity(Qt::CaseInsensitive);
  setFilterKeyColumn(-1);
  setFilterRole(Qt::EditRole);
  setDynamicSortFilter(false);
  setSourceModel(m_sourceModel);
}

MessagesProxyModel::~MessagesProxyModel() {
  qDebug("Destroying MessagesProxyModel instance.");
}

MessagesModel *MessagesProxyModel::sourceModel() {
  return m_sourceModel;
}

bool MessagesProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
  return QSortFilterProxyModel::lessThan(left, right);
}

QModelIndexList MessagesProxyModel::mapListFromSource(const QModelIndexList &indexes, bool deep) {
  QModelIndexList mapped_idxs;

  foreach (const QModelIndex &index, indexes) {
    if (deep) {
      mapped_idxs << mapFromSource(m_sourceModel->index(index.row(), index.column()));
    }
    else {
      mapped_idxs << mapFromSource(index);
    }
  }

  return mapped_idxs;
}

QModelIndexList MessagesProxyModel::mapListToSource(const QModelIndexList &indexes) {
  QModelIndexList source_idxs;

  foreach (const QModelIndex &index, indexes) {
    source_idxs << mapToSource(index);
  }

  return source_idxs;
}

