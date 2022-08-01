#include <iostream>
#include <vector>
//Thread building blocks library
#include <tbb/task_scheduler_init.h>
//Free Image library
#include <FreeImagePlus.h>
#include <chrono>
#include <tbb/parallel_for.h>
#include <thread>
#include <mutex>
#define _USE_MATH_DEFINES
#include <tbb/blocked_range.h>
#include <tbb/blocked_range2d.h>
#include <cstdlib>
#include <math.h>
#include <random>
#include <cstdint>
#include <functional>
#include <string>

using namespace std;
using namespace tbb;
using namespace std::chrono;


void stage1_sequential()
{
    clock_t startTime = clock();
    cout << "Performing part 1 ..." << endl;
    fipImage inputImage;
    inputImage.load("Images\\render_top_1.png");
    inputImage.convertToFloat();

    auto width = inputImage.getWidth();
    auto height = inputImage.getHeight();
    const float* const inputBuffer = (float*)inputImage.accessPixels();

    fipImage inputImage2;
    inputImage2.load("Images\\render_top_2.png");
    inputImage2.convertToFloat();

    const float* const inputBuffer2 = (float*)inputImage2.accessPixels();

    fipImage inputImage3;
    inputImage3.load("Images\\render_bottom_1.png");
    inputImage3.convertToFloat();

    const float* const inputBuffer3 = (float*)inputImage3.accessPixels();

    fipImage inputImage4;
    inputImage4.load("Images\\render_bottom_2.png");
    inputImage4.convertToFloat();

    const float* const inputBuffer4 = (float*)inputImage4.accessPixels();

    fipImage outputImage;
    outputImage = fipImage(FIT_FLOAT, width, height, 32);
    float* outputBuffer = (float*)outputImage.accessPixels();

    fipImage outputImageTop;
    outputImageTop = fipImage(FIT_FLOAT, width, height, 32);
    float* outputBufferTop = (float*)outputImageTop.accessPixels();

    fipImage outputImageBottom;
    outputImageBottom = fipImage(FIT_FLOAT, width, height, 32);
    float* outputBufferBottom = (float*)outputImageBottom.accessPixels();

    uint64_t numElements = width * height;

    for (int i = 0; i < numElements; i++)
    {

        if ((inputBuffer[i] == inputBuffer2[i]))
        {
            outputBufferTop[i] = 0.0f;
        }
        else
        {
            outputBufferTop[i] = 1.0f;
        }

        if ((inputBuffer3[i] == inputBuffer4[i]))
        {
            outputBufferBottom[i] = 0.0f;
        }
        else
        {
            outputBufferBottom[i] = 1.0f;
        }

        outputBuffer[i] = outputBufferTop[i] + outputBufferBottom[i];
    }
    cout << "Part 1 - Saving stage1_Top, stage1_Bottom, stage1_Combined \n";

    outputImage.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    outputImage.convertTo24Bits();
    outputImage.save("Images\\stage1_combined.png");

    outputImageTop.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    outputImageTop.convertTo24Bits();
    outputImageTop.save("Images\\stage1_top.png");

    outputImageBottom.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    outputImageBottom.convertTo24Bits();
    outputImageBottom.save("Images\\stage1_Bottom.png");
   
    clock_t endTime = clock();
    clock_t Ticks = endTime - startTime;
    double Seconds = Ticks / (double)CLOCKS_PER_SEC;
    cout << "\n" << "Time Taken: " << Seconds << " Seconds" << "\n";
}

void thread1()
{
    cout << "Performing part 1 thread1 ...\n" << endl;
    fipImage inputImage;
    inputImage.load("Images\\render_top_1.png");
    inputImage.convertToFloat();

    auto width = inputImage.getWidth();
    auto height = inputImage.getHeight();
    const float* const inputBuffer = (float*)inputImage.accessPixels();

    fipImage inputImage2;
    inputImage2.load("Images\\render_top_2.png");
    inputImage2.convertToFloat();

    const float* const inputBuffer2 = (float*)inputImage2.accessPixels();

    fipImage outputImageTop;
    outputImageTop = fipImage(FIT_FLOAT, width, height, 32);
    float* outputBufferTop = (float*)outputImageTop.accessPixels();

    fipImage outputImage;
    outputImage = fipImage(FIT_FLOAT, width, height, 32);
    float* outputBuffer = (float*)outputImage.accessPixels();

    uint64_t numElements = width * height;

    for (int i = 0; i < numElements; i++)
    {

        if ((inputBuffer[i] == inputBuffer2[i]))
        {
            outputBufferTop[i] = 0.0f;
        }
        else
        {
            outputBufferTop[i] = 1.0f;
        }
    }
    outputImageTop.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    outputImageTop.convertTo24Bits();
    outputImageTop.save("Images\\stage1_top.png");
}

