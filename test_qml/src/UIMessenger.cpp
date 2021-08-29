#include "UIMessenger.h"


#include <QEventLoop>
#include <QTimer>
#include "common/LoggingCategories.h"
#undef CurrentLoggingCategory
#define CurrentLoggingCategory CommonLoggingCategory

MessageButton ButtonOk      = {"Ok","Ok",MessageButton::BT_STANDART,""};
MessageButton ButtonYes     = {"Yes","Yes",MessageButton::BT_STANDART,""};
MessageButton ButtonNo      = {"No","No",MessageButton::BT_STANDART,""};
MessageButton ButtonCancel  = {"Cancel","No",MessageButton::BT_STANDART,""};
MessageButton ButtonApply   = {"Apply","Yes",MessageButton::BT_STANDART,""};
MessageButton ButtonStop    = {"Stop","Ok",MessageButton::BT_HIGHLITED1,"actionPlatformStop"};
MessageButton ButtonClose    = {"Close","Ok",MessageButton::BT_HIGHLITED1,""};
MessageButton ButtonStopMovement    = {"Stop","Ok",MessageButton::BT_HIGHLITED1,"actionStopMovement"};

UIMessenger::UIMessenger(QObject* parent /*= 0*/)
	: QObject(parent)
	, mUserAnswer("")
    , mSourcePath("qrc:/img/")
{
    mTimer.setSingleShot(true);
    QObject::connect(&mTimer, &QTimer::timeout, [&](){
                                                        mLoop.quit();
                                                        emit signalHideMessage(QVariant());
                                                    });

    QObject::connect(this, static_cast<void (UIMessenger::*)(QPrivateSignal)>(&UIMessenger::signalHideMessage), &mLoop, &QEventLoop::quit);
}

QString UIMessenger::showMessage(MessageType aType, const QString aText, int aShowingTime /*= -1*/, bool aIsNeedToWaitAnswer)
{
    QString icons[] = { mSourcePath+"message-info.svg",
                        mSourcePath+"message-warning.svg",
                        mSourcePath+"message-request.svg",
                        mSourcePath+"message-spinner.gif",
                        mSourcePath+"message-error.svg",
                        mSourcePath+"message-warning.svg",
                        mSourcePath+"message-done.svg",
                        mSourcePath+"message-spinner.gif"
                        };

    QString captions[] = {  tr("Information"),
                            tr("Warning"),
                            tr("Request"),
                            tr("Processing..."),
                            tr("Error"),
                            tr("Information"),
                            tr("Welldone"),
                            tr("Processing...")
                            };

    QList<MessageButton> buttons[] = {
        {ButtonOk},
        {ButtonCancel,ButtonOk},
        {ButtonCancel,ButtonYes},
        {ButtonStop},
        {ButtonCancel,ButtonOk},
        {ButtonOk},
        {ButtonCancel,ButtonApply},
        {}
    };

    return showMessage(icons[aType],captions[aType], aText, buttons[aType], aShowingTime, aIsNeedToWaitAnswer);
}

QString UIMessenger::showMessage(const QString &aIcon, const QString aCaption, const QString &aText, const QList<MessageButton> aButtons, int aShowingTime /*= -1*/, bool aIsNeedToWaitAnswer)
{
    QVariantMap dataMap;
    QVariantList buttonsList;

    dataMap["icon"] = aIcon;
    dataMap["caption"] = aCaption;
    dataMap["text"] = aText;

    for(auto& button : aButtons)
    {
        QVariantMap buttonMap;
        buttonMap["caption"] = button.mCaption;
        buttonMap["mode"] = button.mMode;
        buttonMap["action"] = button.mAction;
        buttonMap["key"] = button.mKey;
        buttonsList << buttonMap;
    }

    emit signalShowMessage(dataMap,buttonsList);

    etDebug() << "SHOW MESSAGE: " << aIcon << aCaption << aText;
    return waitMessageAnswer(aShowingTime,aIsNeedToWaitAnswer);
}

QString UIMessenger::waitMessageAnswer(int aShowingTime, bool aIsNeedToWaitAnswer)
{
    if (aShowingTime > 0)
        mTimer.start(aShowingTime);

    if(aIsNeedToWaitAnswer)
    {
        mLoop.exec();
        etDebug() << "HIDE MESSAGE: ANSWER:" << mUserAnswer;
        return mUserAnswer;
    }
    return "";
}

void UIMessenger::hideMessage()
{
    etDebug() << "HIDE MESSAGE";
    emit signalHideMessage(QPrivateSignal());
    emit signalHideMessage(QVariant());
}

QMessageBox::StandardButton UIMessenger::getUserButton() const
{
	if (mUserAnswer == "Yes") return QMessageBox::Yes;
	if (mUserAnswer == "No") return QMessageBox::No;
	if (mUserAnswer == "Ok") return QMessageBox::Ok;

    return QMessageBox::Ok;
}

void UIMessenger::setSourcePath(QString &mPath)
{
    mSourcePath = mPath;
}

void UIMessenger::slotUserAnswerReceived(const QString& aText)
{
	mUserAnswer = aText;
    hideMessage();
}
