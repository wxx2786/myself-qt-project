#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QFileDialog>
#include<QDir>
#include<QMediaPlayer>
#include<QAudioOutput>
#include<QUrl>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建output对象
    audioOutput=new QAudioOutput(this);
    //创建媒体播放对象
    mediaPlayer=new QMediaPlayer(this);
    mediaPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.0);
    ui->volumeSlider->hide();
    ui->listWidget_2->hide();
    //mediaPlayer->setSource(QUrl::fromPercentEncoding(""));
    //获取当前媒体的时长 通过信号关联获取
    connect(mediaPlayer,&QMediaPlayer::durationChanged,this,[=](qint64 duration)
            {
        ui->totalLabel->setText(QString("%1:%2").arg(duration/1000/60,2,10,QChar('0')).arg(duration/1000%60,2,10,QChar('0')));
        ui->playCourseSlider->setRange(0,duration);
        ui->volumeSlider->setRange(0.0,100.00);
            });

    //获取当前播放时间
    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,[=](qint64 pos){
        ui->curLabel->setText(QString("%1:%2").arg(pos/1000/60,2,10,QChar('0')).arg(pos/1000%60,2,10,QChar('0')));
        ui->playCourseSlider->setValue(pos);
    });

    //拖到滑块，让音乐播放进度改变
    connect(ui->playCourseSlider,&QSlider::sliderMoved,mediaPlayer,&QMediaPlayer::setPosition);
    //connect(ui->volumeSlider,&QSlider::sliderMoved,audioOutput,&QAudioOutput::setVolume);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_7_clicked()
{
    qInfo()<<"hello student";
    auto path=QFileDialog::getExistingDirectory(this,"请选择音乐文件目录","D:\\CPP_project\\qt_project\\MusicPlayer\\assert\\music");
    QDir dir(path);
    auto musicList=dir.entryList(QStringList()<<"*.mp3"<<"*.wav");
    //把音乐名字放入listwidget展示
    ui->listWidget->addItems(musicList);

    ui->listWidget->setCurrentRow(0);

    for(auto file:musicList)
        playList.append(QUrl::fromLocalFile(path+'/'+file));
}


void Widget::on_pushButton_10_clicked()
{
    switch (mediaPlayer->playbackState()) {
    case QMediaPlayer::PlaybackState::StoppedState:
    {   curPlayIndex=ui->listWidget->currentRow();
        ui->pushButton_10->setStyleSheet("QPushButton{""icon: url(:/assert/playing.png);""}");
        mediaPlayer->setSource(playList[curPlayIndex]);
        mediaPlayer->play();
        break;
    }
    case QMediaPlayer::PlaybackState::PlayingState:
        ui->pushButton_10->setStyleSheet("QPushButton{""icon: url(:/assert/pause.png);""}");
        mediaPlayer->pause();
        break;

    case QMediaPlayer::PlaybackState::PausedState:
        ui->pushButton_10->setStyleSheet("QPushButton{""icon: url(:/assert/playing.png);""}");
        mediaPlayer->play();
        break;

    }

}

//上一曲
void Widget::on_pushButton_9_clicked()
{
    if(curPlayIndex-1<0) curPlayIndex=playList.size()-1;
    else
        curPlayIndex=(curPlayIndex-1)%playList.size();
    ui->listWidget->setCurrentRow(curPlayIndex);
    mediaPlayer->setSource(playList[curPlayIndex]);
    mediaPlayer->play();
    //ui->listWidget_2->addItem(playList[curPlayIndex]);
}

//下一曲
void Widget::on_pushButton_11_clicked()
{

    curPlayIndex=(curPlayIndex+1)%playList.size();
    ui->listWidget->setCurrentRow(curPlayIndex);
    mediaPlayer->setSource(playList[curPlayIndex]);
    mediaPlayer->play();
    //ui->listWidget_2->addItem(playList[curPlayIndex]);
}



void Widget::on_listWidget_doubleClicked(const QModelIndex &index)
{
    curPlayIndex=index.row();
    mediaPlayer->setSource(playList[curPlayIndex]);
    mediaPlayer->play();
}






void Widget::on_volumeSlider_sliderMoved(int position)
{
    audioOutput->setVolume(float(position)/100);
}




void Widget::on_pushButton_12_clicked()
{
    if(ui->volumeSlider->isHidden()){
        ui->volumeSlider->show();
    }else{
        ui->volumeSlider->hide();
    }
}


void Widget::on_pushButton_8_clicked()
{
    if(ui->listWidget_2->isHidden()){
        ui->listWidget_2->show();
    }else{
        ui->listWidget_2->hide();
    }
}