void thread2() 
{
    cout << "Performing part 1 thread2 ...\n" << endl;
    fipImage inputImage3;
    inputImage3.load("Images\\render_bottom_1.png");
    inputImage3.convertToFloat();
   
    auto width = inputImage3.getWidth();
    auto height = inputImage3.getHeight();
    const float* const inputBuffer = (float*)inputImage3.accessPixels();

    const float* const inputBuffer3 = (float*)inputImage3.accessPixels();

    fipImage inputImage4;
    inputImage4.load("Images\\render_bottom_2.png");
    inputImage4.convertToFloat();

    const float* const inputBuffer4 = (float*)inputImage4.accessPixels();

    fipImage outputImage;
    outputImage = fipImage(FIT_FLOAT, width, height, 32);
    float* outputBuffer = (float*)outputImage.accessPixels();

    fipImage outputImageBottom;
    outputImageBottom = fipImage(FIT_FLOAT, width, height, 32);
    float* outputBufferBottom = (float*)outputImageBottom.accessPixels();

    uint64_t numElements = width * height;

    for (int i = 0; i < numElements; i++)
    {
        if ((inputBuffer3[i] == inputBuffer4[i]))
        {
            outputBufferBottom[i] = 0.0f;
        }
        else
        {
            outputBufferBottom[i] = 1.0f;
        }
    }
    outputImageBottom.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    outputImageBottom.convertTo24Bits();
    outputImageBottom.save("Images\\stage1_Bottom.png");

}

void thread3()
{
    cout << "Performing part 1 thread3 ...\n" << endl;
    fipImage inputImage;
    inputImage.load("Images\\stage1_Bottom.png");
    inputImage.convertToFloat();

    auto width = inputImage.getWidth();
    auto height = inputImage.getHeight();
    const float* const inputBuffer = (float*)inputImage.accessPixels();

    fipImage inputImage2;
    inputImage2.load("Images\\stage1_top.png");
    inputImage2.convertToFloat();

    const float* const inputBuffer2 = (float*)inputImage2.accessPixels();


    fipImage outputImage;
    outputImage = fipImage(FIT_FLOAT, width, height, 32);
    float* outputBuffer = (float*)outputImage.accessPixels();


    uint64_t numElements = width * height;

    for (int i = 0; i < numElements; i++)
    {
        outputBuffer[i] = inputBuffer[i] + inputBuffer2[i];
    }
    outputImage.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    outputImage.convertTo24Bits();
    outputImage.save("Images\\stage1_combined.png");
}

void stage2blurparallel()
{
    cout << "Performing part 2 blur parallel...\n" << endl;
    clock_t startTime = clock();
    fipImage inputImage;
    inputImage.load("Images\\stage1_combined.png");
    inputImage.convertToFloat();

    auto width = inputImage.getWidth();
    auto height = inputImage.getHeight();
    const float* const inputBuffer = (float*)inputImage.accessPixels();

    fipImage OutputImage;
    OutputImage = fipImage(FIT_FLOAT, width, height, 32);
    float* OutputBuffer = (float*)OutputImage.accessPixels();

    parallel_for(blocked_range2d<uint64_t, uint64_t>(1, height - 1, 1, width - 1), [&](const blocked_range2d<uint64_t, uint64_t>& r)
    {
        auto y1 = r.rows().begin();
        auto y2 = r.rows().end();
        auto x1 = r.cols().begin();
        auto x2 = r.cols().end();

        for (auto y = y1; y < y2; ++y)
        {
            for (auto x = x1; x < x2; ++x)
            {
                OutputBuffer[y * width + x] = inputBuffer[(y - 1) * width + (x - 1)] * 0.0987
                    + inputBuffer[(y - 1) * width + x]
                    * 0.116766 + inputBuffer[(y - 1) * width + (x + 1)] * 0.0987
                    + inputBuffer[y * width + (x - 1)] * 0.116766 + inputBuffer[y * width + x] * 0.138138 +
                    inputBuffer[(y + 1) * width + (x + 1)] * 0.116766
                    + inputBuffer[(y + 1) * width + (x - 1)] * 0.0987 + inputBuffer[(y + 1) * width + x] * 0.116766 + inputBuffer[(y + 1) * width + (x + 1)] * 0.0987;
            }
        }
    });

    OutputImage.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    OutputImage.convertTo24Bits();
    OutputImage.save("Images\\stage2_blurred.png");

    clock_t endTime = clock();
    clock_t Ticks = endTime - startTime;
    double Seconds = Ticks / (double)CLOCKS_PER_SEC;
    cout << "\n" << "Time Taken: " << Seconds << " Seconds" << "\n";
}

