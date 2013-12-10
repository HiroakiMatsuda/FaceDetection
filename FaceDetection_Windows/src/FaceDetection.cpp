// -*- C++ -*-
/*!
 * @file  FaceDetection.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "FaceDetection.h"

// OpenCV
#pragma comment(lib,"opencv_core246.lib")
#pragma comment(lib,"opencv_highgui246.lib")
#pragma comment(lib,"opencv_objdetect246.lib")
#pragma comment(lib,"opencv_imgproc246.lib")

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define WIDTH  640
#define HEIGHT 480
#define BPP 24

cv::VideoCapture cap;
cv::CascadeClassifier cascade;

// Module specification
// <rtc-template block="module_spec">
static const char* facedetection_spec[] =
  {
    "implementation_id", "FaceDetection",
    "type_name",         "FaceDetection",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Hiroaki Matsuda",
    "category",          "CAMERA",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.xml", "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml",
    // Widget
    "conf.__widget__.xml", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
FaceDetection::FaceDetection(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_pointOut("face_piont", m_point)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
FaceDetection::~FaceDetection()
{
}



RTC::ReturnCode_t FaceDetection::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("face_piont", m_pointOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("xml", m_conf_xml, "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml");
  // </rtc-template>
  
  cap = cv::VideoCapture(0);

  cap.set(CV_CAP_PROP_FRAME_WIDTH, WIDTH);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);

  if(!cap.isOpened())
  {
      return RTC::RTC_ERROR;    
  }

  return RTC::RTC_OK;
}



RTC::ReturnCode_t FaceDetection::onActivated(RTC::UniqueId ec_id)
{
  std::string cascadeName = m_conf_xml; 

  std::cout << "Read XML:" << cascadeName << std::endl;
  if(!cascade.load(cascadeName))
  {
    std::cout << "Can no find XML" << std::endl;
    return RTC::RTC_ERROR;
  }
  
  std::cout << "CreateWindow" << std::endl;
  cv::namedWindow("FaceDetection", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);

  return RTC::RTC_OK;
}


RTC::ReturnCode_t FaceDetection::onDeactivated(RTC::UniqueId ec_id)
{
  std::cout << "DestroyWindow" << std::endl;
  cv::destroyWindow("FaceDetection");

  return RTC::RTC_OK;
}


RTC::ReturnCode_t FaceDetection::onExecute(RTC::UniqueId ec_id)
{
  cv::Mat frame;
  cap >> frame;


  double scale = 4.0; 
  cv::Mat gray, smallImg(cv::saturate_cast<int>(frame.rows/scale), cv::saturate_cast<int>(frame.cols/scale), CV_8UC1);
  cv::cvtColor(frame, gray, CV_BGR2GRAY);
  cv::resize(gray, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
  cv::equalizeHist( smallImg, smallImg);

  std::vector<cv::Rect> faces;

  cascade.detectMultiScale(smallImg, faces,1.1, 2, CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

  std::vector<cv::Rect>::const_iterator r = faces.begin();
  for(; r != faces.end(); ++r) {
    cv::Point center;
    int radius;
    center.x = cv::saturate_cast<int>((r->x + r->width*0.5)*scale);
    center.y = cv::saturate_cast<int>((r->y + r->height*0.5)*scale);
    radius = cv::saturate_cast<int>((r->width + r->height)*0.25*scale);
    cv::circle( frame, center, radius, cv::Scalar(80,80,255), 3, 8, 0 );
    std::cout << center.x << " " << center.y << std::endl;
    m_point.data.x = center.x;
    m_point.data.y = center.y;
    setTimestamp(m_point);
    m_pointOut.write();
    
  }
  
  cv::imshow("FaceDetection", frame);
  
  cv::waitKey(1);

  return RTC::RTC_OK;
}



extern "C"
{
 
  void FaceDetectionInit(RTC::Manager* manager)
  {
    coil::Properties profile(facedetection_spec);
    manager->registerFactory(profile,
                             RTC::Create<FaceDetection>,
                             RTC::Delete<FaceDetection>);
  }
  
};


