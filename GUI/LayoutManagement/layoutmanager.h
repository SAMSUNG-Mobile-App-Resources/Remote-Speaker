#pragma once

#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QAudio>
#include <QAudioDeviceInfo>
#include <QtDebug>
#include <QEvent>

/*!
 * \brief The LayoutManager class
 * It's is the base class. It defines the basic behavior, makes the output of widgets for a specific layout.
 * This class for handling commands from the user.
 * For example, pressing a button, selecting an audio device, etc.
 */
class LayoutManager : public QWidget
{
    Q_OBJECT

public:
    virtual ~LayoutManager();

signals:
    void somebodyConnected();
    void somebodyDisonnected();

protected slots:
    /*!
     * \brief changeBoxesToLabels
     * Show labels on mainLayout instead of boxes respectively.
     * When the user starts to send audio, the format should be unavailable for editing.
     */
    void changeBoxesToLabels();
    /*!
     * \brief changeLabelsToBoxes
     * Show boxes on mainLayout instead of labels respectively
     */
    void changeLabelsToBoxes();
    virtual void connected();
    virtual void disconnected();
    virtual void handleStartButtonClicked(){}
    virtual void handleStopButtonClicked(){}
    virtual void handleConnectButtonClicked(){}
    virtual void handleDisconnectButtonClicked(){}
    virtual void handleMuteButtonClicked(){}
    virtual void handleBadConfigure(){}
    virtual void handleGoodConfigure(){}
    virtual void handleStopped(){}
    virtual void handleBufferSizeChanged(int){}
    virtual void handleProcessedUsec(quint64){}

private slots:
    /*!
     * \brief showOptionsForCurrentDevice
     * Show all options of audio format by Labels and QComboBoxes
     * for the current audio device
     */
    void showOptionsForCurrentDevice();
    void refreshCurrentAudioFormat();
    void refreshCurrentDeviceInfo();
    /*!
     * \brief setPreferredFormat
     * Set default format values for this of QComboBoxes
     */
    void setPreferredFormat();

protected:
    /*!
     * \brief initSpecificWidgets
     * Initialize individual widgets for the Sender and the Receiver.
     * Presetting and adding them to the mainLayout.
     */
    virtual void initSpecificWidgets() = 0;
    /*!
     * \brief initAllWidgets
     * Initialize all widgets to mainLayout.
     */
    void initAllWidgets();
    /*!
     * \brief changeEvent
     * \param event
     * Updates the text in widgets according to the new language if it changed,
     * otherwise transfers control to the parent class.
     */
    virtual void changeEvent(QEvent* event);

    QGridLayout* mainLayout = nullptr; /// class will add widgets to this layout
    QAudio::Mode audioMode; /// Sender has Input mode, Receiver has Output mode
    QAudioFormat currentAudioFormat = QAudioFormat(); /// Current audio format (Sample rate, channel count, ...)
    QAudioDeviceInfo* currentDeviceInfo = nullptr; /// Info about current device (e.g. about Stereo Mix)

    // current widgets (different for sender and receiver)
    QLabel* deviceLabel = nullptr; /// Label for deviceBox
    QComboBox* deviceBox = nullptr; /// Contains all available devices

    QLabel* ipLabel = nullptr; /// Label for ipLineEdit
    QLabel* portLabel = nullptr; /// Label for portLineEdit
    QLineEdit* ipLineEdit = nullptr; /// Input line for ip
    QLineEdit* portLineEdit = nullptr; /// Input line for port
    QLabel* infoLabel = nullptr; /// Here there will be some information text

private:
    void initLabelAndBox();
    void initAudioOptionsWidgets();
    void fillDeviceBox();
    void fillBoxes();
    /*!
     * \brief showBoxes
     * Show QComboBoxes with audio options on mainLayout
     */
    void showBoxes();
    /*!
     * \brief hideBoxes
     * Hide boxes for audio format options from mainLayout
     */
    void hideBoxes();
    /*!
     * \brief dropBoxes
     * Hide QComboBoxes for audio format options from mainLayout and clear them
     */
    void dropBoxes();
    /*!
     * \brief showLabels
     * Show QLabels for audio options on mainLayout
     */
    void showLabels();
    /*!
     * \brief hideLabels
     * Hide labels for audio format options from mainLayout
     */
    void hideLabels();
    /*!
     * \brief showSpecialLabels
     * Show special labels to mainLayout on place of boxes respectively
     */
    void showSpecialLabels();
    /*!
     * \brief hideSpecialLabels
     * Hide special labels from mainLayout
     */
    void hideSpecialLabels();
    /*!
     * \brief sampleTypeToQString
     * \param type
     * \return QString for SampleType
     * Adjuvant function, e.g.
     * sampleTypeToQString(QAudioFormat::SampleType::UnSignedInt) == QString("UnSignedInt")
     */
    QString sampleTypeToQString(QAudioFormat::SampleType type);
    /*!
     * \brief qStringToSampleType
     * \param qstring
     * \return SampleType for QString
     * Adjuvant function, e.g.
     * qStringToSampleType(QString("SignedInt")) == QAudioFormat::SampleType::SignedInt
     */
    QAudioFormat::SampleType qStringToSampleType(QString qString);
    /*!
     * \brief removeWidgetsFromLayout
     * Removing of all widgets added to the mainLayout by this manager
     */
    void removeWidgetsFromLayout();
    /*!
     * \brief deleteWidgets
     * Deleting of all widgets added to the mainLayout by this manager.
     * (freeing memory)
     */
    void deleteWidgets();

    // QLabels of options
    QLabel* sampleRateLabel = nullptr;
    QLabel* channelCountLabel = nullptr;
    QLabel* sampleSizeLabel = nullptr;
    QLabel* audioCodecLabel = nullptr;
    QLabel* byteOrderLabel = nullptr;
    QLabel* sampleTypeLabel = nullptr;

    // QComboBoxes of options
    QComboBox* sampleRateComboBox = nullptr;
    QComboBox* channelCountComboBox = nullptr;
    QComboBox* sampleSizeComboBox = nullptr;
    QComboBox* audioCodecComboBox = nullptr;
    QComboBox* byteOrderComboBox = nullptr;
    QComboBox* sampleTypeComboBox = nullptr;

    // QLabels for change current option in boxes to them
    QLabel* labelForDeviceBox = nullptr;
    QLabel* labelForSampleRateBox = nullptr;
    QLabel* labelForChannelCountBox = nullptr;
    QLabel* labelForSampleSizeBox = nullptr;
    QLabel* labelForAudioCodecBox = nullptr;
    QLabel* labelForByteOrderBox = nullptr;
    QLabel* labelForSampleTypeBox = nullptr;
};

