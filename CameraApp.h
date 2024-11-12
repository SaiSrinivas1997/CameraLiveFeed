
#ifndef CAMERA_APP_H
#define CAMERA_APP_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTimer>
#include <opencv2/opencv.hpp>

class CameraApp : public QMainWindow {
    Q_OBJECT

public:
    CameraApp(QWidget *parent = nullptr);
    ~CameraApp();

private slots:
    void startCamera();
    void stopCamera();
    void pauseCamera();
    void updateFrame();
    void changeResolution(int index);

private:
    void setupUI();
    void setupConnections();

    cv::VideoCapture cap;         // OpenCV video capture object
    QLabel *videoLabel;           // Label for displaying video frames
    QTimer *timer;                // Timer for frame updates
    QComboBox *resolutionSelector;// ComboBox for selecting resolution
    QPushButton *startButton;     // Button to start video
    QPushButton *pauseButton;     // Button to pause video
    QPushButton *stopButton;      // Button to stop video
    bool isPaused = false;        // Flag to control pause state
};

#endif // CAMERA_APP_H
