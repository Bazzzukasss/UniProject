#include "QMLListModel.h"
#include "common/LoggingCategories.h"
#undef CurrentLoggingCategory
#define CurrentLoggingCategory UiLoggingCategory

QMLListModel::QMLListModel(QObject *apParent)
	: QMLListModel({}, apParent)
{}

QMLListModel::QMLListModel(QHash<QByteArray, int> const& aRoleIndices, QObject *apParent)
	: QStandardItemModel(apParent)
	, mRoleIndices(aRoleIndices)
{
	connect(this, &QStandardItemModel::rowsInserted, this, &QMLListModel::rowCountChanged);
	connect(this, &QStandardItemModel::rowsRemoved, this, &QMLListModel::rowCountChanged);
	connect(this, &QStandardItemModel::modelReset, this, &QMLListModel::rowCountChanged);
}

void QMLListModel::append(QVariantMap const& aArguments)
{
	QStandardItemModel::appendRow(mapToItem(aArguments));
}

void QMLListModel::clear()
{
	QStandardItemModel::clear();
}

QVariantMap QMLListModel::get(int aIndex) const
{
    return itemToMap(QStandardItemModel::item(aIndex));
}

Q_INVOKABLE void QMLListModel::insert(int aIndex, QVariantMap const& aArguments)
{
	if (aIndex > 0 && aIndex < QStandardItemModel::rowCount())
		QStandardItemModel::insertRow(aIndex, mapToItem(aArguments));
	else if (aIndex == QStandardItemModel::rowCount())
		append(aArguments);
	else
        etDebug() << "QMLListModel::insert called with invalid index argument:" << aIndex;
}

Q_INVOKABLE void QMLListModel::move(int aFrom, int aTo, int aCount)
{
	if (aFrom < 0 || aTo < 0
		|| (aFrom + aCount) >= QStandardItemModel::rowCount() 
		|| (aTo + aCount) >= QStandardItemModel::rowCount())
		return;

	for (int i = 0; i < aCount; ++aCount)
	{
		// swap the items between the from and to
		auto pFrom = QStandardItemModel::takeItem(aFrom + i);
		QStandardItemModel::setItem(aFrom + i, QStandardItemModel::takeItem(aTo + i));
		QStandardItemModel::setItem(aTo + i, pFrom);
	}
}

Q_INVOKABLE void QMLListModel::remove(int aIndex, int aCount)
{
	QStandardItemModel::removeRows(aIndex, aCount);
}

Q_INVOKABLE void QMLListModel::set(int aIndex, QVariantMap const& aArguments)
{
	if (aIndex == QStandardItemModel::rowCount())
		QStandardItemModel::appendRow(new QStandardItem);

	if (auto pItem = QStandardItemModel::item(aIndex))
		mapToItem(aArguments, pItem);
}

Q_INVOKABLE void QMLListModel::setProperty(int aIndex, QString const& aProperty, QVariant const& aValue)
{
	if (auto pItem = QStandardItemModel::item(aIndex))
		pItem->setData(aValue, propertyToRole(aProperty));
}

QHash<int, QByteArray> QMLListModel::roleNames() const
{
	QHash<int, QByteArray> hash;
	for (auto it = mRoleIndices.begin(); it != mRoleIndices.end(); ++it)
		hash.insert(*it, it.key());
	return hash;
}

QHash<QByteArray, int>::const_iterator QMLListModel::insertRole(QByteArray const& aKey)
{
	return mRoleIndices.insert(aKey, Qt::UserRole + mRoleIndices.size());
}

QVariantMap QMLListModel::itemToMap(QStandardItem const* apItem, QVariantMap aMap) const
{
	if (apItem != nullptr) 
	{
		for (auto itRoleIdx = mRoleIndices.begin(); itRoleIdx != mRoleIndices.end(); ++itRoleIdx)
		{
			aMap.insert(QString::fromUtf8(itRoleIdx.key()), apItem->data(*itRoleIdx));
		}
	}
	else 
	{
        etDebug() << "QMLListModel::itemToMap called for nullptr item";
	}
	return aMap;
}

QStandardItem* QMLListModel::mapToItem(QVariantMap const& aMap, QStandardItem* apItem)
{
	for (auto itArg = aMap.begin(); itArg != aMap.end(); ++itArg)
	{
		apItem->setData(*itArg, propertyToRole(itArg.key()));
	}

	return apItem;
}

int QMLListModel::propertyToRole(QString const& aProperty)
{
	auto const key = aProperty.toUtf8();
	auto itRoleIdx = mRoleIndices.constFind(key);
	if (mRoleIndices.constEnd() == itRoleIdx)
	{
		itRoleIdx = insertRole(key);
	}
	return *itRoleIdx;
}

