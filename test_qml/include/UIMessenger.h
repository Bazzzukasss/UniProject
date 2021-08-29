#ifndef UIMESSENGER_H
#define UIMESSENGER_H

#include <QObject>
#include <QString>
#include <QMessageBox>
#include <QVariant>
#include <QTimer>
#include <QEventLoop>

struct MessageButton{
    enum ButtonMode {BT_STANDART,BT_HIGHLITED1,BT_HIGHLITED2};

    QString mCaption;
    QString mKey;
    ButtonMode mMode;
    QString mAction;
};

extern MessageButton ButtonOk;
extern MessageButton ButtonYes;
extern MessageButton ButtonNo;
extern MessageButton ButtonCancel;
extern MessageButton ButtonApply;
extern MessageButton ButtonStop;
extern MessageButton ButtonStopPlatform;
extern MessageButton ButtonStopMovement;

class UIMessenger : public QObject
{
	Q_OBJECT

public:
    enum MessageType { MT_INFORMATION, MT_WARNING, MT_REQUEST, MT_MOVING, MT_ERROR, MT_ATTENTION, MT_DONE, MT_WAIT };


    UIMessenger(QObject* parent = 0);

    QString showMessage(const QString& aIcon, const QString aCaption, const QString& aText, const QList<MessageButton> aButtons, int aShowingTime = -1, bool aIsNeedToWaitAnswer = true);
    QString showMessage(MessageType aType, const QString aText, int aShowingTime = -1, bool aIsNeedToWaitAnswer = true);
	void hideMessage();
	QMessageBox::StandardButton getUserButton() const;    
    void setSourcePath(QString& mPath);

public slots:
	void slotUserAnswerReceived(const QString& aText);

signals:
    void signalShowMessage(QVariant aData, QVariant aButtons);
    void signalHideMessage(QPrivateSignal);
    void signalHideMessage(QVariant);

private:
	QString mUserAnswer;
    QString mSourcePath;
    QTimer mTimer;
    QEventLoop mLoop;

    QString waitMessageAnswer(int aShowingTime, bool aIsNeedToWaitAnswer);
};

#endif // UIMESSENGER_H
