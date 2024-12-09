#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

cv::Mat image;

int first_version();
int second_version();

int main(int argc, char** argv) {
    // Загрузка изображения
    //image = cv::imread("akatsuki.jpg");
    image = cv::imread("for_rep.jpg");;
    //return first_version();
    return second_version();
}

int first_version() {
    if (image.empty()) {
        std::cerr << "Could not open or find the image!" << std::endl;
        return -1;
    }

    // Отображение исходного изображения
    cv::imshow("Original Image", image);

    // Загрузка каскада Хаара
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_alt2.xml")) {
        std::cerr << "Error loading cascade classifier!" << std::endl;
        return -1;
    }

    std::vector<cv::Rect> faces;
    cv::Mat gray_image;

    // Преобразование изображения в оттенки серого
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray_image, gray_image);

    // Обнаружение лиц
    face_cascade.detectMultiScale(gray_image, faces, 1.1, 10, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    // Рисование прямоугольников вокруг обнаруженных лиц
    for (size_t i = 0; i < faces.size(); i++) {
        cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        ellipse(image, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4);
    }

    // Отображение результата
    cv::imshow("Detected Face", image);
    cv::waitKey(0);

    return 0;
}

int second_version() {
    if (image.empty()) {
        std::cerr << "Could not open or find the image!" << std::endl;
        return -1;
    }

    // Создание копии исходного изображения для отображения обнаруженных лиц
    cv::Mat detected_image = image.clone();

    // Загрузка каскада Хаара
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_alt2.xml")) {
        std::cerr << "Error loading cascade classifier!" << std::endl;
        return -1;
    }

    std::vector<cv::Rect> faces;
    cv::Mat gray_image;

    // Преобразование изображения в оттенки серого
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(gray_image, gray_image);

    // Обнаружение лиц
    face_cascade.detectMultiScale(gray_image, faces, 1.1, 10, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    // Рисование прямоугольников вокруг обнаруженных лиц
    for (size_t i = 0; i < faces.size(); i++) {
        cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        ellipse(detected_image, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 4);
    }

    // Создание пустого изображения для отображения двух изображений рядом
    cv::Mat combined_image;
    cv::hconcat(image, detected_image, combined_image);

    // Отображение результата
    cv::imshow("Original and Detected Faces", combined_image);
    cv::waitKey(0);

    return 0;
}