void stage2blursequential()
{
    cout << "Performing part 2 blur squential..." << endl;
    clock_t startTime = clock();
    fipImage inputImage;
    inputImage.load("Images\\stage1_combined.png");
    inputImage.convertToFloat();

    auto width = inputImage.getWidth();
    auto height = inputImage.getHeight();
    const float* const inputBuffer = (float*)inputImage.accessPixels();

    fipImage OutputImage;
    OutputImage = fipImage(FIT_FLOAT, width, height, 32);
    float* OutputBuffer = (float*)OutputImage.accessPixels();

    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            OutputBuffer[y * width + x] = inputBuffer[(y - 1) * width + (x - 1)] * 0.0987
                + inputBuffer[(y - 1) * width + x]
                * 0.116766 + inputBuffer[(y - 1) * width + (x + 1)] * 0.0987
                + inputBuffer[y * width + (x - 1)] * 0.116766 + inputBuffer[y * width + x] * 0.138138 +
                inputBuffer[(y + 1) * width + (x + 1)] * 0.116766
                + inputBuffer[(y + 1) * width + (x - 1)] * 0.0987 + inputBuffer[(y + 1) * width + x] * 0.116766 + inputBuffer[(y + 1) * width + (x + 1)] * 0.0987;
        }
    }
    OutputImage.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    OutputImage.convertTo24Bits();
    OutputImage.save("Images\\stage2_blurred.png");

    clock_t endTime = clock();
    clock_t Ticks = endTime - startTime;
    double Seconds = Ticks / (double)CLOCKS_PER_SEC;
    cout << "\n" << "Time Taken: " << Seconds << " Seconds" << "\n";

}

void stage2threshold()
{
    cout << "Performing part 2 threshold..." << endl;
    clock_t startTime = clock();
    fipImage inputImage;
    inputImage.load("Images\\stage2_blurred.png");
    inputImage.convertToFloat();

    auto width = inputImage.getWidth();
    auto height = inputImage.getHeight();
    const float* const inputBuffer = (float*)inputImage.accessPixels();

    uint64_t numElements = width * height;

    fipImage OutputImage;
    OutputImage = fipImage(FIT_FLOAT, width, height, 32);
    float* OutputBuffer = (float*)OutputImage.accessPixels();

    for (int i = 0; i < numElements; i++)
    {
        if ((inputBuffer[i] != 0.0f))
        {
            OutputBuffer[i] = 1.0f;
        }
    }

    OutputImage.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    OutputImage.convertTo24Bits();
    OutputImage.save("Images\\stage2_threshold.png");

    clock_t endTime = clock();
    clock_t Ticks = endTime - startTime;
    double Seconds = Ticks / (double)CLOCKS_PER_SEC;
    cout << "\n" << "Time Taken: " << Seconds << " Seconds" << "\n";

}

void stage2thresholdparallel()
{
    cout << "Performing part 2 threshold..." << endl;
    clock_t startTime = clock();
    fipImage inputImage;
    inputImage.load("Images\\stage2_blurred.png");
    inputImage.convertToFloat();

    auto width = inputImage.getWidth();
    auto height = inputImage.getHeight();
    const float* const inputBuffer = (float*)inputImage.accessPixels();

    fipImage OutputImage;
    OutputImage = fipImage(FIT_FLOAT, width, height, 32);
    float* OutputBuffer = (float*)OutputImage.accessPixels();

    parallel_for(blocked_range2d<uint64_t, uint64_t>(1, height - 1, 1, width - 1), [&](const blocked_range2d<uint64_t, uint64_t>& r)
    {
        auto y1 = r.rows().begin();
        auto y2 = r.rows().end();
        auto x1 = r.cols().begin();
        auto x2 = r.cols().end();

        for (auto y = y1; y < y2; ++y)
        {
            for (auto x = x1; x < x2; ++x)
            {
                if ((inputBuffer[y * width + x] != 0.0f))
                {
                    OutputBuffer[y * width + x] = 1.0f;
                }
            }
        }

    });

    OutputImage.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    OutputImage.convertTo24Bits();
    OutputImage.save("Images\\stage2_threshold.png");

    clock_t endTime = clock();
    clock_t Ticks = endTime - startTime;
    double Seconds = Ticks / (double)CLOCKS_PER_SEC;
    cout << "\n" << "Time Taken: " << Seconds << " Seconds" << "\n";
}

