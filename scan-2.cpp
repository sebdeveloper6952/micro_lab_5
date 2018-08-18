#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

static void help()
{
    cout
        << "\n--------------------------------------------------------------------------" << endl
        << "This program shows how to scan image objects in OpenCV (cv::Mat). As use case"
        << " we take an input image and divide the native color palette (255) with the "  << endl
        << "input. Shows C operator[] method, iterators and at function for on-the-fly item address calculation."<< endl
        << "Usage:"                                                                       << endl
        << "./Scan imageNameToUse divideWith [G]"          			                      << endl
        << "if you add a G parameter the image is processed in gray scale"                << endl
        << "--------------------------------------------------------------------------"   << endl
        << endl;
}

void duplicateImage(Mat& input, Mat &output);
/*
Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar * table);

*/
int main( int argc, char* argv[])
{
    help();
    if (argc < 3)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    if( argc == 4 && !strcmp(argv[3],"G") )
        I = imread(argv[1], IMREAD_GRAYSCALE);
    else
        I = imread(argv[1], IMREAD_COLOR);

    if (!I.data)
    {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

/*
    int divideWith = 0; // convert our input string to number - C++ style
    stringstream s;
    s << argv[2];
    s >> divideWith;
    if (!s || !divideWith)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }

    uchar table[256];
    for (int i = 0; i < 256; ++i)
       table[i] = (uchar)(divideWith * (i/divideWith));

    const int times = 100;
    double t;

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceC(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the C operator [] (averaged for "
         << times << " runs): " << t << " milliseconds."<< endl;

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceIterator(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the iterator (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        ScanImageAndReduceRandomAccess(clone_i, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;

    Mat lookUpTable(1, 256, CV_8U);
    uchar *p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];

    t = (double)getTickCount();

    for (int i = 0; i < times; ++i)
        LUT(I, lookUpTable, J);

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the LUT function (averaged for "
        << times << " runs): " << t << " milliseconds."<< endl;
    
    */
    
    /// Nuestro codigo comienza aca
    cout << "Image has " << I.channels() << " channels." << endl;
    cout << "Original image has type: " << I.type() << endl;
    
    int oRows = I.rows;
    int oCols = I.cols;
    cout << "Image has dimensions: " << oCols << "x" << oRows << endl;
    int imageType = I.channels() == 3 ? CV_8UC3 : CV_8U;
    Mat duplicada = Mat(oRows*2, oCols*2, imageType);
    cout << "Duplicated image has dimensions: " << duplicada.cols << "x" << duplicada.rows << endl;
    
    
    duplicateImage(I, duplicada);
    
    /// Mostrar imagen duplicada
    namedWindow("Duplicada");
    imshow("Duplicada", duplicada);
    
    waitKey(0);
    
    return 0;
}

void duplicateImage(Mat &input, Mat &output) 
{
	int row, col;
	int channels = input.channels();
	switch(channels) 
	{
		case 1: 
		{
			for(row = 0; row < input.rows; row++)
			{
				for(col = 0; col < input.cols; col++)
				{
					output.at<uchar>(row*2,col*2) = input.at<uchar>(row,col);
					output.at<uchar>(row*2, col*2+1) = input.at<uchar>(row,col);
					output.at<uchar>(row*2+1, col*2) = input.at<uchar>(row,col);
					output.at<uchar>(row*2+1, col*2+1) = input.at<uchar>(row,col);
				}
			}
			break;
		}
		case 3: 
		{
			for(row = 0 ; row < input.rows; row++)
			{
				for(col = 0; col < input.cols; col++)
				{
					/// Blue color
					output.at<Vec3b>(row*2, col*2)[0] = input.at<Vec3b>(row,col)[0];
					output.at<Vec3b>(row*2, col*2+1)[0] = input.at<Vec3b>(row,col)[0];
					output.at<Vec3b>(row*2+1, col*2)[0] = input.at<Vec3b>(row,col)[0];
					output.at<Vec3b>(row*2+1, col*2+1)[0] = input.at<Vec3b>(row,col)[0];
					/// Green color
					output.at<Vec3b>(row*2, col*2)[1] = input.at<Vec3b>(row,col)[1];
					output.at<Vec3b>(row*2, col*2+1)[1] = input.at<Vec3b>(row,col)[1];
					output.at<Vec3b>(row*2+1, col*2)[1] = input.at<Vec3b>(row,col)[1];
					output.at<Vec3b>(row*2+1, col*2+1)[1] = input.at<Vec3b>(row,col)[1];
					/// Red color
					output.at<Vec3b>(row*2, col*2)[2] = input.at<Vec3b>(row,col)[2];
					output.at<Vec3b>(row*2, col*2+1)[2] = input.at<Vec3b>(row,col)[2];
					output.at<Vec3b>(row*2+1, col*2)[2] = input.at<Vec3b>(row,col)[2];
					output.at<Vec3b>(row*2+1, col*2+1)[2] = input.at<Vec3b>(row,col)[2];
				}
			}
			break;
		}
	}
}

/*
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* p;
    for( i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];
        }
    }
    return I;
}

Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            MatIterator_<uchar> it, end;
            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = table[*it];
            break;
        }
    case 3:
        {
            MatIterator_<Vec3b> it, end;
            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }

    return I;
}

Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            for( int i = 0; i < I.rows; ++i)
                for( int j = 0; j < I.cols; ++j )
                    I.at<uchar>(i,j) = table[I.at<uchar>(i,j)];
            break;
        }
    case 3:
        {
         Mat_<Vec3b> _I = I;

         for( int i = 0; i < I.rows; ++i)
            for( int j = 0; j < I.cols; ++j )
               {
                   _I(i,j)[0] = table[_I(i,j)[0]];
                   _I(i,j)[1] = table[_I(i,j)[1]];
                   _I(i,j)[2] = table[_I(i,j)[2]];
            }
         I = _I;
         break;
        }
    }

    return I;
}
* */
