
// MOTORS
#define FRONT_LEFT 0
#define FRONT_RIGHT 1
#define REAR_LEFT 2
#define REAR_RIGHT 3

#define SPEED_MAX 255

namespace Drive {

    void setup();
    void forward(int durationMs);
    void reverse(int durationMs);
    void right();

}