void part3sequential()
{
    cout << "Performing part 3 ..." << endl;
    clock_t startTime = clock();
    fipImage inputImagethresh;
    inputImagethresh.load("Images\\stage2_threshold.png");
    inputImagethresh.convertToFloat();

    auto width = inputImagethresh.getWidth();
    auto height = inputImagethresh.getHeight();
    const float* const inputBufferthresh = (float*)inputImagethresh.accessPixels();

    fipImage inputImage;
    inputImage.load("Images\\render_top_1.png");

    const float* const inputBuffer = (float*)inputImage.accessPixels();

    double count = 0;

    RGBQUAD colour;

    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            if(inputBufferthresh[y * width + x] == 1.0f)
            {
                inputImage.getPixelColor(x, y, &colour);
                colour.rgbRed = 255 - colour.rgbRed;
                colour.rgbGreen = 255 - colour.rgbGreen;
                colour.rgbBlue = 255 - colour.rgbBlue;
                inputImage.setPixelColor(x, y, &colour);
                count++;
            }
        }
    }

    uint64_t numElements = width * height;
    double percentage = 0;

    percentage = count / numElements * 100;
    cout << percentage << "%" << " = White Pixels" << endl;

    inputImage.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    inputImage.convertTo24Bits();
    inputImage.save("Images\\finial_image.png");

    clock_t endTime = clock();
    clock_t Ticks = endTime - startTime;
    double Seconds = Ticks / (double)CLOCKS_PER_SEC;
    cout << "\n" << "Time Taken: " << Seconds << " Seconds" << "\n";
}

void part3parallel()
{
    cout << "Performing part 3 ..." << endl;
    clock_t startTime = clock();
    fipImage inputImagethresh;
    inputImagethresh.load("Images\\stage2_threshold.png");
    inputImagethresh.convertToFloat();

    auto width = inputImagethresh.getWidth();
    auto height = inputImagethresh.getHeight();
    const float* const inputBufferthresh = (float*)inputImagethresh.accessPixels();

    fipImage inputImage;
    inputImage.load("Images\\render_top_1.png");

    const float* const inputBuffer = (float*)inputImage.accessPixels();

    double count = 0;

    RGBQUAD colour;
    mutex mutex;

    parallel_for(blocked_range2d<uint64_t, uint64_t>(1, height - 1, 1, width - 1), [&](const blocked_range2d<uint64_t, uint64_t>& r)
    {
        auto y1 = r.rows().begin();
        auto y2 = r.rows().end();
        auto x1 = r.cols().begin();
        auto x2 = r.cols().end();

        for (auto y = y1; y < y2; ++y)
        {
            for (auto x = x1; x < x2; ++x)
            {
                mutex.lock();
                if (inputBufferthresh[y * width + x] == 1.0f)
                {
                    inputImage.getPixelColor(x, y, &colour);
                    colour.rgbRed = 255 - colour.rgbRed;
                    colour.rgbGreen = 255 - colour.rgbGreen;
                    colour.rgbBlue = 255 - colour.rgbBlue;
                    inputImage.setPixelColor(x, y, &colour);
                    count++;
                }
                mutex.unlock();
            }
        }
    });
    
    uint64_t numElements = width * height;
    double percentage = 0;

    percentage = count / numElements * 100;
    cout << percentage << "%" << " = White Pixels" << endl;

    inputImage.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
    inputImage.convertTo24Bits();
    inputImage.save("Images\\finial_image.png");

    clock_t endTime = clock();
    clock_t Ticks = endTime - startTime;
    double Seconds = Ticks / (double)CLOCKS_PER_SEC;
    cout << "\n" << "Time Taken: " << Seconds << " Seconds" << "\n";
}



int main()
{
	int nt = task_scheduler_init::default_num_threads();
	task_scheduler_init T(nt);
    
//	//Part 1 (Image Comparison): -----------------DO NOT REMOVE THIS COMMENT----------------------------//
    
    stage1_sequential();
    
    /*clock_t startTime = clock();

    thread thread1(thread1);
    thread thread2(thread2);
    thread1.join();
    thread2.join();
   
    thread thread3(thread3);
    thread3.join();

    clock_t endTime = clock();
    clock_t Ticks = endTime - startTime;
    double Seconds = Ticks / (double)CLOCKS_PER_SEC;
    cout << "\n" << "Time Taken: " << Seconds << " Seconds" << "\n";*/

//	//Part 2 (Blur & post-processing): -----------DO NOT REMOVE THIS COMMENT----------------------------//
    //stage2blurparallel();
    stage2blursequential();
    stage2threshold();
    //stage2thresholdparallel();

	//Part 3 (Image Mask): -----------------------DO NOT REMOVE THIS COMMENT----------------------------//
    part3sequential();
    //part3parallel();

	return 0;
}

