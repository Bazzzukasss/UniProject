#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlProperty>

#include "UIMessenger.h"
#include "UILogic.h"

#include "common/LoggingCategories.h"
#undef CurrentLoggingCategory
#define CurrentLoggingCategory UiLoggingCategory

UILogic::UILogic(QQmlApplicationEngine* apEngine, QObject *parent)
    : QObject(parent)
    , mpEngine(apEngine)
    , mpUIMessenger( new UIMessenger(this) )
{   
    connect(mpEngine,&QQmlApplicationEngine::objectCreated,[&](){
        mpQuickWindow = qobject_cast<QQuickWindow*>(mpEngine->rootObjects().value(0));

        initialize();
        emit signalUICreated();
    });
}

void UILogic::initialize()
{
    etDebug()<< "UILogic::initializeConnections";
    connect(mpQuickWindow, SIGNAL(signalUIParameterChaged(QString, QVariant)), this, SLOT(slotUIParameterChanged(QString, QVariant)));
    connect(mpQuickWindow, SIGNAL(signalUIAction(QString, QVariant)), this, SLOT(slotUIAction(QString, QVariant)));
    connect(mpQuickWindow, SIGNAL(signalUIMessageAnswer(QString)), mpUIMessenger, SLOT(slotUserAnswerReceived(QString)));

    connect(mpUIMessenger, SIGNAL(signalShowMessage(QVariant, QVariant)), mpQuickWindow, SLOT(showMessage(QVariant, QVariant)));
    connect(mpUIMessenger, SIGNAL(signalHideMessage(QVariant)), mpQuickWindow, SLOT(hideMessage()));
    connect(this, SIGNAL(signalGoToMenu(QVariant)), mpQuickWindow, SLOT(goTo(QVariant)));
}

void UILogic::defaultHandler(QString aParam, QVariant aValue)
{
    etDebug() << "Unhandled handler:" << aParam << aValue;
}

void UILogic::executeHandler(UIHandlerMap &aHandlers, QString aParam, QVariant aValue)
{
    if(aHandlers.contains(aParam))
        aHandlers[aParam](aValue);
    else
        defaultHandler(aParam,aValue);
}

//QML
QVariant UILogic::getQMLProperty(const QString &aParamID)
{
    return QQmlProperty::read(mpQuickWindow, aParamID);
}

void UILogic::setQMLProperty(const QString &aParamID, const QVariant &aValue)
{
    etDebug()<<"Set QML property:"<<aParamID<<aValue;
    QQmlProperty::write(mpQuickWindow, aParamID, aValue);
}

void UILogic::setContextProperty(const QString &aName, QObject *aValue)
{
    mpEngine->rootContext()->setContextProperty(aName,aValue);
}

//Message
QString UILogic::showMessage(UIMessenger::MessageType aType, const QString aText, int aWaitingTime, bool isNeedToWaitAnswer)
{
    return mpUIMessenger->showMessage(aType,aText,aWaitingTime,isNeedToWaitAnswer);
}

QString UILogic::showMessage(const QString &aIcon, const QString aCaption, const QString &aText, const QList<MessageButton> aButtons, int aWaitingTime, bool isNeedToWaitAnswer)
{
    return mpUIMessenger->showMessage(aIcon,aCaption,aText,aButtons,aWaitingTime,isNeedToWaitAnswer);
}

void UILogic::hideMessage()
{
    mpUIMessenger->hideMessage();
}

void UILogic::slotUIParameterChanged(QString aParam, QVariant aValue)
{
    executeHandler(mParamHandlers,aParam,aValue);
}

void UILogic::slotUIAction(QString aParam, QVariant aValue)
{
    executeHandler(mActionHandlers,aParam,aValue);
}
