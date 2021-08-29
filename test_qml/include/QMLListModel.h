#ifndef QMLListModel_h
#define QMLListModel_h
#pragma once

#include <QStandardItemModel>
#include <QByteArray>
#include <QHash>
#include <vector>
#include <unordered_map>

class QMLListModel : public QStandardItemModel
{
	Q_OBJECT
	Q_PROPERTY(int count READ rowCount NOTIFY rowCountChanged)

signals:
	void rowCountChanged();

public:
	explicit QMLListModel(QObject *apParent = nullptr);

	explicit QMLListModel(QHash<QByteArray, int> const& aRoleIndices, QObject *apParent = nullptr);

	virtual ~QMLListModel() = default;

	/*Mimic QML ListModel's interface for interoperability*/

	/**
	 * \brief Adds a new item to the end of the list model, with the values in aArguments.
	 */
	Q_INVOKABLE virtual void append(QVariantMap const& aArguments);

	/**
	 * \brief Deletes all content from the model.
	 */
	Q_INVOKABLE virtual void clear();

	/**
	 * \brief Returns the item at index in the list model.
	 *		  The index must be an element in the list.
	 * \return a variant map containing the properties of the item
	 */
    Q_INVOKABLE virtual QVariantMap get(int aIndex) const;

	/**
	 * \brief Adds a new item to the list model at position index, with the values in aArgument.
	 */
	Q_INVOKABLE virtual void insert(int aIndex, QVariantMap const& aArguments);

	/**
	 * \brief Moves n items from one position to another.
	 *		  The from and to ranges must exist; for example, to move 
	 *		  the first 3 items to the end of the list:
	 */
	Q_INVOKABLE virtual void move(int aFrom, int aTo, int aCount);

	/**
	 * \brief Deletes the content at index from the model.
	 */
	Q_INVOKABLE virtual void remove(int aIndex, int aCount);

	/**
	 * \brief Changes the item at index in the list model with the values in aArguments. 
	 *		  Properties not appearing in aArguments are left unchanged.
	 *		  If index is equal to count() then a new item is appended to the list. 
	 *		  Otherwise, index must be an element in the list.
	 */
	Q_INVOKABLE virtual void set(int aIndex, QVariantMap const& aArguments);

	/**
	 * \brief Changes the property of the item at index in the list model to value.
	 *	      The index must be an element in the list.
	 */
	Q_INVOKABLE virtual void setProperty(int aIndex, QString const& aProperty, QVariant const& aValue);

protected:
	virtual QHash<int, QByteArray> roleNames() const override;
	
	QHash<QByteArray, int>::const_iterator insertRole(QByteArray const& aKey);

    QVariantMap itemToMap(QStandardItem const* apItem, QVariantMap aMap = QVariantMap() ) const;
	QStandardItem* mapToItem(QVariantMap const& aMap, QStandardItem* apItem = new QStandardItem);
	int propertyToRole(QString const& aProperty);

private:
	QHash<QByteArray, int> mRoleIndices;
};


#endif

