#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace cv;
const unsigned int LOGO_DATA[] = {0,0,0};

const char* base_out_path = "/Users/haodong/Desktop/";
int before() {
    //const char* imagePath = "/Users/haodong/Desktop/collected.png";
    //Mat img = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);
    Mat img(43, 43, CV_8UC4);
    unsigned char * p = img.ptr<unsigned char>(0);
    for(int i = 0; i < 43; i++)
        for(int j = 0; j < 43; j++)
        {
            unsigned char r,g,b,a;
            unsigned int val = LOGO_DATA[i * 43 + j];
            a = val & 255; val >>= 8;
            r = val & 255; val >>= 8;
            g = val & 255; val >>= 8;
            b = val & 255;
            *p = b; p++;
            *p = g; p++;
            *p = r; p++;
            *p = a; p++;
        }
    cout << img << endl;
    //const char* outputPath = "/Users/haodong/Desktop/out.txt";
    const char* savetoImagePath = "/Users/haodong/Desktop/123.png";
    //namedWindow("123", CV_WINDOW_AUTOSIZE);
    //imshow("123", img);
    imwrite(savetoImagePath, img);
    return 0;
}


char str[100];
const char* base_path = "/Users/haodong/Desktop/rockvr/";
const char* image_path[] = {"43", "48", "64", "96", "192"};
const int image_n[] = {43, 48, 64, 96, 192};
const char* ext_path = ".png";
const int ARRAY_MAX_LENGTH = 43 * 43 + 48 * 48 + 64 * 64 + 96 * 96 + 192 * 192;
unsigned int outarray[ARRAY_MAX_LENGTH];
int image_to_alpha()
{
    unsigned int* out_p = outarray;
    for(int i = 0, l; i < 5; i++)
    {
        memset(str, 0, sizeof str);
        strcpy(str, base_out_path);
        l = strlen(str);
        strcpy(str + l, image_path[i]);
        l = strlen(str);
        strcpy(str + l, ext_path);

        puts(str);

        Mat img = imread(str, CV_LOAD_IMAGE_UNCHANGED);
        unsigned char* p = img.ptr<unsigned char>(0);
        unsigned char r,g,b,a;
        int n = image_n[i];


        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                b = *p; p++;
                g = *p; p++;
                r = *p; p++;
                a = *p; p++;
                unsigned int val = 0;
                //val |= b; val <<= 8;
                //val |= g; val <<= 8;
                //val |= r; val <<= 8;
                val |= a;
                *out_p = val;
                out_p++;
            }
    }

    memset(str, 0, sizeof str);
    strcpy(str, base_path);
    strcpy(str + strlen(str), "out.txt");
    freopen(str, "w", stdout);
    for(int i = 0; i < ARRAY_MAX_LENGTH; i++)
        printf("%u,", outarray[i]);
}
unsigned int temp[192 * 192];
char in_path[100];
char out_path[100];
int image_up_down_reverse()
{
    for(int i = 0, l; i < 5; i++)
    {
        //const char * in_path = "/Users/haodong/Desktop/rockvr/43.png";
        //const char * out_path = "/Users/haodong/Desktop/43.png";
        memset(in_path, 0, sizeof in_path);
        strcpy(in_path, base_path);
        l = strlen(in_path);
        strcpy(in_path + l, image_path[i]);
        l = strlen(in_path);
        strcpy(in_path + l, ext_path);


        memset(out_path, 0, sizeof out_path);
        strcpy(out_path, base_out_path);
        l = strlen(out_path);
        strcpy(out_path + l, image_path[i]);
        l = strlen(out_path);
        strcpy(out_path + l, ext_path);

        printf("in_path = %s\n", in_path);
        printf("out_path = %s\n", out_path);

        Mat img = imread(in_path, CV_LOAD_IMAGE_UNCHANGED);

        unsigned char* p = img.ptr<unsigned char>(0);
        int n = image_n[i];
        Mat out_img(n,n,CV_8UC4);
        unsigned char* out_p = out_img.ptr<unsigned char>(0);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                int x = n - 1 - i;
                *(out_p + x * 4 * n + j * 4 + 0) = *p++;
                *(out_p + x * 4 * n + j * 4 + 1) = *p++;
                *(out_p + x * 4 * n + j * 4 + 2) = *p++;
                *(out_p + x * 4 * n + j * 4 + 3) = *p++;
            }
        cout << out_img << endl;
        imwrite(out_path, out_img);
    }
}
int main()
{
    //image_up_down_reverse();
    image_to_alpha();
}