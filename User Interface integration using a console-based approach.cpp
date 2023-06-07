#include <iostream>
#include <vector>
#include <algorithm>

// Train Class
class Train {
private:
    std::string name;
    int id;
    int speed;
    int position;

public:
    Train(const std::string& trainName, int trainID)
        : name(trainName), id(trainID), speed(0), position(0) {}

    void accelerate(int amount) {
        speed += amount;
    }

    void decelerate(int amount) {
        speed -= amount;
        if (speed < 0)
            speed = 0;
    }

    void move() {
        position += speed;
    }

    std::string getName() const {
        return name;
    }

    int getSpeed() const {
        return speed;
    }

    int getPosition() const {
        return position;
    }
};

// Track Class
class Track {
private:
    std::vector<int> trackSegments;

public:
    void addTrackSegment(int length) {
        trackSegments.push_back(length);
    }

    int getTotalLength() const {
        int total = 0;
        for (int segment : trackSegments)
            total += segment;
        return total;
    }

    int getSegmentAtPosition(int position) const {
        int segmentIndex = 0;
        int segmentStartPosition = 0;

        for (int segment : trackSegments) {
            int segmentEndPosition = segmentStartPosition + segment;
            if (position >= segmentStartPosition && position < segmentEndPosition)
                return segmentIndex;

            segmentStartPosition = segmentEndPosition;
            segmentIndex++;
        }

        return -1;  // Invalid position
    }
};

// TrainController Class
class TrainController {
private:
    std::vector<Train> trains;

public:
    void addTrain(const Train& train) {
        trains.push_back(train);
    }

    void removeTrain(int trainIndex) {
        if (trainIndex >= 0 && trainIndex < trains.size()) {
            trains.erase(trains.begin() + trainIndex);
        }
    }

    int getTrainCount() const {
        return trains.size();
    }

    const Train& getTrainWithHighestSpeed() const {
        auto it = std::max_element(trains.begin(), trains.end(),
            [](const Train& train1, const Train& train2) {
                return train1.getSpeed() < train2.getSpeed();
            }
        );

        return *it;
    }

    const std::vector<Train>& getAllTrains() const {
        return trains;
    }
};

// TrainSimulation Class
class TrainSimulation {
private:
    Track track;
    TrainController trainController;
    bool isRunning;

public:
    TrainSimulation()
        : isRunning(false) {}

    void initialize() {
        // Create a track with segments
        track.addTrackSegment(50);
        track.addTrackSegment(30);
        track.addTrackSegment(70);
        track.addTrackSegment(40);

        // Create trains and add them to the controller
        Train train1("Express", 1);
        Train train2("Local", 2);
        Train train3("Freight", 3);

        trainController.addTrain(train1);
        trainController.addTrain(train2);
        trainController.addTrain(train3);
    }

    void start() {
        isRunning = true;
        while (isRunning) {
            for (Train& train : trainController.getAllTrains()) {
                train.move();
            }
            displayTrainInformation();
        }
    }

    void stop() {
        isRunning = false;
    }

    void displayTrain
