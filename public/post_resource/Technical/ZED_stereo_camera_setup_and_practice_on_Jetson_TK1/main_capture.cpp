/* 
Program: 
Store images and corresponding depth map by ZED stereo camera.
This program is developed based on ZED-OpenCV example. 
A continously capturing feature is added.
Press key "o", then the camera starts to capture images until reach a certain number which can be set.

Developed by H.Y. ZHAN

Version history
Ver.0.0 | 2016-09-09 | initial release


This program saves left image, disparity image and depth map from time to time.
The program follows the following struture.
|-- Includes
    |-- Standard includes
    |-- OpenCV includes
    |-- ZED Includes
|-- Setup Parameters
|-- Self-defined functions
|-- Default structures and functions
|-- Main


*/

//standard includes
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <iostream>

//opencv includes
#include <opencv2/opencv.hpp>

//ZED Includes
#include <zed/Camera.hpp>
#include <zed/utils/GlobalDefine.hpp>

// main setup parameters
double resize_fac = 1; //this resize factor will resize height and width of left image. e.g. original shape is 1280x720, with resize_fac = 0.5, the final image shape will be 640x360
int img_cnt = 50; //number of images to be captured
int delay_cnt = 5; // For every 5 cnts, take a photo
std::string img_dir = "../captured_image/Image/"; // directory for saving left image
std::string disp_img_dir = "../captured_image/Disparity/"; // directory for saving disparity image
std::string depth_map_dir = "../captured_image/DepthMap/"; //directory for saving depth map
/***/

int ttl_cnt = img_cnt * delay_cnt;

// Self-defined functions

void save_left_img(sl::zed::Camera* zed, std::string filename) {
    sl::zed::resolution imSize = zed->getImageSize();

    cv::Mat SbS(imSize.height, imSize.width, CV_8UC4);
    cv::Mat leftIm(SbS, cv::Rect(0, 0, imSize.width, imSize.height));

    slMat2cvMat(zed->retrieveImage(sl::zed::SIDE::LEFT)).copyTo(leftIm);

    cv::cvtColor(SbS, SbS, CV_RGBA2RGB);
    cv::resize(SbS,SbS, cv::Size(), resize_fac, resize_fac);

    cv::imwrite(filename, SbS);
}

void save_disp_img(sl::zed::Camera* zed, cv::Mat disp, std::string filename) {
    cv::Mat dispSnapshot;
    disp.copyTo(dispSnapshot);
    cv::resize(dispSnapshot, dispSnapshot, cv::Size(), resize_fac, resize_fac);
    cv::imwrite(filename, dispSnapshot);

}

void save_depth_map(sl::zed::Camera* zed, sl::zed::Mat depth, std::string filename) {
    cv::Mat depth_mat;
    cv::Mat depth_16UC;
    slMat2cvMat(depth).copyTo(depth_mat);
    cv::Mat depth_8UC4(depth_mat.rows, depth_mat.cols, CV_8UC4, depth_mat.data);
    cv::Mat depth_32f(depth_mat.rows, depth_mat.cols, CV_32F, depth_8UC4.data);
    depth_32f.convertTo(depth_16UC, CV_16U);
    cv::imwrite(filename, depth_16UC);
    // cv::imwrite(filename, depth_8UC4);
}
/***/

// Default structure and functions
typedef struct mouseOCVStruct {
    float* data;
    uint32_t step;
    cv::Size _image;
    cv::Size _resize;
    std::string name;
    std::string unit;
} mouseOCV;

mouseOCV mouseStruct;

static void onMouseCallback(int32_t event, int32_t x, int32_t y, int32_t flag, void * param) {
    if (event == CV_EVENT_LBUTTONDOWN) {
        mouseOCVStruct* data = (mouseOCVStruct*) param;


        int y_int = (y * data->_image.height / data->_resize.height);
        int x_int = (x * data->_image.width / data->_resize.width);

        float* ptr_image_num = (float*) ((int8_t*) data->data + y_int * data->step);
        float dist = ptr_image_num[x_int];

        if (isValidMeasure(dist)){
            printf("\n%s : %2.2f %s\n", data->name.c_str(), dist, data->unit.c_str());
        }
        else {
            if (dist == TOO_FAR)
                printf("\n%s is too far.\n", data->name.c_str(), dist, data->unit.c_str());
            else if (dist == TOO_CLOSE)
                printf("\n%s is too close.\n", data->name.c_str(), dist, data->unit.c_str());
            else
                printf("\n%s not avaliable\n", data->name.c_str(), dist, data->unit.c_str());
        }
    }
}

