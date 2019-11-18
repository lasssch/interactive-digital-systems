#include <Arduino.h>
#include <unity.h>
#include <drone.h>
#include <WiFiConnection.h>

Drone drone;
WifiConnection con;

void test_connection_before_connect_call(void) {
    delay(500);
    TEST_ASSERT_EQUAL(con.connected, false);
}

void test_connection_after_connect_call(void) {
    con.connect("TELLO-FE2EE8", "");
    delay(500);
    TEST_ASSERT_EQUAL(con.connected, true);
}

void test_connection(void) {
    drone.connect("TELLO-FE2EE8", "");
    delay(500);
    TEST_ASSERT_EQUAL(drone.connected(), true);
}

void test_taking_off_command(void) {
    drone.connect("TELLO-FE2EE8", "");
    drone.sendCommand("takeoff");
    TEST_ASSERT_EQUAL(drone.flying, true);
}

void test_not_flying(void) {
    drone.connect("TELLO-FE2EE8", "");
    TEST_ASSERT_EQUAL(drone.flying, false);
}

void test_button_pressed(void) {
    drone.connect("TELLO-FE2EE8", "");
    drone.emergency = false;
    drone.buttonPressed();
    TEST_ASSERT_EQUAL(drone.emergency, true);
}

void setup() {
    delay(2000);

    UNITY_BEGIN();    
    
    RUN_TEST(test_connection);
    RUN_TEST(test_taking_off_command);
    RUN_TEST(test_not_flying);
    RUN_TEST(test_button_pressed);
    RUN_TEST(test_connection_before_connect_call);
    RUN_TEST(test_connection_after_connect_call);   

    UNITY_END(); 
    
}

void loop()
{
    
}