#pragma once
#include <vector>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <Eigen/Dense>

#include "lib.h"

class PointCloudProcessor
{
    std::vector<Eigen::Vector3f> pointCloud;
    std::vector<cv::Vec3i> colorCloud;

public:
    PointCloudProcessor(const std::string& filePath)
    {
        try {
            lib::readXYZFile(filePath, pointCloud);
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void detectSphereRand4p(int iterations, float ransacThreshold, float rMin, float rMax, std::vector<Eigen::Vector3f>& inliers, Eigen::Vector3f& S0, float& r, std::vector<int>& inlierIndices);

    void detectSphereWithAdjacency(int iterations, int adjacencyThreshold, float ransacThreshold, float rMin, float rMax, std::vector<Eigen::Vector3f>& inliers, Eigen::Vector3f& S0, float& r, std::vector<int>& inlierIndices);

    void detectSphereWithDistance(int iterations, float distanceThreshold, float ransacThreshold, float rMin, float rMax, std::vector<Eigen::Vector3f>& inliers, Eigen::Vector3f& S0, float& r, std::vector<int>& inlierIndices);

    void findKNearestNeighbors(const std::vector<Eigen::Vector3f>& pointCloud, const Eigen::Vector3f& queryPoint, std::vector<int>& indices, int k);

    void fitSphereNonit(const std::vector<Eigen::Vector3f>& pointCloud, const std::vector<int>& indices, Eigen::Vector3f& S0, float& r);

    void classifySpherePoints(const std::vector<Eigen::Vector3f>& pointCloud, const Eigen::Vector3f& S0, float r, float ransacThreshold, std::vector<int>& inlierIndices);

    void pointsFromIndices(const std::vector<Eigen::Vector3f>& pointCloud, const std::vector<int>& indices, std::vector<Eigen::Vector3f>& selectedPoints);

    void fitSphereLsq(const std::vector<Eigen::Vector3f>& pointCloud, Eigen::Vector3f& S0, float& r);

    Eigen::Vector3f fitSphere4p(const std::vector<Eigen::Vector3f>& points);

    void displayPointCloud() {
        lib::displayPointCloud(pointCloud);
    }

    void writeFile(std::string path) {
        lib::writePly(path, pointCloud, colorCloud);
    }

    void colorInlierIndicesRed(std::vector<int>& inlierIndices, const Eigen::Vector3f& S0Lid);
};