void saveSbSimage(sl::zed::Camera* zed, std::string filename) {
    sl::zed::resolution imSize = zed->getImageSize();

    cv::Mat SbS(imSize.height, imSize.width * 2, CV_8UC4);
    cv::Mat leftIm(SbS, cv::Rect(0, 0, imSize.width, imSize.height));
    cv::Mat rightIm(SbS, cv::Rect(imSize.width, 0, imSize.width, imSize.height));

    slMat2cvMat(zed->retrieveImage(sl::zed::SIDE::LEFT)).copyTo(leftIm);
    slMat2cvMat(zed->retrieveImage(sl::zed::SIDE::RIGHT)).copyTo(rightIm);

    cv::imshow("Saving Image", SbS);
    cv::cvtColor(SbS, SbS, CV_RGBA2RGB);

    cv::imwrite(filename, SbS);
}
/***/


//main  function

int main(int argc, char **argv) {
    // Clear files in captured image folder
    std::system(("exec rm -r " + img_dir + '*').c_str());
    std::system(("exec rm -r " + disp_img_dir + '*').c_str());
    std::system(("exec rm -r " + depth_map_dir + '*').c_str());
    /**/ 


    if (argc > 3) {
        std::cout << "Only the path of a SVO or a InitParams file can be passed in arg." << std::endl;
        return -1;
    }

    // quick check of arguments
    bool readSVO = false;
    std::string SVOName;
    bool loadParams = false;
    std::string ParamsName;
    if (argc > 1) {
        std::string _arg;
        for (int i = 1; i < argc; i++) {
            _arg = argv[i];
            if (_arg.find(".svo") != std::string::npos) { // if a SVO is given we save its name
                readSVO = true;
                SVOName = _arg;
            }
            if (_arg.find(".ZEDinitParam") != std::string::npos) { // if a parameters file is given we save its name
                loadParams = true;
                ParamsName = _arg;
            }
        }
    }
    /***/

    sl::zed::Camera* zed;
    
    // SVO playback mode
    if (!readSVO) // Use in Live Mode
        zed = new sl::zed::Camera(sl::zed::HD720);
    else // Use in SVO playback mode
        zed = new sl::zed::Camera(SVOName);
    /***/

    // define a struct of parameters for the initialization
    sl::zed::InitParams params;
    /***/

    if (loadParams)// a file is given in argument, we load it
        params.load(ParamsName);

 
    sl::zed::ERRCODE err = zed->init(params);
    std::cout << "Error code : " << sl::zed::errcode2str(err) << std::endl;
    if (err != sl::zed::SUCCESS) {// Quit if an error occurred
        delete zed;
        return 1;
    }

    // Save the initialization parameters
    params.save("MyParam");

    char key = ' ';
    bool record = false;
    int ViewID = 2;
    int cnt = 0;
    int ConfidenceIdx = 100;
    std::string img_name;
    std::string disp_img_name;
    std::string depth_map_name;
    

    bool DisplayDisp = true;
    bool displayConfidenceMap = false;

    int width = zed->getImageSize().width;
    int height = zed->getImageSize().height;

    cv::Mat disp(height, width, CV_8UC4);
    cv::Mat anaplyph(height, width, CV_8UC4);
    cv::Mat confidencemap(height, width, CV_8UC4);

    cv::Size DisplaySize(720, 404);
    cv::Mat dispDisplay(DisplaySize, CV_8UC4); //matrix store disparity map
    cv::Mat anaplyphDisplay(DisplaySize, CV_8UC4); 
    cv::Mat confidencemapDisplay(DisplaySize, CV_8UC4);

    sl::zed::SENSING_MODE dm_type = sl::zed::STANDARD;
    /***/

    /* Init mouse callback */
    sl::zed::Mat depth;
    zed->grab(dm_type);
    depth = zed->retrieveMeasure(sl::zed::MEASURE::DEPTH); // Get the pointer

    // Set the structure
    mouseStruct._image = cv::Size(width, height);
    mouseStruct._resize = DisplaySize;
    mouseStruct.data = (float*) depth.data;
    mouseStruct.step = depth.step;
    mouseStruct.name = "DEPTH";
    mouseStruct.unit = unit2str(params.unit);
    /***/

    // the depth is limited to 20. METERS as define in zed::init()
    zed->setDepthClampValue(5000);
    /***/

    //create Opencv Windows
    cv::namedWindow(mouseStruct.name, cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback(mouseStruct.name, onMouseCallback, (void*) &mouseStruct) ;
    cv::namedWindow("VIEW", cv::WINDOW_AUTOSIZE);
    /***/

    std::cout << "Press 'q' to exit" << std::endl;

    //Jetson only. Execute the calling thread on core 2
    sl::zed::Camera::sticktoCPUCore(2);
    /***/

    sl::zed::ZED_SELF_CALIBRATION_STATUS old_self_calibration_status = sl::zed::SELF_CALIBRATION_NOT_CALLED;
    //loop until 'q' is pressed
    while (key != 'q') { //get key, use this command, key = cv::waitKey(5);
        // DisparityMap filtering
        zed->setConfidenceThreshold(ConfidenceIdx);

        // Get frames and launch the computation
        bool res = zed->grab(dm_type); 
        /*
        grab(SENSING_MODE dmtype = SENSING_MODE::STANDARD,bool compute-Measure = 1, bool computeDisparity=1, bool compute XYZ=1)
        This function grabs a new image, rectifies it and computes the disparity mapand optionally the depth map.
        It returns false if no problem, otherwise return true
        */

        if (!res) {
            // Estimated rotation :
            if (old_self_calibration_status != zed->getSelfCalibrationStatus()) {
                std::cout << "Self Calibration Status : " << sl::zed::statuscode2str(zed->getSelfCalibrationStatus()) << std::endl;
                old_self_calibration_status = zed->getSelfCalibrationStatus();
            }

            depth = zed->retrieveMeasure(sl::zed::MEASURE::DEPTH); // Get the pointer


            // The following is the best way to save a disparity map/ Image / confidence map in Opencv Mat.
            // Be Careful, if you don't save the buffer/data on your own, it will be replace by a next retrieve (retrieveImage, NormalizeMeasure, getView....)
            // !! Disparity, Depth, confidence are in 8U,C4 if normalized format !! //
            // !! Disparity, Depth, confidence are in 32F,C1 if only retrieve !! //


            /***************  DISPLAY:  ***************/
            // Normalize the DISPARITY / DEPTH map in order to use the full color range of grey level image
            // Toggle Disparity / Depth view
            // DisplayDisp: bool, if true, display Disparity view; else, display depth view
            if (DisplayDisp)
                slMat2cvMat(zed->normalizeMeasure(sl::zed::MEASURE::DISPARITY)).copyTo(disp);
            else
                slMat2cvMat(zed->normalizeMeasure(sl::zed::MEASURE::DEPTH)).copyTo(disp);


            // To get the depth at a given position, click on the DISPARITY / DEPTH map image
            cv::resize(disp, dispDisplay, DisplaySize);
            imshow(mouseStruct.name, dispDisplay);

            if (displayConfidenceMap) {
                slMat2cvMat(zed->normalizeMeasure(sl::zed::MEASURE::CONFIDENCE)).copyTo(confidencemap);
                cv::resize(confidencemap, confidencemapDisplay, DisplaySize);
                imshow("confidence", confidencemapDisplay);
            }

            //Even if Left and Right images are still available through getView() function, it's better since v0.8.1 to use retrieveImage for cpu readback because GPU->CPU is done async during depth estimation.
            // Therefore :
            // -- if disparity estimation is enabled in grab function, retrieveImage will take no time because GPU->CPU copy has already been done during disp estimation
            // -- if disparity estimation is not enabled, GPU->CPU copy is done in retrieveImage fct, and this function will take the time of copy.
            if (ViewID == sl::zed::STEREO_LEFT || ViewID == sl::zed::STEREO_RIGHT)
                slMat2cvMat(zed->retrieveImage(static_cast<sl::zed::SIDE> (ViewID))).copyTo(anaplyph);
            else
                slMat2cvMat(zed->getView(static_cast<sl::zed::VIEW_MODE> (ViewID))).copyTo(anaplyph);

            cv::resize(anaplyph, anaplyphDisplay, DisplaySize);
            imshow("VIEW", anaplyphDisplay);

            key = cv::waitKey(5);


            // Record images and save images locally
            img_name = img_dir + "ZEDImage_" + std::to_string(cnt/delay_cnt) + std::string(".png") ;
            disp_img_name = disp_img_dir + "ZEDDisparity_" + std::to_string(cnt/delay_cnt) + std::string(".png") ;
            depth_map_name = depth_map_dir + "ZEDDepthMap_" + std::to_string(cnt/delay_cnt) + std::string(".png");
            if (record){
                if (cnt%delay_cnt==0){
                    save_left_img(zed, img_name);
                    save_disp_img(zed, disp, disp_img_name);
                    save_depth_map(zed, depth, depth_map_name);
                }
                cnt++;    
                if (cnt == ttl_cnt){
                    record = !record;
                    std::cout << "Recording completed!" << std::endl;
                }
            }
            /***/


            // Keyboard shortcuts
            switch (key) {
                    // ______________  THRESHOLD __________________
                case 'b':
                    ConfidenceIdx -= 10;
                    std::cout << "ConfidenceIdx " << ConfidenceIdx << std::endl;
                    break;
                case 'n':
                    ConfidenceIdx += 10;
                    std::cout << "ConfidenceIdx " << ConfidenceIdx << std::endl;
                    break;

                    //re-compute stereo alignment
                case 'a':
                    zed->resetSelfCalibration();
                    break;

                    //Change camera settings (here --> gain)
                case 'g': //increase gain of 1
                {
                    int current_gain = zed->getCameraSettingsValue(sl::zed::ZED_GAIN) + 1;
                    zed->setCameraSettingsValue(sl::zed::ZED_GAIN, current_gain);
                    std::cout << "set Gain to " << current_gain << std::endl;
                }
                    break;

                case 'h': //decrease gain of 1
                {
                    int current_gain = zed->getCameraSettingsValue(sl::zed::ZED_GAIN) - 1;
                    zed->setCameraSettingsValue(sl::zed::ZED_GAIN, current_gain);
                    std::cout << "set Gain to " << current_gain << std::endl;
                }
                    break;


                    // ______________  VIEW __________________
                case '0': // left
                    ViewID = 0;
                    break;
                case '1': // right
                    ViewID = 1;
                    break;
                case '2': // anaglyph
                    ViewID = 2;
                    break;
                case '3': // gray scale diff
                    ViewID = 3;
                    break;
                case '4': // Side by side
                    ViewID = 4;
                    break;
                case '5': // overlay
                    ViewID = 5;
                    break;

                    // ______________  Display Confidence Map __________________
                case 's':
                    displayConfidenceMap = !displayConfidenceMap;
                    break;

                    //______________ SAVE ______________
                case 'w': // image and depth map
                    save_left_img(zed, img_name);
                    save_depth_map(zed, depth, depth_map_name);
                    cnt++;
                    break;

                case 'v': // disparity
                    save_disp_img(zed, disp, disp_img_name);
                    cnt++;
                    break;
                    

                case 'o':
                    cnt = 0;
                    record = !record;
                    if (record){
                        std::cout << "Recording..." << std::endl;
                    }
                    else{
                        std::cout << "Stop recording..." << std::endl;
                    }
                    break;

                   //________________Sensing mode_____________________________
                case 'r':
                    dm_type = sl::zed::SENSING_MODE::STANDARD;
                    std::cout << "SENSING_MODE " << sensing_mode2str(dm_type) << std::endl;
                    break;
                case 'f':
                    dm_type = sl::zed::SENSING_MODE::FILL;
                    std::cout << "SENSING_MODE " << sensing_mode2str(dm_type) << std::endl;
                    break;

                case 'd':
                    DisplayDisp = !DisplayDisp;
                    if (!DisplayDisp) {
                        std::cout << "Depth" << std::endl;
                    }
                    
                    break;
            }
            // limit ConfidenceIdx between 1 and 100
            ConfidenceIdx = ConfidenceIdx < 1 ? 1 : ConfidenceIdx; //condition ? result_if_true : result_if_false
            ConfidenceIdx = ConfidenceIdx > 100 ? 100 : ConfidenceIdx;
            /***/
        }
    }

    delete zed;
    return 0;
}
