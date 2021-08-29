#ifndef UILOGIC_H
#define UILOGIC_H

#include <QObject>
#include <QVariant>
#include <QMap>
#include "UIMessenger.h"

class QQuickWindow;
class QQmlApplicationEngine;

typedef std::function<void(QVariant const&)> UIHandler;
typedef QMap<QString,UIHandler> UIHandlerMap;

class UILogic : public QObject
{
    Q_OBJECT

public:
    explicit UILogic(QQmlApplicationEngine* apEngine, QObject *parent = nullptr);
    virtual ~UILogic(){}

    QVariant getQMLProperty(QString const& aParamID);
    void setQMLProperty(QString const& aParamID, QVariant const& aValue);
    void setContextProperty(const QString &aName, QObject *aValue);    

    QString showMessage(UIMessenger::MessageType aType, const QString aText, int aWaitingTime = -1, bool isNeedToWaitAnswer = true);
    QString showMessage(const QString& aIcon, const QString aCaption, const QString& aText, const QList<MessageButton> aButtons, int aWaitingTime = -1, bool isNeedToWaitAnswer = true);
    void hideMessage();

signals:
    void signalUICreated();

protected:
    QQmlApplicationEngine*  mpEngine;
    UIMessenger*              mpUIMessenger;
    QQuickWindow*           mpQuickWindow;
    UIHandlerMap            mActionHandlers;
    UIHandlerMap            mParamHandlers;

    virtual void defaultHandler(QString aParam, QVariant aValue);
    void executeHandler(UIHandlerMap& aHandlers, QString aParam, QVariant aValue);

    virtual void initialize();

private slots:
    void slotUIParameterChanged(QString aParam, QVariant aValue);
    void slotUIAction(QString aParam, QVariant aValue);    
};

#endif // UILOGIC_H
