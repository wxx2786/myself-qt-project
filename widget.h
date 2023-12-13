#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QUrl>

class QMediaPlayer;
class QAudioOutput;
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_volumeSlider_sliderMoved(int position);



    void on_pushButton_12_clicked();

private:
    Ui::Widget *ui;
    QList<QUrl>playList;
    int curPlayIndex=0;
    QMediaPlayer*mediaPlayer;
    QAudioOutput*audioOutput;
};
#endif // WIDGET_H
