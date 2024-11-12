#include "CameraApp.h"
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QVariant>

CameraApp::CameraApp(QWidget *parent) : QMainWindow(parent), cap(0) {
    setupUI();
    setupConnections();
}

CameraApp::~CameraApp() {
    if (cap.isOpened()) {
        cap.release();
    }
}

void CameraApp::setupUI() {
    // Initialize UI components
    videoLabel = new QLabel(this);
    videoLabel->setFixedSize(640, 480); // Set default resolution size

    startButton = new QPushButton("Start", this);
    pauseButton = new QPushButton("Pause", this);
    stopButton = new QPushButton("Stop", this);

    resolutionSelector = new QComboBox(this);
    resolutionSelector->addItem("640x480", QVariant::fromValue(cv::Size(640, 480)));
    resolutionSelector->addItem("1280x720", QVariant::fromValue(cv::Size(1280, 720)));
    resolutionSelector->addItem("1920x1080", QVariant::fromValue(cv::Size(1920, 1080)));

    timer = new QTimer(this);

    // Set up layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(videoLabel);
    layout->addWidget(resolutionSelector);
    layout->addWidget(startButton);
    layout->addWidget(pauseButton);
    layout->addWidget(stopButton);

    QWidget *container = new QWidget();
    container->setLayout(layout);
    setCentralWidget(container);
}

void CameraApp::setupConnections() {
    // Connect signals to slots
    connect(startButton, &QPushButton::clicked, this, &CameraApp::startCamera);
    connect(pauseButton, &QPushButton::clicked, this, &CameraApp::pauseCamera);
    connect(stopButton, &QPushButton::clicked, this, &CameraApp::stopCamera);
    connect(timer, &QTimer::timeout, this, &CameraApp::updateFrame);
    connect(resolutionSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CameraApp::changeResolution);
}

void CameraApp::startCamera() {
    if (!cap.isOpened()) {
        cap.open(0); // Open default camera
    }
    timer->start(30); // Start timer for frame updates every 30ms
    isPaused = false;
}

void CameraApp::pauseCamera() {
    isPaused = !isPaused;
}

void CameraApp::stopCamera() {
    timer->stop();
    cap.release(); // Release the camera
    videoLabel->clear(); // Clear the video display
}

void CameraApp::updateFrame() {
    if (isPaused || !cap.isOpened()) return;

    cv::Mat frame;
    cap >> frame; // Capture frame from camera

    if (frame.empty()) return;

    // Convert the frame to RGB
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    
    // Convert to QImage
    QImage qImg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    videoLabel->setPixmap(QPixmap::fromImage(qImg).scaled(videoLabel->size(), Qt::KeepAspectRatio));
}

void CameraApp::changeResolution(int index) {
    if (cap.isOpened()) {
        QVariant selectedRes = resolutionSelector->currentData();
        cv::Size res = selectedRes.value<cv::Size>();
        cap.set(cv::CAP_PROP_FRAME_WIDTH, res.width);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, res.height);
    }
}
